/*
 *  Copyright 2008-2011 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/*! \file cpp/memory.h
 *  \brief Classes for managing C++-typed memory.
 */

#pragma once

#include <thrust/detail/config.h>
#include <thrust/detail/pointer_base.h>
#include <thrust/detail/reference_base.h>
#include <thrust/detail/type_traits.h>
#include <ostream>

namespace thrust
{
// put the canonical tag in the same ns as the backend's entry points
// XXX cpp's entry points should be under system, not backend
namespace detail
{
namespace backend
{
namespace cpp
{

struct tag {};

} // end cpp
} // end backend
} // end detail

namespace system
{
namespace cpp
{

// alias cpp's tag here
using thrust::detail::backend::cpp::tag;

// forward declaration of reference for pointer
template<typename Element> class reference;

template<typename T>
  class pointer
    : public thrust::detail::pointer_base<
               thrust::cpp::pointer<T>,
               T,
               thrust::cpp::reference<T>,
               thrust::cpp::tag
             >
{
  private:
    typedef thrust::detail::pointer_base<
      thrust::cpp::pointer<T>,
      T,
      thrust::cpp::reference<T>,
      thrust::cpp::tag
    > super_t;

  public:
    // XXX doxygenate these

    // note that cpp::pointer's member functions need __host__ __device__
    // to interoperate with nvcc + thrust::detail::dereference

    __host__ __device__
    pointer() : super_t() {}

    template<typename OtherT>
    __host__ __device__
    explicit pointer(OtherT *ptr) : super_t(ptr) {}

    template<typename OtherT>
    __host__ __deivce__
    pointer &operator=(const pointer<OtherT> &other) : super_t(other) {}

    template<typename OtherT>
    __host__ __device__
    pointer &operator=(const pointer<OtherT> &other)
    {
      return super_t::operator=(other);
    }
}; // end pointer


template<typename T>
  class reference
    : public thrust::detail::reference_base<
               thrust::cpp::reference<T>,
               T,
               thrust::cpp::pointer<T>
             >
{
  private:
    typedef thrust::detail::reference_base<
      thrust::cpp::reference<T>,
      T,
      thrust::cpp::pointer<T>
    > super_t;

  public:
    typedef typename super_t::value_type value_type;
    typedef typename super_t::pointer    pointer;

    template<typename OtherT>
    __host__ __device__
    reference(const reference<OtherT> &other,
              typename thrust::detail::enable_if_convertible<
                typename reference<OtherT>::pointer,
                pointer
              >::type * = 0)
      : super_t(other)
    {}

    __host__ __device__
    explicit reference(const pointer &ptr)
      : super_t(ptr)
    {}

    template<typename OtherT>
    reference &operator=(const reference<OtherT> &other);

    reference &operator=(const value_type &x);
}; // end reference

template<typename T>
__host__ __device__
void swap(reference<T> &x, reference<T> &y);

} // end cpp
} // end system

// alias system::cpp names at top-level
namespace cpp
{

using thrust::system::cpp::tag;
using thrust::system::cpp::pointer;
using thrust::system::cpp::reference;

} // end cpp

} // end thrust

#include <thrust/system/cpp/detail/memory.inl>


