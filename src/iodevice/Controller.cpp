
#include "mixr/iodevice/Controller.hpp"

#include "mixr/base/numeric/Number.hpp"

#include <iostream>

namespace mixr {
namespace iodevice {

IMPLEMENT_SUBCLASS(Controller, "Controller")
EMPTY_DELETEDATA(Controller)

BEGIN_SLOTTABLE(Controller)
    "deviceIndex",   // 1) Device Index (default: 0)
END_SLOTTABLE(Controller)

BEGIN_SLOT_MAP(Controller)
    ON_SLOT( 1, setSlotDeviceIndex,  mixr::base::Number)
END_SLOT_MAP()

Controller::Controller()
{
   STANDARD_CONSTRUCTOR()
}

void Controller::copyData(const Controller& org, const bool)
{
   BaseClass::copyData(org);

   deviceIndex = org.deviceIndex;

   numAI = org.numAI;
   inData = org.inData;

   numDI = org.numDI;
   inBits = org.inBits;
}

//------------------------------------------------------------------------------
// Access Functions
//------------------------------------------------------------------------------

unsigned short Controller::getNumDiscreteInputChannels() const
{
   return numDI;
}

unsigned short Controller::getNumDiscreteInputPorts() const
{
   return 1;
}

bool Controller::getDiscreteInput(bool* const value, const unsigned int bit, const unsigned int) const
{
   bool ok = false;
   if (value != nullptr && bit < numDI) {
      *value = inBits[bit];
      ok = true;
   }
   return ok;
}

unsigned short Controller::getNumAnalogInputs() const
{
   return numAI;
}

bool Controller::getAnalogInput(double* const value, const unsigned int channel) const
{
   bool ok = false;
   if (value != nullptr && channel < numAI) {
      *value = inData[channel];
      ok = true;
   }
   return ok;
}

unsigned int Controller::getDeviceIndex() const
{
   return deviceIndex;
}


//------------------------------------------------------------------------------
// Set Functions
//------------------------------------------------------------------------------

// Device number
bool Controller::setDeviceIndex(const int v)
{
   bool ok = false;
   if (v >= 0 && v <= 31) {
      deviceIndex = static_cast<unsigned int>(v);
      ok = true;
   }
   return ok;
}


//------------------------------------------------------------------------------
// Slot Functions
//------------------------------------------------------------------------------

// deviceIndex: device index
bool Controller::setSlotDeviceIndex(const mixr::base::Number* const msg)
{
   bool ok = false;
   if (msg != nullptr) {
      ok = setDeviceIndex( msg->getInt() );
   }
   return ok;
}

}
}


