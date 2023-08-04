// Copyright (c) [2021] [Mahmoud Mohamed]
// Licensed under the MIT License.

#ifndef STR_H
#define STR_H

#include <cstring>
#include <iostream>
#include <vector>

class STR
{
private:
    char *_Data;
    size_t _Length;

    // concatenation operator
    friend STR operator+(const STR &str1, const STR &str2)
    {
        char *tempData = new char[str1._Length + str2._Length + 1];
        strcpy_s(tempData, str1._Length + str2._Length + 1, str1._Data);
        strcat_s(tempData, str1._Length + str2._Length + 1, str2._Data);
        STR result(tempData);
        delete[] tempData;
        return result;
    }

    // Function to invert the case of a character
    char invertLetterCase(char ch)
    {
        // If the character is uppercase, convert it to lowercase; otherwise, convert it to uppercase
        return std::isupper(ch) ? std::tolower(ch) : std::toupper(ch);
    }

    // Function to Check if the Given Character Is a Vowel or Not
    bool isVowel(char ch)
    {
        ch = tolower(ch);
        switch (ch)
        {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
        }
    }

public:
    // static constant for "not found" (npos)
    static const size_t npos = static_cast<size_t>(-1);

    // static method to Join a vector of STR objects into a single STR object using a delimiter
    static STR join(const std::vector<STR> &vString, const STR &delimiter = " ")
    {
        STR result;
        for (size_t i = 0; i < vString.size(); i++)
        {
            result += vString[i];
            if (i != vString.size() - 1)
                result += delimiter;
        }
        return result;
    }

    // static method to Join an array of STR objects into a single STR object using a delimiter
    static STR join(const STR arr[], const size_t &arrLength, const STR &delimiter = " ")
    {
        STR result;
        for (size_t i = 0; i < arrLength; i++)
        {
            result += arr[i];
            if (i != arrLength - 1)
                result += delimiter;
        }
        return result;
    }

    // Constructor
    STR(const char *str = "")
    {
        _Length = std::strlen(str);
        _Data = new char[_Length + 1];
        strcpy_s(_Data, _Length + 1, str);
    }

    // Copy constructor
    STR(const STR &other)
    {
        _Length = other._Length;
        _Data = new char[_Length + 1];
        strcpy_s(_Data, _Length + 1, other._Data);
    }

    // Destructor
    ~STR()
    {
        delete[] _Data;
    }

    // Overloading the insertion operator (<<)
    friend std::ostream &operator<<(std::ostream &os, const STR &str)
    {
        os << str._Data;
        return os;
    }

    // Overloading the extraction operator (>>)
    friend std::istream &operator>>(std::istream &is, STR &str)
    {
        // Read input from the stream
        const size_t bufferSize = 1024;
        char buffer[bufferSize];
        is.getline(buffer, bufferSize);

        // Assign the read input to the STR object
        str = buffer;

        return is;
    }

    // Overloading the subscript operator []
    char &operator[](size_t index)
    {
        if (index >= _Length)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
        return _Data[index];
    }

    // Const version of the subscript operator []
    const char &operator[](size_t index) const
    {
        if (index >= _Length)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
        return _Data[index];
    }

    // assignment operator for STR objects
    STR &operator=(const STR &source)
    {
        if (this != &source)
        {
            delete[] _Data;
            _Length = source._Length;
            _Data = new char[_Length + 1];
            strcpy_s(_Data, _Length + 1, source._Data);
        }
        return *this;
    }

    // assignment operator for const char* "array of character"
    STR &operator=(const char *str)
    {
        delete[] _Data;
        _Length = std::strlen(str);
        _Data = new char[_Length + 1];
        strcpy_s(_Data, _Length + 1, str);
        return *this;
    }

    // Overloading the += operator for STR
    STR &operator+=(const STR &str)
    {
        // Calculate the new length for the combined strings
        size_t newLength = _Length + str._Length;

        // Allocate memory for the new string
        char *newData = new char[newLength + 1];

        // Copy the current data to the new buffer
        strcpy_s(newData, newLength + 1, _Data);

        // Append the data from the other string
        strcat_s(newData, newLength + 1, str._Data);

        // Deallocate the old data and update the pointer and length
        delete[] _Data;
        _Data = newData;
        _Length = newLength;

        return *this;
    }

