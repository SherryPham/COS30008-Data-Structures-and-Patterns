
// COS30008, Midterm 2024

#include <iostream>
#include <string>

#define P1
#define P2

static size_t gCount = 0;

#include "KeyProvider.h"
#include "VigenereForwardIterator.h"

void VigenereForwardIterator::initializeTable()
{
    for (char row = 0; row < CHARACTERS; row++)
    {
        char lChar = 'B' + row;

        for (char column = 0; column < CHARACTERS; column++)
        {
            if (lChar > 'Z')
                lChar = 'A';

            fMappingTable[row][column] = lChar++;
        }
    }
}

#ifdef P1

void runP1()
{
    gCount++;

    std::cout << "Test KeyProvider" << std::endl;

    std::string lKey = "Relations";
    std::string lPhrase1 = "To be, or not to be: that is the question:";
    std::string lPhrase2 = "Be cool";
    std::string lPhrase3 = "";

    // create first iterator
    // fKey == "RELATIONSRELATIONSRELATIONSREL"
    // fSize == 30
    // fIndex == 0
    KeyProvider iter1(lKey, lPhrase1);

    std::cout << "First key sequence: \"";

    for (; iter1 != iter1.end(); iter1++)
    {
        std::cout << *iter1;
    }

    std::cout << "\"" << std::endl;

    std::cout << "Second key sequence: \"";

    // create second iterator
    // fKey == "RELATI"
    // fSize == 6
    // fIndex == 0
    for (char c : KeyProvider(lKey, lPhrase2))
    {
        std::cout << c;
    }

    std::cout << "\"" << std::endl;

    std::cout << "Third key sequence: \"";

    // create second iterator
    // fKey == ""
    // fSize ==
    // fIndex == 0
    for (char c : KeyProvider(lKey, lPhrase3))
    {
        std::cout << c;
    }

    std::cout << "\"" << std::endl;

    std::cout << "done" << std::endl;
}

#endif

#ifdef P2

void runP2()
{
    gCount++;

    std::cout << "Test VigenereForwardIterator" << std::endl;

    std::string lKey = "Relations";
    std::string lPhrase1 = "To be, or not to be: that is the question:";

    std::cout << "First phrase: \"" << lPhrase1 << "\"" << std::endl;

    std::string lEncoded1;
    VigenereForwardIterator iter1(lKey, lPhrase1);

    for (; iter1 != iter1.end(); ++iter1)
    {
        lEncoded1 += *iter1;
    }

    std::cout << "Encoded text: \"" << lEncoded1 << "\"" << std::endl;

    std::string lDecoded1;
    VigenereForwardIterator iter2(lKey, lEncoded1, EVigenereMode::Decode);

    for (; iter2 != iter2.end(); iter2++)
    {
        lDecoded1 += *iter2;
    }

    std::cout << "Decoded text: \"" << lDecoded1 << "\"" << std::endl;

    std::string lPhrase2 = "Be cool";

    std::cout << "Second phrase: \"" << lPhrase2 << "\"" << std::endl;
    std::string lEncoded2;

    for (char c : VigenereForwardIterator(lKey, lPhrase2))
    {
        lEncoded2 += c;
    }

    std::cout << "Encoded text: \"" << lEncoded2 << "\"" << std::endl;

    std::string lDecoded2;

    for (char c : VigenereForwardIterator(lKey, lEncoded2, EVigenereMode::Decode))
    {
        lDecoded2 += c;
    }

    std::cout << "Decoded text: \"" << lDecoded2 << "\"" << std::endl;

    std::string lPhrase3 = "";

    std::cout << "Third phrase: \"" << lPhrase3 << "\"" << std::endl;
    std::string lEncoded3;

    for (char c : VigenereForwardIterator(lKey, lPhrase3))
    {
        lEncoded3 += c;
    }

    std::cout << "Encoded text: \"" << lEncoded3 << "\"" << std::endl;

    std::string lDecoded3;

    for (char c : VigenereForwardIterator(lKey, lEncoded3, EVigenereMode::Decode))
    {
        lDecoded3 += c;
    }

    std::cout << "Decoded text: \"" << lDecoded3 << "\"" << std::endl;

    std::cout << "done" << std::endl;
}

#endif

int main(int argc, char* argv[])
{
#ifdef P1
    runP1();
#endif

#ifdef P2
    runP2();
#endif

    if (gCount != 0)
    {
        std::cout << gCount << " Test(s) completed." << std::endl;
    }
    else
    {
        std::cout << "No Test enabled." << std::endl;
    }

    return 0;
}
