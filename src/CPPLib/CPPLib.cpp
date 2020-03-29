#include "CPPLib/CPPLib.hpp"

namespace CPPLib {
std::string Hello(std::string& name)
{
    return "Hello " + name;
}
template <typename T>
std::vector<T> MultiplyByScalar(std::vector<T>& vec, T scalar)
{
    std::vector<T> b;
    b.reserve(vec.size());

    std::transform(vec.begin(), vec.end(), std::back_inserter(b), [scalar](auto& a_elem) { return a_elem * scalar; });

    return b;
}

// Forward declare specialization
// https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl
template std::vector<double> MultiplyByScalar<double>(std::vector<double>& vec, double scalar);
template std::vector<int> MultiplyByScalar<int>(std::vector<int>& vec, int scalar);
template std::vector<size_t> MultiplyByScalar<size_t>(std::vector<size_t>& vec, size_t scalar);

} // namespace CPPLib