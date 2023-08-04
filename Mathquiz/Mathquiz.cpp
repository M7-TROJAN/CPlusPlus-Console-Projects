// Copyright (c) [2021] [Mahmoud Mohamed]
// Licensed under the MIT License.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <ctime>
#include <windows.h>
enum ENQuestionsLevel
{
    VERY_EASY = 1,
    EASY = 2,
    MEDIUM = 3,
    HARD = 4,
    VERY_HARD = 5
};
enum ENOperationType
{
    ADD = 1,
    SUB = 2,
    MUL = 3,
    DIV = 4,
    MIX = 5
};
ENQuestionsLevel questionLevel;
ENOperationType  operationType;
short TOTAL_QUESTIONS = 0;
short NUMBER_OF_CORRECT_ANSWERS = 0;
short NUMBER_OF_WRONG_ANSWERS = 0;

void welcome()
{
    std::cout << "\n";
    std::cout << "                ------------------------------------------------------------------------------\n";
    std::cout << "                |*********************** Welcome To The Math quiz Game **********************|\n";
    std::cout << "                ------------------------------------------------------------------------------\n";
    std::cout << "                                                Let's Play!!" << std:: endl;
    std::cout << "                ------------------------------------------------------------------------------\n\n";
}

bool playAgain()
{
    char choice = 'y';
    std::cout << "\n                       Do You Want To Play Again (y/n)?: ";
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y')
    {
        system("color 0f");
        system("cls");
        TOTAL_QUESTIONS = 0;
        NUMBER_OF_CORRECT_ANSWERS = 0;
        NUMBER_OF_WRONG_ANSWERS = 0;
        return true;
    }
    else
    {
        std::cin.clear();
        std::cin.ignore(100000, '\n');
        return false;
    }
}

void makeSeparator(int size)
{
    for(int i = 0 ; i < size ; i++)
        std::cout << "-";
    std::cout << "\n";
}

std::string getTestResult()
{
    if (NUMBER_OF_CORRECT_ANSWERS >= NUMBER_OF_WRONG_ANSWERS)
    {
        system("color 2f");
        return "Pass :)";
    }
    system("color 4f");
    return "Fail :(";
}

// Generates a random number between the given range and returns it as game choice
short getRandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

char getOperatorLetter(ENOperationType op)
{
    switch (op)
    {
    case ENOperationType::ADD:
        return '+';
    case ENOperationType::MUL:
        return '*';
    case ENOperationType::SUB:
        return '-';
    case ENOperationType::DIV:
        return '/';
    }
    return getOperatorLetter((ENOperationType)getRandomNumber(1,4));
}

std::string getStringQuestionLevel(ENQuestionsLevel level)
{
    switch (level)
    {
    case ENQuestionsLevel::VERY_EASY:
        return "Very Easy";
    case ENQuestionsLevel::EASY:
        return "Easy";
    case ENQuestionsLevel::MEDIUM:
        return "Medium";
    case ENQuestionsLevel::HARD:
        return "Hard";
    case ENQuestionsLevel::VERY_HARD:
        return "Very Hard";
    default:
        return "Mix";
    }
}

short getScorePercentage()
{
    // return ((float)NUMBER_OF_CORRECT_ANSWERS / (float)TOTAL_QUESTIONS) * 100;
    short percentage = ((float)NUMBER_OF_CORRECT_ANSWERS / (float)TOTAL_QUESTIONS) * 100;
    return percentage;
}

void theEnd()
{
    std::string stringQuestionLevel = getStringQuestionLevel(questionLevel);
    std::string stringOperationType = "";
    if(operationType == MIX)
        stringOperationType = "Mix";
    else
        stringOperationType = getOperatorLetter(operationType);

    std::cout << "\n\n";
    std::cout << "                       ----------------------------------------------------------------------\n";
    std::cout << "                       |                       +++ T H E  E N D +++                         |\n";
    std::cout << "                       ----------------------------------------------------------------------\n";
    std::cout << "\n";
    std::cout << "                       -------------------------- [Final Results] ---------------------------\n";
    std::cout << "                       Total Questions     : " << TOTAL_QUESTIONS           << "\n";
    std::cout << "                       Questions Level     : " << stringQuestionLevel       << "\n";
    std::cout << "                       Operation type      : " << stringOperationType       << "\n";
    std::cout << "                       Correct Answers     : " << NUMBER_OF_CORRECT_ANSWERS << "\n";
    std::cout << "                       Wrong Answers       : " << NUMBER_OF_WRONG_ANSWERS   << "\n";
    std::cout << "                       Score in percentage : " << getScorePercentage()      << "%\n";
    std::cout << "                       Test Result         : " << getTestResult()           << "\n";
    std::cout << "                       ----------------------------------------------------------------------" << std:: endl;
}

