// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <spark/Game.hpp>
#include <di/injector.hpp>
#include <exception>
#include <sstream>
#include <typeinfo>
#include <iostream>
#include <spark/io/Dispatcher.hpp>


namespace spark
{

void reportException(const std::exception& e)
{
    std::ostringstream os;
    os << "An internal exception of type " << typeid(e).name() << " has occured:\n" << e.what();
#ifdef _WIN32
    MessageBoxA(0, os.str().c_str(), "Exception", MB_ICONERROR | MB_YESNO | MB_DEFBUTTON2) == IDYES);
#else // _WIN32
    std::cerr << os.str();
#endif // _WIN32
}

void reportUnknownException()
{
    const char *msg = "An internal exception of unknown type has occured!";
#ifdef _WIN32
    MessageBoxA(0, msg, "Exception", MB_ICONERROR | MB_YESNO | MB_DEFBUTTON2) == IDYES);
#else // _WIN32
    std::cerr << msg;
#endif // _WIN32
}

struct GameModule
{
    void operator()(di::registry& r)
    {
        r.add(
            r.type<Game>()
        );
        r.add(
            r.type<io::IDispatcher>().implementation<io::Dispatcher>()
        );
    }
};

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

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    spark::runGame();
    return 0;
}
#else // _WIN32
int main()
{
    spark::runGame();
}
#endif // _WIN32