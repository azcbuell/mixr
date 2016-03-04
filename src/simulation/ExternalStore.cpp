
#include "openeaagles/simulation/ExternalStore.h"

#include "openeaagles/base/Number.h"
#include "openeaagles/base/String.h"

namespace oe {
namespace simulation {

//------------------------------------------------------------
// Dummy weapon for non-releasable, non-jettisonable stores
//------------------------------------------------------------
IMPLEMENT_SUBCLASS(ExternalStore, "ExternalStore")

// Slot table
BEGIN_SLOTTABLE(ExternalStore)
   "type",        // 1) Type of external store string
   "jettisonable" // 2) External store can be jettisoned (default: true)
END_SLOTTABLE(ExternalStore)

// Map slot table to handles
BEGIN_SLOT_MAP(ExternalStore)
   ON_SLOT( 1, setSlotType, basic::String)
   ON_SLOT( 2, setSlotJettisonable, basic::Number )
END_SLOT_MAP()

// Event() map
BEGIN_EVENT_HANDLER(ExternalStore)
   ON_EVENT( JETTISON_EVENT, onJettisonEvent)
END_EVENT_HANDLER()

//------------------------------------------------------------------------------
// Class support functions
//------------------------------------------------------------------------------
ExternalStore::ExternalStore()
{
   STANDARD_CONSTRUCTOR()

      initData();
}

// init member data
void ExternalStore::initData()
{
   type = nullptr;
   canJettison = true; // default
   jettisoned = false;
}

// Copy member data
void ExternalStore::copyData(const ExternalStore& org, const bool cc)
{
   BaseClass::copyData(org);
   if (cc) initData();

   {
      const basic::String* p = nullptr;
      if (org.type != nullptr) p = org.type->clone();
      setSlotType( p );
      if (p != nullptr) p->unref();
   }

   canJettison  = org.canJettison;
   jettisoned = org.jettisoned;
}

// Delete member data
void ExternalStore::deleteData()
{
   type = nullptr;
}

//------------------------------------------------------------------------------
// Reset
//------------------------------------------------------------------------------
void ExternalStore::reset()
{
   BaseClass::reset();

   jettisoned = false;
}

//------------------------------------------------------------------------------
// Event handlers
//------------------------------------------------------------------------------
bool ExternalStore::onJettisonEvent()
{
   bool ok = false;
   if (canJettison && !jettisoned) {
      // If we can be jettisoned and we haven't already been ...
      jettisoned =  true;
      ok = true;
   }
   return ok;
}

//------------------------------------------------------------------------------
// Get functions
//------------------------------------------------------------------------------

// Get the type string
const basic::String* ExternalStore::getType() const
{
   return type;
}

// True if the weapon can be jettisioned
bool ExternalStore::isJettisonable() const
{
   return canJettison;
}

// True if the weapon has been jettisioned
bool ExternalStore::isJettisoned() const
{
   return jettisoned;
}

//------------------------------------------------------------------------------
// Set functions
//------------------------------------------------------------------------------

// Sets the jettision enable flag
bool ExternalStore::setJettisonable(const bool f)
{
   canJettison = f;
   return true;
}

//------------------------------------------------------------------------------
// Set slot functions
//------------------------------------------------------------------------------

// Set type string
bool ExternalStore::setSlotType(const basic::String* const msg)
{
   type = msg;
   return true;
}

// jettisonable: weapon can be jettisoned
bool ExternalStore::setSlotJettisonable(basic::Number* const p)
{
   setJettisonable( p->getBoolean() );
   return true;
}

//------------------------------------------------------------------------------
// getSlotByIndex()
//------------------------------------------------------------------------------
basic::Object* ExternalStore::getSlotByIndex(const int si)
{
   return BaseClass::getSlotByIndex(si);
}

//------------------------------------------------------------------------------
// serialize
//------------------------------------------------------------------------------
std::ostream& ExternalStore::serialize(std::ostream& sout, const int i, const bool slotsOnly) const
{
   int j = 0;
   if ( !slotsOnly ) {
      indent(sout,i);
      sout << "( " << getFactoryName() << std::endl;
      j = 4;
   }

   if (type != nullptr) {
      indent(sout,i+j);
      sout << "type: " << *type << std::endl;
   }

   indent(sout,i+j);
   sout << "jettisonable: " << isJettisonable() << std::endl;

   BaseClass::serialize(sout,i+j,true);

   if ( !slotsOnly ) {
      indent(sout,i);
      sout << ")" << std::endl;
   }

   return sout;
}


} // end simulation namespace
} // end oe namespace
