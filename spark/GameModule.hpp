// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef SPARK_GAMEMODULE_HPP
#define SPARK_GAMEMODULE_HPP

#include <di/registry.hpp>

namespace spark
{

class GameModule
{
public:
    void operator()(di::registry& r);
};


}
#endif /* SPARK_GAMEMODULE_HPP */
