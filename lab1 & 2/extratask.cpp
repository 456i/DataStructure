#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

void addNodes(Node*& head, int n) {
    for (int i = 1; i <= n; ++i) {
        Node* newNode = new Node(i);
        newNode->next = head;
        head = newNode;
    }
}

void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

void deletePrevious(Node*& head, int target) {
    if (!head || !head->next) return;

    Node* prev = nullptr;
    Node* curr = head;
    Node* beforePrev = nullptr;

    while (curr && curr->data != target) {
        beforePrev = prev;
        prev = curr;
        curr = curr->next;
    }

    if (!curr || !prev) return;

    if (beforePrev)
        beforePrev->next = curr;
    else
        head = curr;


    delete prev;
}

int main() {
    Node* head = nullptr;

    addNodes(head, 5);

    cout << "List after adding nodes: ";
    printList(head);

    deletePrevious(head, 2);

    cout << "List after deleting prev-prev nodes: ";
    printList(head);
    return 0;
}