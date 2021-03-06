
#ifndef __mixr_iodevice_platform_UsbJoystick_linux_H__
#define __mixr_iodevice_platform_UsbJoystick_linux_H__

#include "mixr/iodevice/Controller.hpp"

namespace mixr {
namespace iodevice {

//------------------------------------------------------------------------------
// Class: UsbJoystick
//
// Factory name: UsbJoystick
//------------------------------------------------------------------------------
class UsbJoystick : public Controller
{
    DECLARE_SUBCLASS(UsbJoystick, Controller)

public:
   UsbJoystick();

   // base::IoDevice functions
   virtual void processInputs(const double dt, base::IoData* const inData) override;

   // base::Component functions
   virtual void reset() override;

private:
   int stream {};
   char deviceName[128] {};
};

}
}

#endif

