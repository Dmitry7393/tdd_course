/*
Given a phrase, count the occurrences of each word in that phrase. Ignore whitespaces and punctual symbols
For example for the input "olly olly in come free please please let it be in such manner olly"
olly: 3
in: 2
come: 1
free: 1
please: 2
let: 1
it: 1
be: 1
manner: 1
such: 1
*/

#include <gtest/gtest.h>
#include <string>
#include <map>

/*
There are going to be 2 functions
1. getWordsFromSentence, that removes punctual symbols and returns vector with words
2. countWords, that calls getWordsFromSentence and uses map to count the occurrences of each word

Test plan
1) Implement function getWordsFromSentence
   1. "hello"
   2. "hello     hello"
   3. "  test  three words"
   4. "hi.,;!?"
   5. "hello, hello"
   6. "olly olly in   come free please please let it be    in such manner olly?"
   7. "hello,hello"
   8. "hello, world, hello!"
   9. "hello.world. hi"

2) Implement function countWords
   1. "aaaa bbbb cccc aaa aaaa"
   2. "olly olly in come free please please let it be in such manner    olly!"
   3. "olly! olly in come,free please please let it. be in such manner olly"
*/

std::vector<std::string> getWordsFromSentence(const std::string& sentence)
{
    std::vector<std::string> result;
    std::string modifiedSentence = sentence;

    const char punctualSymbols[] = { '.', ',', '!', '?', ';' };
    for (int i = 0; i < sizeof(punctualSymbols); i++)
    {
        std::replace(modifiedSentence.begin(), modifiedSentence.end(), punctualSymbols[i], ' ');
    }

    std::istringstream iss(modifiedSentence);
    std::string word;

    while(getline(iss, word, ' '))
    {
        if (word.length() > 0)
            result.push_back(word);
    }

    return result;
}

TEST(getWordsFromSentence, testSingleWord_hello)
{
    std::vector<std::string> expected = { "hello" };
    ASSERT_EQ(getWordsFromSentence("hello"), expected);
}

TEST(getWordsFromSentence, testTwoWords)
{
    std::vector<std::string> expected = { "hello", "hello" };
    ASSERT_EQ(getWordsFromSentence("hello     hello"), expected);
}

TEST(getWordsFromSentence, testThreeWords)
{
    std::vector<std::string> expected = { "test", "three", "words" };
    ASSERT_EQ(getWordsFromSentence("  test  three words"), expected);
}


TEST(getWordsFromSentence, workWithPunctualSymbols)
{
    std::vector<std::string> expected = { "hi" };
    ASSERT_EQ(getWordsFromSentence("hi.,;!?"), expected);
}
