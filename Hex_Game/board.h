#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class NodeColor { Empty, Red, Blue };
enum class NodeType { TopLeft, TopCenter, TopRight, SideLeft, Center, SideRight, BottomLeft, BottomCenter, BottomRight };

class Node {
public:
    // Constructor
    Node(NodeType t, NodeColor c) : type(t), color(c) { }

    // Destructor
    ~Node() {}

    // Get the Node type
    NodeType GetNodeType() const { return type; }

    // Set the Node color
    void SetNodeColor(NodeColor c) { color = c; }

    // Get the Node color
    NodeColor GetNodeColor() const { return color; }

    friend ostream& operator<< (ostream& os, const Node& n);

private:
    NodeType type;
    NodeColor color;
};

ostream& operator<< (ostream& os, const Node& n) {
    switch (n.GetNodeColor()) {
        case NodeColor::Empty:
            cout << ".";
            break;
        case NodeColor::Red:
            cout << "x";
            break;
        case NodeColor::Blue:
            cout << "o";
            break;
    }
    return os;
}

class Board {
public:
    // Constructor
    Board(int brdSize) : boardSize(brdSize) {
        // Top Row
        // Top Left corner node
        Node n1(NodeType::TopLeft, NodeColor::Empty);
        myBoard.push_back(n1);
        // Top center nodes
        for (int i = 0; i < boardSize - 2; ++i) {
            Node n2(NodeType::TopCenter, NodeColor::Empty);
            myBoard.push_back(n2);
        }
        // Top Right corner node
        Node n3(NodeType::TopRight, NodeColor::Empty);
        myBoard.push_back(n3);

        // Center Rows
        for (int i = 0; i < boardSize - 2; ++i) {
            // Left Side node
            Node n4(NodeType::SideLeft, NodeColor::Empty);
            myBoard.push_back(n4);
            // Center nodes
            for (int j = 0; j < boardSize - 2; ++j) {
                Node n5(NodeType::Center, NodeColor::Empty);
                myBoard.push_back(n5);
            }
            // Right Side node
            Node n6(NodeType::SideRight, NodeColor::Empty);
            myBoard.push_back(n6);
        }

        // Bottom Row
        // Bottom Left corner node
        Node n7(NodeType::BottomLeft, NodeColor::Empty);
        myBoard.push_back(n7);
        // Bottom center nodes
        for (int i = 0; i < boardSize - 2; ++i) {
            Node n8(NodeType::BottomCenter, NodeColor::Empty);
            myBoard.push_back(n8);
        }
        // Bottom Right corner node
        Node n9(NodeType::BottomRight, NodeColor::Empty);
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
    string spaces = "";
    for (int i = 0; i < b.boardSize-1; ++i) {
        cout << spaces;

        for (int j = 0; j < b.boardSize-1; ++j) {
            cout << b.myBoard.at(b.GetIdx(i, j)) << " - ";
        }
        cout << b.myBoard.at(b.GetIdx(i, b.boardSize - 1)) << endl;

        spaces += " ";
        cout << spaces;

        for (int j = 0; j < b.boardSize - 1; ++j) {
            cout << "\\ / ";
        }
        cout << "\\" << endl;

        spaces += " ";
    }

    cout << spaces;

    for (int j = 0; j < b.boardSize - 1; ++j) {
        cout << b.myBoard.at(b.GetIdx(b.boardSize - 1, j)) << " - ";
    }
    cout << b.myBoard.at(b.GetIdx(b.boardSize - 1, b.boardSize - 1)) << endl;

    return os;
}

#endif