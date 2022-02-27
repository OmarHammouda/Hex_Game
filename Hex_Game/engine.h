#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <cctype>
#include <string>
#include "board.h"

enum class GameMode { ExitGame, MainMenu, SetupBoard, PlayGame };

class HexGame {
public:
    HexGame() : mode(GameMode::MainMenu) {
        string gameName =
            "             __    __   _______ ___   ___      _______      ___      .___  ___.  _______\n"
            "            |  |  |  | |   ____|\\  \\ /  /     /  _____|    /   \\     |   \\/   | |   ____|\n"
            "            |  |__|  | |  |__    \\  V  /     |  |  __     /  ^  \\    |  \\  /  | |  |__\n"
            "            |   __   | |   __|    >   <      |  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|\n"
            "            |  |  |  | |  |____  /  .  \\     |  |__| |  /  _____  \\  |  |  |  | |  |____\n"
            "            |__|  |__| |_______|/__/ \\__\\     \\______| /__/     \\__\\ |__|  |__| |_______|\n";

        cout << gameName << endl;

        while (mode != GameMode::ExitGame) {
            switch (mode) {
                case GameMode::MainMenu:
                    mainMenu();
                    break;
                case GameMode::SetupBoard:
                    setupBoard();
                    break;
                case GameMode::PlayGame:
                    playGame();
                    break;
            }
        }

        // Exiting Game
        cout << "Thanks for playing HEX. Bye!" << endl << endl;
    }

private:
    GameMode mode;
    bool opponentIsAI;
    Board myBoard;

    // Check the Game Mode

    // Start Game. Give player the option to play against another player or the AI
    void mainMenu() {
        string userInput;

        while (true) {
            cout << "Main Menu. Would you like to \n  (1)Play against another player\n  (2)Play against the AI\n  (Q)uit" << endl;
            getline(cin, userInput);
            cout << endl;
            if (!userInput.empty()) {
                if (userInput.at(0) == '1') {
                    opponentIsAI = false;
                    mode = GameMode::SetupBoard;
                    break;
                }
                else if (userInput.at(0) == '2') {
                    opponentIsAI = true;
                    mode = GameMode::SetupBoard;
                    break;
                }
                else if (toupper(userInput.at(0)) == 'Q') {
                    mode = GameMode::ExitGame;
                    break;
                }
                else {
                    cout << "Wrong input, please choose either option 1 or 2 or (Q)uit." << endl;
                }
            }
            else {
                cout << "Wrong input, please choose either option 1 or 2 or (Q)uit." << endl;
            }
        }
    }

    // Create a Board after asking player of the size
    void setupBoard() {
        int userInput;
        string userInput2;

        while (true) {
            cout << "Please enter the size of the board: ";
            cin >> userInput;
            cout << endl;

            // Check if the input value is valid.
            if (cin.fail() || userInput < 1) {
                cin.clear();
                cin.ignore(10000, '\n');

                cout << "The input you entered is incorrect. The board size has to be a positive integer (i.e. > 0).\nPlease choose one of the following options:" << endl;
                cout << "  (B)ack to main menu.\n  (Q)uit the game.\n  Any other key to re-enter the board size." << endl;
                getline(cin, userInput2);
                cout << endl;
                if (!userInput2.empty() && toupper(userInput2.at(0)) == 'B') {
                    mode = GameMode::MainMenu;
                    break;
                }
                else if (!userInput2.empty() && toupper(userInput2.at(0)) == 'Q') {
                    mode = GameMode::ExitGame;
                    break;
                }
                else {
                    continue;
                }
            }
            else {
                Board b(userInput);
                myBoard = b;
                mode = GameMode::PlayGame;
                break;
            }
        }
        cin.clear();
        cin.ignore(10000, '\n');
    }

    // Play the game
    void playGame() {
        cout << "###################################################################\n"
                "####################### Starting New Game #########################\n"
                "###################################################################" << endl << endl;

        if (opponentIsAI) {
            cout << "AI not implemented yet!" << endl << endl;
            mode = GameMode::MainMenu;
        }
        else {
            playerVSplayer();
        }
    }

    // Player vs Player game
    void playerVSplayer() {
        int turnCount = 0;

        while (true) {
            getPlayerInputCoords((turnCount % 2) + 1, turnCount);
            if (mode != GameMode::PlayGame) {
                break;
            }
        }
    }

    // Get Coordinates from Player
    void getPlayerInputCoords(int playerID, int& turnCount) {
        int inputRow, inputCol;

        turnCount++;

        // Print turn number, and who's turn it is, then print the board
        cout << endl;
        cout << "Turn " << turnCount << ". Player " << playerID << "'s turn." << endl << endl;
        cout << myBoard << endl;

        // Ask the player to choose a row and column numbers. Then check whether the input is valid.
        bool exitLoop;
        // First, choose row
        while (true) {
            cout << "Choose Row Number: ";
            cin >> inputRow;
            exitLoop = checkPlayerInput(cin.fail(), inputRow, "Row");
            if (exitLoop) {
                break;
            }
        }
        // If player chose to go back to main menu or exit the game, no need to continue
        if (mode != GameMode::PlayGame) {
            return;
        }
        // Second, choose col
        while (true) {
            cout << "Choose Column Number: ";
            cin >> inputCol;
            exitLoop = checkPlayerInput(cin.fail(), inputCol, "Column");
            if (exitLoop) {
                break;
            }
        }
        // If player chose to go back to main menu or exit the game, no need to continue
        if (mode != GameMode::PlayGame) {
            return;
        }
        // Check if the at the entered position, the board is empty, if yes, set the node at that location
        if (myBoard.isNodeEmpty(inputRow, inputCol)) {
            myBoard.SetNodePlayer(inputRow, inputCol, playerID);
        }
        else {
            turnCount--;
            cout << "The node at the entered coordinates is already occupied. Please choose other coordinates." << endl;
        }
    }

    bool checkPlayerInput(bool cinFailed, int playerInput, string dimension) {
        char input;
        if (cinFailed || (playerInput < 0) || (playerInput > myBoard.GetBoardSize()-1) ) {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << endl;
            cout << "Wrong Input! " << dimension << " number should be an integer from 0 to " << (myBoard.GetBoardSize() - 1) << endl;
            cout << "Press (B) to go back to main menu, (Q) to quit the game entirely or any other key to re-enter the " << dimension << " number." << endl;

            cin >> input;
            cin.clear();
            cin.ignore(10000, '\n');
            cout << endl;
            if (toupper(input) == 'B') {
                mode = GameMode::MainMenu;
                return true;
            }
            else if (toupper(input) == 'Q') {
                mode = GameMode::ExitGame;
                return true;
            }
            else {
                return false;
            }
        }
        return true;
    }
};

#endif