    // Overloading the += operator for char
    STR &operator+=(char ch)
    {
        // Calculate the new length for the combined string
        size_t newLength = _Length + 1;

        // Allocate memory for the new string
        char *newData = new char[newLength + 1];

        // Copy the current data to the new buffer
        strcpy_s(newData, newLength + 1, _Data);

        // Append the character at the end
        newData[newLength - 1] = ch;

        // Null-terminate the string
        newData[newLength] = '\0';

        // Deallocate the old data and update the pointer and length
        delete[] _Data;
        _Data = newData;
        _Length = newLength;

        return *this;
    }

    // Method to get the length of the string
    size_t length() const
    {
        return _Length;
    }

    // Clear the content of the STR object and make it empty
    void clear()
    {
        _Length = 0;
        delete[] _Data;
        _Data = new char[1];
        strcpy_s(_Data, 1, "\0");
    }

    // Check if the STR object is empty
    bool empty() const
    {
        return _Length == 0;
    }

    // Method to get the last character of the STR object
    char back()
    {
        return _Length == 0 ? '\0' : _Data[_Length - 1];
    }

    // Method to get the first character of the STR object
    char front()
    {
        return _Length == 0 ? '\0' : _Data[0];
    }

    // Method to get a C-style string
    const char *c_style_str() const
    {
        return _Data;
    }

    // Append method for C-style strings
    STR &append(const char *newStr)
    {
        // Calculate the new length for the combined strings
        size_t newLength = _Length + std::strlen(newStr);

        // Allocate memory for the new string
        char *newData = new char[newLength + 1];

        // Copy the current data to the new buffer
        strcpy_s(newData, newLength + 1, _Data);

        // Append the data from the other string
        strcat_s(newData, newLength + 1, newStr);

        // Deallocate the old data and update the pointer and length
        delete[] _Data;
        _Data = newData;
        _Length = newLength;

        return *this;
    }

    // Append method for STR objects
    STR &append(const STR &str)
    {
        // Calculate the new length for the combined strings
        size_t newLength = _Length + str._Length;

        // Allocate memory for the new string
        char *newData = new char[newLength + 1];

        // Copy the current data to the new buffer
        strcpy_s(newData, newLength + 1, _Data);

        // Append the data from the other string
        strcat_s(newData, newLength + 1, str._Data);

        // Deallocate the old data and update the pointer and length
        delete[] _Data;
        _Data = newData;
        _Length = newLength;

        return *this;
    }

    // at method to access characters at a specific index
    char &at(size_t index)
    {
        if (index >= _Length)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
        return _Data[index];
    }

    // Const version of at method for read-only access
    const char &at(size_t index) const
    {
        if (index >= _Length)
        {
            throw std::out_of_range("Error: Index out of range.");
        }
        return _Data[index];
    }

    // Method to remove the last character from the STR object
    STR &pop_back()
    {
        if (_Length > 0)
        {
            _Length--;
            char *newData = new char[_Length + 1];
            strncpy_s(newData, _Length + 1, _Data, _Length);
            newData[_Length] = '\0';
            delete[] _Data;
            _Data = newData;
        }
        return *this;
    }

    // Method to append a character to the end of the STR object
    STR &push_back(char ch)
    {
        size_t newLength = _Length + 1;

        char *newData = new char[newLength + 1];
        strcpy_s(newData, newLength + 1, _Data);
        newData[newLength - 1] = ch;
        newData[newLength] = '\0';

        delete[] _Data;
        _Data = newData;
        _Length = newLength;

        return *this;
    }

    // Method to assign a new string to the STR object
    STR &assign(const char *newStr)
    {
        delete[] _Data;
        _Length = std::strlen(newStr);
        _Data = new char[_Length + 1];
        strcpy_s(_Data, _Length + 1, newStr);
        return *this;
    }

    // Method to erase characters from the string
    STR &erase(size_t startPos, size_t count = 1)
    {
        if (startPos >= _Length || startPos < 0)
        {
            // If the starting position is out of range or negative, do nothing.
            return *this;
        }

        // Adjust the count to ensure we don't go beyond the string length.
        count = std::min(count, _Length - startPos);

        // Calculate the new length after erasing characters.
        size_t newLength = _Length - count;

        // Allocate memory for the new string.
        char *newData = new char[newLength + 1];

        // Copy the part of the string before the erase position.
        strncpy_s(newData, newLength + 1, _Data, startPos);

        // Copy the part of the string after the erased characters.
        strcpy_s(newData + startPos, newLength - startPos + 1, _Data + startPos + count);

        // Deallocate the old data and update the pointer and length.
        delete[] _Data;
        _Data = newData;
        _Length = newLength;

        return *this;
    }

