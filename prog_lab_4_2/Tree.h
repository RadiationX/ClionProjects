//
// Created by radiationx on 10.05.17.
//


#ifndef PROG_LAB_4_2_TREE_H
#define PROG_LAB_4_2_TREE_H

#include "iostream"

using namespace std;
struct Node {
    int value;
    int size = 0;
    Node *nodes = NULL;
};

class Tree {
private:
    Node root;
    int capacity = 0;

    void add(Node &root, int value) {
        if (root.nodes == NULL) {
            root.nodes = new Node[capacity];
        }

        if (root.size < capacity) {
            root.nodes[root.size].value = value;
            root.size++;
        } else {
            int minIndex = 0;
            for (int i = 1; i < capacity; i++) {
                if (root.nodes[minIndex].size != root.nodes[i].size) {
                    minIndex = i;
                    break;
                }
            }
            add(root.nodes[minIndex], value);
        }
    }

    void printTree(Node &root, int level) {
        for (int j = 0; j < level; j++) {
            if (j == level - 1) {
                cout << "+---";
            } else {
                cout << "|   ";
            }
        }
        cout << root.value << endl;
        for (int i = 0; i < root.size; i++) {
            level++;
            printTree(root.nodes[i], level);
            level--;
        }
    }

    int sum(Node &root) {
        int res = 0;
        res += root.value;
        for (int i = 0; i < root.size; i++) {
            res += sum(root.nodes[i]);
        }
        return res;
    }

public:
    Tree(int capacity) {
        this->capacity = capacity;
        root.value = 0;
    }

    void add(int value) {
        add(root, value);
    }

    void printTree() {
        cout << "TREE:" << endl;
        printTree(root, 0);
    }

    int sum() {
        int res = sum(root);
        cout << "SUM VALUES: " << res << endl;
        return res;
    }
};


#endif //PROG_LAB_4_2_TREE_H
