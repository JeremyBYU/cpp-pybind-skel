
#include "cpplib_pybind/cpplib_pybind.hpp"
#include "cpplib_pybind/docstring/docstring.hpp"

using namespace CPPLib;

PYBIND11_MODULE(cpplib, m)
{
    m.doc() = "Python binding of CPPLib";

    py::bind_vector<std::vector<double>>(m, "VectorDouble", py::buffer_protocol());
    py::bind_vector<std::vector<int>>(m, "VectorInt", py::buffer_protocol());
    py::bind_vector<std::vector<std::size_t>>(m, "VectorULongInt", py::buffer_protocol());

    m.def("hello", &CPPLib::Hello, "name"_a);
    docstring::FunctionDocInject(m, "hello", {{"name", "The name to say hello with"}});

    m.def("multiply_by_scalar", &CPPLib::MultiplyByScalar<double>, "vec"_a, "scalar"_a, "Multiplies a vector");
    m.def("multiply_by_scalar", &CPPLib::MultiplyByScalar<int>, "vec"_a, "scalar"_a, "Multiplies a vector");
    m.def("multiply_by_scalar", &CPPLib::MultiplyByScalar<size_t>, "vec"_a, "scalar"_a, "Multiplies a vector");
    docstring::FunctionDocInject(
        m, "multiply_by_scalar",
        {{"vec", "A list of numbers (double, int, size_t)"}, {"scalar", "A scalar number to multiply the list by."}});
}