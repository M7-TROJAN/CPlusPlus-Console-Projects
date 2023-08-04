#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

struct stUser
{
    string userName;
    string password;
    int permissions = 0;
    bool markForDelete = false;
};

stUser CurrentUser;

struct stClientData
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance = 0.0;
    bool MarkForDelete = false;
};

enum enMainMenuOptions
{
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eTransactions = 6,
    eManageUsers = 7,
    eLogOut = 8
};

enum enTransactionsMenuOptions
{
    eDeposit = 1,
    eWithdraw = 2,
    eTotalBalances = 3,
    eMainMenu = 4
};

enum enManageUsersMenuOptions
{
    eListUsers = 1,
    eAddNewUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eMainMene = 6
};


enum enMainMenuPermissions
{
    eAll = -1,
    pListClients = 1,
    pAddNewClient = 2,
    pDeleteClient = 4,
    pUpdateClients = 8,
    pFindClient = 16,
    pTransactions = 32,
    pManageUsers = 64
};

void ShowMainMenu();
void GoBackToMainMenu();
void ShowTransactionsMenu();
void ShowManageUsersMenu();
bool CheckAccessPermission(enMainMenuPermissions Permission);
void login();

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

// This Function To Get a Positive Number From User
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

// This Function To Get a PinCode From User
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

// This Function To Converts a number to its textual representation
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
            "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };

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

bool ConvertLineToRecord(const string& line, stClientData& client, const string& separator = "##")
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

stUser ConvertUserLineToRecord(const string& line, const string& separator = "##")
{
    stUser User;
    vector<string> vUserData;
    vUserData = splitString(line, separator);
    User.userName = vUserData[0];
    User.password = vUserData[1];
    User.permissions = stoi(vUserData[2]);
    return User;
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

string ConvertUserRecordToLine(stUser User, string separator = "##")
{
    string stClientRecord = "";
    stClientRecord += User.userName + separator;
    stClientRecord += User.password + separator;
    stClientRecord += to_string(User.permissions);
    return stClientRecord;
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

bool UserExistsByUsername(string Username, string FileName)
{
    ifstream MyFile;
    MyFile.open(FileName);
    if (MyFile.is_open())
    {
        string Line;
        stUser User;
        while (getline(MyFile, Line))
        {
            User = ConvertUserLineToRecord(Line);
            if (User.userName == Username)
            {
                MyFile.close();
                return true;
            }
        }
        MyFile.close();
    }
    return false;
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

int ReadPermissionsToSet()
{
    int Permissions = 0;
    char Answer = 'n';
    cout << "\nDo you want to give full access (y/n)? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        return -1; // Return -1 to indicate full access
    }

    cout << "\nPlease choose the permissions to grant:\n";
    cout << "---------------------------------------\n";

    cout << "Show Clients List? (y/n) ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {

        Permissions += enMainMenuPermissions::pListClients;
    }

    cout << "Add New Clients? (y/n) ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::pAddNewClient;
    }

    cout << "Delete Clients? (y/n) ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::pDeleteClient;
    }

    cout << "Update Client? (y/n) ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::pUpdateClients;
    }

    cout << "Find Client? (y/n) ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::pFindClient;
    }

    cout << "Perform Transactions? (y/n) ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::pTransactions;
    }

    cout << "Manage Users? (y/n) ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y')
    {
        Permissions += enMainMenuPermissions::pManageUsers;
    }

    return Permissions;
}

stUser ReadNewUser()
{
    stUser User;
    cout << "Enter Username: ";
    getline(cin >> ws, User.userName);
    while (UserExistsByUsername(User.userName, UsersFileName))
    {
        cout << "\nUser with username [" << User.userName << "] already exists. Please enter another username: ";
        getline(cin >> ws, User.userName);
    }
    cout << "Enter Password? ";
    getline(cin, User.password);
    User.permissions = ReadPermissionsToSet();
    return User;
}

