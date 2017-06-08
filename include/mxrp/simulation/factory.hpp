
#ifndef __mxrp_simulation_factory_H__
#define __mxrp_simulation_factory_H__

#include <string>

namespace mxrp {
namespace base { class Object; }
namespace simulation {
base::Object* factory(const std::string&);
}
}

#endif
