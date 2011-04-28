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

namespace spark
{

class Game
{
public:

    DI_CONSTRUCTOR(Game, (io::PIDispatcher dispatcher))
        : dispatcher(dispatcher) { }

    void run();

private:

    io::PIDispatcher dispatcher;
};

typedef boost::shared_ptr<Game> PGame;

}
#endif /* SPARK_GAME_HPP */
