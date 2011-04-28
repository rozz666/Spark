// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <spark/io/Dispatcher.hpp>
#include <spark/test/googlemock.hpp>

using namespace testing;
using namespace spark;

struct spark_io_Dispatcher : testing::Test
{
    io::Dispatcher dispatcher;
};

TEST_F(spark_io_Dispatcher, processFrame)
{
}
