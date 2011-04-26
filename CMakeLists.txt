project(spark)

cmake_minimum_required(VERSION 2.8)

include_directories("." "gmock-1.6.0/fused-src" "dicpp/include")

if(CMAKE_COMPILER_IS_GNUXX)
    set(CMAKE_CXX_FLAGS "-Wall")
endif(CMAKE_COMPILER_IS_GNUXX)

add_library(
    gmock STATIC
    gmock-1.6.0/fused-src/gmock-gtest-all.cc
)

add_library(
    dicpp STATIC
    dicpp/lib/src/type_info.cpp
    dicpp/lib/src/scope.cpp
    dicpp/lib/src/scopes
    dicpp/lib/src/scopes/thread_local_singleton.cpp
    dicpp/lib/src/scopes/no_scope.cpp
    dicpp/lib/src/scopes/singleton.cpp
    dicpp/lib/src/demangle.cpp
    dicpp/lib/src/registry.cpp
    dicpp/lib/src/empty.cpp
    dicpp/lib/src/type_provider.cpp
)

add_executable(
    spark_unittest
    spark/test/unit/main.cpp
    spark/test/GoogleTestController.cpp
)

target_link_libraries(spark_unittest gmock dicpp)
