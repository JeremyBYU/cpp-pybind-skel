.. CPPLib documentation master file, created by
   sphinx-quickstart on Mon Apr  3 14:18:28 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.
   NOTE: The python modules documentation for PURE python modules must be explicitly annotated with meta data. See below Line 51.

.. image:: _static/logo_1.png
    :alt: CPPLib Logo
    :width: 320px
    :align: center

-----------

CPPLib: A Great CPPLib
===============================================

.. only: not latex

    Contents:

.. toctree::
    :maxdepth: 1
    :caption: Getting Started

    introduction
    builddocs


.. _tutorial_index:

.. toctree::
    :maxdepth: 1
    :caption: Tutorial

    tutorial/Python/index
    tutorial/C++/index

.. _python_api_index:

.. toctree::
    :maxdepth: 1
    :caption: Python API

    python_api/cpplib
    python_api/cpplib.helper

..
    This is a comment. Please duplicate the module and meta data you want here!
    Meta data can be a string at the end that says python_only. To be used for pure python module (no pybind).
    MAKE_DOCS/python_api/cpplib
    MAKE_DOCS/python_api/cpplib.helper python_only

.. _cpp_api_index:

.. toctree::
    :maxdepth: 1
    :caption: C++ API

    cpp_api/cpp_library_root
