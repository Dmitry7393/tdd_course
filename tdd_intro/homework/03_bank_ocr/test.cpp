/*### Bank OCR

Your manager has recently purchased a machine that assists in reading letters and faxes sent in by branch offices. The machine scans the paper documents, and produces a file with a number of entries. You will write a program to parse this file.

#### Specification
#### User Story 1

The following format is created by the machine:
```
    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|
```
Each entry is 3 lines long, and each line has 27 characters. 3 lines of each entry contain an account number written using pipes and underscores.

Each account number should have 9 digits, all of which should be in the range 0-9. A normal file contains around 500 entries.

Write a program that can take this file and parse it into actual account numbers.

Example input and output
```
 _  _  _  _  _  _  _  _  _
| || || || || || || || || |
|_||_||_||_||_||_||_||_||_|

=> 000000000

  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 111111111

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
|_ |_ |_ |_ |_ |_ |_ |_ |_

=> 222222222

 _  _  _  _  _  _  _  _  _
 _| _| _| _| _| _| _| _| _|
 _| _| _| _| _| _| _| _| _|

=> 333333333

|_||_||_||_||_||_||_||_||_|
  |  |  |  |  |  |  |  |  |

=> 444444444

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
 _| _| _| _| _| _| _| _| _|

=> 555555555

 _  _  _  _  _  _  _  _  _
|_ |_ |_ |_ |_ |_ |_ |_ |_
|_||_||_||_||_||_||_||_||_|

=> 666666666

 _  _  _  _  _  _  _  _  _
  |  |  |  |  |  |  |  |  |
  |  |  |  |  |  |  |  |  |

=> 777777777

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
|_||_||_||_||_||_||_||_||_|

=> 888888888

 _  _  _  _  _  _  _  _  _
|_||_||_||_||_||_||_||_||_|
 _| _| _| _| _| _| _| _| _|

=> 999999999

    _  _     _  _  _  _  _
  | _| _||_||_ |_   ||_||_|
  ||_  _|  | _||_|  ||_| _|

=> 123456789
```
*/
#include <gtest/gtest.h>
#include <string>

const unsigned short g_digitLen = 3;
const unsigned short g_linesInDigit = 3;
struct Digit
{
    std::string lines[g_linesInDigit];
};

const unsigned short g_digitsOnDisplay = 9;
struct Display
{
    std::string lines[g_linesInDigit];
};

const Digit s_digit0 = { " _ ",
                         "| |",
                         "|_|"
                       };
const Digit s_digit1 = { "   ",
                         "  |",
                         "  |"
                       };
const Digit s_digit2 = { " _ ",
                         " _|",
                         "|_ "
                       };
const Digit s_digit3 = { " _ ",
                         " _|",
                         " _|"
                       };
const Digit s_digit4 = { "   ",
                         "|_|",
                         "  |"
                       };
const Digit s_digit5 = { " _ ",
                         "|_ ",
                         " _|"
                       };
const Digit s_digit6 = { " _ ",
                         "|_ ",
                         "|_|"
                       };
const Digit s_digit7 = { " _ ",
                         "  |",
                         "  |"
                       };
const Digit s_digit8 = { " _ ",
                         "|_|",
                         "|_|"
                       };
const Digit s_digit9 = { " _ ",
                         "|_|",
                         " _|"
                       };

