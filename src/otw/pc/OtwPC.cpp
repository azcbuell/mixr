
#include "mixr/otw/pc/OtwPC.hpp"

#include "mixr/otw/OtwModel.hpp"

#include "dsFlightModelData.hpp"

#include "mixr/models/player/AirVehicle.hpp"
#include "mixr/models/player/GroundVehicle.hpp"
#include "mixr/models/player/Missile.hpp"
#include "mixr/models/player/Player.hpp"

#include "mixr/base/network/NetHandler.hpp"
#include "mixr/base/SlotTable.hpp"
#include "mixr/base/Identifier.hpp"
#include "mixr/base/Pair.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/base/numeric/Number.hpp"
#include "mixr/base/osg/Vec3d"

namespace mixr {
namespace otw {

IMPLEMENT_SUBCLASS(OtwPC, "OtwPC")

BEGIN_SLOTTABLE(OtwPC)
    "netOutput",        // 1) Network output handler
END_SLOTTABLE(OtwPC)

// Map slot table to handles
BEGIN_SLOT_MAP(OtwPC)
    ON_SLOT(1,setSlotNetOutput,base::NetHandler)
END_SLOT_MAP()

OtwPC::OtwPC() : netOutput(nullptr)
{
    STANDARD_CONSTRUCTOR()
    setMaxRange(0);
    setMaxModels(0);
    setMaxElevations(0);
}

void OtwPC::copyData(const OtwPC& org, const bool cc)
{
    BaseClass::copyData(org);

    if (cc) {
        setMaxRange(0);
        setMaxModels(0);
        setMaxElevations(0);
    }
    netOutput = nullptr;
    netInit = org.netInit;
    netInitFail = org.netInitFail;
    scnt = 0;
}

void OtwPC::deleteData()
{
    netOutput = nullptr;
    netInit = false;
    netInitFail = false;
}

//------------------------------------------------------------------------------
// modelFactory() -- Create OtwModel objects unique to interface
//------------------------------------------------------------------------------
OtwModel* OtwPC::modelFactory()
{
    return new OtwModel();
}

//------------------------------------------------------------------------------
// hotFactory() -- Create OtwHot objects unique to interface
//------------------------------------------------------------------------------
OtwModel* OtwPC::hotFactory()
{
    return new OtwModel();
}

//------------------------------------------------------------------------------
// sendOwnshipAndModels() - Send state data for ownship and models
//------------------------------------------------------------------------------
void OtwPC::sendOwnshipAndModels()
{
    scnt--;
    if (scnt <= 0) {
        sendPcData();
        scnt = 5;   // send every 5th frame
    }
}

//------------------------------------------------------------------------------
// sendElevationRequests() - Sends terrain height requests
//------------------------------------------------------------------------------
void OtwPC::sendElevationRequests()
{
}

//------------------------------------------------------------------------------
// recvElevations() - Receives terrain height data
//------------------------------------------------------------------------------
void OtwPC::recvElevations()
{
}

//------------------------------------------------------------------------------
// frameSync() - Trigger the frame update
//------------------------------------------------------------------------------
void OtwPC::frameSync()
{
    // Initialization
    if (!isNetworkInitialized() && !didInitializationFail()) {
        if (initNetwork()) {
            netInit = true;
            netInitFail = false;
        }
        else {
            netInit = false;
            netInitFail = true;
        }
    }
}

//------------------------------------------------------------------------------
// reset() - Reset OTW
//------------------------------------------------------------------------------
void OtwPC::reset()
{
    BaseClass::reset();
}

//------------------------------------------------------------------------------
// initNetwork() -- Init the network
//------------------------------------------------------------------------------
bool OtwPC::initNetwork()
{
    bool ok = true;

    // Initialize network output handler
    if (netOutput != nullptr) {
        if (netOutput->initNetwork(true)) {
            if (isMessageEnabled(MSG_INFO)) {
                std::cout << "netOutput Initialize OK" << std::endl;
            }
        }
    }
    else {
        if (isMessageEnabled(MSG_ERROR)) {
        std::cerr << "OtwPC::initNetwork(): failure to find the network output handler (see slot 'netOutput')" << std::endl;
        }
        ok = false;
    }

    return ok;
}

//------------------------------------------------------------------------------
// Set Slot Functions
//------------------------------------------------------------------------------

// Net Network Output Handler
bool OtwPC::setSlotNetOutput(base::NetHandler* const msg)
{
    netOutput = msg;
    return true;
}

//------------------------------------------------------------------------------
// sendPcData() -- Send PC data block
//------------------------------------------------------------------------------
void OtwPC::sendPcData()
{
    //const double DEG2MR = (PI / 180.0f * 1000.0f);

    // Ownship type air vehicle?
    const auto av = dynamic_cast<const models::AirVehicle*>(getOwnship());
    if (av != nullptr) {

        dsFlightModelData fmd;

        fmd.m_x_cg = 0;
        fmd.m_y_cg = 0;
        fmd.m_z_cg = 0;          // altitude

        const base::Vec3d pos = av->getPosition();
        fmd.m_pilot_eye_x = pos[0] * base::distance::M2FT;
        fmd.m_pilot_eye_y = pos[1] * base::distance::M2FT;
        fmd.m_pilot_eye_z = -pos[2] * base::distance::M2FT;   // altitude

        fmd.m_alphad = av->getAngleOfAttackD();
        fmd.m_betad = av->getSideSlipD();
        fmd.m_mach = av->getMach();
        fmd.m_runalt = 0.0;

        fmd.m_theta    = static_cast<float_4>(av->getPitchD());
        fmd.m_phi      = static_cast<float_4>(av->getRollD());
        fmd.m_psi      = static_cast<float_4>(av->getHeadingD());
        fmd.m_airspeed = static_cast<float_4>(av->getTotalVelocityKts());

        fmd.m_heading = static_cast<float_4>(av->getHeadingD());

        fmd.m_dlg = 0;           // landing gear position 90 is down (scaled to 0-1)
        fmd.m_dsb = static_cast<float_4>(av->getSpeedBrakePosition()/100.0f);   // speed break 60 is out (scaled to 0-1)
        fmd.m_nz  = static_cast<float_4>(av->getGload());

        fmd.m_aetrc = 0;         // Commanded throttle position
        fmd.m_afterburner = 0;   // logical, true in in A/B

        fmd.m_target_id = 0;

        fmd.m_id_self = 0;       // make use of a hole
        fmd.m_flags = 0;

        fmd.m_target_x = 0;
        fmd.m_target_y = 0;
        fmd.m_target_z = 0;

        fmd.m_target_theta = 0;
        fmd.m_target_phi = 0;
        fmd.m_target_psi = 0;

        fmd.m_target_uearth = 0;
        fmd.m_target_vearth = 0;
        fmd.m_target_wearth = 0;
        fmd.m_target_vcas = 0;

        if (netOutput != nullptr) {
           netOutput->sendData( reinterpret_cast<char*>(&fmd), sizeof(fmd) );
        }
    }
}

}
}

