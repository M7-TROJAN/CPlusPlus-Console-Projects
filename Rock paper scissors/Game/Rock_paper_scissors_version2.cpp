// Copyright (c) [2021] [Mahmoud Mohamed]
// Licensed under the MIT License.
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <fstream>
#include <cstdio>
// Enumeration for game choices
enum enGameChoice
{
    ROCK = 1,
    PAPER = 2,
    SCISSORS = 3
};

// Global variables to keep track of game statistics
enGameChoice PLAYER_CHOICE;
enGameChoice COMPUTER_CHOICE;
short total_GAME_ROUNDS = 0;
short PLAYER_WINS_tIMES = 0;
short COMPUTER_WINS_tIMES = 0;
short DRAW_tIMES = 0;
std::string FINAL_WINNEr = "NONE";

// Reads an integer value from the user between the given range and returns it
int readNumber_From_To(int from, int to, std::string message)
{
    int number = 0;
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

// Generates a random number between the given range and returns it as game choice
short getComputerChoice(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

// Returns the string representation of the given game choice
std::string stringChoice(enGameChoice choice)
{
    switch (choice)
    {
    case PAPER:
        return "Paper";
    case ROCK:
        return "Rock";
    case SCISSORS:
        return "Scissors";
    default:
        return "Unknown";
    }
}

/*
Function To Determines the winner of the round based on the player and computer choices
Updates the game statistics accordingly and returns the winner as a string
*/
std::string getRoundWinner(enGameChoice playerChoice, enGameChoice computerChoice)
{
    if (playerChoice == computerChoice)
    {
        system("color 6f");
        DRAW_tIMES++;
        return "Draw (No Winner)";
    }

    if ((playerChoice == enGameChoice::ROCK && computerChoice == enGameChoice::SCISSORS) ||
        (playerChoice == enGameChoice::PAPER && computerChoice == enGameChoice::ROCK) ||
        (playerChoice == enGameChoice::SCISSORS && computerChoice == enGameChoice::PAPER))
    {
        PLAYER_WINS_tIMES++;
        system("color 2f");
        return "Player";
    }
    // if you reach here then Computer is the winner.
    std::cout << "\a";
    system("color 4f");
    COMPUTER_WINS_tIMES++;
    return "Computer";
}

std::string getFinalWinner()
{
    if (PLAYER_WINS_tIMES > COMPUTER_WINS_tIMES)
    {
        system("color 2f");
        return "Player";
    }
    else if (PLAYER_WINS_tIMES < COMPUTER_WINS_tIMES)
    {
        std::cout << "\a";
        system("color 4f");
        return "Computer";
    }
    else
    {
        system("color 6f");
        return "Draw (No Winner)";
    }
}

void addGameResultToFile(const std::string &playerName)
{
    time_t currentTime = time(nullptr);
    tm localTime;
    localtime_s(&localTime, &currentTime);

    // get date
    short day = localTime.tm_mday;
    short month = localTime.tm_mon + 1;
    short year = localTime.tm_year + 1900;
    std::string date = std::to_string(day) + "-" + std::to_string(month) + "-" + std::to_string(year);

    // get hour
    short hour24 = localTime.tm_hour;
    short hour12 = hour24 % 12;
    short minute = localTime.tm_min;
    short second = localTime.tm_sec;
    const char *amPmIndicator = (hour24 < 12) ? "AM" : "PM";
    // check if hour12 is equal  0
    if (hour12 == 0)
        hour12 = 12; // Convert 0 to 12 in the 12-hour time format
    std::string time = std::to_string(hour12) + ":" + std::to_string(minute) + ":" + std::to_string(second) + amPmIndicator;

    std::fstream MyFile;
    std::string filePath = "history\\" + date + ".txt"; 
    MyFile.open(filePath, std::ios::app);
    if (MyFile.is_open())
    {
        MyFile << "\n\n";
        MyFile << "                           " << date << " | " << time << "\n";
        MyFile << "----------------------------- [Game Results] -------------------------\n";
        MyFile << "Player Name: " << playerName << "\n";
        MyFile << "Game Rounds: " << total_GAME_ROUNDS << "\n";
        MyFile << "Player Won Times: " << PLAYER_WINS_tIMES << "\n";
        MyFile << "Computer Won Times: " << COMPUTER_WINS_tIMES << "\n";
        MyFile << "Draw Times: " << DRAW_tIMES << "\n";
        MyFile << "Final Winner: " << getFinalWinner() << "\n";
        MyFile << "----------------------------------------------------------------------\n";
        MyFile.close();
    }
}

void gameOVER(const std::string &playerName)
{
    std::cout << "\n\n";
    std::cout << "                       ----------------------------------------------------------------------\n";
    std::cout << "                       |                       +++ G A M E   O V E R +++                    |\n";
    std::cout << "                       ----------------------------------------------------------------------\n";
    std::cout << "\n";
    std::cout << "                       ----------------------------- [Game Results] -------------------------\n";
    std::cout << "                       Player Name        :" << playerName << "\n";
    std::cout << "                       Game Rounds        :" << total_GAME_ROUNDS << "\n";
    std::cout << "                       Player Won Times   :" << PLAYER_WINS_tIMES << "\n";
    std::cout << "                       Computer Won Times :" << COMPUTER_WINS_tIMES << "\n";
    std::cout << "                       Draw Times         :" << DRAW_tIMES << "\n";
    std::cout << "                       Final Winner       :" << getFinalWinner() << "\n";
    std::cout << "                       ----------------------------------------------------------------------\n";

    addGameResultToFile(playerName);
}

void startRound(short roundNumber)
{
    std::cout << "Round [" << roundNumber << "] Begins:\n";
    PLAYER_CHOICE = (enGameChoice)readNumber_From_To(1, 3, "Enter Your Choice: [1]:Rock, [2]:Paper, [3]:Scissors: ");
    COMPUTER_CHOICE = (enGameChoice)getComputerChoice(1, 3);

    std::cout << "\n---------------- Round [" << roundNumber << "] ----------------\n\n";
    std::cout << "Player   Choice: " << stringChoice(PLAYER_CHOICE) << "\n";
    std::cout << "Computer Choice: " << stringChoice(COMPUTER_CHOICE) << "\n";
    std::cout << "Round    Winner: " << getRoundWinner(PLAYER_CHOICE, COMPUTER_CHOICE) << "\n";
    std::cout << "\n--------------------------------------------\n";
    total_GAME_ROUNDS++;
}

bool playAgain()
{
    char choice = ' ';
    std::cout << "\n                       Do You Want To Play Again (y/n)?: ";
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y')
    {
        system("color 0f");
        system("cls");
        total_GAME_ROUNDS = 0;
        PLAYER_WINS_tIMES = 0;
        COMPUTER_WINS_tIMES = 0;
        DRAW_tIMES = 0;
        return true;
    }
    else
    {
        std::cin.clear();
        std::cin.ignore(100000, '\n');
        return false;
    }
}

void startGame()
{
    std::string playerName = "";
    std::getline(std::cin, playerName);
    int rounds = 0;
    do
    {
        rounds = readNumber_From_To(1, 10, "How Many Rounds (from 1 to 10)?:\n");
        for (short i = 1; i <= rounds; i++)
            startRound(i);
        gameOVER(playerName);
    } while (playAgain());
}

void welcome()
{
    std::cout << "                ----------------------- Welcome to the game of Rock-Paper-Scissors. -----------------------\n";
    std::cout << "                Game rules:\n";
    std::cout << "                -- Rock beats Scissors\n";
    std::cout << "                -- Scissors beats Paper\n";
    std::cout << "                -- Paper beats Rock\n";
    std::cout << "                -------------------------------------------------------------------------------------------\n";
    std::cout << "                                                    Let's Play!!\n";
    std::cout << "                                               Please Enter Your Name:\n";
    std::cout << "                                                     ";
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