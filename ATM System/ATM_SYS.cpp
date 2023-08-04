// Copyright (c) [2021] [Mahmoud Mohamed]
// Licensed under the MIT License.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
using namespace std;

const string CLIENTS_FILENAME = "Clients.txt";

struct stClientData
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0.0;
    bool isEnteringPINCodeWrong = false;
};

enum enMainMenuOptions
{
    eQuickWithdraw = 1,
    eNormalWithdraw = 2,
    eDeposit = 3,
    eCheckBallance = 4,
    eChangePinCode = 5,
    eLogout = 6,
};

stClientData CURRENT_CLIENT;
vector<stClientData> VECTOR_OF_CLIENTS;
int INDEX_OF_CURRENT_CLIENT;

void showMainMenu();
void goBackToMainMenu();
void login();

// This function splits a string into words using a delimiter
std::vector<std::string> splitString(const std::string &str, const std::string &delimiter = "##")
{
    std::vector<std::string> words;
    std::string currentWord;

    // Iterate through the string to extract and add each word to the vector
    size_t delimiterPos = 0;
    std::string remainingStr = str; // Store the remaining string for manipulation
    while ((delimiterPos = remainingStr.find(delimiter)) != std::string::npos)
    {
        currentWord = remainingStr.substr(0, delimiterPos);
        if (!currentWord.empty())
        {
            words.push_back(currentWord);
        }
        remainingStr.erase(0, delimiterPos + delimiter.length());
    }

    // Add the last word if it exists
    if (!remainingStr.empty())
    {
        words.push_back(remainingStr);
    }

    return words;
}

// Reads an integer value from the user between the given range and returns it
int getInputInRange(const int &from, const int &to, const std::string &message = "")
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer between " << from << " to " << to << std::endl;
            continue;
        }
        if (number < from || number > to)
        {
            std::cout << "Please enter a number between " << from << " to " << to << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    } while (true);
    return number;
}

int getAmountToDeposit()
{
    int amount;
    do
    {
        std::cout << "Enter the amount to deposit (multiple of 5): ";
        std::cin >> amount;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid amount. Please enter a positive numeric value." << endl;
        }
        else if (amount <= 0)
            std::cout << "Invalid amount. Please enter a positive number.\n";
        else if (amount % 5 != 0)
            std::cout << "Invalid amount. Please enter a multiple of 5.\n";
        else if (amount > 10000)
            std::cout << "Deposit limit exceeded. You can deposit a maximum of $10,000 at a time.\n";

    } while (amount <= 0 || amount % 5 != 0 || amount > 10000);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return amount;
}

int getAmountToWithdraw()
{
    int amount;
    do
    {
        std::cout << "Enter the amount to withdraw (multiple of 5): ";
        std::cin >> amount;

        if (cin.fail() || amount < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid amount. Please enter a positive numeric value." << endl;
        }
        else if (amount % 5 != 0)
        {
            std::cout << "Invalid amount. Please enter a multiple of 5.\n";
        }
        else if (amount > 10000)
        {
            std::cout << "Withdrawal limit exceeded. You can withdraw a maximum of $10,000 at a time.\n";
        }
    } while (amount < 0 || amount % 5 != 0 || amount > 10000);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return amount;
}

// This Function To Get a PinCode From User
std::string readPinCode(const std::string &message)
{
    std::string pinCode;

    while (true)
    {
        std::cout << message;
        std::cin >> pinCode;

        // Check if the input was invalid
        if (std::cin.fail() || pinCode.length() != 4 || !std::all_of(pinCode.begin(), pinCode.end(), [](char c)
                                                                     { return std::isdigit(static_cast<unsigned char>(c)); }))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input! Pin Code should be a 4-digit numeric value." << std::endl;
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }

    return pinCode;
}

