# Custom String Class (str)

This is a custom C++ string class `str` that extends the functionality of the standard `std::string` class. It provides additional methods for manipulating strings, such as capitalizing words, inverting letter cases, counting letters, generating passwords, and more.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Usage](#usage)
- [Contact](#contact)

## Introduction

The `str` class is designed to provide enhanced string manipulation capabilities beyond what's offered by the standard `std::string` class. It extends the functionality of the standard class with various utility methods for working with strings.

## Features

- Capitalize the first letter of each word in a string.
- Convert all letters to lowercase or uppercase.
- Invert the case of all letters in a string.
- Count the occurrences of specific letters or types of letters.
- Generate strong passwords.
- Trim leading and trailing spaces from a string.
- Reverse the order of words in a string.
- Replace occurrences of substrings with optional case sensitivity.
- Check if a string consists of all capital or lowercase letters.

## Usage

To use the `str` class, include the `custom_string.h` header file in your C++ code:

```cpp
#include "custom_string.h"

int main() {
    str s = "Hello, World!";
    
    // Example usage of methods
    s.capitalizeFirstLetterOfEachWord();
    s.lowerAllStringLetters();
    s.invertAllStringLettersCase();
    // ... and so on
    
    return 0;
}
```
## Contact
For any inquiries or questions, please contact [mahmoud.abdalaziz@outlook.com].

Happy coding!

[Mahmoud Mohamed]
- Email: mahmoud.abdalaziz@outlook.com
- LinkedIn: [Mahmoud Mohamed Abdalaziz](https://www.linkedin.com/in/mahmoud-mohamed-abd/)