vector<stUser> loadUsersDataFromFile(const string& filePath)
{
    vector<stUser> vUsers;
    std::ifstream file(filePath);
    if (file.is_open())
    {
        string Line;
        stUser User;
        while (getline(file, Line))
        {
            User = ConvertUserLineToRecord(Line);
            vUsers.push_back(User);
        }
        file.close();
    }
    return vUsers;
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

void PrintUserRecordLine(stUser User)
{
    cout << "| " << setw(15) << left << User.userName;
    cout << "| " << setw(10) << left << User.password;
    cout << "| " << setw(40) << left << User.permissions;
}

void PrintClientRecordBalanceLine(const stClientData& Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAccessDeniedMessage()
{
    cout << "\n================================================\n";
    cout << "\t\tAccess Denied\n";
    cout << "You don't have permission to perform this action.\n";
    cout << "Please contact your administrator for assistance.\n";
    cout << "=================================================\n";
}

void ShowAllClientsScreen()
{
    if (!CheckAccessPermission(enMainMenuPermissions::pListClients))
    {
        ShowAccessDeniedMessage();
        return;
    }
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

void ShowAllUsersScreen()
{
    vector<stUser> vUsers = loadUsersDataFromFile(UsersFileName);
    cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    if (vUsers.size() == 0)
        cout << "\t\t\t\tNo Users Available In the System!";
    else
        for (stUser User : vUsers)
        {
            PrintUserRecordLine(User);
            cout << endl;
        }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
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
    cout << "\t\t\t\t" << NumberToText((int)TotalBalances);
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

void PrintUserCard(stUser User)
{
    cout << "\nThe following are the user details:\n";
    cout << "-----------------------------------";
    cout << "\nUsername : " << User.userName;
    cout << "\nPassword : " << User.password;
    cout << "\nPermissions : " << User.permissions;
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

bool FindUserByUsername(const string& Username, const vector<stUser>& vUsers, stUser& User)
{
    for (const stUser& U : vUsers)
    {
        if (U.userName == Username)
        {
            User = U;
            return true;
        }
    }
    return false;
}

bool findUserByUsernameAndPassword(const string& Username, const string& Password, stUser& User)
{
    vector<stUser> vUsers = loadUsersDataFromFile(UsersFileName);
    for (const stUser& U : vUsers)
    {
        if (U.userName == Username && U.password == Password)
        {
            User = U;
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

stUser ChangeUserRecord(string Username)
{
    stUser User;
    User.userName = Username;
    cout << "\n\nEnter Password: ";
    getline(cin >> ws, User.password);
    User.permissions = ReadPermissionsToSet();
    return User;
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

bool MarkUserForDeleteByUsername(const string& Username, vector<stUser>& vUsers)
{
    for (stUser& U : vUsers)
    {
        if (U.userName == Username)
        {
            U.markForDelete = true;
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
                // we only write records that are not marked for delete.
                DataLine = convertRecordToLine(C, "##");
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
}

vector<stUser> SaveUsersDataToFile(const string& FileName, const vector<stUser>& vUsers)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (stUser U : vUsers)
        {
            if (U.markForDelete == false)
            {
                // we only write records that are not marked for delete.
                DataLine = ConvertUserRecordToLine(U);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUsers;
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

void AddNewUser()
{
    stUser User;
    User = ReadNewUser();
    AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(User));
}

void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {
        cout << "Adding New User:\n\n";
        AddNewUser();
        cout << "\nUser Added Successfully. Do you want to add more Users? (Y/N): ";
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

bool DeleteUserByUsername(string Username, vector<stUser>& vUsers)
{
    if (Username == "admin")
    {
        cout << "\n\nYou cannot Delete This User.";
        return false;
    }

    stUser User;
    char Answer = 'n';
    if (FindUserByUsername(Username, vUsers, User))
    {
        PrintUserCard(User);
        cout << "\n\nAre you sure you want delete this User?(Y/N): ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByUsername(Username, vUsers);
            SaveUsersDataToFile(UsersFileName, vUsers);
            // Refresh Users
            vUsers = loadUsersDataFromFile(UsersFileName);
            cout << "\n\nUser Deleted Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with Username (" << Username << ") is Not Found!";
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

bool UpdateUserByUsername(string Username, vector<stUser>& vUsers)
{
    stUser User;
    char Answer = 'n';
    if (FindUserByUsername(Username, vUsers, User))
    {
        PrintUserCard(User);
        cout << "\n\nAre you sure you want update this User?(Y/N):  ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (stUser& U : vUsers)
            {
                if (U.userName == Username)
                {
                    U = ChangeUserRecord(Username);
                    break;
                }
            }
            SaveUsersDataToFile(UsersFileName, vUsers);
            cout << "\n\nUser Updated Successfully.";
            return true;
        }
    }
    else
    {
        cout << "\nUser with Account Number (" << Username << ")  is Not Found !";
    }
    return false;
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber: ";
    cin >> AccountNumber;
    return AccountNumber;
}

string ReadUserName()
{
    string Username = "";
    cout << "\nPlease enter Username: ";
    cin >> Username;
    return Username;
}

void ShowListUsersScreen()
{
    ShowAllUsersScreen();
}

void ShowAddNewUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New User Screen";
    cout << "\n-----------------------------------\n";
    AddNewUsers();
}

void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Users Screen";
    cout << "\n-----------------------------------\n";
    vector<stUser> vUsers = loadUsersDataFromFile(UsersFileName);
    string Username = ReadUserName();
    DeleteUserByUsername(Username, vUsers);
}

void ShowUpdateUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Users Screen";
    cout << "\n-----------------------------------\n";
    vector<stUser> vUsers = loadUsersDataFromFile(UsersFileName);
    string Username = ReadUserName();
    UpdateUserByUsername(Username, vUsers);
}

void ShowDeleteClientScreen()
{
    if (!CheckAccessPermission(enMainMenuPermissions::pDeleteClient))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenu();
        return;
    }
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";
    vector<stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{
    if (!CheckAccessPermission(enMainMenuPermissions::pUpdateClients))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenu();
        return;
    }
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";
    vector<stClientData> vClients = LoadClientsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowAddNewClientsScreen()
{
    if (!CheckAccessPermission(enMainMenuPermissions::pAddNewClient))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenu();
        return;
    }
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";
    AddNewClients();
}

void ShowFindClientScreen()
{
    if (!CheckAccessPermission(enMainMenuPermissions::pFindClient))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenu();
        return;
    }
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

void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";
    vector<stUser> vUsers = loadUsersDataFromFile(UsersFileName);
    stUser User;
    string Username = ReadUserName();
    if (FindUserByUsername(Username, vUsers, User))
        PrintUserCard(User);
    else
        cout << "\nUser with Username [" << Username << "] is not found !";
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

bool CheckAccessPermission(enMainMenuPermissions Permission)
{
    if (CurrentUser.permissions == enMainMenuPermissions::eAll)
        return true;
    if ((Permission & CurrentUser.permissions) == Permission)
        return true;
    else
        return false;
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

void GoBackToManageUsersMenu()
{
    cout << "\n\nPress any key to go back to Manage Users Menu...";
    system("pause > nul");
    ShowManageUsersMenu();
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
    if (!CheckAccessPermission(enMainMenuPermissions::pTransactions))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenu();
        return;
    }

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

void PerformManageUsersMenuOption(enManageUsersMenuOptions ManageUsersMenuOption)
{
    switch (ManageUsersMenuOption)
    {
    case enManageUsersMenuOptions::eListUsers:
        system("cls");
        ShowListUsersScreen();
        GoBackToManageUsersMenu();
        break;

    case enManageUsersMenuOptions::eAddNewUser:
        system("cls");
        ShowAddNewUserScreen();
        GoBackToManageUsersMenu();
        break;

    case enManageUsersMenuOptions::eDeleteUser:
        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageUsersMenu();
        break;

    case enManageUsersMenuOptions::eUpdateUser:
        system("cls");
        ShowUpdateUserScreen();
        GoBackToManageUsersMenu();
        break;

    case enManageUsersMenuOptions::eFindUser:
        system("cls");
        ShowFindUserScreen();
        GoBackToManageUsersMenu();
        break;

    case enManageUsersMenuOptions::eMainMene:
        ShowMainMenu();
    }
}

void ShowManageUsersMenu()
{
    if (!CheckAccessPermission(enMainMenuPermissions::pManageUsers))
    {
        ShowAccessDeniedMessage();
        GoBackToMainMenu();
        return;
    }
    system("cls");
    cout << "===========================================\n";
    cout << "\tManage Users Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menu.\n";
    cout << "===========================================\n";

    enManageUsersMenuOptions Choice;
    Choice = (enManageUsersMenuOptions)getInputInRange(1, 6, "Choose What DO You Want To DO [1 to 6]?: ");
    PerformManageUsersMenuOption(Choice);
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
    case enMainMenuOptions::eManageUsers:
        system("cls");
        ShowManageUsersMenu();
        break;
    case enMainMenuOptions::eLogOut:
        system("cls");
        login();
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
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";

    enMainMenuOptions Choice;
    Choice = (enMainMenuOptions)getInputInRange(1, 8, "Choose What DO You Want To DO [1 to 8]?: ");
    PerformMainMenuOption(Choice);
}

bool LoadUserInfo(string Username, string Password)
{
    if (findUserByUsernameAndPassword(Username, Password, CurrentUser))
        return true;
    else
        return false;
}

void login()
{
    bool LoginFailed = false;
    string Username, Password;
    do
    {
        system("cls");
        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";
        if (LoginFailed)
        {
            cout << "Invalid Username or Password!\n";
        }
        cout << "Enter Username: ";
        cin >> Username;
        cout << "Enter Password: ";
        cin >> Password;
        LoginFailed = !LoadUserInfo(Username, Password);
    } while (LoginFailed);
    ShowMainMenu();
}

int main()
{
    login();
    std::cin.get();
    return 0;
}

/*
Note: Use the following credentials to log in with full access:

Username: admin
Password: admin

*/