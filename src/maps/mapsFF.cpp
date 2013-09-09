//------------------------------------------------------------------------------
// mapsFormFunc()
//------------------------------------------------------------------------------

#include "openeaagles/maps/mapsFF.h"

#include "openeaagles/maps/rpfMap/rpfMapFF.h"
#include "openeaagles/maps/vpfMap/vpfMapFF.h"

namespace Eaagles {
namespace Maps {

Basic::Object* mapsFormFunc(const char* formname)
{
    Basic::Object* newform = Rpf::rpfMapFormFunc(formname);
    if (newform == 0) newform = Vpf::vpfMapFormFunc(formname);
    return newform;
}

} // end Maps namespace
} // end Eaagles namespace