// Function to convert a number to its textual representation
std::string NumberToText(const long long& number)
{
    // Check if the number is zero
    if (number == 0)
    {
        return "";
    }

    // Check if the number is negative
    if (number < 0)
    {
        return "Negative " + NumberToText(-number);
    }

    // Handle numbers from 1 to 19
    if (number >= 1 && number <= 19)
    {
        std::string unitsText[] =
        {
            "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
            "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
        };
        return unitsText[number] + " ";
    }

    // Handle numbers from 20 to 99
    if (number >= 20 && number <= 99)
    {
        std::string tensText[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        return tensText[number / 10] + " " + NumberToText(number % 10);
    }

    // Handle numbers from 100 to 999
    if (number >= 100 && number <= 999)
    {
        return NumberToText(number / 100) + "Hundred " + NumberToText(number % 100);
    }

    // Handle numbers from 1000 to 1999
    if (number >= 1000 && number <= 1999)
    {
        return "One Thousand " + NumberToText(number % 1000);
    }
    // Handle numbers from 2000 to 999,999
    if (number >= 2000 && number <= 999999)
    {
        return NumberToText(number / 1000) + "Thousands " + NumberToText(number % 1000);
    }

    // Handle numbers from 1,000,000 to 1,999,999
    if (number >= 1000000 && number <= 1999999)
    {
        return "One Million " + NumberToText(number % 1000000);
    }
    // Handle numbers from 2,000,000 to 999,999,999
    if (number >= 2000000 && number <= 999999999)
    {
        return NumberToText(number / 1000000) + "Millions " + NumberToText(number % 1000000);
    }

    // Handle numbers from 1,000,000,000 to 1,999,999,999
    if (number >= 1000000000 && number <= 1999999999)
    {
        return "One Billion " + NumberToText(number % 1000000000);
    }
    // Handle numbers from 2,000,000,000 to 999,999,999,999
    if (number >= 2000000000 && number <= 999999999999)
    {
        return NumberToText(number / 1000000000) + "Billions " + NumberToText(number % 1000000000);
    }

    // Handle numbers from 1,000,000,000,000 to 1,999,999,999,999  "I Can't Read these Numbers :")😂"
    if (number >= 1000000000000 && number <= 1999999999999)
    {
        return "One Trillion " + NumberToText(number % 1000000000000);
    }
    else
    {
        return NumberToText(number / 1000000000000) + "Trillions " + NumberToText(number % 1000000000000);
    }
}

// Function to convert a number to its textual representation
std::string convertNumberToText(const long long& number)
{
    std::string text = NumberToText(number);
    if(text.empty())
        return "Zero";
    return text;
}

bool convertLineToRecord(const string &line, stClientData &client, const string &separator = "##")
{
    vector<string> clientData = splitString(line, separator);
    if (clientData.size() != 6)
    {
        return false; // Error: Incorrect number of data elements
    }
    client.AccountNumber = clientData[0];
    client.PinCode = clientData[1];
    client.Name = clientData[2];
    client.Phone = clientData[3];
    client.AccountBalance = std::stod(clientData[4]);
    client.isEnteringPINCodeWrong = std::stoi(clientData[5]);
    return true;
}

string convertRecordToLine(const stClientData &client, const string &Separator = "##")
{
    string stringClientRecord;

    stringClientRecord += client.AccountNumber + Separator;
    stringClientRecord += client.PinCode + Separator;
    stringClientRecord += client.Name + Separator;
    stringClientRecord += client.Phone + Separator;
    stringClientRecord += to_string(client.AccountBalance) + Separator;
    stringClientRecord += to_string(client.isEnteringPINCodeWrong);

    return stringClientRecord;
}

void saveClientsDataToFile()
{
    fstream MyFile;
    MyFile.open(CLIENTS_FILENAME, ios::out); // overwrite
    string dataLine;
    if (MyFile.is_open())
    {
        for (const stClientData &client : VECTOR_OF_CLIENTS)
        {
            dataLine = convertRecordToLine(client, "##");
            MyFile << dataLine << endl;
        }
        MyFile.close();
    }
}

vector<stClientData> loadClientsDataFromFile(const string &filePath)
{
    vector<stClientData> vClients;
    std::ifstream file(filePath);
    if (file.is_open())
    {
        std::string line;
        stClientData client;
        while (std::getline(file, line))
        {
            if (convertLineToRecord(line, client, "##"))
            {
                vClients.push_back(client);
            }
            else
            {
                std::cerr << "Unexpected Error While Reading Clients Line.: " << std::endl;
                break;
            }
        }
        file.close();
    }
    else
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }
    return vClients;
}

