#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;
const string ClientsFileName = "Clients.txt";
void ShowMainMenu();
void ShowTransactionsMenu();
struct stClientData
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0.0;
    bool MarkForDelete = false;
};
// This function splits a string into words using a delimiter
std::vector<std::string> splitString(const std::string& str, const std::string& delimiter)
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

bool ConvertLineToRecord(const string& line, stClientData& client, const string& separator = ", ")
{
    vector<string> clientData = splitString(line, separator);
    if (clientData.size() != 5)
    {
        return false; // Error: Incorrect number of data elements
    }
    client.AccountNumber = clientData[0];
    client.PinCode = clientData[1];
    client.Name = clientData[2];
    client.Phone = clientData[3];
    client.AccountBalance = std::stod(clientData[4]);
    return true;
}
string convertRecordToLine(const stClientData& client, const string& Separator = ", ")
{
    string stringClientRecord;

    stringClientRecord += client.AccountNumber + Separator;
    stringClientRecord += client.PinCode + Separator;
    stringClientRecord += client.Name + Separator;
    stringClientRecord += client.Phone + Separator;
    stringClientRecord += to_string(client.AccountBalance);

    return stringClientRecord;
}

bool ClientExistsByAccountNumber(const string& AccountNumber, const string& FileName)
{
    ifstream MyFile;
    MyFile.open(FileName);
    if (MyFile.is_open())
    {
        string line;
        while (getline(MyFile, line))
        {
            if (line.substr(0, AccountNumber.length()) == AccountNumber)
            {
                MyFile.close();
                return true;
            }
        }
        MyFile.close();
    }
    return false;
}

