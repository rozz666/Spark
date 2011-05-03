// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef SPARK_IO_ITIMER_HPP
#define SPARK_IO_ITIMER_HPP

#include <boost/shared_ptr.hpp>
#include <spark/stdint.hpp>

namespace spark
{
namespace io
{

class ITimer
{
public:
    virtual ~ITimer() { }
    virtual uint32 getMillis() const = 0;
protected:
    ITimer& operator=(const ITimer& ) { return *this; }
};

typedef boost::shared_ptr<ITimer> PITimer;

}
}
#endif /* SPARK_IO_ITIMER_HPP */
