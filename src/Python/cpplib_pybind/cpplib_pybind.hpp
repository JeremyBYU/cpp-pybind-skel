
#pragma once

#include <pybind11/numpy.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h> // Include first to suppress compiler warnings
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include "CPPLib/CPPLib.hpp"

namespace py = pybind11;
using namespace py::literals;

// Use this if you want no copy returns for stl vectors
// If not then just delete/comment this out
PYBIND11_MAKE_OPAQUE(std::vector<size_t>);
PYBIND11_MAKE_OPAQUE(std::vector<double>);
PYBIND11_MAKE_OPAQUE(std::vector<int>);

namespace pybind11 {
namespace detail {

template <typename T, typename Class_>
void bind_default_constructor(Class_& cl)
{
    cl.def(py::init([]() { return new T(); }), "Default constructor");
}

template <typename T, typename Class_>
void bind_copy_functions(Class_& cl)
{
    cl.def(py::init([](const T& cp) { return new T(cp); }), "Copy constructor");
    cl.def("__copy__", [](T& v) { return T(v); });
    cl.def("__deepcopy__", [](T& v, py::dict& memo) { return T(v); });
}

} // namespace detail
} // namespace pybind11