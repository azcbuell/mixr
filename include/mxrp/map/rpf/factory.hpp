
#ifndef __mxrp_map_rpf_factory_H__
#define __mxrp_map_rpf_factory_H__

#include <string>

namespace mxrp {
namespace base { class Object; }
namespace rpf {
base::Object* factory(const std::string&);
}
}

#endif