    // Method to insert a substring into the string
    STR &insert(size_t pos, const STR &str)
    {
        if (pos > _Length)
        {
            throw std::out_of_range("Error: Insert position out of range.");
        }

        // Calculate the new length after inserting the substring.
        size_t newLength = _Length + str._Length;

        // Allocate memory for the new string.
        char *newData = new char[newLength + 1];

        // Copy the part of the string before the insertion position.
        strncpy_s(newData, newLength + 1, _Data, pos);

        // Copy the inserted substring.
        strcpy_s(newData + pos, newLength - pos + 1, str._Data);

        // Copy the part of the string after the inserted substring.
        strcpy_s(newData + pos + str._Length, newLength - pos - str._Length + 1, _Data + pos);

        // Deallocate the old data and update the pointer and length.
        delete[] _Data;
        _Data = newData;
        _Length = newLength;

        return *this;
    }

    // Method to find the position of a substring within the string
    size_t find(const STR &str, size_t pos = 0) const
    {
        // Get the length of the substring to search for
        size_t searchLength = str._Length;

        // If the substring is empty, return position 0 (it's always found at the beginning)
        if (searchLength == 0)
            return 0;

        // If the substring is longer than the main string, return npos
        if (searchLength > _Length)
            return npos;

        // Adjust the search range based on the pos parameter
        size_t maxStart = _Length - searchLength;
        for (size_t i = pos; i <= maxStart; i++)
        {
            if (strncmp(_Data + i, str._Data, searchLength) == 0)
            {
                // Substring found, return the position
                return i;
            }
        }

        // Substring not found, return a special value (npos)
        return STR::npos;
    }

    // Method to extract a substring from the string
    STR substr(size_t position, size_t length = npos) const
    {
        // If position is out of range, throw an exception
        if (position >= _Length)
        {
            throw std::out_of_range("Error: Position out of range.");
        }

        // If length is npos or longer than remaining characters, adjust length
        if (length == npos || position + length > _Length)
        {
            length = _Length - position;
        }

        // Create a new STR object with the extracted substring
        STR result;
        result._Data = new char[length + 1];
        strncpy_s(result._Data, length + 1, _Data + position, length);
        result._Data[length] = '\0';
        result._Length = length;

        return result;
    }

    // Replace substring with another substring
    STR &replace(const STR &target, const STR &replacement)
    {
        // Find the first occurrence of the target substring
        size_t startPos = find(target);

        while (startPos != STR::npos)
        {
            // Erase the target substring
            erase(startPos, target.length());

            // Insert the replacement substring at the same position
            insert(startPos, replacement);

            // Find the next occurrence of the target substring
            startPos = find(target, startPos + replacement.length());
        }

        return *this;
    }

    // Method to reverse the characters of the STR object
    STR &reverse()
    {
        size_t left = 0;
        size_t right = _Length - 1;

        while (left < right)
        {
            char temp = _Data[left];
            _Data[left] = _Data[right];
            _Data[right] = temp;

            left++;
            right--;
        }

        return *this;
    }