void cheekAnswer(float number1 , float number2 , char op , float answer)
{
    switch (op)
    {
    case '+':
        if(number1 + number2 == answer)
        {
            system("color 2f");
            std::cout << "Correct Answer.\n";
            NUMBER_OF_CORRECT_ANSWERS++;
            // Pause for 2 seconds
            Sleep(1000);
            system("color 0f");
        }
        else
        {
            system("color 4f");
            std::cout << "\aWrong Answer.\n";
            printf("Right Answer Is %.1f\n",number1 + number2);
            NUMBER_OF_WRONG_ANSWERS++;
            Sleep(1000);
            system("color 0f");
        }
        break;
    case '-':
        if(number1 - number2 == answer)
        {
            system("color 2f");
            std::cout << "Correct Answer.\n";
            NUMBER_OF_CORRECT_ANSWERS++;
            Sleep(1000);
            system("color 0f");
        }
        else
        {
            system("color 4f");
            std::cout << "\aWrong Answer.\n";
            printf("Right Answer Is %.1f\n",number1 - number2);
            NUMBER_OF_WRONG_ANSWERS++;
            Sleep(1000);
            system("color 0f");
        }
        break;
    case '*':
        if(number1 * number2 == answer)
        {
            system("color 2f");
            std::cout << "Correct Answer.\n";
            NUMBER_OF_CORRECT_ANSWERS++;
            Sleep(1000);
            system("color 0f");
        }
        else
        {
            system("color 4f");
            std::cout << "\aWrong Answer.\n";
            printf("Right Answer Is %.1f\n",number1 * number2);
            NUMBER_OF_WRONG_ANSWERS++;
            Sleep(1000);
            system("color 0f");
        }
        break;
    case '/':
        if(number1 / number2 == answer || (int)number1 / (int)number2 == int(answer))
        {
            system("color 2f");
            std::cout << "Correct Answer.\n";
            NUMBER_OF_CORRECT_ANSWERS++;
            Sleep(1000);
            system("color 0f");
        }
        else
        {
            system("color 4f");
            std::cout << "\aWrong Answer.\n";
            printf("Right Answer Is %.1f\n",number1 / number2);
            NUMBER_OF_WRONG_ANSWERS++;
            Sleep(1000);
            system("color 0f");
        }
        break;
    default:
        break;
    }
}

// Reads an integer value from the user between the given range and returns it
int readNumber_From_To(int from, int to, std::string message = "")
{
    float number = 0;
    do
    {
        // Read an integer value from the user
        std::cout << message;
        std::cin >> number;

        // Check if the input was invalid (i.e. not an integer)
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a valid integer between " << from << " to " << to << std::endl;
            continue;
        }
        if (number < from || number > to)
        {
            std::cout << "Please enter a number between " << from << " to " << to << std::endl;
            continue;
        }
        break;
    } while (true);
    return number;
}

void getQuizInfo()
{
    TOTAL_QUESTIONS = readNumber_From_To(1, 100, "How Many Questions Do You Want To Answer (from 1 to 100)?:\n");
    makeSeparator(56);
    questionLevel = (ENQuestionsLevel)readNumber_From_To(1, 5, "choose The Level Of Questions\n[1] Very Easy\n[2] Easy\n[3] Med\n[4] Hard\n[5] Very Hard\nEnter your Choice: ");
    makeSeparator(56);
    operationType = (ENOperationType)readNumber_From_To(1, 5, "choose Operation Type\n[1] Addition\n[2] Subtraction\n[3] Multiplication\n[4] Division\n[5] Mix\nEnter your Choice: ");
    makeSeparator(56);
}

float get_float(std::string message = "")
{
    float number = 0;
    do
    {
        // Read a float value from the user
        std::cout << message;
        std::cin >> number;

        // Check if the input was invalid (i.e. not a number)
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            // cout << "Invalid input. Please enter a valid number." << endl;
            continue;
        }
        break;
    } while (true);
    return number;
}

void getnQuestionNumbers(short &number1, short &number2, ENQuestionsLevel level)
{
    int x, y;
    if(level == VERY_EASY)
    {
        x = getRandomNumber(1,10);
        y = getRandomNumber(1,10);
    }
    else if(level == EASY)
    {
        x = getRandomNumber(1,20);
        y = getRandomNumber(1,20);
    }
    else if(level == MEDIUM)
    {
        x = getRandomNumber(1,50);
        y = getRandomNumber(1,50);
    }
    else if(level == HARD)
    {
        x = getRandomNumber(10,100);
        y = getRandomNumber(10,100);
    }
    else if (level == VERY_HARD)
    {
        x = getRandomNumber(10,300);
        y = getRandomNumber(10,300);
    }

    if(x > y)
    {
        number1 = x;
        number2 = y;
    }
    else
    {
        number1 = y;
        number2 = x;
    }
}

void startRound(short roundNumber)
{
    short number1 = 0 , number2 = 0;
    getnQuestionNumbers(number1, number2, questionLevel);
    float answer = 0;
    char op = getOperatorLetter(operationType);

    std::cout << "\nQuestion Number [" << roundNumber << "]:\n";
    makeSeparator(21);
    std::cout <<  number1 << " " << op << " " << number2 << " = ";
    answer = get_float();
    cheekAnswer(number1, number2, op , answer);
    makeSeparator(21);
}

void startGame()
{
    do
    {
        getQuizInfo();
        for (short i = 1; i <= TOTAL_QUESTIONS; i++)
            startRound(i);
        theEnd();
    } while (playAgain());
}

int main()
{
    srand((unsigned)time(NULL));
    welcome();
    startGame();
    system("color 0f");
    std::cout << "Press any key to close this window . . . ";
    std::cin.get();
}