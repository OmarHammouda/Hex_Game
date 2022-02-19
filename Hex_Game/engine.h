#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <cctype>
#include <string>

class HexGame {
public:
    HexGame() {
        string gameName =
            "             __    __   _______ ___   ___      _______      ___      .___  ___.  _______\n"
            "            |  |  |  | |   ____|\\  \\ /  /     /  _____|    /   \\     |   \\/   | |   ____|\n"
            "            |  |__|  | |  |__    \\  V  /     |  |  __     /  ^  \\    |  \\  /  | |  |__\n"
            "            |   __   | |   __|    >   <      |  | |_ |   /  /_\\  \\   |  |\\/|  | |   __|\n"
            "            |  |  |  | |  |____  /  .  \\     |  |__| |  /  _____  \\  |  |  |  | |  |____\n"
            "            |__|  |__| |_______|/__/ \\__\\     \\______| /__/     \\__\\ |__|  |__| |_______|\n";

        cout << gameName << endl;

        // Start the game
        startGame();
    }
private:

    // Start Game
    void startGame() {
        char userInput;

        while (true) {
            cout << "Would you like to \n  (1)Play against another player\n  (2)Play against the AI\n  (Q)uit" << endl;
            cin >> userInput;

            if (userInput == '1') {
                break;
            }
            else if (userInput == '2') {
                break;
            }
            else if (toupper(userInput) == 'Q') {
                cout << "Didn't even try the game?  YOUR LOSS!" << endl;
                break;
            }
            else
                cout << "Wrong input, please choose either option 1 or 2 or (Q)uit." << endl;
        }
    }
};

#endif