    // This method splits a STR object into words using a delimiter and return a vector of these words
    std::vector<STR> split(const STR &delimiter = " ") const
    {
        std::vector<STR> words;
        STR currentWord;

        // Iterate through the STR object to extract and add each word to the vector
        size_t delimiterPos = 0;
        STR remainingStr(*this); // Create a copy of the current STR object for manipulation
        while ((delimiterPos = remainingStr.find(delimiter)) != STR::npos)
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

    // method to capitalize the first letter of each word
    STR &capitalizeFirstLetterOfEachWord()
    {
        bool isNewWord = true;
        for (size_t i = 0; i < _Length; i++)
        {
            char &ch = _Data[i];
            if (isNewWord && ch != ' ')
                ch = toupper(ch);
            isNewWord = (ch == ' ' ? true : false);
        }
        return *this;
    }

    // method to Lowercased the first letter of each word
    STR &lowercaseFirstLetterOfEachWord()
    {
        bool isNewWord = true;
        for (size_t i = 0; i < _Length; i++)
        {
            char &ch = _Data[i];
            if (isNewWord && ch != ' ')
                ch = tolower(ch);
            isNewWord = (ch == ' ' ? true : false);
        }
        return *this;
    }

    // InvertAllStringLettersCase is a method to invert the case of all letters
    STR &invertAllLettersCase()
    {
        for (size_t i = 0; i < _Length; i++)
        {
            _Data[i] = invertLetterCase(_Data[i]);
        }
        return *this;
    }

    // method to count the number of lowercase letters
    int countLowerLetters()
    {
        int lowerLettersCount = 0;
        for (size_t i = 0; i < _Length; i++)
        {
            if (std::islower(_Data[i]))
                lowerLettersCount++;
        }
        return lowerLettersCount;
    }

    // method to count the number of uppercase letters
    int countUpperLetters()
    {
        int upperLettersCount = 0;
        for (size_t i = 0; i < _Length; i++)
        {
            if (std::isupper(_Data[i]))
                upperLettersCount++;
        }
        return upperLettersCount;
    }

    // method to count the occurrences of a specific letter in STR object
    int countSpecificLetter(char target, bool MatchCase = true)
    {
        int count = 0;
        for (size_t i = 0; i < _Length; i++)
        {
            if (MatchCase)
            {
                if (_Data[i] == target)
                    count++;
            }
            else
            {
                if (tolower(_Data[i]) == tolower(target))
                    count++;
            }
        }
        return count;
    }

    // Function to count the vowel letters in a STR object
    int countVowelLetters()
    {
        int count = 0;
        for (size_t i = 0; i < _Length; i++)
        {
            if (isVowel(_Data[i]))
                count++;
        }
        return count;
    }

    // Method to count the number of words in a STR object
    size_t countWords()
    {
        const char delimiter = ' ';
        size_t wordCount = 0;
        bool isNewWord = true;

        for (size_t i = 0; i < _Length; i++)
        {
            if (_Data[i] == delimiter)
            {
                isNewWord = true;
            }
            else if (isNewWord)
            {
                isNewWord = false;
                wordCount++;
            }
        }

        return wordCount;
    }

    // Method to reverse the order of words in the STR object
    STR &reverseWords()
    {
        STR result = ""; // Initialize an empty STR to store the reversed words
        STR temp = "";   // Initialize an empty STR to store each word temporarily

        for (size_t i = 0; i < _Length; i++)
        {
            if (_Data[i] == ' ')
            {
                // If a space is encountered, it means the current word is complete
                // Append the temporary word to the result STR along with a space
                result = temp + STR(" ") + result;
                temp = STR(); // Reset the temporary STR for the next word
            }
            else
            {
                // If a non-space character is encountered, append it to the temporary STR
                temp += _Data[i];
            }
        }

        // Add the last word to the result STR (there is no space after the last word)
        result = temp + STR(" ") + result;

        // Remove the last space
        result.pop_back();

        // Assign the reversed words back to the current STR object
        *this = result;

        return *this;
    }

    // Trim the leading spaces from the STR object
    STR &trimLeft()
    {
        size_t start = 0;
        while (start < _Length && _Data[start] == ' ')
        {
            start++;
        }

        if (start > 0)
        {
            // Shift the data to remove spaces
            size_t newLength = _Length - start;
            char *newData = new char[newLength + 1];
            strncpy_s(newData, newLength + 1, _Data + start, newLength);
            newData[newLength] = '\0';

            // Deallocate the old data and update the pointer and length
            delete[] _Data;
            _Data = newData;
            _Length = newLength;
        }

        return *this;
    }

    // Trim the trailing spaces from the STR object
    STR &trimRight()
    {
        size_t end = _Length - 1;
        while (end > 0 && _Data[end] == ' ')
        {
            end--;
        }

        if (end < _Length - 1)
        {
            // Truncate the string to remove trailing spaces
            _Data[end + 1] = '\0';
            _Length = end + 1;
        }

        return *this;
    }

    // Trim the leading and trailing spaces from the STR object
    STR &trim()
    {
        trimLeft();
        trimRight();
        return *this;
    }

    // Method to check if the STR object contains all capital letters
    bool isAllCaps() const
    {
        for (size_t i = 0; i < _Length; i++)
        {
            if (!std::isupper(_Data[i]))
                return false;
        }
        return true;
    }

    // Method to check if the STR object contains all lowercase letters
    bool isAllLower() const
    {
        for (size_t i = 0; i < _Length; i++)
        {
            if (!std::islower(_Data[i]))
                return false;
        }
        return true;
    }

    // Method to remove all punctuation letters from a the STR object
    STR &removePunctLetters()
    {
        /*
        Iterate over the string in reverse order
        By iterating over the string in reverse order,
        the characters will be safely removed without affecting the correctness of the results.
        */
        for (int i = _Length - 1; i >= 0; i--)
        {
            // Check if the character is a punctuation letter
            if (ispunct(_Data[i]))
                erase(i); // Remove the punctuation letter
        }

        return *this;
    }
};

#endif // STR_H