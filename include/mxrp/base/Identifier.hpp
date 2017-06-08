
#ifndef __mxrp_base_Identifier_H__
#define __mxrp_base_Identifier_H__

#include "mxrp/base/String.hpp"

namespace mxrp {
namespace base {

//------------------------------------------------------------------------------
// Class: Identifier
// Description: A single unquoted word (usually from the input file), which
//              can contain upper and lower case letters, numbers, special
//              characters, but not spaces.
//
// Note: When setting the identifier, any spaces will be replaced
//       with underscores.
//
// Factory name: Identifier
//------------------------------------------------------------------------------
class Identifier : public String
{
    DECLARE_SUBCLASS(Identifier, String)

public:
    Identifier(const char* string);
    Identifier();

    virtual void setStr(const char* string) override;
    virtual void catStr(const char* string) override;
};

}
}

#endif
