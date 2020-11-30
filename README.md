# C++ and Python Library

This is a template repository used to create  C++/Python libraries. This is for individual who want to write a *standalone* C++ library that can *also* be bound to Python using [Pybind11](https://pybind11.readthedocs.io/en/stable/) for better performance. This repository additionally takes care of the intricate world of building **binary** wheels automatically and publishing to PyPI, including linux and windows. I have tried my best to use good tools and practices in this repo to provide a clean codebase for others to start their project on. What you see in this repo is not all my work, but lessons/code I have learned after observing [others work](#acknowledgements). 

## Key Features

* C++ Library is independent of Python Extension, i.e. can be dropped into pure C++ projects.
* Cross platform using Modern CMake.
* Benchmark ([Nanobench](https://github.com/martinus/nanobench)) and Testing ([doctest](https://github.com/onqtam/doctest)) built in.
* Good handling of thirdparty dependencies using CMake `FetchContent`.
* Documentation for both C++ and Python created using Sphinx, Doxygen, Breathe, and Exhale. The documentation is unified into one website.
* Integration of CMake into `setup.py` so that `pip install` works for python users wanting to build manually (CMake must be installed still).
    *  Note that the C++ Library and even the python extension can still be built with standard CMake procedures, see [Build with CMake](#build-manually-with-cmake)
* Automatic building of python **binary** wheels using [github actions](https://docs.github.com/en/free-pro-team@latest/actions/learn-github-actions), see [Workflow](#workflow)

This repo relies upon using Modern CMake to build both the C++ and Python Extension libraries. I find that integrating it all in CMake leads to a much nicer *developer* experience. External users *building* the library will need CMake installed which may be a consideration before using this template repo as a starting point. However, this repo has a github workflow setup to automatically build python **binary** wheels for you and upload to PyPI for a variety of python versions/OS/architectures! Please see [workflows](#workflows)

## Instructions For Using Template

1. `git clone https://github.com/JeremyBYU/cpp-pybind-skel.git`

### Rename Files

You will want to rename files and library names with a simple `find and replace` using your IDE/editor. Lets say you named your project `SimpleImageFilters` with an associates short acronym of `SIF` . Then simply find and replace in this repository the following (case sensitivity matters):

* `CPPLib` -> `SimpleImageFilters` - C++ Top Namespace and CMake Project Name
* `CPPLIB` -> `SIMPLEIMAGEFILTERS` - Same but uppercase, used in CMake
* `CPPL` -> `SIF` - Acronym used in CMake alias for project
* `cpplib` -> `simpleimagefilters` - Python Library Extension Name

A helper python script, `rename_project.py` is provided if desired. I would recommend using it because it saves a lot of time.

Note: you don't have to use the naming convention proposed above and may use any you would like. I think the most important thing is simply that the Python extension target is different then C++ library target.

## Build Project Manually

You can build the project manually in two ways: one in pure CMake, the other using python `setup.py`.
### Build Manually With CMake

Building happens entirely with CMake. This is meant really only for the library developers who are working on C++ and Python in an edit-compile cycle.

#### C++

1. `mkdir cmake-build && cd cmake-build` 
2. `cmake ..` -  Note - For windows also add `-DCMAKE_GENERATOR_PLATFORM=x64` 
3. `cmake --build . -j$(nproc) --config Release`

Build options:

```text
CPPL_BUILD_BENCHMARKS:BOOL=ON // CPPL - Build Benchmarks
CPPL_BUILD_EXAMPLES:BOOL=ON // CPPL - Build Examples
CPPL_BUILD_PYMODULE:BOOL=ON // CPPL -Build Python Module
CPPL_BUILD_TESTS:BOOL=ON // CPPL - Build Tests
CPPL_BUILD_WERROR:BOOL=OFF // CPPL - Add Werror flag to build (turns warnings into errors)
CPPL_WITH_OPENMP:BOOL=ON // CPPL - Build with OpenMP Support
```

#### Python 

This is meant for advanced python users who are actively developing the extension.

1. Install [conda](https://conda.io/projects/conda/en/latest/) or create a python virtual environment ([Why?](https://medium.freecodecamp.org/why-you-need-python-environments-and-how-to-manage-them-with-conda-85f155f4353c)). I recommend conda for Windows users.
2. Perform `CMake` build as described above
3. `cd cmake-build && cmake --build . --target python-package --config Release` 
4. `cd lib/python_package &&  pip install -e .` 

You can build a binary wheel that you can distribute to users with your **exact** same platform by

1. `cmake --build . --target pip-package --config Release` 

The wheel should then be at `cmake-build\lib\python_package\pip_package`. Note you can alternatively build using [Python setup.py](#build-manually-with-python)

### Build Manually with Python

The root directory `setup.py` file has been modified to build with CMake. This is meant for python users that need to build manually (for some reason) but are not actively developing or changing the code.

1. Install [conda](https://conda.io/projects/conda/en/latest/) or create a python virtual environment ([Why?](https://medium.freecodecamp.org/why-you-need-python-environments-and-how-to-manage-them-with-conda-85f155f4353c)). I recommend conda for Windows users.
2. `pip install .` - Call from root directory

That should be it!

## Install with Python

If you only care about installing the python extension you can install from the binary wheels generated by the github action workflows. The binary wheels are uploaded to PyPi. Therefore, after configuring the workflow and tagging a version, you can install as:

1. `pip install cpplib` - Change `cpplib` to whatever your python extension will end up being.

## Workflows

Several github action workflows are included in this repository. The first is the binary wheel creation and uploading to pypi.

### Binary Wheel

This [workflow file](.github/wheels.yml) generates the binary wheels and uploads to PyPI. You will need to configure your github repository with a token access to publish to `PyPI` and `PyPITest`. Please read [here](https://github.com/pypa/gh-action-pypi-publish) about what is expected. Note that this workflow only run on the master branch, and publishing only occurs on tagged releases.

### Tests

Automatic testing is also done using this [test workflow file](.github/tests.yml) 
## Documentation

C++ classes and functions are documented in their header files. Associated Python functions/classes which are bound with Pybind11 are *re-documented*. This is for two reasons:

1. The function/class API might actually be slightly different in arguments and return types (e.g., list vs. std::vector) and more detail/nuance may be desired in one form of the other.
2. I have no idea how to share them.

For Python, I am using this [method](./src/Python/cpplib_pybind/docstring/docstring.hpp) to inject further documentation into functions/classes which was developed by [Intel at Open3D](https://github.com/intel-isl/Open3D). They provide a function that can transform an input `map` of arg/description pairs and convert to [Googles Python Docstring format](https://sphinxcontrib-napoleon.readthedocs.io/en/latest/example_google.html).

### Documentation Website Generation

Documentation building has been taken from Open3D with some small modification. Python *and* C++ documentation is generated using `Sphinx` into the **same** website. The C++ API is actually integrated into sphinx using `breathe/exhale`. Please see `docs/builddocs.rst`.


## Release Steps

These are the release steps that I perform to create a release.

1. Make all necessary changes
2. `python scripts/manage_versions.py --bump patch`
3. `pip install .`
4. `cd src_docs && python make_docs.py && cd ..`
5. commit changes
6. `python scripts/manage_versions.py --tag`
7. `git push origin dev --tags`

## FAQ

###
**Q:** ERROR: Could not install packages due to an EnvironmentError

**A:** Remove the `build` directory
## Acknowledgements

I have learned a lot by listening/watching/reading about C++. I can't list them all but the following links had the most influence in developing this repo.

* [Open3D](https://github.com/intel-isl/Open3D) - Much of this repo comes from following their practices.  After having made many C++/Python projects I find this code structure to be the best for hybrid projects.
* [Modern CMake](https://cliutils.gitlab.io/modern-cmake/) - An invaluable resource which has taught me about CMake.
* [Mapbox hpp-skel](https://github.com/mapbox/hpp-skel) - A great starting point for *header-only* libraries. Almost everything MapBox makes is gold to me.
* [Parselmouth](https://github.com/YannickJadoul/Parselmouth) - A great resource on using github workflows!



