// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef SPARK_IO_MITIMER_HPP
#define SPARK_IO_MITIMER_HPP

#include <spark/io/ITimer.hpp>
#include <spark/test/googlemock.hpp>

namespace spark
{
namespace io
{

struct MITimer : ITimer
{
    MOCK_CONST_METHOD0(getMillis, uint32());
};

typedef boost::shared_ptr<MITimer> PMITimer;

}
}
#endif /* SPARK_IO_MITIMER_HPP */
