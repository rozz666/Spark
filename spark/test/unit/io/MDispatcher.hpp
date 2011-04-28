// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef SPARK_IO_MDISPATCHER_HPP
#define SPARK_IO_MDISPATCHER_HPP

#include <spark/io/IDispatcher.hpp>
#include <spark/test/googlemock.hpp>

namespace spark
{
namespace io
{

struct MDispatcher : IDispatcher
{
    MOCK_METHOD0(processFrame, bool());
};

typedef boost::shared_ptr<MDispatcher> PMDispatcher;

}
}
#endif /* SPARK_IO_MDISPATCHER_HPP */
