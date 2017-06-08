
#ifndef __mxrp_models_Sam_H__
#define __mxrp_models_Sam_H__

#include "mxrp/models/player/Missile.hpp"

namespace mxrp {
namespace models {

//------------------------------------------------------------------------------
// Class: Sam
//
// Description: Base class for Surface to Air (SAM) Missiles
//
// Factory name: Sam
//------------------------------------------------------------------------------
class Sam : public Missile
{
    DECLARE_SUBCLASS(Sam, Missile)

public:
    Sam();

    virtual const char* getDescription() const override;
    virtual const char* getNickname() const override;
    virtual int getCategory() const override;
};

}
}

#endif
