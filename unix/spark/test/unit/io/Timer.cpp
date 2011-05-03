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

    void testTimer(unsigned sec1, unsigned usec1, unsigned sec2, unsigned usec2, uint32 result)
    {
        timeval time1 = { sec1, usec1 };
        timeval time2 = { sec2, usec2 };
        {
            InSequence seq;
            EXPECT_CALL(*mock::systemMock, gettimeofday(_)).WillOnce(DoAll(SetArgReferee<0>(time1), Return(0)));
            EXPECT_CALL(*mock::systemMock, gettimeofday(_)).WillOnce(DoAll(SetArgReferee<0>(time2), Return(0)));
        }
        io::Timer timer;
        ASSERT_EQ(result, timer.getMillis());
    }
};

TEST_F(spark_io_Timer, constructor)
{
    EXPECT_CALL(*mock::systemMock, gettimeofday(_)).WillOnce(Return(0));
    io::Timer timer;
}

TEST_F(spark_io_Timer, getMillis)
{
    ASSERT_NO_FATAL_FAILURE(testTimer(0, 0, 0, 0, 0));
    ASSERT_NO_FATAL_FAILURE(testTimer(0, 0, 1, 0, 1000));
    ASSERT_NO_FATAL_FAILURE(testTimer(358624357, 0, 358624358, 0, 1000));
    ASSERT_NO_FATAL_FAILURE(testTimer(0, 1000, 0, 1999, 0));
    ASSERT_NO_FATAL_FAILURE(testTimer(0, 1000, 0, 2000, 1));
    ASSERT_NO_FATAL_FAILURE(testTimer(0, 1999, 0, 2000, 0));
    ASSERT_NO_FATAL_FAILURE(testTimer(0, 999999, 1, 0, 0));
}
