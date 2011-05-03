// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <spark/GameModule.hpp>
#include <spark/Game.hpp>
#include <spark/io/Dispatcher.hpp>
#include <spark/io/Timer.hpp>

namespace spark
{

void GameModule::operator()(di::registry& r)
{
    r.add(
        r.type<Game>()
    );
    r.add(
        r.type<io::IDispatcher>().implementation<io::Dispatcher>()
    );
    r.add(
        r.type<io::ITimer>().implementation<io::Timer>()
    );
}

}
