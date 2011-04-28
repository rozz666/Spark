// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <spark/Game.hpp>
#include <spark/test/googlemock.hpp>

using namespace testing;
using namespace spark;

struct spark_Game : testing::Test
{
    Game game;
};

TEST_F(spark_Game, run)
{
    game.run();
}
