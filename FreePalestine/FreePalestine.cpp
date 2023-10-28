#include <iostream>
#include <windows.h>
using namespace std;

enum class Color
{
	Black = 8,
	Green = 2,
	Red = 4,
	White = 15
};

class FreePalestine
{
private:

	static constexpr int delayDuration = 5000; // 5 seconds

	// Function to set the console text color
	void setConsoleColor(Color colorCode)
	{
		int consoleColor = static_cast<int>(colorCode);

		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(consoleHandle, consoleColor);
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
				redBlockCount++;
			}
			else
			{
				redBlockCount--;
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
	// Function to draw the entire flag
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
			system("cls");

			freePalestine();

			Sleep(delayDuration);

			system("cls");

			DrawFlag();

			Sleep(delayDuration);
		}
	}
};

int main()
{
	FreePalestine freedom;
	freedom.start();
	return 0;
}