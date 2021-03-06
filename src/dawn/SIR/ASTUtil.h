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

#ifndef DAWN_SIR_ASTUTIL_H
#define DAWN_SIR_ASTUTIL_H

#include "dawn/SIR/ASTFwd.h"
#include "dawn/SIR/SIR.h"
#include "dawn/Support/ArrayRef.h"
#include <memory>
#include <unordered_map>

namespace dawn {

/// @brief Replace `oldExpr` with `newExpr` in `stmt`
///
/// Note that `oldExpr` is identfied by its `std::shared_ptr` and not its content. To replace
/// fields or variables in expr see `Optimizer/Replacing.cpp`.
///
/// @param stmt     Statement to analyze
/// @param oldExpr  Expression to replace
/// @param newExpr  Expression to use as a replacement
///
/// @ingroup sir
extern void replaceOldExprWithNewExprInStmt(const std::shared_ptr<Stmt>& stmt,
                                            const std::shared_ptr<Expr>& oldExpr,
                                            const std::shared_ptr<Expr>& newExpr);

/// @brief Replace `oldStmt` with `newStmt` in `stmt`
///
/// Note that `oldStmt` is identfied by its `std::shared_ptr` and not its content.
///
/// @param stmt     Statement to analyze
/// @param oldStmt  Statement to replace
/// @param newStmt  Statement to use as a replacement
///
/// @ingroup sir
extern void replaceOldStmtWithNewStmtInStmt(const std::shared_ptr<Stmt>& stmt,
                                            const std::shared_ptr<Stmt>& oldStmt,
                                            const std::shared_ptr<Stmt>& newStmt);

/// @brief Try to evaluate the expression `expr`
///
/// Expressions can only be evaluated if they consist of unary, binary or ternary operators on
/// literals. Variable accesses (which reference literals or global constants) are only resolved if
/// a map of the value of each variable is provided. The value of these variable is currently
/// supplied as a `double` as this allows us to represent `int`s as well as `bool`s.
///
/// @param expr            Expression to evaluate
/// @param result          Result of the evaulation if successful, unmodified otherwise
/// @param variableMap     Map of variable name to respective value. If empty, no variables are
///                        resolved.
/// @returns `true` if evaluation was successful, `false` otherwise
///
/// @ingroup sir
/// @{
extern bool evalExprAsDouble(const std::shared_ptr<Expr>& expr, double& result,
                             const std::unordered_map<std::string, double>& variableMap =
                                 std::unordered_map<std::string, double>());
extern bool evalExprAsInteger(const std::shared_ptr<Expr>& expr, int& result,
                              const std::unordered_map<std::string, double>& variableMap =
                                  std::unordered_map<std::string, double>());
extern bool evalExprAsBoolean(const std::shared_ptr<Expr>& expr, bool& result,
                              const std::unordered_map<std::string, double>& variableMap =
                                  std::unordered_map<std::string, double>());
/// @}

/// @brief Find all the different fields used in a given statement
///
/// This method iterates trough the complete AST and returns a vector of all the fields used. This
/// can be used to determine if Stencils are legal and for auto generation of new stencils.
///
/// @param ast              AST to evaluate
/// @returns                a Vector of all the Fields used in the stencil
/// @ingroup testing
extern std::vector<sir::Field> getFieldFromStencilAST(const std::shared_ptr<AST>& ast);

class ASTHelper {
public:
  template <typename Container, typename Type>
  static bool replaceOperands(std::shared_ptr<Type> const& oldExpr,
                              std::shared_ptr<Type> const& newExpr, Container& operands) {
    for(int i = 0; i < operands.size(); ++i) {
      if(operands[i] == oldExpr) {
        operands[i] = newExpr;
        return true;
      }
    }
    return false;
  }
};

} // namespace dawn

#endif