double get_Positive_double(const std::string& message)
{
    double number = 0;
    do
    {
        // Read a double value from the user
        std::cout << message;
        std::cin >> number;

        // Check if the input was invalid (i.e. not an number) or the input was less than 1
        if (std::cin.fail() || number < 1)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid Positive number." << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    } while (true);
    return number;
}

bool isDigit(char c) {
    return std::isdigit(static_cast<unsigned char>(c));
}

std::string readPinCode(const std::string& message)
{
    std::string pinCode;

    while (true)
    {
        std::cout << message;
        std::cin >> pinCode;

        // Check if the input was invalid
        if (std::cin.fail() || pinCode.length() != 4 || !std::all_of(pinCode.begin(), pinCode.end(), [](char c) { return std::isdigit(static_cast<unsigned char>(c)); }))
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

std::string readPhoneNumber(const std::string& message)
{
    std::string phoneNumber;

    while (true)
    {
        std::cout << message;
        std::cin >> phoneNumber;

        if (std::cin.fail() || phoneNumber.length() != 11 || !std::all_of(phoneNumber.begin(), phoneNumber.end(), [](char c) { return std::isdigit(static_cast<unsigned char>(c)); }))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input! Phone number should be a 11-digit numeric value." << std::endl;
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return phoneNumber;
}

stClientData ReadNewClient()
{
    stClientData client;

    cout << "Enter Account Number: ";
    getline(cin >> ws, client.AccountNumber);
    while (ClientExistsByAccountNumber(client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << client.AccountNumber << "] already exists, Please Enter another Account Number: ";
        getline(cin >> ws, client.AccountNumber);
    }

    client.PinCode = readPinCode("Enter Pin Code: ");

    cout << "Enter Name: ";
    getline(cin, client.Name);

    client.Phone = readPhoneNumber("Enter Phone Number: ");

    client.AccountBalance = get_Positive_double("Enter Account Balance: ");

    return client;
}

vector<stClientData> LoadClientsDataFromFile(const string& filePath)
{
    vector<stClientData> vClients;
    std::ifstream file(filePath);
    if (file.is_open())
    {
        std::string line;
        stClientData client;
        while (std::getline(file, line))
        {
            if (ConvertLineToRecord(line, client, "##"))
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

void PrintClientRecordLine(const stClientData& Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
    vector<stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    if (vClients.size() == 0 || vClients.empty())
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (const stClientData& Client : vClients)
        {
            PrintClientRecordLine(Client);
            cout << endl;
        }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

// Function To Converts a number to its textual representation
std::string NumberToText(const long long& number)
{
    if (number == 0)
    {
        return "";
    }

    if (number >= 1 && number <= 19)
    {
        std::string arr[] =
        {
            "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten",
            "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
        };
        return arr[number] + " ";
    }

    if (number >= 20 && number <= 99)
    {
        std::string arr[] = {
            "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

        return arr[number / 10] + " " + NumberToText(number % 10);
    }

    if (number >= 100 && number <= 999)
    {
        return NumberToText(number / 100) + "Hundred " + NumberToText(number % 100);
    }

    if (number >= 1000 && number <= 1999)
    {
        return "One Thousand " + NumberToText(number % 1000);
    }
    if (number >= 2000 && number <= 999999)
    {
        return NumberToText(number / 1000) + "Thousands " + NumberToText(number % 1000);
    }

    if (number >= 1000000 && number <= 1999999)
    {
        return "One Million " + NumberToText(number % 1000000);
    }
    if (number >= 2000000 && number <= 999999999)
    {
        return NumberToText(number / 1000000) + "Millions " + NumberToText(number % 1000000);
    }

    if (number >= 1000000000 && number <= 1999999999)
    {
        return "One Billion " + NumberToText(number % 1000000000);
    }
    if (number >= 2000000000 && number <= 999999999999)
    {
        return NumberToText(number / 1000000000) + "Billions " + NumberToText(number % 1000000000);
    }

    if (number >= 1000000000000 && number <= 1999999999999)
    {
        return "One Trillion " + NumberToText(number % 1000000000000);
    }
    else
    {
        return NumberToText(number / 1000000000000) + "Trillions " + NumberToText(number % 1000000000000);
    }
}

void PrintClientRecordBalanceLine(const stClientData& Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowTotalBalances()
{
    vector <stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;
    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (stClientData Client : vClients)
        {
            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;
            cout << endl;
        }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\tTotal Balances = " << TotalBalances << endl;
    cout << "\t\t\t" << NumberToText(TotalBalances);
}

void PrintClientCard(const stClientData& Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccount Number: " << Client.AccountNumber;
    cout << "\nPin Code : " << Client.PinCode;
    cout << "\nName : " << Client.Name;
    cout << "\nPhone : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}
bool FindClientByAccountNumber(const string& AccountNumber, const vector<stClientData>& vClients, stClientData& Client)
{
    for (const stClientData& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}
stClientData ChangeClientRecord(const string& AccountNumber)
{
    stClientData client;
    client.AccountNumber = AccountNumber;

    client.PinCode = readPinCode("Enter Pin Code: ");

    cout << "Enter Name: ";
    getline(cin, client.Name);

    client.Phone = readPhoneNumber("Enter Phone Number: ");

    client.AccountBalance = get_Positive_double("Enter Account Balance: ");

    return client;
}

bool MarkClientForDeleteByAccountNumber(const string& AccountNumber, vector<stClientData>& vClients)
{
    for (stClientData& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}
void SaveClientsDataToFile(const string& FileName, const vector<stClientData>& vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (const stClientData& C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                // we only write records that are not marked for
                DataLine = convertRecordToLine(C, "##");
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
}

void AddDataLineToFile(const string& FileName, const string& stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}
void AddNewClient()
{
    stClientData Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, convertRecordToLine(Client, "##"));
}
void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        cout << "Adding New Client:\n\n";
        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

bool DeleteClientByAccountNumber(const string& AccountNumber, vector<stClientData>& vClients)
{
    stClientData Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(ClientsFileName, vClients);
            // Refresh Clients
            vClients = LoadClientsDataFromFile(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }
    return false;
}
bool UpdateClientByAccountNumber(const string& AccountNumber, vector<stClientData>& vClients)
{
    stClientData Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client (y/n)?: ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (stClientData& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveClientsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }
    return false;
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";
    vector<stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";
    vector<stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}
void ShowAddNewClientsScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";
    AddNewClients();
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";
    vector<stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    stClientData Client;
    string AccountNumber = ReadClientAccountNumber();
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

bool DepositBalanceToClientByAccountNumber(const string& AccountNumber, const double& Amount, vector<stClientData>& vClients)
{
    char Answer = 'n';
    cout << "\n\nAre you sure you want perform this transaction? y / n? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        for (stClientData& client : vClients)
        {
            if (client.AccountNumber == AccountNumber)
            {
                client.AccountBalance += Amount;
                SaveClientsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << client.AccountBalance;
                return true;
            }
        }
    }
    return false;
}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";
    stClientData Client;
    vector<stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n ";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientCard(Client);
    double Amount = get_Positive_double("Please Enter Deposit Amount: ");
    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";
    stClientData Client;
    vector <stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }
    PrintClientCard(Client);

    // Check If the Client balance is Zero
    if (Client.AccountBalance == 0)
    {
        cout << "Your balance is currently zero. You are unable to withdraw funds at this time.";
        return;
    }

    double Amount = get_Positive_double("Please Enter withdraw Amount: ");

    //Validate that the amount does not exceeds the balance i.e not bigger than balance
    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        Amount = get_Positive_double("Please Enter another Amount: ");
    }
    DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void GoBackToMainMenu()
{
    cout << "\n\nPress any key to go back to Main Menu...";
    system("pause > nul");
    ShowMainMenu();
}

void GoBackToTransactionsMenu()
{
    cout << "\n\nPress any key to go back to Transactions Menu...";
    system("pause > nul");
    ShowTransactionsMenu();
}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}



// Reads an integer value from the user between the given range and returns it
int getInputInRange(const int& from, const int& to, const std::string& message = "")
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

enum enMainMenuOptions
{
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eTransactions = 6,
    eExit = 7
};

enum enTransactionsMenuOptions
{
    eDeposit = 1,
    eWithdraw = 2,
    eTotalBalances = 3,
    eMainMenu = 4
};

void PerformTransactionsOption(enTransactionsMenuOptions TransactionsMenuOption)
{
    switch (TransactionsMenuOption)
    {
    case enTransactionsMenuOptions::eDeposit:
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenu();
        break;
    case enTransactionsMenuOptions::eWithdraw:
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenu();
        break;
    case enTransactionsMenuOptions::eTotalBalances:
        system("cls");
        ShowTotalBalances();
        GoBackToTransactionsMenu();
        break;
    case enTransactionsMenuOptions::eMainMenu:
        system("cls");
        ShowMainMenu();
        break;
    }
}

void ShowTransactionsMenu()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\tTransactions Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menu.\n";
    cout << "===========================================\n";

    enTransactionsMenuOptions Choice;
    Choice = (enTransactionsMenuOptions)getInputInRange(1, 4, "Choose What DO You Want To DO [1 to 4]?: ");
    PerformTransactionsOption(Choice);
}

void PerformMainMenuOption(enMainMenuOptions MainMenuOption)
{
    switch (MainMenuOption)
    {
    case enMainMenuOptions::eListClients:
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eAddNewClient:
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::eTransactions:
        system("cls");
        ShowTransactionsMenu();
        break;
    case enMainMenuOptions::eExit:
        system("cls");
        ShowEndScreen();
        break;
    }
}

void ShowMainMenu()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t   Main Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Exit.\n";
    cout << "===========================================\n";

    enMainMenuOptions Choice;
    Choice = (enMainMenuOptions)getInputInRange(1, 7, "Choose What DO You Want To DO [1 to 7]?: ");
    PerformMainMenuOption(Choice);
}

int main()
{
    ShowMainMenu();
    std::cin.get();
    return 0;
}