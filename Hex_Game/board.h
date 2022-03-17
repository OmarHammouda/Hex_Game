#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum class NodePlayer { Empty, Player1, Player2 };

ostream& operator<< (ostream& os, const NodePlayer& np) {
    switch (np)
    {
        case NodePlayer::Player1: os << "Player 1"; break;
        case NodePlayer::Player2: os << "Player 2"; break;
    }
    return os;
}

class Node;


class Edge {
public:
    Edge(int node1Idx, int node2Idx) : isConnected(false) {
        firstNodeIdx = node1Idx;
        secondNodeIdx = node2Idx;
    }

    bool GetConnectionState() { return isConnected; }

    void SetConnectionStateTrue() { isConnected = true; }

    int GetFirstNodeIdx() { return firstNodeIdx; }

    int GetSecondNodeIdx() { return secondNodeIdx; }

private:
    bool isConnected;
    int firstNodeIdx;
    int secondNodeIdx;
};


class Node {
public:
    // Constructor
    Node(int row, int col, int idxInVec) : player(NodePlayer::Empty), isConnectedSide1(false), isConnectedSide2(false) {
        idx2D.rowIdx = row;
        idx2D.colIdx = col;
        idx1D = idxInVec;
    }

    // Destructor
    ~Node() {}

    // Set the Node player
    void SetNodePlayer(NodePlayer pl) { player = pl; }

    // Get the Node player
    NodePlayer GetNodePlayer() const { return player; }

    // Get rowIdx
    int GetRowIdx() const { return idx2D.rowIdx; }

    // Get colIdx
    int GetColIdx() const { return idx2D.colIdx; }

    // Get 1D index
    int Get1DIdx() const { return idx1D; }

    // Add edge to neighbour node
    void AddEdge(int eIdx) { edgeIdx.push_back(eIdx); }

    // Get the vector of edge indicies
    vector<int> GetAllEdges() const { return edgeIdx; }

    // Set isConnectedSide1 to true
    void SetConnectedSide1True() { isConnectedSide1 = true; }

    // Set isConnectedSide2 to true
    void SetConnectedSide2True() { isConnectedSide2 = true; }

    // Get isConnectedSide1
    bool GetisConnectedSide1() const { return isConnectedSide1; }

    // Get isConnectedSide2
    bool GetisConnectedSide2() const { return isConnectedSide2; }

    // Check if 2 sides are connected
    bool CheckConnectedBothSides() { return (isConnectedSide1 && isConnectedSide2); }

    friend ostream& operator<< (ostream& os, const Node& n);

private:
    NodePlayer player;
    vector<int> edgeIdx;
    bool isConnectedSide1;
    bool isConnectedSide2;
    int idx1D;
    struct {
        int rowIdx;
        int colIdx;
    } idx2D;
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
    Board() : lastPlayedIdx(-1) {};

    void ClearBoard() {
        boardSize = 0;
        lastPlayedIdx = -1;
        nodes.clear();
        edges.clear();
    }

    // Constructor
    void SetupBoard(int brdSize) {
        boardSize = brdSize;
        // Create nodes
        for (int i = 0; i < boardSize; ++i) {
            for (int j = 0; j < boardSize; ++j) {
                Node n(i,j,GetIdx(i,j));
                nodes.push_back(n);
            }
        }
        // Create edges for each node
        int idx1D;
        vector<int> rowOffset = { 0, 1, 1 };
        vector<int> colOffset = { 1, -1, 0 };
        for (auto it = nodes.begin(); it != nodes.end(); ++it) {
            for (unsigned int i = 0; i < rowOffset.size(); ++i) {
                idx1D = GetIdx(it->GetRowIdx() + rowOffset.at(i), it->GetColIdx() + colOffset.at(i));
                if (idx1D != -1) {
                    Edge e(it->Get1DIdx(), idx1D);
                    edges.push_back(e);
                    it->AddEdge(edges.size() - 1);
                    nodes.at(idx1D).AddEdge(edges.size() - 1);
                }
            }
        }
    }

