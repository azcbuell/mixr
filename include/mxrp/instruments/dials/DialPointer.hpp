
#ifndef __mxrp_instruments_DialPointer_H__
#define __mxrp_instruments_DialPointer_H__

#include "mxrp/instruments/dials/AnalogDial.hpp"

namespace mxrp {
namespace instruments {

//------------------------------------------------------------------------------
// Class: DialPointer
//
// Description: Pointer that will spin around a defined arc or circle at a defined
// scaled rate.
// Input:  UPDATE_INSTRUMENTS (from instruments)
//------------------------------------------------------------------------------
class DialPointer : public AnalogDial
{
    DECLARE_SUBCLASS(DialPointer,AnalogDial)

public:
    DialPointer();

    virtual void draw() override;
};

}
}

#endif