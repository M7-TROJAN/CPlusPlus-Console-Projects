# Rock Paper Scissors Game

This is a simple command-line Rock Paper Scissors game written in C++. Test your luck against the computer in a series of rounds. Each round, you and the computer choose Rock, Paper, or Scissors. The winner of each round is determined by the classic game rules:

- Rock beats Scissors
- Scissors beats Paper
- Paper beats Rock

At the end of the game, the total number of rounds played, your wins, computer wins, and draws are displayed. The ultimate winner is determined based on the overall number of victories.

## How to Play

1. Compile and run the program using a C++ compiler.
2. The game will display a welcome message and prompt you to enter your name.
3. Enter your name and press Enter to start.
4. Specify the number of rounds you wish to play (between 1 and 10).
5. For each round, enter your choice:
   - 1: Rock
   - 2: Paper
   - 3: Scissors
6. The game reveals choices and announces the round winner.
7. Repeat steps 5 and 6 for the chosen number of rounds.
8. After the game, view final results: rounds played, your wins, computer wins, and the overall victor.
9. Choose to play again by entering 'y' or 'Y', or any other key to exit.

## Code Review

Here's a summary of the key points in the code structure and implementation:

- Functions and global variables manage game logic and statistics.
- Enumeration `enGameChoice` represents game choices (Rock, Paper, Scissors).
- `readNumber_From_To` function captures an integer from the user within a specified range.
- `getComputerChoice` function generates a random number within a given range for the computer's choice.
- `stringChoice` function converts a game choice enum to a string.
- `getRoundWinner` function determines the round winner based on player and computer choices.
- `getFinalWinner` function identifies the overall game winner by counting wins.
- `addGameResultToFile` function appends results to a file named by date.
- `gameOVER` function displays final results, calls `addGameResultToFile`.
- `startRound` function initiates a round with player and computer choices and determines the winner.
- `playAgain` function prompts replay or game exit.
- `startGame` function is the game entry point, collecting name, rounds, and initiating game play.
- `welcome` function displays a game welcome message.
- `main` function initializes the random number generator, calls `welcome`, and starts the game.

Please note that this code does not cover all possible errors and assumes valid input data. Enhance the code based on your specific needs.

Feel free to modify and adapt the code. For questions or further assistance, please contact me.

## Very Important Note
This Rock Paper Scissors Game project is a training exercise designed to demonstrate basic programming skills and concepts. It is not intended to be used as a replacement for professional-grade game development frameworks or engines. The game lacks advanced features, optimizations, and graphical interfaces typically found in commercial games.
Feel free to adapt and extend the code for educational purposes and personal projects. If you have any questions, please let me know!

## Author

- Mahmoud Mohamed
- Email: mahmoud.abdalaziz@outlook.com
- LinkedIn: [Mahmoud Mohamed Abdalaziz](https://www.linkedin.com/in/mahmoud-mohamed-abd/)

Enjoy the Rock Paper Scissors game and have fun challenging the computer!

## License

This Rock Paper Scissors Game is developed by Mahmoud Mohamed as a simple project. This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
