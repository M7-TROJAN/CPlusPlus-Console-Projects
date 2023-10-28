#include <iostream>
#include <chrono>
#include <thread>

#ifdef _WIN32 // Windows specific code
#include <windows.h>
#else
#define RESET "\033[0m"
#define RED "\033[31m"   /* Red */
#define BLACK "\033[40m" /* Black */
#define GREEN "\033[32m" /* Green */
#define WHITE "\033[37m" /* White */
#endif

using namespace std;

enum class Color
{
    Green = 2,
    Red = 4,
    Black = 8,
    White = 15
};

class FreePalestine
{
private:
    static constexpr int delayDuration = 4000; // 4 seconds

    void setConsoleColor(Color colorCode)
    {
#ifdef _WIN32 // Windows specific code
        int consoleColor = static_cast<int>(colorCode);
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(consoleHandle, consoleColor);
#else
        string color;
        switch (colorCode)
        {
        case Color::Red:
            color = RED;
            break;
        case Color::Black:
            color = BLACK;
            break;
        case Color::Green:
            color = GREEN;
            break;
        case Color::White:
            color = WHITE;
            break;
        default:
            color = RESET;
            break;
        }
        cout << color;
#endif
    }

    // Function to draw the top part of the flag
    void DrawFlagFirstPart()
    {
        for (int row = 1; row <= 6; row++)
        {
            // Draw The Red Part
            for (int redBlocks = 0; redBlocks < row; redBlocks++)
            {
                setConsoleColor(Color::Red);
                cout << "# ";
            }

            // Draw The Black Part
            for (int blackBlocks = row + 1; blackBlocks <= 51; blackBlocks++)
            {
                setConsoleColor(Color::Black);
                cout << "# ";
            }
            cout << endl;
        }
    }

    // Function to draw the middle part of the flag
    void DrawFlagSecondPart()
    {
        int redBlockCount = 7;
        for (int row = 1; row <= 9; row++)
        {
            // Draw The Red Part
            for (int redBlocks = 1; redBlocks <= redBlockCount; redBlocks++)
            {
                setConsoleColor(Color::Red);
                cout << "# ";
            }
            // Draw The White Part
            for (int whiteBlocks = redBlockCount + 1; whiteBlocks <= 51; whiteBlocks++)
            {
                setConsoleColor(Color::White);
                cout << "# ";
            }
            cout << endl;

            if (row < 5)
            {
                ++redBlockCount;
            }
            else
            {
                --redBlockCount;
            }
        }
    }

    // Function to draw the bottom part of the flag
    void DrawFlagThirdPart()
    {
        int redBlockCount = 6;
        for (int row = 1; row <= 6; row++)
        {
            // Draw The Red Part
            for (int redBlocks = 1; redBlocks <= redBlockCount; redBlocks++)
            {
                setConsoleColor(Color::Red);
                cout << "# ";
            }

            // Draw The Green Part
            for (int greenBlocks = redBlockCount + 1; greenBlocks <= 51; greenBlocks++)
            {
                setConsoleColor(Color::Green);
                cout << "# ";
            }
            cout << endl;

            redBlockCount--;
        }
    }

    void DrawFreePalestine()
    {
        cout << "\n";

        setConsoleColor(Color::Red);

        cout << "                             # # # # # #    # # # # # #      # # # # #     # # # # #\n";
        cout << "                             #              #         #      #             #\n";
        cout << "                             #              #         #      #             #\n";
        cout << "                             # # # # # #    # # # # # #      #             #\n";
        cout << "                             #              #       #        # # # # #     # # # # #\n";
        cout << "                             #              #        #       #             #\n";
        cout << "                             #              #         #      #             #\n";
        cout << "                             #              #          #     # # # # #     # # # # #\n";

        cout << "\n\n";

        setConsoleColor(Color::Green);

        cout << "# # # # # #        #          #             # # # # #      # # # # #     # # # # #     #    ##       #   # # # # #\n";
        cout << "#         #      #   #        #             #             #                  #         #    # #      #   #        \n";
        cout << "#         #     #     #       #             #             #                  #         #    #  #     #   #        \n";
        cout << "# # # # # #    #       #      #             #              # # # # #         #         #    #   #    #   #        \n";
        cout << "#             # # # # # #     #             # # # # #               #        #         #    #    #   #   # # # # #\n";
        cout << "#            #           #    #             #                       #        #         #    #     #  #   #        \n";
        cout << "#           #             #   #             #                       #        #         #    #      # #   #        \n";
        cout << "#          #               #  # # # # # #   # # # # #     # # # # # #        #         #    #       ##   # # # # #\n";
    }

public:
    void DrawFlag()
    {
        DrawFlagFirstPart();
        DrawFlagSecondPart();
        DrawFlagThirdPart();
    }

    void freePalestine()
    {
        DrawFreePalestine();
    }

    void start()
    {
        while (true)
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            freePalestine();

            this_thread::sleep_for(chrono::milliseconds(delayDuration));

#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            DrawFlag();

            this_thread::sleep_for(chrono::milliseconds(delayDuration));
        }
    }
};

int main()
{
    FreePalestine freedom;
    freedom.start();
    cin.get();
    return 0;
}