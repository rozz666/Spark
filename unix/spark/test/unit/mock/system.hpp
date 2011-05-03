// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef SPARK_MOCK_SYSTEM_HPP
#define SPARK_MOCK_SYSTEM_HPP

#include <spark/system/time.hpp>
#include <spark/test/googlemock.hpp>
#include <boost/scoped_ptr.hpp>

namespace spark
{
namespace mock
{

struct System
{
    MOCK_METHOD1(gettimeofday, int(timeval& ));
};

extern boost::scoped_ptr<System> systemMock;

void resetSystemMock();
void verifySystemMock();

}
}
#endif // SPARK_MOCK_SYSTEM_HPP