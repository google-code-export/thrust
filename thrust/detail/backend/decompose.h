/*
 *  Copyright 2008-2012 NVIDIA Corporation
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

#pragma once

namespace thrust
{
namespace detail
{
namespace backend
{

  template <typename IndexType>
    class index_range
    {
      public:
        typedef IndexType index_type;

        __host__ __device__
          index_range(index_type begin, index_type end) : m_begin(begin), m_end(end) {}

        __host__ __device__
          index_type begin(void) const { return m_begin; }

        __host__ __device__
          index_type end(void)   const { return m_end; }

        __host__ __device__
          index_type size(void)  const { return m_end - m_begin; }

      private:
        index_type m_begin;
        index_type m_end;
    };

  template <typename IndexType>
    class uniform_decomposition
    {
      public:
        typedef IndexType index_type;

        uniform_decomposition(index_type N, index_type granularity, index_type max_intervals)
        {
          index_type grains = (N + granularity - 1) / granularity;

          if (grains <= max_intervals)
          {
            m_N              = N;
            m_intervals      = grains;
            m_threshold      = 0;
            m_small_interval = granularity;
            m_large_interval = 0;
          }
          else
          {
            m_N              = N;
            m_intervals      = max_intervals;
            m_threshold      = grains % m_intervals;
            m_small_interval = granularity * (grains / m_intervals);
            m_large_interval = m_small_interval + granularity;
          }
        }

        __host__ __device__
          index_range<index_type> operator[](const index_type& i) const
          {
            if (i < m_threshold)
            {
              index_type begin = m_large_interval * i;
              index_type end   = begin + m_large_interval;
              return index_range<index_type>(begin, end);
            }
            else
            {
              index_type begin = m_large_interval * m_threshold + m_small_interval * (i - m_threshold);
              index_type end   = (begin + m_small_interval < m_N) ? begin + m_small_interval : m_N;
              return index_range<index_type>(begin, end);
            }
          }

        __host__ __device__
          index_type size(void) const
          {
            return m_intervals;
          }

      private:

        index_type m_N;
        index_type m_intervals;
        index_type m_threshold;
        index_type m_small_interval;
        index_type m_large_interval;
    };


} // end namespace backend
} // end namespace detail
} // end namespace thrust