bool findClientByAccountNumberAndPinCode(const string &accountNumber, const string &pinCode)
{
    VECTOR_OF_CLIENTS = loadClientsDataFromFile(CLIENTS_FILENAME);
    int counter = 0;
    for (const stClientData &client : VECTOR_OF_CLIENTS)
    {
        if (client.AccountNumber == accountNumber && client.PinCode == pinCode)
        {
            CURRENT_CLIENT = client;
            INDEX_OF_CURRENT_CLIENT = counter;
            return true;
        }
        counter++;
    }
    return false;
}

bool checkClientInfo(const string &accountNumber, const string &pinCode)
{
    if (findClientByAccountNumberAndPinCode(accountNumber, pinCode))
        return true;
    else
        return false;
}

bool depositBalance(const double &Amount)
{
    char Answer = 'n';
    cout << "\n\nAre you sure you want perform this transaction? (Y/N): ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        CURRENT_CLIENT.AccountBalance += Amount;

        // refresh Client date
        VECTOR_OF_CLIENTS.at(INDEX_OF_CURRENT_CLIENT) = CURRENT_CLIENT;
        saveClientsDataToFile();

        cout << "\n\nDone Successfully. New balance is: " << CURRENT_CLIENT.AccountBalance;
        return true;
    }
    return false;
}

void showDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";
    cout << "The maximum Deposit limit is $10,000 at a time\n";
    double amount = getAmountToDeposit();
    depositBalance(amount);
}

void showQuickWithdrawScreen()
{
    // Check If the Client balance is Zero
    if (CURRENT_CLIENT.AccountBalance == 0)
    {
        cout << "Your balance is currently zero. You are unable to withdraw funds at this time.";
        return;
    }

    const short withdrawalAmounts[] = {20, 50, 100, 200, 400, 600, 800, 1000};

    cout << "\n==============================================\n";
    cout << "\t\tQuick Withdraw";
    cout << "\n==============================================\n";
    cout << "\t[1] 20          \t[2] 50\n";
    cout << "\t[3] 100         \t[4] 200\n";
    cout << "\t[5] 400         \t[6] 600\n";
    cout << "\t[7] 800         \t[8] 1000\n";
    cout << "\t\t   [9] Exit\n";
    cout << "==============================================\n";
    cout << "Your Ballance Is: " << CURRENT_CLIENT.AccountBalance << "\n";

    short choice;
    choice = getInputInRange(1, 9, "Choose an option [1 to 9]?: ");

    if (choice == 9)
        return;

    short selectedAmount = withdrawalAmounts[choice - 1];
    // Validate that the amount does not exceeds the balance i.e not bigger than balance
    while (selectedAmount > CURRENT_CLIENT.AccountBalance)
    {
        cout << "\nAmount exceeds the balance. You can withdraw up to: " << CURRENT_CLIENT.AccountBalance << endl;
        cout << "Please enter another amount: ";
        choice = getInputInRange(1, 9, "Choose an option [1 to 9]?: ");
        if (choice == 9)
        {
            goBackToMainMenu();
            return;
        }
        selectedAmount = withdrawalAmounts[choice - 1];
    }

    depositBalance(-selectedAmount);
}

void showNormalWithdrawScreen()
{
    // Check If the Client balance is Zero
    if (CURRENT_CLIENT.AccountBalance == 0)
    {
        cout << "Your balance is currently zero. You are unable to withdraw funds at this time.";
        return;
    }

    cout << "\n==============================================\n";
    cout << "\t\tNormal Withdraw";
    cout << "\n==============================================\n";
    cout << "The maximum withdrawal limit is $10,000 at a time\n";
    double amount;
    amount = getAmountToWithdraw();

    if (amount <= 0)
    {
        cout << "Invalid amount. Withdrawal canceled.";
        return;
    }

    while (amount > CURRENT_CLIENT.AccountBalance)
    {
        cout << "\nAmount exceeds the balance. You can withdraw up to: " << CURRENT_CLIENT.AccountBalance << endl;
        cout << "Please enter another amount: ";
        amount = getAmountToWithdraw();
    }
    depositBalance(-amount);
}

