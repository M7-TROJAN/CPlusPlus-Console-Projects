# ATM System Project

Welcome to the ATM System Project, a simple implementation of an Automated Teller Machine using C++. This project allows users to perform various banking operations, including deposits, withdrawals, balance inquiries, and PIN code changes.

## Features

- **Login:** Users can securely log in using their account number and PIN code.
- **Quick Withdrawal:** Choose from predefined withdrawal amounts for swift transactions.
- **Normal Withdrawal:** Enter a custom withdrawal amount as needed.
- **Deposit:** Easily deposit funds into your account.
- **Check Balance:** View your account balance with a simple inquiry.
- **Change PIN Code:** Enhance security by updating your PIN code.
- **Logout:** Safely end your session when done.

## Requirements

- C++ compiler
- Integrated development environment (IDE) such as Visual Studio or a code editor like VSCode.

## Usage

1. Compile the source code using a C++ compiler.
2. Run the compiled executable.
3. Choose from the following account numbers: A120, A150, A160, A190, A145, S400, V200, X900, F890. The default PIN for all accounts is 0000.
4. Follow the on-screen instructions to navigate the ATM system.

## Data Storage

Client data is stored in `Clients.txt`. Each line represents a client record with the following fields, separated by the `##` delimiter:

1. Account Number
2. PIN Code
3. Name
4. Phone
5. Account Balance
6. Failed PIN Attempts

## Limitations

- The application supports a maximum deposit limit of $10,000 per transaction.
- Withdrawal amounts must be multiples of $5 and up to $10,000.
- PIN codes must be 4-digit numeric values.

## Contributions

Contributions to the ATM System Project are highly appreciated! If you have ideas, improvements, or bug fixes, please feel free to modify the code to suit your needs. If you have questions or suggestions, don't hesitate to reach out.

## License

This ATM System Project is open-source and available for anyone to use and modify.

## Note

The project assumes a specific format for the Clients.txt file, where each line represents a client record with fields separated by "##". Any changes to the file format may require modifications in the code.

Please note that this code does not include error handling for all possible scenarios, and it assumes the input data is well-formed. You may need to enhance the code based on your specific requirements and use cases.

Feel free to modify and adapt the code to suit your needs. If you have any further questions, please let me know!

## Important Note

This project serves as a programming exercise to demonstrate fundamental coding skills. It is not intended for use as a real-world banking application and lacks advanced features and security measures required for production systems.

## very Important Note

The project within this repository serves as a testament to my adeptness in fundamental programming skills and concepts, meticulously crafted to showcase the extent of my capabilities.

## Author

- Mahmoud Mohamed
- Email: mahmoud.abdalaziz@outlook.com
- LinkedIn: [Mahmoud Mohamed](https://www.linkedin.com/in/mahmoud-mohamed-abd/)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
