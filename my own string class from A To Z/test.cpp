// Copyright (c) [2021] [Mahmoud Mohamed]
// Licensed under the MIT License.

#include <cstring>
#include <iostream>
#include "str.h"

using namespace std;

int main()
{
    STR str1 = "Mahmoud Mohamed Abdalaziz Mattar";

    vector<STR> vec = str1.split();

    for(STR &st : vec)
    {
        cout << st << endl;
    }

    STR str2 = STR::join(vec);

    cout << str2 << endl;

    str1.invertAllLettersCase();
    cout << str1 << endl;

    STR str5 = "mahmoud! mattar%$ / a*&l^i";

    str5.removePunctLetters();

    cout << str5 << endl;

    cout << str5.countSpecificLetter('M',0);

    return 0;

    return 0;
}