void showCheckBallanceScreen()
{
    cout << "\n-------------------------------------\n";
    cout << "\tCheck Ballance Screen";
    cout << "\n-------------------------------------\n";

    cout << "Your Ballance Is: " << CURRENT_CLIENT.AccountBalance << endl;
    cout << convertNumberToText((int)CURRENT_CLIENT.AccountBalance);

    int fractionalPart = static_cast<int>(round((CURRENT_CLIENT.AccountBalance - int(CURRENT_CLIENT.AccountBalance)) * 100));
    if (fractionalPart > 0)
        cout << "And " << convertNumberToText(fractionalPart) << "cent.";
}

void showChangePinCodeScreen()
{
    cout << "\n==============================================\n";
    cout << "\t\tChange Pin Code";
    cout << "\n==============================================\n";

    string oldPinCode;
    int counter = 0;
    while (true)
    {
        oldPinCode = readPinCode("Enter Old Pin Code: ");
        if (CURRENT_CLIENT.PinCode == oldPinCode)
        {
            break;
        }
        cout << "Incorrect old Pin Code. Please try again.\n";
        counter++;

        if (counter == 3)
        {
            CURRENT_CLIENT.isEnteringPINCodeWrong = true;
            VECTOR_OF_CLIENTS.at(INDEX_OF_CURRENT_CLIENT) = CURRENT_CLIENT;
            saveClientsDataToFile();
            cout << "You have entered the old PIN incorrectly three times. Please contact the bank.\n";
            system("pause > nul");
            login();
        }
    }

    string newPinCode;
    string confirmPinCode;
    do
    {
        newPinCode = readPinCode("Enter New Pin Code: ");
        confirmPinCode = readPinCode("Re-enter New Pin Code: ");
        if (newPinCode != confirmPinCode)
        {
            cout << "The entered PIN codes do not match. Please try again.\n";
        }
    } while (newPinCode != confirmPinCode);

    // Update the pin code for the current client
    CURRENT_CLIENT.PinCode = newPinCode;
    VECTOR_OF_CLIENTS.at(INDEX_OF_CURRENT_CLIENT) = CURRENT_CLIENT;
    saveClientsDataToFile();

    cout << "Pin Code has been successfully changed.\n";
}

void goBackToMainMenu()
{
    cout << "\n\nPress any key to go back to Main Menu...";
    system("pause > nul");
    showMainMenu();
}

void performMainMenuOption(enMainMenuOptions MainMenuOption)
{
    switch (MainMenuOption)
    {
    case enMainMenuOptions::eQuickWithdraw:
        system("cls");
        showQuickWithdrawScreen();
        goBackToMainMenu();
        break;
    case enMainMenuOptions::eNormalWithdraw:
        system("cls");
        showNormalWithdrawScreen();
        goBackToMainMenu();
        break;
    case enMainMenuOptions::eDeposit:
        system("cls");
        showDepositScreen();
        goBackToMainMenu();
        break;
    case enMainMenuOptions::eCheckBallance:
        system("cls");
        showCheckBallanceScreen();
        goBackToMainMenu();
        break;
    case enMainMenuOptions::eChangePinCode:
        system("cls");
        showChangePinCodeScreen();
        goBackToMainMenu();
        break;
    case enMainMenuOptions::eLogout:
        system("cls");
        login();
        break;
    }
}

void showMainMenu()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t   Main Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Ballance.\n";
    cout << "\t[5] Change PinCode.\n";
    cout << "\t[6] Logout.\n";
    cout << "===========================================\n";

    enMainMenuOptions Choice;
    Choice = (enMainMenuOptions)getInputInRange(1, 6, "Choose What DO You Want To DO [1 to 6]?: ");
    performMainMenuOption(Choice);
}

void login()
{
    bool loginFailed = false;
    string accountNumber, pinCode;
    int PINWrongInputTime = 0;
    do
    {
        system("cls");
        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";
        if (loginFailed)
        {
            cout << "Invalid accountNumber or pinCode!\n";
        }
        cout << "Enter AccountNumber: ";
        cin >> accountNumber;
        cout << "Enter Pin: ";
        cin >> pinCode;
        loginFailed = !checkClientInfo(accountNumber, pinCode);
    } while (loginFailed);

    if(CURRENT_CLIENT.isEnteringPINCodeWrong == true)
    {
        system("cls");
        cout << "Your account has been temporarily suspended for security reasons. Please contact the bank for further assistance and to resolve the issue.\n";
        return;
    }
    showMainMenu();
}

int main()
{
    login();
    system("pause > nul");
    return 0;
}
