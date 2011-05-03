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
#include <spark/test/unit/io/MITimer.hpp>
#include <boost/make_shared.hpp>

using namespace testing;
using namespace spark;

struct spark_io_Dispatcher : testing::Test
{
    io::PMITimer timer;
    io::Dispatcher dispatcher;

    spark_io_Dispatcher()
        : timer(boost::make_shared<io::MITimer>()),
        dispatcher(timer) { }
};

TEST_F(spark_io_Dispatcher, processFrame)
{
    EXPECT_CALL(*timer, getMillis()).WillOnce(Return(0));
    ASSERT_TRUE(dispatcher.processFrame());

    EXPECT_CALL(*timer, getMillis()).WillOnce(Return(4999));
    ASSERT_TRUE(dispatcher.processFrame());
}

TEST_F(spark_io_Dispatcher, processFrameTimeout)
{
    EXPECT_CALL(*timer, getMillis()).WillOnce(Return(5000));
    ASSERT_FALSE(dispatcher.processFrame());
}