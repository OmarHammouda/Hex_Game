#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class NodePlayer { Empty, Player1, Player2 };
enum class NodePosition { TopLeft, TopCenter, TopRight, SideLeft, Center, SideRight, BottomLeft, BottomCenter, BottomRight };

class Node {
public:
    // Constructor
    Node(NodePosition p) : position(p), player(NodePlayer::Empty) { }

    // Destructor
    ~Node() {}

    // Get the Node position on the board
    NodePosition GetNodePosition() const { return position; }

    // Set the Node player
    void SetNodePlayer(NodePlayer pl) { player = pl; }

    // Get the Node player
    NodePlayer GetNodePlayer() const { return player; }

    friend ostream& operator<< (ostream& os, const Node& n);

private:
    NodePosition position;
    NodePlayer player;
};

ostream& operator<< (ostream& os, const Node& n) {
    switch (n.GetNodePlayer()) {
        case NodePlayer::Empty:
            cout << ".";
            break;
        case NodePlayer::Player1:
            cout << "x";
            break;
        case NodePlayer::Player2:
            cout << "o";
            break;
    }
    return os;
}

class Board {
public:
    // Default Constructor
    Board() {};

    // Constructor
    Board(int brdSize) : boardSize(brdSize) {
        // Top Row
        // Top Left corner node
        Node n1(NodePosition::TopLeft);
        myBoard.push_back(n1);
        // Top center nodes
        for (int i = 0; i < boardSize - 2; ++i) {
            Node n2(NodePosition::TopCenter);
            myBoard.push_back(n2);
        }
        // Top Right corner node
        Node n3(NodePosition::TopRight);
        myBoard.push_back(n3);

        // Center Rows
        for (int i = 0; i < boardSize - 2; ++i) {
            // Left Side node
            Node n4(NodePosition::SideLeft);
            myBoard.push_back(n4);
            // Center nodes
            for (int j = 0; j < boardSize - 2; ++j) {
                Node n5(NodePosition::Center);
                myBoard.push_back(n5);
            }
            // Right Side node
            Node n6(NodePosition::SideRight);
            myBoard.push_back(n6);
        }

        // Bottom Row
        // Bottom Left corner node
        Node n7(NodePosition::BottomLeft);
        myBoard.push_back(n7);
        // Bottom center nodes
        for (int i = 0; i < boardSize - 2; ++i) {
            Node n8(NodePosition::BottomCenter);
            myBoard.push_back(n8);
        }
        // Bottom Right corner node
        Node n9(NodePosition::BottomRight);
        myBoard.push_back(n9);
    }

    // Given the row and columns indices, return the 1D index in the vector
    int GetIdx(int row, int col) const {
        return row * boardSize + col;
    }

    friend ostream& operator<< (ostream& os, const Board& b);

private:
    int boardSize;
    vector<Node> myBoard;
};

ostream& operator<< (ostream& os, const Board& b) {
    string spaces = "    ";

    cout << spaces << "  ";
    for (int i = 0; i < b.boardSize-1; ++i) {
        cout << i << " \\ ";
    }
    cout << (b.boardSize - 1) << endl;

    for (int i = 0; i < b.boardSize-1; ++i) {
        cout << spaces << i << "  ";

        for (int j = 0; j < b.boardSize-1; ++j) {
            cout << b.myBoard.at(b.GetIdx(i, j)) << " - ";
        }
        cout << b.myBoard.at(b.GetIdx(i, b.boardSize - 1)) << endl;

        spaces += " ";
        cout << spaces << "-  ";

        for (int j = 0; j < b.boardSize - 1; ++j) {
            cout << "\\ / ";
        }
        cout << "\\" << endl;

        spaces += " ";
    }

    cout << spaces << (b.boardSize - 1) << "  ";

    for (int j = 0; j < b.boardSize - 1; ++j) {
        cout << b.myBoard.at(b.GetIdx(b.boardSize - 1, j)) << " - ";
    }
    cout << b.myBoard.at(b.GetIdx(b.boardSize - 1, b.boardSize - 1)) << endl;

    return os;
}

#endif