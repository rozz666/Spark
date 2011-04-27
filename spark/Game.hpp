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

namespace spark
{

class Game
{
public:

    void run();
};

typedef boost::shared_ptr<Game> SharedGame;

}
#endif /* SPARK_GAME_HPP */
