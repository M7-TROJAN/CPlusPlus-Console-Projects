// str.h
#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H

#include <string>
#include <vector>
#include <algorithm>
#include <random> // for random_device, mt19937, uniform_int_distribution

class str : public std::string
{
    // Function to invert the case of a character
    char invertLetterCase(char ch)
    {
        // If the character is uppercase, convert it to lowercase; otherwise, convert it to uppercase
        return std::isupper(ch) ? std::tolower(ch) : std::toupper(ch);
    }

    // Convert all letters to lowercase
    std::string lower(const std::string &oroginal)
    {
        std::string s = oroginal;
        for (char &c : s)
        {
            c = std::tolower(c);
        }
        return s;
    }

public:
    str() : std::string("") {}                    // Default Constructor
    str(const char *s) : std::string(s) {}        // Constructor that accepts const char*
    str(const std::string &s) : std::string(s) {} // Constructor that accepts a string
    str(const str &s) : std::string(s) {}         // Constructor that accepts another str object

    // Function to capitalize the first letter of each word in a string
    str &capitalizeFirstLetterOfEachWord()
    {
        bool isNewWord = true;
        for (char &ch : *this)
        { // Access the base std::string
            if (isNewWord && ch != ' ')
                ch = toupper(ch);
            isNewWord = (ch == ' ' ? true : false);
        }
        return *this;
    }

    // Function to Lowercased the first letter of each word in a string
    str &lowercaseFirstLetterOfEachWord()
    {
        bool isNewWord = true;
        for (char &ch : *this)
        { // Access the base std::string
            if (isNewWord && ch != ' ')
                ch = tolower(ch);
            isNewWord = (ch == ' ' ? true : false);
        }
        return *this;
    }

    // InvertAllStringLettersCase is a function to invert the case of all letters
    str &InvertAllStringLettersCase()
    {
        // Iterate over each character
        for (char &c : *this)
        {
            // Call the invertLetterCase function to invert the case of the character
            c = invertLetterCase(c);
        }
        return *this;
    }

    // Function to count the number of lowercase letters in a string
    int countLowerLetters()
    {
        int lowerLettersCount = 0;
        for (const char &ch : *this)
        {
            if (std::islower(ch))
                lowerLettersCount++;
        }
        return lowerLettersCount;
    }

    // Function to count the number of uppercase letters in a string
    int countUpperLetters()
    {
        int upperLettersCount = 0;
        for (const char &ch : *this)
        {
            if (std::isupper(ch))
                upperLettersCount++;
        }
        return upperLettersCount;
    }

    // Function to count the occurrences of a specific letter in a given string
    int countSpecificLetter(char target, bool MatchCase = true)
    {
        int count = 0;
        for (const char &ch : *this)
        {
            if (MatchCase)
            {
                if (ch == target)
                    count++;
            }
            else
            {
                if (tolower(ch) == tolower(target))
                    count++;
            }
        }
        return count;
    }

    // Function to Check if the Given Character Is a Vowel or Not
    static bool isVowel(char ch)
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

    // Function to count the occurrences of vowel letters in a given string
    int countVowelLetters()
    {
        int count = 0;
        for (const char &ch : *this)
        {
            if (isVowel(ch))
                count++;
        }
        return count;
    }

    // This function counts the number of words in a given string
    size_t countWords()
    {
        std::string sentence = *this;
        const std::string delimiter = " ";
        std::string currentWord;
        size_t wordCount = 0;

        // Iterate through the sentence to extract and count each word
        size_t delimiterPos = 0;
        while ((delimiterPos = sentence.find(delimiter)) != std::string::npos)
        {
            currentWord = sentence.substr(0, delimiterPos);
            if (!currentWord.empty())
            {
                wordCount++;
            }
            sentence.erase(0, delimiterPos + delimiter.length());
        }

        // Count the last word if it exists
        if (!sentence.empty())
        {
            wordCount++;
        }

        return wordCount;
    }

