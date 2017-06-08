
#include "mxrp/simulation/AbstractOtw.hpp"

namespace mxrp {
namespace simulation {

IMPLEMENT_ABSTRACT_SUBCLASS(AbstractOtw, "AbstractOtw")

EMPTY_SLOTTABLE(AbstractOtw)
EMPTY_COPYDATA(AbstractOtw)
EMPTY_DELETEDATA(AbstractOtw)
EMPTY_SERIALIZER(AbstractOtw)

AbstractOtw::AbstractOtw()
{
   STANDARD_CONSTRUCTOR()
}

}
}
