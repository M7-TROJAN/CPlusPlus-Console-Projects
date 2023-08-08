# Custom String Class (str.h)

![GitHub last commit](https://img.shields.io/github/last-commit/mattar740/CustomStringClass)
![GitHub stars](https://img.shields.io/github/stars/mattar740/CustomStringClass)
![GitHub forks](https://img.shields.io/github/forks/mattar740/CustomStringClass)

The STR class is a custom implementation inspired by the standard string class in C++ with additional methods to manipulate and analyze strings. It provides various features for string manipulation, including concatenation, character case conversion, substring extraction, word count, and more. 
This README.md file explains the features and usage of the STR class.

## Table of Contents

- [Features](#features)
- [Features](#list_of_methods)
- [Usage](#usage)
- [How to Use](#How_to_Use)
- [Examples](#Examples)
- [Code Review](#Code_Review)
- [Note](#Note)
- [Very Important Note](#Very_Important_Note)
- [Acknowledgments](#Acknowledgments)
- [Author](#Author)
- [License](#License)

## Features

- **Concatenation:** Easily concatenate two STR objects using the `+` operator.
- **Character Manipulation:** Invert the case of characters, check for vowels, count lower/uppercase letters, and more.
- **Element Access:** Access characters at specific indices using the subscript operator `[]`.
- **Substring Operations:** Extract substrings, replace substrings, reverse word order, and count words.
- **Case Conversion:** Convert the case of the entire string or first letters of words.
- **Trimming:** Remove leading/trailing spaces from the string.
- **Utility Functions:** Get string length, check if empty, find specific characters, and more.

## list_of_methods
You can see a list of all methods implemented in the `STR` class from here [list of methods](Implemented_Methods)

## How_to_Use

1. Clone this repository from GitHub.
2. Open the project in your C++ development environment.
3. Include the `str.h` header file in your project to use the custom string class.
4. Build and compile the source code.

## Usage

To use the `str` class, copy 'STR.h' file to your project folder include the `str.h` header file in your C++ code:

```cpp
#include "str.h"

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

## Examples
Here are some examples of using the STR class:

# Example1:
```cpp
#include "str.h"
#include <iostream>

int main() {
    STR str1 = "Hello";
    STR str2 = " World!";
    
    STR result = str1 + str2;
    
    std::cout << result << std::endl; // Output: "Hello World!"
    
    result.pop_back();

    std::cout << result << std::endl; // Output: "Hello World"

    result.push_back('!');

    std::cout << result << std::endl; // Output: "Hello World!"


    result += " i'm mahmoud"
    std::cout << result << std::endl; // Output: "Hello World! i'm mahmoud"

    // And more than 35 other methods that you can discover
    
    return 0;
}
```
# Example2:
```cpp
#include "str.h"
#include <iostream>

int main() {
    STR str1 = "hello world";
    str1.capitalizeFirstLetterOfEachWord();  // "Hello World"

    STR str2 = "this Is A Test";
    str2.lowercaseFirstLetterOfEachWord();        // "this is a test"

    STR str3 = "ThIs Is A MiXeD cAsE StRiNg";
    str3.invertAllStringLettersCase();          // "tHiS iS a mIxEd CaSe sTrInG"

    size_t wordCount = str3.countWords();       // Count words: 6

    str3.reverseWords();                        // "StRiNg CaSe MiXeD A Is ThIs"

    bool allCaps = str3.isAllCaps();             // false
    bool allLower = str3.isAllLower();           // false

    // And more than 35 other methods that you can discover

    return 0;
}
```
# Example3:
```cpp
#include "str.h"
#include <iostream>
using namespace std;

int main() {
    STR str1 = "hello world!";
    vector<STR> vec = str1.split();

    for(STR &str : vec)
    {
        cout << str << endl;
    }

    // Output: 
    // Hello 
    // World!

    STR str2 = str2.join(vec);
    cout << str2 << endl; // Output: Hello World!

    // And more than 35 other methods that you can discover

    return 0;
}
```
## Code_Review

- The STR class provides functionality similar to the standard std::string class.
- It includes methods for concatenation, character manipulation, case conversion, and more.
- The class is well-documented and includes comments explaining each method.
- Error handling is implemented for index out of range and other possible issues.
- The code uses dynamic memory allocation and appropriate memory management.

## Note

This Custom String Class project is a demonstration of string manipulation concepts in C++. It may not include all features or optimizations of a production-level string class.

## Very_Important_Note
This Custom String Class project is a training exercise designed to demonstrate basic programming skills and concepts. It is not intended to be used as a replacement for the standard std::string class in real-world applications.

## Acknowledgments

I would like to express my heartfelt gratitude to my teacher, Mohammed Abu-Hadhoud, for his guidance, support, and inspiration throughout the development of this Custom String Class project. His dedication to teaching and commitment to helping his students succeed have been invaluable. Thank you, MR. Mohammed, for your unwavering encouragement and mentorship 🙏❤️.

- Teacher: Mohammed Abu-Hadhoud
- LinkedIn: [Mohammed Abu-Hadhoud](https://www.linkedin.com/in/abuhadhoud/)
- Website: [Programming Advices](https://programmingadvices.com/)

## Author

- Mahmoud Mohamed
- Email: mahmoud.abdalaziz@outlook.com
- LinkedIn: [Mahmoud Mohamed Abdalaziz](https://www.linkedin.com/in/mahmoud-mohamed-abd/)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