    // This function splits a string into words using a delimiter
    std::vector<std::string> splitString(const std::string &delimiter = " ")
    {
        std::vector<std::string> words;
        std::string currentWord;

        // Iterate through the string to extract and add each word to the vector
        size_t delimiterPos = 0;
        std::string remainingStr = *this; // Store the remaining string for manipulation
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

    // This function joins a vector of strings into a single string using a delimiter
    str &join(const std::vector<std::string> &vString, const std::string &delimiter = " ")
    {
        if (vString.empty())
            return *this;

        str result = "";
        for (int i = 0; i < vString.size(); i++)
        {
            result += vString.at(i);
            if (i != vString.size() - 1)
                result += delimiter;
        }
        if (!(*this).empty())
        {
            trimRight();
            *this = *this + " " + result;
        }
        else
        {
            *this = result;
        }
        return *this;
    }

    /// Join an array of strings into the current string using a delimiter
    str &join(const std::string arr[], const short &arrLength, const str &delimiter = " ")
    {
        str result = "";
        for (int i = 0; i < arrLength; i++)
        {
            result += arr[i];
            if (i != arrLength - 1)
                result += delimiter;
        }

        if (!(*this).empty())
        {
            trimRight();
            *this = *this + " " + result;
        }
        else
        {
            *this = result;
        }

        return *this;
    }

    // Trim the leading spaces from the string
    str &trimLeft()
    {
        size_t pos = find_first_not_of(' ');
        if (pos != std::string::npos)
        {
            (*this) = substr(pos);
        }
        return *this;
    }

    // Trim the trailing spaces from the string
    str &trimRight()
    {
        size_t pos = find_last_not_of(' ');
        if (pos != std::string::npos)
        {
            (*this) = substr(0, pos + 1);
        }
        return *this;
    }

    // Trim the leading and trailing spaces from the string
    str &trim()
    {
        return trimLeft().trimRight();
    }

    // Reverse the order of words in the string
    str &reverse_words()
    {
        std::string result = ""; // Initialize an empty string to store the reversed words
        std::string temp = "";   // Initialize an empty string to store each word temporarily

        for (int i = 0; i < (*this).length(); i++)
        {
            if ((*this)[i] == ' ')
            {
                // If a space is encountered, it means the current word is complete
                // Append the temporary word to the result string along with a space
                result = temp + " " + result;
                temp = ""; // Reset the temporary string for the next word
            }
            else
            {
                // If a non-space character is encountered, append it to the temporary string
                temp += (*this)[i];
            }
        }

        // Add the last word to the result string (there is no space after the last word)
        result = temp + " " + result;

        // Remove the last space
        result.pop_back();

        (*this) = result; // Update the current string with the reversed words
        return (*this);
    }

    // Convert all letters to lowercase
    str &lowerAllStringLetters()
    {
        for (char &c : *this)
        {
            c = std::tolower(c);
        }
        return *this;
    }

    // Convert all letters to uppercase
    str &upperAllStringLetters()
    {
        for (char &c : *this)
        {
            c = std::toupper(c);
        }
        return *this;
    }

    /* This function replaces occurrences of a substring in a given string, with optional case sensitivity.
    It splits the original string into words, and for each word, checks if it matches the old substring.
    If a match is found, the word is replaced with the new substring.
    The modified words are then joined back into a single string and returned. */
    str &replaceWord(const std::string &oldSubstr, const std::string &newSubstr, bool matchCase = true)
    {
        // Split the original string into words
        std::vector<std::string> words = splitString(" ");

        // Iterate over each word
        for (std::string &word : words)
        {
            // Check if the case should be matched or ignored
            if (matchCase)
            {
                // If case should be matched, replace the word if it matches the old substring
                if (word == oldSubstr)
                    word = newSubstr;
            }
            else
            {
                // If case should be ignored, replace the word if it matches the old substring (case-insensitive)
                if (lower(word) == lower(oldSubstr))
                    word = newSubstr;
            }
        }

        *this = "";
        *this = join(words);
        return *this;
    }

    // Function to remove all punctuation letters
    str &removeAllPunctLetters()
    {
        std::string modifiedStr = *this;

        /*
        Iterate over the string in reverse order
        By iterating over the string in reverse order,
        the characters will be safely removed without affecting the correctness of the results.
        */
        for (int i = modifiedStr.length() - 1; i >= 0; i--)
        {
            // Check if the character is a punctuation letter
            if (ispunct(modifiedStr[i]))
                modifiedStr.erase(i, 1); // Remove the punctuation letter
        }

        *this = modifiedStr;
        return *this;
    }

    // Function to check if a string is all capital letters
    bool isAllCaps()
    {
        return std::all_of(begin(), end(), [](char c)
                           { return std::isupper(c); });
    }

    // Function to check if a string is all lower letters
    bool isAllLower()
    {
        return std::all_of(begin(), end(), [](char c)
                           { return std::islower(c); });
    }

    // Function to generate a strong password
    static std::string GeneratePassword()
    {
        const int PASSWORD_LENGTH = 16;
        const std::string CHARACTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        std::random_device rd;                                           // creates a random_device object to obtain a seed for the random number generator
        std::mt19937 gen(rd());                                          // creates a mersenne_twister_engine seeded with the random_device object
        std::uniform_int_distribution<> dis(0, CHARACTERS.length() - 1); // creates a uniform integer distribution object for generating random numbers between 0 and the length of the character set - 1

        std::string password = "";
        for (int i = 0; i < PASSWORD_LENGTH; i++)
        {
            password += CHARACTERS[dis(gen)]; // generate a random character from the character set
        }

        return password;
    }
};
#endif // CUSTOM_STRING_H
