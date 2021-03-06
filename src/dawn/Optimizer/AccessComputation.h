//===--------------------------------------------------------------------------------*- C++ -*-===//
//                          _
//                         | |
//                       __| | __ ___      ___ ___
//                      / _` |/ _` \ \ /\ / / '_  |
//                     | (_| | (_| |\ V  V /| | | |
//                      \__,_|\__,_| \_/\_/ |_| |_| - Compiler Toolchain
//
//
//  This file is distributed under the MIT License (MIT).
//  See LICENSE.txt for details.
//
//===------------------------------------------------------------------------------------------===//

#ifndef DAWN_OPTIMIZER_ACCESSCOMPUTATION_H
#define DAWN_OPTIMIZER_ACCESSCOMPUTATION_H

#include "dawn/Support/ArrayRef.h"
#include <memory>
#include <vector>

namespace dawn {

class StatementAccessesPair;
class StencilInstantiation;
class StencilFunctionInstantiation;

/// @name Access computation routines
/// @ingroup optimizer
/// @{

/// @fn computeAccesses
/// @brief Compute the Accesses of `statementAccessesPairs`
/// @ingroup optimizer
extern void
computeAccesses(StencilInstantiation* instantiation,
                ArrayRef<std::shared_ptr<StatementAccessesPair>> statementAccessesPairs);

/// @fn computeAccesses
/// @brief Compute the caller and callee Accesses of `statementCallerAccessesPairs`
///
/// The caller Accesses will have the initial offset added (e.g if a stencil function is called with
/// `avg(u(i+1))` the initial offset of `u` is `[1, 0, 0]`) while the callee will not.
///
/// @see StencilFunctionInstantiation
/// @ingroup optimizer
extern void
computeAccesses(std::shared_ptr<StencilFunctionInstantiation> stencilFunctionInstantiation,
                ArrayRef<std::shared_ptr<StatementAccessesPair>> statementAccessesPairs);

/// @}

} // namespace dawn

#endif
