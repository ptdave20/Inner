//
// Created by ptdave on 3/18/17.
//

#include "Inner.h"

#ifndef INNER_TYPEDEFS_H
#define INNER_TYPEDEFS_H

template<class T>
class UpdateFunction : public std::function<void(T,const float&)> {};


template<class T>
class LogicFunction : public std::function<void(T,const float&)> {};



#endif //INNER_TYPEDEFS_H