    // Check if node is empty
    bool isNodeEmpty(int row, int col) const {
        int nodeIdx = GetIdx(row, col);
        return nodes.at(nodeIdx).GetNodePlayer() == NodePlayer::Empty;
    }

    // Play a turn
    bool ModifyBoardAfterTurn(int row, int col, int playerID) {
        int nodeIdx = GetIdx(row, col);
        lastPlayedIdx = nodeIdx;
        // Assign the node to the player
        nodes.at(nodeIdx).SetNodePlayer(static_cast<NodePlayer>(playerID));
        // Setup the connections from the current node to neighbours
        ModifyConnections();
        // Check if current player won
        return CheckIfWon();
    }

    // Get boardSize
    int GetBoardSize() const {
        return boardSize;
    }

    // Get the last played node's index 1D
    int GetLastPlayedIdx() const { return lastPlayedIdx; }

    friend ostream& operator<< (ostream& os, const Board& b);

private:
    int boardSize;
    int lastPlayedIdx;
    vector<Node> nodes;
    vector<Edge> edges;

    // Given the row and columns indices, return the 1D index in the vector
    int GetIdx(int row, int col) const {
        int idx1D;
        if (row < 0 || col < 0 || row >= boardSize || col >= boardSize) {
            idx1D = -1;
        }
        else
        {
            idx1D = row * boardSize + col;
        }
        return idx1D;
    }

    // Setup the connections
    void ModifyConnections() {
        for (auto eIdx : nodes.at(lastPlayedIdx).GetAllEdges()) {
            if (edges.at(eIdx).GetConnectionState() == false) // Check the connection is not already established
            {
                int n1 = edges.at(eIdx).GetFirstNodeIdx();
                int n2 = edges.at(eIdx).GetSecondNodeIdx();
                if (nodes.at(n1).GetNodePlayer() == nodes.at(n2).GetNodePlayer()) {
                    edges.at(eIdx).SetConnectionStateTrue();
                }
            }
        }
    }

    // Check if the current player won
    bool CheckIfWon() {
        // Player 1 aims to connect the left and right sides, Player 2 top and bottom sides
        Node* n = &nodes.at(lastPlayedIdx);
        NodePlayer pl = n->GetNodePlayer();
        // Check if the node is on the side and set the connected flags accordingly
        if (pl == NodePlayer::Player1) {
            if (n->GetColIdx() == 0)
                n->SetConnectedSide1True();
            else if (n->GetColIdx() == (boardSize - 1))
                n->SetConnectedSide2True();
        }
        else {
            if (n->GetRowIdx() == 0)
                n->SetConnectedSide1True();
            else if (n->GetRowIdx() == (boardSize - 1))
                n->SetConnectedSide2True();
        }
        // Check the surrounding nodes and set the connected flags accordingly
        for (auto eIdx : n->GetAllEdges()) {
            if (edges.at(eIdx).GetConnectionState() == true)
            {
                int n1 = edges.at(eIdx).GetFirstNodeIdx();
                int n2 = edges.at(eIdx).GetSecondNodeIdx();
                if (nodes.at(n1).GetisConnectedSide1() != nodes.at(n2).GetisConnectedSide1()) {
                    nodes.at(n1).SetConnectedSide1True();
                    nodes.at(n2).SetConnectedSide1True();
                }
                if (nodes.at(n1).GetisConnectedSide2() != nodes.at(n2).GetisConnectedSide2()) {
                    nodes.at(n1).SetConnectedSide2True();
                    nodes.at(n2).SetConnectedSide2True();
                }
            }
        }
        return n->CheckConnectedBothSides();
    }
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
            cout << b.nodes.at(b.GetIdx(i, j)) << " - ";
        }
        cout << b.nodes.at(b.GetIdx(i, b.boardSize - 1)) << endl;

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
        cout << b.nodes.at(b.GetIdx(b.boardSize - 1, j)) << " - ";
    }
    cout << b.nodes.at(b.GetIdx(b.boardSize - 1, b.boardSize - 1)) << endl;

    return os;
}

#endif