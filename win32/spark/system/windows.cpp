// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#include <spark/system/windows.hpp>

namespace spark
{
namespace system
{

DWORD timeGetTime()
{
	return ::timeGetTime();
}

}
}
