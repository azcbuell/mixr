
#ifndef __mxrp_graphics_Cursor_H__
#define __mxrp_graphics_Cursor_H__

#include "mxrp/graphics/Field.hpp"

namespace mxrp {
namespace graphics {

//------------------------------------------------------------------------------
// Class: Cursor
//
// Factory name: Cursor
//------------------------------------------------------------------------------
class Cursor : public Field
{
    DECLARE_SUBCLASS(Cursor, Field)

public:
   Cursor();
   virtual void updateData(const double dt = 0.0) override;
};

}
}

#endif
