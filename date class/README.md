# date.h - A Date Manipulation Library

`date.h` is a C++ library that provides a set of functions for manipulating dates, calculating date differences, and performing various operations involving dates and periods.

## Features

- Increment and decrement dates.
- Calculate differences between dates.
- Check for valid dates.
- Calculate the number of days in a month.
- Determine business days and weekends.
- Manipulate date periods.
- Convert dates to strings and vice versa.

## Installation

1. Download the `date.h` file and include it in your C++ project.
2. Include the `date.h` header in your source code:

```cpp
#include "date.h"

```

## Usage

## Date Manipulation

```cpp
stDate currentDate = getCurrentDate();
stDate nextDay = IncreaseDateByOneDay(currentDate);
stDate previousMonth = DecreaseDateByOneMonth(currentDate);
// ... and more 
```

## Date Difference Calculation

```cpp
stDate date1 = {12, 7, 2023};
stDate date2 = {25, 7, 2023};
int daysDifference = differenceBetween2Dates(date1, date2, true);
// ... and more 
```

## Period Manipulation

```cpp
stPeriod vacation = ReadPeriod();
int vacationLength = PeriodLengthInDays(vacation, true);
// ... and more 
```

## Date Validation

```cpp
stDate inputDate = readDate("Enter a date: ");
if (isValidDate(inputDate)) {
    // Do something with valid date
} else {
    // Handle invalid date
}
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments
The date.h library was inspired by the need for a simple and efficient date manipulation tool in C++. Special thanks to the community and 
all my friends and everyone for their feedback and contributions 🙏🙏❤️.



Feel free to modify and adapt the library's functions according to your needs.

For more information and examples, refer to the provided functions and usage in the library's source files.

## ## Author
Created by [Mahmoud Mohamed]
- Email: mahmoud.abdalaziz@outlook.com
- LinkedIn: [Mahmoud Mohamed Abdalaziz](https://www.linkedin.com/in/mahmoud-mohamed-abd/)