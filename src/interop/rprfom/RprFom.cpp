
#include "mixr/interop/rprfom/RprFom.hpp"
 
namespace mixr {
namespace rprfom {

//==============================================================================
// BaseEntity Structure (S)
//==============================================================================

IMPLEMENT_SUBCLASS(BaseEntity, "BaseEntity")
EMPTY_SLOTTABLE(BaseEntity)
EMPTY_DELETEDATA(BaseEntity)

void BaseEntity::copyData(const BaseEntity& org, const bool)
{
    BaseClass::copyData(org);
}

//==============================================================================
// PhysicalEntity Structure (S)
//==============================================================================

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(PhysicalEntity, "PhysicalEntity")
EMPTY_DELETEDATA(PhysicalEntity)

void PhysicalEntity::copyData(const PhysicalEntity& org, const bool)
{
    BaseClass::copyData(org);
}

//==============================================================================
// Lifeform Structure (S)
//==============================================================================

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Lifeform, "Lifeform")
EMPTY_DELETEDATA(Lifeform)

void Lifeform::copyData(const Lifeform& org, const bool)
{
    BaseClass::copyData(org);
}

//==============================================================================
// Human Structure (PS)
//==============================================================================

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Human, "Human")
EMPTY_DELETEDATA(Human)

void Human::copyData(const Human& org, const bool)
{
    BaseClass::copyData(org);
}

//==============================================================================
// NonHuman Structure (PS)
//==============================================================================

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(NonHuman, "NonHuman")
EMPTY_DELETEDATA(NonHuman)

void NonHuman::copyData(const NonHuman& org, const bool)
{
    BaseClass::copyData(org);
}

//==============================================================================
// Munition Structure (PS)
//==============================================================================

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Munition, "Munition")
EMPTY_DELETEDATA(Munition)

void Munition::copyData(const Munition& org, const bool)
{
    BaseClass::copyData(org);
}

//==============================================================================
// Platform Structure (S)
//==============================================================================

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Platform, "Platform")
EMPTY_DELETEDATA(Platform)

void Platform::copyData(const Platform& org, const bool)
{
    BaseClass::copyData(org);
}

//==============================================================================
// Aircraft Structure (PS)
//==============================================================================

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Aircraft, "Aircraft")
EMPTY_COPYDATA(Aircraft)
EMPTY_DELETEDATA(Aircraft)

//==============================================================================
// AmphibiousVehicle Structure (PS)
//==============================================================================

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(AmphibiousVehicle, "AmphibiousVehicle")
EMPTY_COPYDATA(AmphibiousVehicle)
EMPTY_DELETEDATA(AmphibiousVehicle)

//==============================================================================
// GroundVehicle Structure (S)
//==============================================================================

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(GroundVehicle, "GroundVehicle")
EMPTY_COPYDATA(GroundVehicle)
EMPTY_DELETEDATA(GroundVehicle)

//==============================================================================
// MultiDomainPlatform Structure (PS)
//==============================================================================

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(MultiDomainPlatform, "MultiDomainPlatform")
EMPTY_COPYDATA(MultiDomainPlatform)
EMPTY_DELETEDATA(MultiDomainPlatform)
  
//==============================================================================
// Spacecraft Structure (PS)
//==============================================================================

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(Spacecraft, "Spacecraft")
EMPTY_COPYDATA(Spacecraft)
EMPTY_DELETEDATA(Spacecraft)
  
//==============================================================================
// SubmersibleVessel Structure (PS)
//==============================================================================

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(SubmersibleVessel, "SubmersibleVessel")
EMPTY_COPYDATA(SubmersibleVessel)
EMPTY_DELETEDATA(SubmersibleVessel)

//==============================================================================
// SurfaceVessel Structure (PS)
//==============================================================================

IMPLEMENT_EMPTY_SLOTTABLE_SUBCLASS(SurfaceVessel, "SurfaceVessel")
EMPTY_COPYDATA(SurfaceVessel)
EMPTY_DELETEDATA(SurfaceVessel)

}
}
