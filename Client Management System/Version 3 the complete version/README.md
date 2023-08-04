# Client Management System

This is a simple command-line Client Management System program written in C++. It allows you to perform various operations on client records, such as adding new clients, updating client information, deleting clients, finding clients by account number, displaying a list of all clients, and performing transactions.

The program provides a command-line interface where users can interact with the system. It displays a main menu with options for different operations. Users can choose the desired operation by entering the corresponding menu number.

The client records are stored in a structured format, where each record represents a client and contains fields such as account number, PIN code, name, phone number, and account balance. The records are read from and written to the `Clients.txt` file using a specific delimiter ("##") to separate the fields.

## New Features

- **Login interface**: The program now includes a login interface. To access the main screen, you must enter the username and password registered in the database, which is a text file (Flat File Database). User credentials are stored in a text file named "Users.txt" attached to the program files.

- **User roles and permissions**: Each user is assigned a specific role, with the administrator having full capabilities such as editing customers, deleting, adding, and comprehensive control over user data and permissions. Other users may have one or more specific permissions tailored to their role.

- **Flexibility to modify user permissions**: You can modify user permissions by logging in as an admin. Administrators have the flexibility to modify user permissions either through the program interface or by directly editing the "Users.txt" file (not recommended). It's important to note that manual modification of the file is discouraged. Modifying user permissions through the program interface ensures data integrity and reduces the risk of potential errors.

- **User data storage**: User data is stored in the "Users.txt" file. Each user's information is organized in a structured format using the "##" delimiter to separate the fields. The file follows the structure: `username##password##permissions`.

    Here's an example of user data stored in the "Users.txt" file:
    ```
    admin##admin##-1
    mahmoud##1234##16
    Ahmed##1234##32
    ```

    In the example above, each line represents a user entry, where the username is followed by the password and permissions associated with that user, all separated by the "##" delimiter.

The program includes various utility functions for handling user input validation, file operations, data manipulation, and transaction processing. These functions ensure the correctness and integrity of the client records and perform transaction operations such as deposit and withdrawal.

## Important Note

This project is intended for training purposes and demonstrates skills in file handling, word processing, logical reasoning, and other relevant areas. The provided source code includes functions for managing client data, such as creating new clients, updating client information, depositing balance, and deleting clients. The code implements basic functionalities for a client management system. Please note that this is a simplified project and may not include advanced features or security measures that would be required in a real-world application.

## Features

- **Adding new clients**: You can add new clients to the system by providing their account number, pin code, name, phone number, and account balance.
- **Updating client information**: You can update the information of an existing client by entering their account number and then providing the updated details.
- **Deleting clients**: You can delete a client from the system by specifying their account number.
- **Finding clients**: You can find a client by their account number and view their details.
- **Displaying all clients**: You can view a list of all clients currently stored in the system.
- **Transactions**: You can perform transactions such as deposit and withdrawal on client accounts.

## How to Run the Program

1. Make sure you have a C++ compiler installed on your system.
2. Clone the repository from GitHub.
3. Open the project in your preferred C++ development environment.
4. Build and compile the source code.
5. Run the executable file generated.

## Usage

1. Compile and run the program using a C++ compiler.
2. The program will display a main menu with options for different operations.
3. Choose an option by entering the corresponding number and pressing Enter.
4. Follow the prompts and provide the required information.
5. The program will perform the selected operation and display the result or any relevant messages.
6. After completing an operation, you will be returned to the main menu.
7. To exit the program, choose the "Exit" option from the main menu.

## Code Review

Here are some key points about the code structure and implementation:

- The program uses file I/O to read and write client data to a file named `Clients.txt`. The file is read and loaded into memory when the program starts, and changes are saved back to the file when necessary.
- The `stClientData` struct represents a client record and stores the account number, pin code, name, phone number, account balance, and a flag to mark records for deletion.
- The program provides various helper functions to handle input validation, string manipulation, file operations, and data manipulation.
- The main functionality is divided into separate functions for each operation, such as adding clients, updating clients, deleting clients, finding clients, and performing transactions.
- The program uses a vector to store and manipulate client records in memory.
- The code includes error handling for file operations, invalid input, and transaction processing.

## Note

The project assumes a specific format for the `Clients.txt` file, where each line represents a client record with fields separated by "##". Any changes to the file format may require modifications in the code.

Please note that this code does not include error handling for all possible scenarios, and it assumes the input data is well-formed. You may need to enhance the code based on your specific requirements and use cases.

Feel free to modify and adapt the code to suit your needs. If you have any further questions, please let me know!

## Very Important Note

This Client Management System project is a training exercise designed to demonstrate basic programming skills and concepts. It is not intended to be used as a real-world application and may not include advanced features or security measures required for production systems.

## Author

- Mahmoud Mohamed
- Email: mahmoud.abdalaziz@outlook.com
- LinkedIn: [Mahmoud Mohamed Abdalaziz](https://www.linkedin.com/in/mahmoud-mohamed-abd/)


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.