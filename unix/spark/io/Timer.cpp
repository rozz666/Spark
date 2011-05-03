// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <spark/io/Timer.hpp>

namespace spark
{
namespace io
{

Timer::Timer()
{
    system::gettimeofday(start);
}

uint32 Timer::getMillis() const
{
    timeval time;
    system::gettimeofday(time);

    return uint32((uint64(time.tv_sec - start.tv_sec) * 1000000u + time.tv_usec - start.tv_usec) / 1000u);
}

}
}
