## General ##
  * What is Thrust?
    * Thrust is a C++ template library for CUDA.  Thrust allows you to program GPUs using an interface similar the C++ Standard Template Library (STL).
  * What is a C++ template library?
    * C++ templates are a way to write generic algorithms and data structures.  A template library is simply a cohesive collection of such algorithms and data structures in a single package.
  * How can I contribute to Thrust?
    * There are many ways! Please refer to [Contributing](Contributing.md) for some ideas.
  * How do I cite Thrust in papers and other publications?
    * Please refer to the page on [Citing](Citing.md).
  * Do I need to build Thrust?
    * No. Since Thrust is a template library you just `#include` the appropriate header files into your `.cu` file and compile with `nvcc`.
  * What data structures does Thrust provide?
    * Currently Thrust provides `thrust::host_vector` and `thrust::device_vector`, which are analogous to `std::vector` in the STL and reside in the host/device memory.  These vector data structures simplify memory management and transferring data between the host and device.
  * What algorithms does Thrust provide?
    * sorting: `thrust::sort` and `thrust::sort_by_key`
    * tranformations: `thrust::transform`
    * reductions: `thrust::reduce` and `thrust::transform_reduce`
    * scans: `thrust::inclusive_scan`, `thrust::exclusive_scan`, `thrust::transform_inclusive_scan`, etc.
    * Refer to [Documentation](Documentation.md) for a complete listing
  * What version of CUDA do I need to develop applications with Thrust?
    * The latest version of Thrust requires [CUDA 4.0](http://www.nvidia.com/object/cuda_get.html) or newer.
  * What platforms does Thrust support?
    * Thrust has been tested extensively on Linux, Windows and MacOSX systems.  Refer to the ReleaseChecklist for a complete list.
  * When will Thrust support OpenCL?
    * The primary barrier to OpenCL support is the lack of an OpenCL compiler and runtime with support for C++ templates (e.g. something similar to `nvcc` and the CUDA Runtime).  These features are necessary to achieve close coupling of the host and device codes.
  * Does Thrust depend on any other libraries?
    * No, Thrust is self-contained and requires no additional libraries.
  * Can I distribute Thrust with my application?
    * Yes!  Thrust is open-source software released under liberal licensing terms.
  * What open-source license does Thrust use?
    * Thrust is licensed under the [Apache License v2.0](http://www.opensource.org/licenses/apache2.0.php)
  * How do I run the unit tests and performance tests for Thrust?
    * Refer to the [DeveloperInfo](DeveloperInfo.md) page.

## Functionality ##
  * Can I create a `thrust::device_vector` from memory I've allocated myself?
    * No.  Instead, wrap your externally allocated raw pointer with `thrust::device_ptr` and pass it to Thrust algorithms. [[example](http://code.google.com/p/thrust/source/browse/examples/cuda/wrap_pointer.cu)].
  * How do I find the array _index_ of the element with the maximum/minumum value?
    * Use `thrust::max_element()` or `thrust::min_element()`, which are found in the file `<thrust/extrema.h>` [[more info](http://thrust.googlecode.com/svn/tags/1.2.0/doc/html/group__extrema.html)].
  * How do I obtain a raw pointer (e.g. `int * ptr`) from a `device_vector`?
    * Use `thrust::raw_pointer_cast(&my_vector[0])` [[example](http://code.google.com/p/thrust/source/browse/examples/cuda/unwrap_pointer.cu)].
  * Can I call Thrust algorithms inside a CUDA kernel?
    * No, it is not currently possible to call Thrust algorithms inside a `__global__` or `__device__` function.
  * Can I call Thrust algorithms from CUDA Fortran?
    * Yes!  For example, this [example](http://cudamusing.blogspot.com/2011/06/calling-thrust-from-cuda-fortran.html) shows how to call Thrust's `sort` algorithm from Fortran.

## Troubleshooting ##

  * Make sure you are using CUDA 3.0 or greater (CUDA 4.0 is highly recommended):
    * run `nvcc --version`
  * Make sure you're compiling files that `#include` Thrust with `nvcc`.
  * Make sure that files that `#include` Thrust have a `.cu` extension. Other extensions (e.g.`.cpp`) will cause `nvcc` to treat the file incorrectly and produce an error message.
  * If all else fails, send a message to [thrust-users](http://groups.google.com/group/thrust-users) and we'll do our best to assist you.