// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <cstddef>
#include <spark/test/unit/mock/system.hpp>

namespace spark
{
namespace system
{

int gettimeofday(timeval& tv)
{
    return mock::systemMock->gettimeofday(tv);
}

}
}
