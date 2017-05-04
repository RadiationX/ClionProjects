#include <iostream>

using namespace std;
struct Node {
    int value;
    int size = 0;
    Node *nodes;
};

void recurse(Node &root);

void recurseRead(Node &root);

int main() {
    Node root;
    root.value = 0;


    recurse(root);
    recurseRead(root);
    return 0;
}

int sukaCount = 1;
int maxCount = 15 + 1;

void recurse(Node &root) {
    if (sukaCount >= maxCount) {
        return;
    }
    cout << "call recurse " << root.size << endl;
    root.nodes = new Node[5];
    for (int i = 0; i < 5; i++) {
        root.nodes[i].value = sukaCount;
        root.size++;
        cout << "add node " << sukaCount << " to " << root.value << endl;
        sukaCount++;
        if (sukaCount >= maxCount) {
            return;
        }

    }
    for (int i = 0; i < 5; i++) {
        recurse(root.nodes[i]);
    }
}

int level = 0;

void recurseRead(Node &root) {
    for (int j = 0; j < level; j++) {
        if (j == level - 1) {
            cout << "+---";
        } else {
            cout << "|\t";
        }
    }
    cout << root.value << endl;
    for (int i = 0; i < root.size; i++) {
        level++;
        recurseRead(root.nodes[i]);
        level--;
    }
}
