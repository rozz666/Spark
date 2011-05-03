// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef SPARK_VIDEO_IRENDERER_HPP
#define SPARK_VIDEO_IRENDERER_HPP

#include <boost/shared_ptr.hpp>

namespace spark
{
namespace video
{

class IRenderer
{
public:
    virtual ~IRenderer() { }
    virtual void processFrame() = 0;
protected:
    IRenderer& operator=(const IRenderer& ) { return *this; }
};

typedef boost::shared_ptr<IRenderer> PIRenderer;

}
}
#endif /* SPARK_VIDEO_IRENDERER_HPP */
