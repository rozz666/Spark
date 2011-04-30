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
#include <di/injector.hpp>
#include <exception>
#include <typeinfo>
#include <iostream>


namespace spark
{

void reportException(const std::exception& e)
{
    std::cerr << "An internal exception of type " << typeid(e).name() << " has occured:\n" << e.what();
}

void reportUnknownException()
{
    std::cerr << "An internal exception of unknown type has occured!";
}

void runGame()
{
    try
    {
        di::injector injector;
        injector.install(GameModule());
        PGame game = injector.construct<PGame>();
        game->run();
    }
    catch (const std::exception& e)
    {
        reportException(e);
    }
    catch (...)
    {
        reportUnknownException();
    }
}

}

int main()
{
    spark::runGame();
}
