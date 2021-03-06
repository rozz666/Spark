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
#include <spark/test/unit/io/MIDispatcher.hpp>
#include <boost/make_shared.hpp>
#include <spark/test/unit/video/MIRenderer.hpp>

using namespace testing;
using namespace spark;

struct spark_Game : testing::Test
{
    io::PMIDispatcher inputDispatcher;
    video::PMIRenderer renderer;
    Game game;

    spark_Game()
        : inputDispatcher(boost::make_shared<io::MIDispatcher>()),
        renderer(boost::make_shared<video::MIRenderer>()),
        game(inputDispatcher, renderer) { }
};

TEST_F(spark_Game, runOneFrame)
{
    EXPECT_CALL(*inputDispatcher, processFrame()).WillOnce(Return(false));
    game.run();
}

TEST_F(spark_Game, runManyFrames)
{
    {
        InSequence seq;
        EXPECT_CALL(*inputDispatcher, processFrame()).WillOnce(Return(true));
        EXPECT_CALL(*renderer, processFrame());
        EXPECT_CALL(*inputDispatcher, processFrame()).WillOnce(Return(true));
        EXPECT_CALL(*renderer, processFrame());
        EXPECT_CALL(*inputDispatcher, processFrame()).WillOnce(Return(false));
    }
    game.run();
}
