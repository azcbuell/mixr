
#include "mixr/base/functors/Function.hpp"

#include "mixr/base/List.hpp"
#include "mixr/base/functors/Tables.hpp"
#include <iostream>

namespace mixr {
namespace base {

//==============================================================================
// class FStorage
//==============================================================================
IMPLEMENT_SUBCLASS(FStorage, "FStorage")
EMPTY_SLOTTABLE(FStorage)
EMPTY_CONSTRUCTOR(FStorage)
EMPTY_COPYDATA(FStorage)
EMPTY_DELETEDATA(FStorage)

//==============================================================================
// Class: Function
//==============================================================================
IMPLEMENT_SUBCLASS(Function, "Function")

BEGIN_SLOTTABLE(Function)
    "table",          // Optional LFI table
END_SLOTTABLE(Function)

BEGIN_SLOT_MAP(Function)
    ON_SLOT( 1, setSlotLfiTable, Table)
END_SLOT_MAP()

Function::Function()
{
   STANDARD_CONSTRUCTOR()

   table = nullptr;
}

void Function::copyData(const Function& org, const bool cc)
{
   BaseClass::copyData(org);
   if (cc) table = nullptr;

   {
      const Table* copy = nullptr;
      if (org.table != nullptr) {
         copy = static_cast<const Table*>(org.table->clone());
      }
      setSlotLfiTable(copy);
      if (copy != nullptr) copy->unref();
   }
}

void Function::deleteData()
{
   setSlotLfiTable(nullptr);
}

//------------------------------------------------------------------------------
// Storage factory
//------------------------------------------------------------------------------
FStorage* Function::storageFactory() const
{
   // Since no derived class handled this ...
   if (table != nullptr) {
      // then we're going to let the table handle it, if any
      return table->storageFactory();
   }
   else {
      // or we're just going to return a standard FStorage object.
      return new FStorage();
   }
}

//------------------------------------------------------------------------------
// Slot functions
//------------------------------------------------------------------------------
bool Function::setSlotLfiTable(const Table* const msg)
{
   table = msg;
   return true;
}

}
}
