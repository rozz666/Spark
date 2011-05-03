// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <spark/io/Timer.hpp>
#include <spark/test/googlemock.hpp>
#include <spark/test/unit/mock/system.hpp>

using namespace testing;
using namespace spark;

struct spark_io_Timer : testing::Test
{
    virtual void SetUp()
    {
        mock::resetSystemMock();
    }

    virtual void TearDown()
    {
        mock::verifySystemMock();
    }

    void testTimer(uint32 msec1, uint32 msec2, uint32 result)
    {
        {
            InSequence seq;
            EXPECT_CALL(*mock::systemMock, timeGetTime()).WillOnce(Return(msec1));
            EXPECT_CALL(*mock::systemMock, timeGetTime()).WillOnce(Return(msec2));
        }
        io::Timer timer;
        ASSERT_EQ(result, timer.getMillis());
    }
};

TEST_F(spark_io_Timer, constructor)
{
    EXPECT_CALL(*mock::systemMock, timeGetTime());
    io::Timer timer;
}

TEST_F(spark_io_Timer, getMillis)
{
    ASSERT_NO_FATAL_FAILURE(testTimer(0, 0, 0));
    ASSERT_NO_FATAL_FAILURE(testTimer(0, 1, 1));
    ASSERT_NO_FATAL_FAILURE(testTimer(99, 100, 1));
}
