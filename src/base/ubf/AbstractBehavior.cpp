
#include "mxrp/base/ubf/AbstractBehavior.hpp"

#include "mxrp/base/Number.hpp"
#include <iostream>

namespace mxrp {
namespace base {
namespace ubf {

IMPLEMENT_ABSTRACT_SUBCLASS(AbstractBehavior, "AbstractBehavior")
EMPTY_DELETEDATA(AbstractBehavior)
EMPTY_COPYDATA(AbstractBehavior)
EMPTY_SERIALIZER(AbstractBehavior)

BEGIN_SLOTTABLE(AbstractBehavior)
   "vote"            //  1) default vote/weight value for actions generated by this behavior
END_SLOTTABLE(AbstractBehavior)

//  mapping of slots to handles
BEGIN_SLOT_MAP(AbstractBehavior)
   ON_SLOT(1, setSlotVote, base::Number)
END_SLOT_MAP()

AbstractBehavior::AbstractBehavior()
{
   STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// Slot functions
//------------------------------------------------------------------------------

// [ 1 .. 65535 ]
bool AbstractBehavior::setSlotVote(const base::Number* const num)
{
   bool ok = false;
   int vote = num->getInt();
   if (vote > 0 && vote <= 65535) {
      setVote(static_cast<unsigned int>(vote));
      ok = true;
   }
   return ok;
}

}
}
}

