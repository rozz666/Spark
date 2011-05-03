// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef SPARK_IO_TIMER_HPP
#define SPARK_IO_TIMER_HPP

#include <boost/shared_ptr.hpp>
#include <spark/system/time.hpp>
#include <spark/stdint.hpp>
#include <spark/io/ITimer.hpp>

namespace spark
{
namespace io
{

class Timer : public ITimer
{
public:

    Timer();
    virtual uint32 getMillis() const;

private:
    timeval start;
};

typedef boost::shared_ptr<Timer> PTimer;

}
}
#endif /* SPARK_IO_TIMER_HPP */
