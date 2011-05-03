// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef SPARK_GAME_HPP
#define SPARK_GAME_HPP

#include <boost/shared_ptr.hpp>
#include <di/constructor.hpp>
#include <spark/io/IDispatcher.hpp>
#include <spark/video/IRenderer.hpp>

namespace spark
{

class Game
{
public:

    DI_CONSTRUCTOR(Game, (io::PIDispatcher dispatcher, video::PIRenderer renderer))
        : dispatcher(dispatcher), renderer(renderer) { }

    void run();

private:

    io::PIDispatcher dispatcher;
    video::PIRenderer renderer;
};

typedef boost::shared_ptr<Game> PGame;

}
#endif /* SPARK_GAME_HPP */
