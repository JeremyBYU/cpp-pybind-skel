#include "CPPLConfig.hpp"
#include <string>

namespace CPPLib {

std::string GetCPPLibVersion() { return std::string("CPPLib ") + CPPLIB_VERSION; }

} // namespace CPPLib