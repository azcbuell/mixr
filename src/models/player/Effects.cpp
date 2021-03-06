
#include "mixr/models/player/Effects.hpp"

#include "mixr/base/List.hpp"
#include "mixr/base/Identifier.hpp"
#include "mixr/base/osg/Vec3d"
#include "mixr/base/numeric/Number.hpp"

#include <cmath>

namespace mixr {
namespace models {

IMPLEMENT_SUBCLASS(Effects,"Effects")
EMPTY_DELETEDATA(Effects)

BEGIN_SLOTTABLE(Effects)
    "dragIndex",        // 1: drag index used by default dynamics
END_SLOTTABLE(Effects)

BEGIN_SLOT_MAP(Effects)
    ON_SLOT(1, setSlotDragIndex, base::Number)
END_SLOT_MAP()

// Weapon data for general bomb
int Effects::getCategory() const                { return GRAVITY; }
const char* Effects::getDescription() const     { return "Generic Effects"; }
const char* Effects::getNickname() const        { return "Effects"; }

Effects::Effects()
{
    STANDARD_CONSTRUCTOR()

    static base::String generic("Effects");
    setType(&generic);

    // Default: unguided, ballistic
    setMaxTOF(10.0);
    setLethalRange(50.0f);
    setMaxBurstRng(500.0f);
    setTSG(9999.0f);
    setSOBT(9999.0f);
    setEOBT(0.0f);
}

void Effects::copyData(const Effects& org, const bool)
{
    BaseClass::copyData(org);
    dragIndex = org.dragIndex;
}

//------------------------------------------------------------------------------
// crashNotification() -- We just hit the ground (need to check fusing and all that jazz)
//------------------------------------------------------------------------------
bool Effects::crashNotification()
{
    const bool ok = killedNotification();
    setDetonationResults(DETONATE_NONE);
    setMode(DETONATED);
    return ok;
}

//------------------------------------------------------------------------------
// collisionNotification() -- We just impacted with another player (need to check fusing and all that jazz)
//------------------------------------------------------------------------------
bool Effects::collisionNotification(Player* const p)
{
    const bool ok = killedNotification(p);
    setMode(DETONATED);
    setDetonationResults(DETONATE_NONE);
    return ok;
}

//------------------------------------------------------------------------------
// updateTOF -- default time of flight
//------------------------------------------------------------------------------
void Effects::updateTOF(const double dt)
{
   // As long as we're active ...
   if (isMode(ACTIVE)) {

      // update time of flight,
      setTOF( getTOF() + dt );

      // and check for the end of the flight
      if (getTOF() >= getMaxTOF()) {
         setMode(DETONATED);
         setDetonationResults(DETONATE_NONE);
         return;
      }
   }
}

//------------------------------------------------------------------------------
// weaponDynamics -- default dynamics; using Robot Aircraft (RAC) dynamics
//------------------------------------------------------------------------------
void Effects::weaponDynamics(const double dt)
{
   // Useful constant
   static const double g = base::ETHG * base::distance::FT2M;      // Acceleration of Gravity (m/s/s)

   // ---
   // Compute & Set acceleration vector (earth)
   // ---

   // First drag
   const base::Vec3d tmp = getVelocity() * (-dragIndex);

   // then gravity
   base::Vec3d ae1 = tmp;
   ae1[IDOWN] += g;

   setAcceleration(ae1);

   // ---
   // Compute & set new velocity vector (earth)
   // ---
   base::Vec3d ve1 = getVelocity() + (ae1 * dt);
   setVelocity(ve1);

   // ---
   // .. Only after setVelocity has been called ...
   // ---
   double vp = getTotalVelocity();
   double vg = getGroundSpeed();

   // ---
   // Set velocity vector (body)
   //  (total velocity is along X)
   // ---
   setVelocityBody(vp, 0.0, 0.0);

   // ---
   // Sent angular values
   // ---
   const double newPsi   = std::atan2(ve1[IEAST],ve1[INORTH]);
   const double newTheta = std::atan2( -ve1[IDOWN], vg );
   setEulerAngles(0.0, newTheta, newPsi);
   setAngularVelocities(0.0, 0.0, 0.0);

}


//------------------------------------------------------------------------------
// Set Slot routines --
//------------------------------------------------------------------------------

// dragIndex: drag index used by default dynamics
bool Effects::setSlotDragIndex(base::Number* const p)
{
    setDragIndex( p->getReal() );
    return true;
}

//==============================================================================
// Class: Chaff
//==============================================================================
IMPLEMENT_SUBCLASS(Chaff,"Chaff")
EMPTY_SLOTTABLE(Chaff)

// Weapon data for general bomb
int Chaff::getCategory() const                { return GRAVITY; }
const char* Chaff::getDescription() const     { return "Generic Chaff"; }
const char* Chaff::getNickname() const        { return "Chaff"; }

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Chaff::Chaff()
{
    STANDARD_CONSTRUCTOR()

    static base::String generic("Chaff");
    setType(&generic);
}

//------------------------------------------------------------------------------
// copyData(), deleteData() -- copy (delete) member data
//------------------------------------------------------------------------------
void Chaff::copyData(const Chaff& org, const bool)
{
    BaseClass::copyData(org);
}

void Chaff::deleteData()
{
}


//==============================================================================
// Class: Flare
//==============================================================================
IMPLEMENT_SUBCLASS(Flare,"Flare")
EMPTY_SLOTTABLE(Flare)

// Weapon data for general bomb
int Flare::getCategory() const                { return GRAVITY; }
const char* Flare::getDescription() const     { return "Generic Flare"; }
const char* Flare::getNickname() const        { return "Flare"; }

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Flare::Flare()
{
    STANDARD_CONSTRUCTOR()

    static base::String generic("Flare");
    setType(&generic);
}

//------------------------------------------------------------------------------
// copyData(), deleteData() -- copy (delete) member data
//------------------------------------------------------------------------------
void Flare::copyData(const Flare& org, const bool)
{
    BaseClass::copyData(org);
}

void Flare::deleteData()
{
}

//==============================================================================
// Class: Decoy
//==============================================================================
IMPLEMENT_SUBCLASS(Decoy,"Decoy")
EMPTY_SLOTTABLE(Decoy)

// Weapon data for general bomb
int Decoy::getCategory() const                { return GRAVITY; }
const char* Decoy::getDescription() const     { return "Generic Decoy"; }
const char* Decoy::getNickname() const        { return "Decoy"; }

//------------------------------------------------------------------------------
// Constructor(s)
//------------------------------------------------------------------------------
Decoy::Decoy()
{
    STANDARD_CONSTRUCTOR()

    static base::String generic("Decoy");
    setType(&generic);
}

//------------------------------------------------------------------------------
// copyData(), deleteData() -- copy (delete) member data
//------------------------------------------------------------------------------
void Decoy::copyData(const Decoy& org, const bool)
{
    BaseClass::copyData(org);
}

void Decoy::deleteData()
{
}

}
}
