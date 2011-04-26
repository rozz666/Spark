// GameScript
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef SPARK_TEST_DEFAULTVALUES_HPP
#define SPARK_TEST_DEFAULTVALUES_HPP
#include <gmock/gmock.h>
#include <boost/shared_ptr.hpp>

namespace testing
{

template <typename T>
class DefaultValue<boost::shared_ptr<T> >
{
public:

    typedef boost::shared_ptr<T> Type;

    static bool IsSet() { return true; }
    static bool Exists() { return IsSet(); }
    static Type Get() { return Type(); }
};

}

#endif /* SPARK_TEST_DEFAULTVALUES_HPP */
