// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <spark/test/GoogleTestController.hpp>
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::UnitTest& unitTest = *testing::UnitTest::GetInstance();
    testing::TestEventListeners& listeners = unitTest.listeners();
    delete listeners.Release(listeners.default_result_printer());
    listeners.Append(new spark::test::GoogleTestController);
    return RUN_ALL_TESTS();
}
