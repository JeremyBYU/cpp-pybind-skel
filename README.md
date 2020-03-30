# C++ and Python Library

This is a template repository used to create  C++/Python libraries. This is for individual who want to write a *standalone* C++ library that can *also* be bound to Python using [Pybind11](https://pybind11.readthedocs.io/en/stable/) for better performance. I have tried my best to use good tools and practices in this repo to provide a clean codebase for others to start their project on. What you see in this repo is not all my work, but lessons/code I have learned after observing others [work](#acknowledgements). 

## Key Features

* C++ Library is independent of Python Extension, i.e. can be dropped into pure C++ projects.
* Cross platform using Modern CMake.
* Benchmark ([Google Benchmark](https://github.com/google/benchmark)) and Testing ([doctest](https://github.com/onqtam/doctest)) built in.
* Good handling of thirdparty dependencies using CMake `FetchContent`.
* Documentation for both C++ and Python created using Doxygen and Sphinx.

This repo relies upon using Modern CMake to build both the C++ and Python Extension libraries. I have previously used a `setup.py` file with `setuptools` to build the python extension. However I find that integrating it all in CMake leads to a much nicer *developer* experience. However external users *building* the library will need CMake installed which may be a consideration before using this template repo as a starting point.

## Instructions For Use

1. `git clone https://github.com/JeremyBYU/cpp-pybind-skel.git`

### Rename Files

You will want to rename files and library names with a simple `find and replace` using your IDE/editor. Lets say you named your project `SimpleImageFilters` with an associates short acronym of `SIF` . Then simply find and replace in this repository the following (case sensitivity matters):

* `CPPLib` -> `SimpleImageFilters` - C++ Top Namespace and CMake Project Name
* `CPPLIB` -> `SIMPLEIMAGEFILTERS` - Same but uppercase, used in CMake
* `CPPL` -> `SIF` - Acronym used in CMake alias for project
* `cpplib` -> `simpleimagefilters` - Python Library Extension Name

A helper python script, `rename_project.py` is provided if desired. 

Note: you don't have to use the naming convention proposed above and may use any you would like. I think the most important thing is simply that the Python extension target is different then C++ library target.

## Build

Building happens entirely with CMake.

### C++

1. `mkdir cmake-build && cd cmake-build` 
2. `cmake ..` -  Note - For windows also add `-DCMAKE_GENERATOR_PLATFORM=x64` 
3. `cmake --build . -j$(nproc) --config Release`

Build options:

```txt
CPPL_BUILD_BENCHMARKS:BOOL=ON // CPPL - Build Benchmarks
CPPL_BUILD_EXAMPLES:BOOL=ON // CPPL - Build Examples
CPPL_BUILD_PYMODULE:BOOL=ON // CPPL -Build Python Module
CPPL_BUILD_TESTS:BOOL=ON // CPPL - Build Tests
CPPL_BUILD_WERROR:BOOL=OFF // CPPL - Add Werror flag to build (turns warnings into errors)
CPPL_WITH_OPENMP:BOOL=ON // CPPL - Build with OpenMP Support
```

### Python

1. Install [conda](https://conda.io/projects/conda/en/latest/) or create a python virtual environment ([Why?](https://medium.freecodecamp.org/why-you-need-python-environments-and-how-to-manage-them-with-conda-85f155f4353c)). I recommend conda for Windows users.
2. Perform `CMake` build as described above
3. `cd cmake-build && cmake --build . --target python-package --config Release` 
4. `cd lib/python_package &&  pip install -e .` 

You can build a binary wheel that you can distribute to users with your **exact** same platform by

1. `cmake --build . --target pip-package --config Release` 

The wheel should then be at `cmake-build\lib\python_package\pip_package`.

TODO - Master the intricate world of conda/pip distribution (multiplatform wheels, manylinux)...

## Documentation

C++ classes and functions are documented in their header files. Associated Python functions/classes which are bound with Pybind11 are *re-documented*. This is for two reasons:

1. The function/class API might actually be slightly different in arguments and return types (e.g., list vs. std::vector) and more detail/nuance may be desired in one form of the other.
2. I have no idea how to share them.

For Python, I am using this [method](./src/Python/cpplib_pybind/docstring/docstring.hpp) to inject further documentation into functions/classes which was developed by [Intel at Open3D](https://github.com/intel-isl/Open3D). They provide a function that can transform an input `map` of arg/description pairs and convert to [Googles Python Docstring format](https://sphinxcontrib-napoleon.readthedocs.io/en/latest/example_google.html).

### Documentation Website Generation

Documentation building has been taken from Open3D with some small modification. Python *and* C++ documentation is generated using `Sphinx` into the **same** website. The C++ API is actually integrated into sphinx using `breathe/exhale`. Please see `docs/builddocs.rst`.

## Acknowledgements

I have learned a lot by listening/watching/reading about C++. I can't list them all but the following links had the most influence in developing this repo.

* [Open3D](https://github.com/intel-isl/Open3D) - Honestly most of this repo comes from following their practices.  After having made many C++/Python projects I find their structure to lead to a much better code design
* [Modern CMake](https://cliutils.gitlab.io/modern-cmake/) - An invaluable resource which has taught me so much about CMake.
* [Mapbox hpp-skel](https://github.com/mapbox/hpp-skel) - A great starting point for *header-only* libraries. Almost everything MapBox makes is gold to me.



