
#include "mxrp/models/environment/AbstractAtmosphere.hpp"

namespace mxrp {
namespace models {

IMPLEMENT_ABSTRACT_SUBCLASS(AbstractAtmosphere, "AbstractAtmosphere")

EMPTY_SLOTTABLE(AbstractAtmosphere)
EMPTY_COPYDATA(AbstractAtmosphere)
EMPTY_DELETEDATA(AbstractAtmosphere)
EMPTY_SERIALIZER(AbstractAtmosphere)

AbstractAtmosphere::AbstractAtmosphere()
{
   STANDARD_CONSTRUCTOR()
}

}
}
