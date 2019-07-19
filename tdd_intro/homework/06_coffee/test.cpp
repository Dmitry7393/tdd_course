/*
We have to develop a coffee machine with TDD. The machine uses the automated source of ingredients, which implements the interface ISourceOfIngredients.

Our machine should be able to produce the coffee accordingly to the next receipts:
- americano: water & coffee 1:2 or 1:3. Water temp 60C
- cappuccino - milk & coffee & milk foam 1:3, 1:3, 1:3. Water temp 80C
- latte - milk & coffee & milk foam 1:4, 1:2, 1:4. Water temp 90C
- marochino - chocolate & coffee & milk foam, 1:4, 1:4, 1:4 and 1:4 is empty

We have 2 possible sizes of the cup:
- little 100 gram
- big 140 gram

Implement worked coffee machine using ISourceOfIngredients to controll the process of coffee production.
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class ISourceOfIngredients
{
public:
    virtual ~ISourceOfIngredients() {}
    virtual void SetCupSize(int gram) = 0;
    virtual void AddWater(int gram) = 0;
    virtual void HeatUpTo(int gram) = 0;
    virtual void AddSugar(int gram) = 0;
    virtual void AddCoffee(int gram) = 0;
    virtual void AddMilk(int gram) = 0;
    virtual void AddMilkFoam(int gram) = 0;
    virtual void AddChocolate(int gram) = 0;
    virtual void AddCream(int gram) = 0;
};

class SourceOfIngredientsMock : public ISourceOfIngredients
{
public:
    MOCK_METHOD1(SetCupSize, void(int));
    MOCK_METHOD1(AddWater, void(int));
    MOCK_METHOD1(HeatUpTo, void(int));
    MOCK_METHOD1(AddSugar, void(int));
    MOCK_METHOD1(AddCoffee, void(int));
    MOCK_METHOD1(AddMilk, void(int));
    MOCK_METHOD1(AddMilkFoam, void(int));
    MOCK_METHOD1(AddChocolate, void(int));
    MOCK_METHOD1(AddCream, void(int));
};

enum CupSize
{
    SMALL_CUP,
    BIG_CUP
};

class CoffeeMachine
{
public:
    CoffeeMachine(ISourceOfIngredients* src)
    {
        m_sourceOfIngredients = src;
    }

    void makeAmericano(CupSize cupSize)
    {
        if (cupSize == SMALL_CUP)
        {
            m_sourceOfIngredients->SetCupSize(100);
            m_sourceOfIngredients->AddCoffee(25);
            m_sourceOfIngredients->AddWater(75);
        }
        else if (cupSize == BIG_CUP)
        {
            m_sourceOfIngredients->SetCupSize(140);
            m_sourceOfIngredients->AddCoffee(46);
            m_sourceOfIngredients->AddWater(94);
        }

        m_sourceOfIngredients->HeatUpTo(60);
    }

    void makeCappuccino(CupSize cupSize)
    {
        if (cupSize == SMALL_CUP)
        {
            m_sourceOfIngredients->SetCupSize(100);
            m_sourceOfIngredients->AddMilk(33);
            m_sourceOfIngredients->AddMilkFoam(33);
            m_sourceOfIngredients->AddCoffee(33);
        }
        else if (cupSize == BIG_CUP)
        {
            m_sourceOfIngredients->SetCupSize(140);
            m_sourceOfIngredients->AddMilk(46);
            m_sourceOfIngredients->AddMilkFoam(46);
            m_sourceOfIngredients->AddCoffee(46);
        }

        m_sourceOfIngredients->HeatUpTo(80);
    }

    void makeLatte(CupSize cupSize)
    {

    }

private:
    ISourceOfIngredients* m_sourceOfIngredients;
};

TEST(CoffeeMachine, makeSmallAmericano)
{
    SourceOfIngredientsMock sourceIngredientMock;
    CoffeeMachine coffeeMachine(&sourceIngredientMock);
    EXPECT_CALL(sourceIngredientMock, SetCupSize(100)).Times(1);
    EXPECT_CALL(sourceIngredientMock, AddWater(75)).Times(1);
    EXPECT_CALL(sourceIngredientMock, AddCoffee(25)).Times(1);
    EXPECT_CALL(sourceIngredientMock, HeatUpTo(60)).Times(1);
    coffeeMachine.makeAmericano(SMALL_CUP);
}

TEST(CoffeeMachine, makeBigAmericano)
{
    SourceOfIngredientsMock sourceIngredientMock;
    CoffeeMachine coffeeMachine(&sourceIngredientMock);
    EXPECT_CALL(sourceIngredientMock, SetCupSize(140)).Times(1);
    EXPECT_CALL(sourceIngredientMock, AddWater(94)).Times(1);
    EXPECT_CALL(sourceIngredientMock, AddCoffee(46)).Times(1);
    EXPECT_CALL(sourceIngredientMock, HeatUpTo(60)).Times(1);
    coffeeMachine.makeAmericano(BIG_CUP);
}

TEST(CoffeeMachine, makeSmallCappuccino)
{
    SourceOfIngredientsMock sourceIngredientMock;
    CoffeeMachine coffeeMachine(&sourceIngredientMock);
    EXPECT_CALL(sourceIngredientMock, SetCupSize(100)).Times(1);
    EXPECT_CALL(sourceIngredientMock, AddMilk(33)).Times(1);
    EXPECT_CALL(sourceIngredientMock, AddMilkFoam(33)).Times(1);
    EXPECT_CALL(sourceIngredientMock, AddCoffee(33)).Times(1);
    EXPECT_CALL(sourceIngredientMock, HeatUpTo(80)).Times(1);
    coffeeMachine.makeCappuccino(SMALL_CUP);
}

TEST(CoffeeMachine, makeBigCappuccino)
{
    SourceOfIngredientsMock sourceIngredientMock;
    CoffeeMachine coffeeMachine(&sourceIngredientMock);
    EXPECT_CALL(sourceIngredientMock, SetCupSize(140)).Times(1);
    EXPECT_CALL(sourceIngredientMock, AddMilk(46)).Times(1);
    EXPECT_CALL(sourceIngredientMock, AddMilkFoam(46)).Times(1);
    EXPECT_CALL(sourceIngredientMock, AddCoffee(46)).Times(1);
    EXPECT_CALL(sourceIngredientMock, HeatUpTo(80)).Times(1);
    coffeeMachine.makeCappuccino(BIG_CUP);
}

TEST(CoffeeMachine, makeSmallLatte)
{
    SourceOfIngredientsMock sourceIngredientMock;
    CoffeeMachine coffeeMachine(&sourceIngredientMock);
    EXPECT_CALL(sourceIngredientMock, SetCupSize(100)).Times(1);
    EXPECT_CALL(sourceIngredientMock, AddMilk(25)).Times(1);
    EXPECT_CALL(sourceIngredientMock, AddCoffee(50)).Times(1);
    EXPECT_CALL(sourceIngredientMock, AddMilkFoam(25)).Times(1);
    EXPECT_CALL(sourceIngredientMock, HeatUpTo(90)).Times(1);
    coffeeMachine.makeLatte(SMALL_CUP);
}
