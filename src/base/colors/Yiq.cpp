
#include "mixr/base/colors/Yiq.hpp"

#include "mixr/base/numbers/Float.hpp"

namespace mixr {
namespace base {

IMPLEMENT_SUBCLASS(Yiq, "yiq")

BEGIN_SLOTTABLE(Yiq)
    "y",  // 1: ... Y component, range(0.0 to 1.0)
    "i",  // 2: ... I component, range(-0.6 to -0.6)
    "q",  // 3: ... Q component, range(-0.52 to 0.52)
END_SLOTTABLE(Yiq)

BEGIN_SLOT_MAP(Yiq)
    ON_SLOT(1, setY, Number)
    ON_SLOT(2, setI, Number)
    ON_SLOT(3, setQ, Number)
END_SLOT_MAP()

Yiq::Yiq(const double y, const double i, const double q)
{
   STANDARD_CONSTRUCTOR()
   yiq[Y] = y;           // set the values
   yiq[I] = i;
   yiq[Q] = q;
   yiq2rgb(color,yiq);   // set the rgb values
}

Yiq::Yiq()
{
   STANDARD_CONSTRUCTOR()
   yiq[Y] = 0.0f;        // default to black
   yiq[I] = 0.0f;
   yiq[Q] = 0.0f;
   yiq2rgb(color,yiq);   // set the rgb values
}

void Yiq::copyData(const Yiq& org, const bool)
{
   BaseClass::copyData(org);
   yiq = org.yiq;
}

EMPTY_DELETEDATA(Yiq)

//------------------------------------------------------------------------------
// Data access functions
//------------------------------------------------------------------------------
double Yiq::y() const
{
    return yiq[Y];
}

double Yiq::i() const
{
    return yiq[I];
}

double Yiq::q() const
{
    return yiq[Q];
}

void Yiq::getYIQ(Vec3d& hhh) const
{
    hhh.set(yiq[Y],yiq[I],yiq[Q]);
}

//------------------------------------------------------------------------------
// setY() -- set the Y value
//------------------------------------------------------------------------------
bool Yiq::setY(Number* const msg)
{
    if (msg == nullptr) return false;
    const double value {msg->getReal()};
    const bool ok = (value >= 0 && value <= 1);
    if (ok) { yiq[Y] = value; yiq2rgb(color,yiq); }
    else std::cerr << "Yiq::setY: invalid entry(" << value << "), valid range: 0 to 1" << std::endl;
    return ok;
}

//------------------------------------------------------------------------------
// setI() -- set the I value
//------------------------------------------------------------------------------
bool Yiq::setI(Number* const msg)
{
    if (msg == nullptr) return false;
    const double value {msg->getReal()};
    const bool ok = (value >= -0.6 && value <= 0.6);
    if (ok) { yiq[I] = value; yiq2rgb(color,yiq); }
    else std::cerr << "Yiq::setI: invalid entry(" << value << "), valid range: -0.6 to 0.6" << std::endl;
    return ok;
}

//------------------------------------------------------------------------------
// setQ() -- set the Q value
//------------------------------------------------------------------------------
bool Yiq::setQ(Number* const msg)
{
    if (msg == nullptr) return false;
    const double value {msg->getReal()};
    const bool ok = (value >= -0.52 && value <= 0.52);
    if (ok) { yiq[Q] = value; yiq2rgb(color,yiq); }
    else std::cerr << "Yiq::setQ: invalid entry(" << value << "), valid range: -0.52 to 0.52" << std::endl;
    return ok;
}

//------------------------------------------------------------------------------
// yiq2rgb() -- converts a YIQ color to a Red, Green, Blue (RGB) value.
//
// This code is based on '/usr/people/4Dgifts/iristools/libgutil/colormod.c'
//------------------------------------------------------------------------------
void Yiq::yiq2rgb(Vec4d& rgb, const Vec3d& yiq)
{
    rgb[RED]   = 1.0f * yiq[Y] + 0.948262f * yiq[I] + 0.624013f * yiq[Q];
    rgb[GREEN] = 1.0f * yiq[Y] - 0.276066f * yiq[I] - 0.639810f * yiq[Q];
    rgb[BLUE]  = 1.0f * yiq[Y] - 1.105450f * yiq[I] + 1.729860f * yiq[Q];
    rgb[ALPHA] = defaultAlpha;
}

//------------------------------------------------------------------------------
// rgb2yiq -- converts a Red, Green, Blue (RGB) color to a YIQ value.
//------------------------------------------------------------------------------
void Yiq::rgb2yiq(Vec3d& yiq, const Vec4d& rgb)
{
    yiq[Y] = 0.30f * rgb[RED] + 0.59f * rgb[GREEN] + 0.11f * rgb[BLUE];
    yiq[I] = 0.60f * rgb[RED] - 0.28f * rgb[GREEN] - 0.32f * rgb[BLUE];
    yiq[Q] = 0.21f * rgb[RED] - 0.52f * rgb[GREEN] + 0.31f * rgb[BLUE];
}

}
}
