# Client Management System

**Client Management System** is a simple command-line program written in C++ that enables you to manage client records efficiently. You can perform various operations such as adding new clients, updating client information, deleting clients, finding clients by account number, and displaying a list of all clients.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Code Review](#code-review)
- [Notes](#notes)
- [Author](#author)

## Introduction

This program provides a user-friendly command-line interface for interacting with the Client Management System. It displays a main menu with options for different operations, and users can easily select their desired action by entering the corresponding menu number.

Client records are stored in a structured format, with each record representing a client and containing important fields such as account number, PIN code, name, phone number, and account balance. The records are read from and written to the `Clients.txt` file, utilizing a specific delimiter ("##") to separate the fields.

The system includes various utility functions that handle essential tasks such as user input validation, file operations, and data manipulation. These functions ensure data correctness and integrity.

## Features

- **Adding New Clients:** Easily add new clients to the system by providing essential details like account number, PIN code, name, phone number, and account balance.

- **Updating Client Information:** Seamlessly update existing client information by entering their account number and providing the updated details.

- **Deleting Clients:** Efficiently remove a client from the system by specifying their account number.

- **Finding Clients:** Quickly locate a client by their account number and view their details.

- **Displaying All Clients:** Obtain a comprehensive list of all clients currently stored in the system.

## Getting Started

Follow these steps to get started with the Client Management System:

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

Here are key points about the code structure and implementation:

- The program utilizes file I/O to read and write client data to a file named `Clients.txt`. The file is read and loaded into memory when the program starts, with changes saved back to the file as necessary.

- The `stClientData` struct represents a client record, storing information like the account number, PIN code, name, phone number, account balance, and a flag to mark records for deletion.

- Various helper functions handle critical tasks such as input validation, string manipulation, and file operations.

- Main functionality is organized into separate functions for different operations, such as adding clients, updating client information, deleting clients, and finding clients.

- The program uses a vector to store and manipulate client records in memory.

- The code includes error handling for file operations and invalid input.

## Notes

- The project assumes a specific format for the `Clients.txt` file, where each line represents a client record with fields separated by "##". Modifications to the file format may necessitate corresponding code adjustments.

- The provided code assumes that the input data is well-formed. Depending on specific requirements and use cases, you may need to enhance error handling for a broader range of scenarios.

## Author

- Mahmoud Mohamed
- Email: mahmoud.abdalaziz@outlook.com
- LinkedIn: [Mahmoud Mohamed Abdalaziz](https://www.linkedin.com/in/mahmoud-mohamed-abd/)

---

**Note:** This project is intended as a training exercise to demonstrate basic programming skills and concepts. It is not suitable for use as a full-fledged real-world application and may lack advanced features or security measures required for production systems.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.