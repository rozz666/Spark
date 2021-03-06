project(spark)

cmake_minimum_required(VERSION 2.8)

if(UNIX)
    set(CMAKE_CXX_FLAGS "-Wall")
    set(OS_NAME "unix")
elseif(WIN32)
    set(OS_NAME "win32")
endif(UNIX)

include_directories("." ${OS_NAME} "gmock-1.6.0/fused-src" "dicpp/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDI_DISABLE_LOGGING")

add_library(
    gmock STATIC
    gmock-1.6.0/fused-src/gmock-gtest-all.cc
)

add_library(
    dicpp STATIC
    dicpp/lib/src/type_info.cpp
    dicpp/lib/src/scope.cpp
    dicpp/lib/src/scopes/thread_local_singleton.cpp
    dicpp/lib/src/scopes/no_scope.cpp
    dicpp/lib/src/scopes/singleton.cpp
    dicpp/lib/src/demangle.cpp
    dicpp/lib/src/registry.cpp
    dicpp/lib/src/empty.cpp
    dicpp/lib/src/type_provider.cpp
)

add_library(
    sparkcore STATIC
    spark/Game.cpp
    spark/GameModule.cpp
)

add_library(
    sparkio STATIC
    spark/io/Dispatcher.cpp
    ${OS_NAME}/spark/io/Timer.cpp
)

add_library(
    sparkvideo STATIC
    spark/video/GLRenderer.cpp
)

if(UNIX)
    add_library(sparksystem STATIC
        unix/spark/system/time.cpp
    )
    add_library(sparksystemmock STATIC
        unix/spark/test/unit/mock/system/time.cpp
        unix/spark/test/unit/mock/system.cpp
    )
    set(OS_SPECIFIC_UNITTESTS
        unix/spark/test/unit/io/Timer.cpp
    )
elseif(WIN32)
    add_library(sparksystem STATIC
        win32/spark/system/windows.cpp
    )
    add_library(sparksystemmock STATIC
        win32/spark/test/unit/mock/system/windows.cpp
        win32/spark/test/unit/mock/system.cpp
    )
    set(OS_SPECIFIC_UNITTESTS
        win32/spark/test/unit/io/Timer.cpp
    )
endif(UNIX)

add_executable(
    spark_unittest
    spark/test/unit/main.cpp
    spark/test/GoogleTestController.cpp
    spark/test/unit/Game.cpp
    spark/test/unit/io/Dispatcher.cpp
    spark/test/unit/video/GLRenderer.cpp
    ${OS_SPECIFIC_UNITTESTS}
)

if(WIN32)
    add_executable(spark WIN32 win32/spark/main.cpp)
else(WIN32)
    add_executable(spark unix/spark/main.cpp)
endif(WIN32)

target_link_libraries(spark_unittest sparkcore sparkio sparkvideo sparksystemmock gmock dicpp)
target_link_libraries(spark sparkcore sparkio sparkvideo sparksystem dicpp)

if(UNIX)
    target_link_libraries(spark_unittest pthread)
elseif(WIN32)
    target_link_libraries(spark winmm)
endif(UNIX)
