
#ifndef __mixr_interop_rprfom_Ntm_H__
#define __mixr_interop_rprfom_Ntm_H__

#include "mixr/interop/common/Ntm.hpp"
#include "mixr/interop/rprfom/NetIO.hpp"

namespace mixr {
namespace base { class List; }
namespace rprfom {

//------------------------------------------------------------------------------
// Class: Ntm
// Description: HLA Network Type Mapper
//
//    This class, which is derived from the simulation::Ntm, maps MIXR
//    player types to/from RPR FOM entity type codes.
//
// Factory name: HlaNtm
// Slots:
//    entityType  <vector>    ! Entity type vector:
//                            !  [ kind domain country category subcategory specific extra ]
//                            !  example: [ 1 2 333 4 5 6 7 ]
//
//------------------------------------------------------------------------------
class Ntm : public interop::Ntm
{
    DECLARE_SUBCLASS(Ntm, interop::Ntm)

public:
   Ntm();

   unsigned char getEntityKind() const         { return kind; }              // Kind type code (or 255 if not valid)
   unsigned char getEntityDomain() const       { return domain; }            // Domain type code
   unsigned short getEntityCountry() const     { return country; }           // Country type code
   unsigned char getEntityCategory() const     { return category; }          // Category type code
   unsigned char getEntitySubcategory() const  { return subcategory; }       // Subcategory type code
   unsigned char getEntitySpecific() const     { return specific; }          // Specific type code
   unsigned char getEntityExtra() const        { return extra; }             // Extra type code

   // Sets the player's entity type codes
   virtual bool setEntityType(
      const unsigned char  kind,
      const unsigned char  domain,
      const unsigned short countryCode,
      const unsigned char  category,
      const unsigned char  subcategory = 0,
      const unsigned char  specific = 0,
      const unsigned char  extra = 0
   );

   // Slot functions
   virtual bool setSlotEntityType(const base::List* const msg);         // Sets entity type enumerations

   // Simulation::Ntm class functions
   virtual bool copyEntityType(interop::Nib* const targetNib) const override;

private:
   // Standard type codes
   unsigned char  kind {};
   unsigned char  domain {};
   unsigned short country {};
   unsigned char  category {};
   unsigned char  subcategory {};
   unsigned char  specific {};
   unsigned char  extra {};
};

}
}

#endif
