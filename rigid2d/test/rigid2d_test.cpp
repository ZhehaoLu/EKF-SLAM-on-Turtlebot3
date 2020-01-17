// Created by Shangzhou Ye, MSR, Northwestern University

#include <gtest/gtest.h>
#include "rigid2d/rigid2d.hpp"
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

TEST(Rigid2dTest, TransformationOperator)
{
    rigid2d::Vector2D translation;
    translation.x = 0;
    translation.y = -1;
    rigid2d::Transform2D trans_test(translation, -(rigid2d::PI / 2.0));

    rigid2d::Vector2D vect_test;
    vect_test.x = 1;
    vect_test.y = 1;

    rigid2d::Vector2D result = trans_test(vect_test);

    ASSERT_DOUBLE_EQ(1, result.x);
    ASSERT_DOUBLE_EQ(-2, result.y);
}

TEST(Rigid2dTest, InputOutput)
{

    rigid2d::Transform2D trans_test;
    std::ostringstream out;
    std::istringstream in("90 1 4");

    in >> trans_test;
    out << trans_test;

    std::string string_ = out.str();
    const char *str1 = string_.c_str();

    const char *str2 = "degrees:90 dx:1 dy:4 \n";

    ASSERT_STREQ(str1, str2);
}

TEST(Rigid2dTest, Inverse)
{
    rigid2d::Vector2D translation;
    translation.x = -1.11022e-16;
    translation.y = -1;
    rigid2d::Transform2D trans_test(translation, rigid2d::PI * 3.0 / 2.0);

    rigid2d::Transform2D result = trans_test.inv();

    std::ostringstream out;
    out << result;

    std::string string_ = out.str();
    const char *str1 = string_.c_str();

    const char *str2 = "degrees:-270 dx:-1 dy:-7.2675e-17 \n";

    ASSERT_STREQ(str1, str2);
}

TEST(Rigid2dTest, Multiplication)
{
    rigid2d::Vector2D translation1;
    translation1.x = -1;
    translation1.y = 0;
    rigid2d::Transform2D trans_test1(translation1, rigid2d::PI / 2.0);

    rigid2d::Vector2D translation2;
    translation2.x = -1;
    translation2.y = -1;
    rigid2d::Transform2D trans_test2(translation2, rigid2d::PI);

    rigid2d::Transform2D result = trans_test1 * trans_test2;

    std::ostringstream out;
    out << result;

    std::string string_ = out.str();
    const char *str1 = string_.c_str();

    const char *str2 = "degrees:270 dx:-1.11022e-16 dy:-1 \n";

    ASSERT_STREQ(str1, str2);
}

// google test main function
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}