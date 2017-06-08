
#ifndef __mxrp_base_factory_H__
#define __mxrp_base_factory_H__

#include <string>

namespace mxrp {
namespace base {

class Object;
Object* factory(const std::string&);
}
}

#endif

