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
#include <sstream>
#include <windows.h>


namespace spark
{

void reportException(const std::exception& e)
{
    std::ostringstream os;
    os << "An internal exception of type " << typeid(e).name() << " has occured:\n" << e.what();
    MessageBoxA(0, os.str().c_str(), "Exception", MB_ICONERROR | MB_YESNO | MB_DEFBUTTON2);
}

void reportUnknownException()
{
    MessageBoxA(
        0, "An internal exception of unknown type has occured!", "Exception", MB_ICONERROR | MB_YESNO | MB_DEFBUTTON2);
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

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    spark::runGame();
    return 0;
}
