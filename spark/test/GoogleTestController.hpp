// GameScript
//
// Copyright (c) 2011 Rafal Przywarski
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef GTESTCONTROLLER_H
#define GTESTCONTROLLER_H

#include <sstream>
#include <iostream>
#include <gtest/gtest.h>

namespace spark
{
namespace test
{

class GoogleTestController : public testing::EmptyTestEventListener
{
public:

    GoogleTestController();

    virtual void OnTestProgramStart(const testing::UnitTest& );
    virtual void OnTestCaseStart(const testing::TestCase& );
    virtual void OnTestStart(const testing::TestInfo& );
    virtual void OnTestEnd(const testing::TestInfo& );
    virtual void OnTestProgramEnd(const testing::UnitTest& );

private:

    std::string currentSuite_;
    std::ostringstream filter_;
    std::ostringstream output_;
    std::ostringstream errors_;
    int ok_, failed_, crashed_;

    template <typename T>
    GoogleTestController& print(T x)
    {
        output_ << x;
        std::cout << x;
        return *this;
    }

    void flush()
    {
        std::cout.flush();
    }

    void loadState();
    void saveState(const std::string& currentSuite, const std::string currentTest);
    void writeString(const std::string& s, FILE *f);
    std::string readString(FILE *f);
    bool validFile(FILE *f);
    static std::string prettyName(std::string name);
};

}
}

#endif // GTESTCONTROLLER_H
