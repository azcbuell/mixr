
#ifndef __mxrp_interop_dis_factory_H__
#define __mxrp_interop_dis_factory_H__

#include <string>

namespace mxrp {
namespace base { class Object; }
namespace dis {
base::Object* factory(const std::string&);
}
}

#endif
