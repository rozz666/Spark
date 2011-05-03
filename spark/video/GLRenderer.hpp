// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef SPARK_VIDEO_GLRENDERER_HPP
#define SPARK_VIDEO_GLRENDERER_HPP

#include <boost/shared_ptr.hpp>
#include <spark/video/IRenderer.hpp>

namespace spark
{
namespace video
{

class GLRenderer : public IRenderer
{
public:

    virtual void processFrame();
};

typedef boost::shared_ptr<GLRenderer> PGLRenderer;

}
}
#endif /* SPARK_VIDEO_GLRENDERER_HPP */
