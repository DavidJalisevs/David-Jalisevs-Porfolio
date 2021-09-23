#include "pch.h"
#include "../Boggle/Boggle.h"
#include "../Boggle/Display.h"
#include "../Boggle/LetterCounter.h"
#include "../Boggle/CalculateScore.h"
#include "../Boggle/WordChecker.h"
#include "../Boggle/WordInput.h"
#include "../Boggle/GamerTag.h"

TEST(Generated_Letters_TEST, Boggle)
{
    
    Boggle createTest;
    createTest.createWords();
    EXPECT_EQ("T",createTest.output);

}

TEST(Output_TEST, LetterCounter)
{

    LetterCounter counterTest;
    std::string test = "hell";
    EXPECT_EQ(4, counterTest.letterCounter(test));

}

TEST(Output_TEST2, LetterCounter)
{

    LetterCounter counterTest;
    std::string test = "heaven";
    EXPECT_EQ(6, counterTest.letterCounter(test));

}

TEST(Calculation_TEST, CalculateScore)
{

    CalculateScore scoreTest;
    LetterCounter LetterCounter;

    std::string test = "random";
 
    EXPECT_EQ(LetterCounter.letterCounter(test) , scoreTest.calculate(LetterCounter.letterCounter(test)));

}

TEST(Validity_TEST, WordChecker)
{

    WordChecker wordCheckTest;
    Boggle forValidTest;

    char letterArray[16] = { char(rand() % 25 + 65) ,char(rand() % 25 + 65) , char(rand() % 25 + 65) , char(rand() % 25 + 65),
                char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,
                char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,
                char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,char(rand() % 25 + 65) ,char(rand() % 25 + 65)
    };

    std::string test = "aidful";

    EXPECT_EQ(test, wordCheckTest.wordCheck(test, forValidTest.letterArray));

}

TEST(Input_TEST, WordInput)
{

    WordInput inputTest;


    EXPECT_EQ("",inputTest.wordInput());
}

TEST(GamerTag_TEST, GamerTag)
{
    GamerTag gamerTagTest;
    std::string test = "hello";

    EXPECT_EQ(gamerTagTest.checkName(), test);
}