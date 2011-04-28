// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef SPARK_IO_IDISPATCHER_HPP
#define SPARK_IO_IDISPATCHER_HPP

#include <boost/shared_ptr.hpp>

namespace spark
{
namespace io
{

class IDispatcher
{
public:
    virtual ~IDispatcher() { }

    virtual bool processFrame() = 0;
protected:
    IDispatcher& operator=(const IDispatcher& ) { return *this; }
};

typedef boost::shared_ptr<IDispatcher> PIDispatcher;

}
}
#endif /* SPARK_IO_IDISPATCHER_HPP */
