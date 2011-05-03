// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef SPARK_IO_DISPATCHER_HPP
#define SPARK_IO_DISPATCHER_HPP

#include <boost/shared_ptr.hpp>
#include <spark/io/IDispatcher.hpp>
#include <spark/io/ITimer.hpp>
#include <di/constructor.hpp>

namespace spark
{
namespace io
{

class Dispatcher : public IDispatcher
{
public:
    DI_CONSTRUCTOR(Dispatcher, (PITimer timer)) : timer(timer) { }
    virtual bool processFrame();
private:
    PITimer timer;
};

typedef boost::shared_ptr<Dispatcher> PDispatcher;

}
}
#endif /* SPARK_IO_DISPATCHER_HPP */
