/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Christian Schulte <schulte@gecode.org>
 *     Mikael Lagerkvist <lagerkvist@gecode.org>
 *
 *  Copyright:
 *     Christian Schulte, 2005
 *     Mikael Lagerkvist, 2005
 *
 *  Last modified:
 *     $Date$ by $Author$
 *     $Revision$
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  "Software"), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef __GECODE_SUPPORT_RANDOM_HH__
#define __GECODE_SUPPORT_RANDOM_HH__

#define GECODE_RAND_MAX

namespace Gecode { namespace Support {

  /** \brief Template for linear congruential generators.
   *
   * This class template defines a simple class for linear
   * congruential generators.
   *
   * The values used for calculation shouldbe specified so that
   *
   * Requires \code #include "gecode/support/random.hh" \endcode
   * \ingroup FuncSupport
   */
  template<unsigned int m, unsigned int a, unsigned int q, unsigned int r>
  class LinearCongruentialGenerator {
    int s;
    unsigned int next() {
      s = a*(s%q) - r*(s/q);
      if (s<0) s += m;
      int res = s;
      if (s==0) s = 1;
      return res;
    }
  public:
    // The maximum size of random numbers generated.
    const unsigned long rand_max;

    /// Construct the generator instance.
    LinearCongruentialGenerator(int _seed = 1)
      : rand_max(1UL<<31) {
      seed(_seed);
    }
    /// Set the current seed
    void seed(unsigned int _seed) {
      s = _seed % m;
      if (s == 0) s = 1;
    }
    /// Get the current seed
    unsigned int seed(void) const {
      return s;
    }
    /// Returns a reandom integer from the interval [0..n)
    unsigned int operator()(unsigned int n) {
      unsigned long x1 = next() & ((1<<16)-1);
      unsigned long x2 = next() & ((1<<16)-1);
      if (n < 2) return 0;
      double d = static_cast<double>(((x1<<16) | x2)%rand_max) / rand_max;
      int val = static_cast<int>(n * d);
      return (val < static_cast<int>(n)) ? val : (n-1);
    }
  };


  /** \brief Default choice of values for the linear congruential
   * generator.
   *
   * While this pseudo-random number generator is not a good source of
   * randomness, it is still an acceptable choice for many
   * applications. The choice of values is taken from D. E. Knuth,
   * The Art of Computer Programming, Vol 2, Seminumerical Algorithms,
   * 3rd edition.
   *
   * Requires \code #include "gecode/support/random.hh" \endcode
   * \ingroup FuncSupport
   */
  typedef LinearCongruentialGenerator<2147483647, 48271, 44488, 3399>
  RandomGenerator;

}}

#endif /* __GECODE_SUPPORT_RANDOM_HH__ */

// STATISTICS: support-any
