//===--------------------------------------------------------------------------------*- C++ -*-===//
//                         _       _
//                        | |     | |
//                    __ _| |_ ___| | __ _ _ __   __ _
//                   / _` | __/ __| |/ _` | '_ \ / _` |
//                  | (_| | || (__| | (_| | | | | (_| |
//                   \__, |\__\___|_|\__,_|_| |_|\__, | - GridTools Clang DSL
//                    __/ |                       __/ |
//                   |___/                       |___/
//
//
//  This file is distributed under the MIT License (MIT).
//  See LICENSE.txt for details.
//
//===------------------------------------------------------------------------------------------===//

#include "gridtools/clang_dsl.hpp"

using namespace gridtools::clang;

stencil compute_extent_test_stencil {
  storage u, out, coeff;

  var flx, fly, lap;
  Do {
    vertical_region(k_start, k_end) {
      lap = u[i + 1] + u[i - 1] + u[j + 1] + u[j - 1] - 4.0 * u;
      if (flx * (u[i+1] - u) > 0)
        flx = 0.;
      else
        flx = lap[i+1] - lap;

      if (fly * (u[j+1] - u) > 0)
      	fly = 0.;
      else 
        fly = lap[j+1] - lap;
      out = u - coeff * (flx - flx[i-1] + fly - fly[j-1]);
    }
  }
};
