// Spark
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef SPARK_VIDEO_MIRENDERER_HPP
#define SPARK_VIDEO_MIRENDERER_HPP

#include <spark/video/IRenderer.hpp>
#include <spark/test/googlemock.hpp>

namespace spark
{
namespace video
{

struct MIRenderer : IRenderer
{
    MOCK_METHOD0(processFrame, void());
};

typedef boost::shared_ptr<MIRenderer> PMIRenderer;

}
}
#endif /* SPARK_VIDEO_MIRENDERER_HPP */
