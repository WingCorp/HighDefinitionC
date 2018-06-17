#ifndef FOLD_H
#define FOLD_H

/**
 * @brief The 'fold' monad, as known from FP.
 * 
 * @file fold.h
 * @author WingCorp
 * @date 2018-06-16
 */

#include "./../dynamic/dynamic.h"
#include "./../iterator/iterator.h"

/**
 * @brief Folds over every entry in the iterator.
 * 
 * @param iterator the iterator to fold over..
 * @param initialState the initial state to fold onto.
 * @param folder the folder function with the signature Dynamic folder(Dynamic acc, Dynamic i)
 * @return Dynamic the final state.
 */
Dynamic fold(Iterator* iterator, Dynamic initialState, Dynamic (*folder) (Dynamic, Dynamic));

#endif
