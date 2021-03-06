
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
// Copyright (c) 2014 Francois Beaune, The appleseedhq Organization
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// appleseed.foundation headers.
#include "foundation/math/permutation.h"
#include "foundation/math/primes.h"
#include "foundation/math/qmc.h"
#include "foundation/math/vector.h"
#include "foundation/utility/benchmark.h"

// Standard headers.
#include <cstddef>

using namespace foundation;

BENCHMARK_SUITE(Foundation_Math_QMC)
{
    template <typename T>
    struct ScalarFixture
    {
        T m_x;

        void radical_inverse_base2_payload()
        {
            m_x = T(0.0);

            for (size_t i = 0; i < 128; ++i)
                m_x += radical_inverse_base2<T>(i);
        }

        void radical_inverse_payload()
        {
            m_x = T(0.0);

            for (size_t s = 0, d = 1; d <= 32; ++d)
            {
                for (size_t i = 0; i < 4; ++i, ++s)
                {
                    m_x +=
                        radical_inverse<T>(
                            Primes[d],
                            s);
                }
            }
        }

        void fast_radical_inverse_payload()
        {
            m_x = T(0.0);

            for (size_t s = 0, d = 1; d <= 32; ++d)
            {
                for (size_t i = 0; i < 4; ++i, ++s)
                {
                    m_x +=
                        fast_radical_inverse<T>(
                            d,
                            s);
                }
            }
        }

        void permuted_radical_inverse_payload()
        {
            m_x = T(0.0);

            for (size_t s = 0, d = 1; d <= 32; ++d)
            {
                for (size_t i = 0; i < 4; ++i, ++s)
                {
                    m_x +=
                        permuted_radical_inverse<T>(
                            Primes[d],
                            FaurePermutations[d],
                            s);
                }
            }
        }

        void fast_permuted_radical_inverse_payload()
        {
            m_x = T(0.0);

            for (size_t s = 0, d = 1; d <= 32; ++d)
            {
                for (size_t i = 0; i < 4; ++i, ++s)
                {
                    m_x +=
                        fast_permuted_radical_inverse<T>(
                            d,
                            FaurePermutations[d],
                            s);
                }
            }
        }
    };

    template <typename T>
    struct Vector2Fixture
    {
        Vector<T, 2> m_x;

        void halton_payload()
        {
            static const size_t Bases[] = { 2, 3 };

            m_x = Vector<T, 2>(0.0f);

            for (size_t i = 0; i < 64; ++i)
                m_x += halton_sequence<T, 2>(Bases, i);
        }

        void hammersley_payload()
        {
            static const size_t Bases[] = { 2 };

            m_x = Vector<T, 2>(0.0f);

            for (size_t i = 0; i < 64; ++i)
                m_x += hammersley_sequence<T, 2>(Bases, i, 64);
        }
    };

    // Radical inverse, single precision.

    BENCHMARK_CASE_F(RadicalInverseBase2_SinglePrecision, ScalarFixture<float>)
    {
        radical_inverse_base2_payload();
    }

    BENCHMARK_CASE_F(RadicalInverse_SinglePrecision, ScalarFixture<float>)
    {
        radical_inverse_payload();
    }

    BENCHMARK_CASE_F(FastRadicalInverse_SinglePrecision, ScalarFixture<float>)
    {
        fast_radical_inverse_payload();
    }

    BENCHMARK_CASE_F(PermutedRadicalInverse_SinglePrecision, ScalarFixture<float>)
    {
        permuted_radical_inverse_payload();
    }

    BENCHMARK_CASE_F(FastPermutedRadicalInverse_SinglePrecision, ScalarFixture<float>)
    {
        fast_permuted_radical_inverse_payload();
    }

    // Radical inverse, double precision.

    BENCHMARK_CASE_F(RadicalInverseBase2_DoublePrecision, ScalarFixture<double>)
    {
        radical_inverse_base2_payload();
    }

    BENCHMARK_CASE_F(RadicalInverse_DoublePrecision, ScalarFixture<double>)
    {
        radical_inverse_payload();
    }

    BENCHMARK_CASE_F(FastRadicalInverse_DoublePrecision, ScalarFixture<double>)
    {
        fast_radical_inverse_payload();
    }

    BENCHMARK_CASE_F(PermutedRadicalInverse_DoublePrecision, ScalarFixture<double>)
    {
        permuted_radical_inverse_payload();
    }

    BENCHMARK_CASE_F(FastPermutedRadicalInverse_DoublePrecision, ScalarFixture<double>)
    {
        fast_permuted_radical_inverse_payload();
    }

    // Halton sequence.

    BENCHMARK_CASE_F(HaltonSequence_Bases2And3_SinglePrecision, Vector2Fixture<float>)
    {
        halton_payload();
    }

    BENCHMARK_CASE_F(HaltonSequence_Bases2And3_DoublePrecision, Vector2Fixture<double>)
    {
        halton_payload();
    }

    // Hammersley sequence.

    BENCHMARK_CASE_F(HammersleySequence_Base2_SinglePrecision, Vector2Fixture<float>)
    {
        hammersley_payload();
    }

    BENCHMARK_CASE_F(HammersleySequence_Base2_DoublePrecision, Vector2Fixture<double>)
    {
        hammersley_payload();
    }
}
