project(spark)

cmake_minimum_required(VERSION 2.8)

include_directories("." "gmock-1.6.0/fused-src" "dicpp/include")

if(UNIX)
    set(CMAKE_CXX_FLAGS "-Wall")
endif(UNIX)

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
)

add_library(
    sparkio STATIC
    spark/io/Dispatcher.cpp
)

add_executable(
    spark_unittest
    spark/test/unit/main.cpp
    spark/test/GoogleTestController.cpp
    spark/test/unit/Game.cpp
    spark/test/unit/io/Dispatcher.cpp
)

add_executable(
    spark
    spark/main.cpp
)

target_link_libraries(spark_unittest sparkcore sparkio gmock dicpp)
target_link_libraries(spark sparkcore sparkio dicpp)

if(UNIX)
    target_link_libraries(spark_unittest pthread)
endif(UNIX)