const Display s_displayAll0 = { " _  _  _  _  _  _  _  _  _ ",
                                "| || || || || || || || || |",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll1 = { "                           ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll2 = {  " _  _  _  _  _  _  _  _  _ ",
                                 " _| _| _| _| _| _| _| _| _|",
                                 "|_ |_ |_ |_ |_ |_ |_ |_ |_ "
};

const Display s_displayAll3 = { " _  _  _  _  _  _  _  _  _ ",
                                " _| _| _| _| _| _| _| _| _|",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_displayAll4 = { "                           ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll5 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_displayAll6 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_ |_ |_ |_ |_ |_ |_ |_ |_ ",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll7 = { " _  _  _  _  _  _  _  _  _ ",
                                "  |  |  |  |  |  |  |  |  |",
                                "  |  |  |  |  |  |  |  |  |"
};

const Display s_displayAll8 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                "|_||_||_||_||_||_||_||_||_|"
};

const Display s_displayAll9 = { " _  _  _  _  _  _  _  _  _ ",
                                "|_||_||_||_||_||_||_||_||_|",
                                " _| _| _| _| _| _| _| _| _|"
};

const Display s_display123456789 = { "    _  _     _  _  _  _  _ ",
                                     "  | _| _||_||_ |_   ||_||_|",
                                     "  ||_  _|  | _||_|  ||_| _|"
};

/*
There are going to be 2 functions:
1. function recognizeSingleCharacter returns a single-digit
2. function recognizeSeveralCharacters returns a full number

Test plan
1. recognize '0'
2. recognize '1'
3. recognize '7'
4. recognize '12'
5. recognize '123'
6. recognize '1234'
7. recognize '000000000
8. recognize '111111111'
9. recognize '555555555'
10. recognize '123456789'
*/

static const std::vector<Digit> g_allSingleDigits = { s_digit0, s_digit1, s_digit2,
                                                      s_digit3, s_digit4, s_digit5,
                                                      s_digit6, s_digit7, s_digit8,
                                                                          s_digit9
                                                    };

int recognizeSingleCharacter(const Digit& digit)
{
    for (int i = 0; i < g_allSingleDigits.size(); i++)
    {
        bool match = true;
        for (int j = 0; j < g_linesInDigit; j++)
        {
            if (digit.lines[j] != g_allSingleDigits[i].lines[j])
            {
                match = false;
            }
        }
        if (match)
        {
            return i;
        }
    }

    return -1;
}

std::string recognizeSeveralCharacters(const Display& display)
{
    std::string result;

    for (int i = 0; i < display.lines[0].size(); i += g_linesInDigit)
    {
        Digit digit = {display.lines[0].substr(i, g_linesInDigit),
                       display.lines[1].substr(i, g_linesInDigit),
                       display.lines[2].substr(i, g_linesInDigit)};
        int recognizedNumber = recognizeSingleCharacter(digit);
        result += std::to_string(recognizedNumber);
    }

   return result;
}

TEST(recognizeSingleCharacter, recognizeCharacter0)
{
    ASSERT_EQ(recognizeSingleCharacter(s_digit0), 0);
}

TEST(recognizeSingleCharacter, recognizeCharacter1)
{
    ASSERT_EQ(recognizeSingleCharacter(s_digit1), 1);
}

TEST(recognizeSingleCharacter, recognizeCharacter7)
{
    ASSERT_EQ(recognizeSingleCharacter(s_digit7), 7);
}

TEST(recognizeSingleCharacter, recognizeCharacter4)
{
    ASSERT_EQ(recognizeSingleCharacter(s_digit4), 4);
}

TEST(recognizeSeveralCharacters, recognizeSequence12)
{
    const Display s_display12 = { "    _ ",
                                  "  | _|",
                                  "  ||_ "
                                };

    ASSERT_EQ(recognizeSeveralCharacters(s_display12), "12");
}

TEST(recognizeSeveralCharacters, recognizeSequence123)
{
    const Display s_display123 = { "    _  _ ",
                                   "  | _| _|",
                                   "  ||_  _|"
                                 };

    ASSERT_EQ(recognizeSeveralCharacters(s_display123), "123");
}

TEST(recognizeSeveralCharacters, recognizeSequence1234)
{
    const Display s_display1234 = { "    _  _    ",
                                    "  | _| _||_|",
                                    "  ||_  _|  |"
                                  };

    ASSERT_EQ(recognizeSeveralCharacters(s_display1234), "1234");
}
