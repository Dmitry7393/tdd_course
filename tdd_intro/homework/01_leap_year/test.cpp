/*
Given a year, report if it is a leap year.

The tricky thing here is that a leap year in the Gregorian calendar occurs:

on every year that is evenly divisible by 4
  except every year that is evenly divisible by 100
    unless the year is also evenly divisible by 400

For example, 1997 is not a leap year, but 1996 is. 1900 is not a leap year, but 2000 is.

If your language provides a method in the standard library that does this look-up, pretend it doesn't exist and implement it yourself.
*/

#include <gtest/gtest.h>

bool isLeapYear(int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0 && year % 400 != 0)
        {
            return false;
        }
        return true;
    }

    return false;
}

TEST(isLeapYear, divisible_by_4)
{
    ASSERT_EQ(isLeapYear(1996), true);
}

TEST(isLeapYear, divisible_by_100)
{
    ASSERT_EQ(isLeapYear(1900), false);
}

TEST(isLeapYear, divisible_by_400)
{
    ASSERT_EQ(isLeapYear(2000), true);
}

TEST(isLeapYear, test2016Year)
{
    ASSERT_EQ(isLeapYear(2016), true);
}

TEST(isLeapYear, testYear400isLeapYear)
{
    ASSERT_EQ(isLeapYear(400), true);
}
