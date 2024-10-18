// Ethan Dilk | COMSC 210 | Midterm 2
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int MINUTES = 20;

class DoublyLinkedList {
private:
    struct Node {
        string data;
        Node* prev;
        Node* next;
        Node(string val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(string value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value) {
        if (!head) return;

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        cout << "   " << temp->data << " left the line" << endl;
        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;

        cout << "   " << temp->data << " left the line" << endl;

        delete temp;
    }

    void push_back(string v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        cout << "   " << newNode->data << " joined the line" << endl;
    }
    
    void push_front(string v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }

        cout << "   " << newNode->data << " (VIP) joins the front of the line" << endl;
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;

        cout << "   " << temp->data << " is served" << endl;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;

        cout << "   " << temp->data << " (at the rear) left the line" << endl;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        cout << "   Resulting Line: " << endl;
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << "       " << current->data << " " << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    int get_length() {
        int length = 0;
        Node* current = head;
        if (!current) {
            return 0;
        }
        while (current) {
            length++;
            current = current->next;

        }
        return length;

    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning
    cout << endl;

    srand(time(0));

    // creating vector to store names
    vector<string> namesVec;
    // ifstream object to read in names
    ifstream names("/Users/ethandilk/Desktop/Computer Science/COMSC 210 - Program Design & Data Structures/Midterm2/names.txt");
    // error if names is null
    if (!names) {
        cout << "Error opening - please try again!" << endl;
        exit(1);
    }

    // initialize names input into vector
    // temp string to store each name
    string n; 
    while(getline(names, n)) {
        namesVec.push_back(n);
    }
    // initializing a DLL object
    DoublyLinkedList newLine;

    cout << "Store Opens: " << endl;
    // creating the initial Store opening simulation of 5 customers being pushed back into the line
    for (int i = 0; i < 5; i++) {
        int randVecIndex = (rand() % 98);
        newLine.push_back(namesVec.at(randVecIndex));
    }
    newLine.print();

    // Simulation of 20 minutes (time periods)
    for (int k = 0; k < 5; k++) {
        cout << "Time Step #" << k + 1 << ": "<< endl;

        // get a random probability between 0 and 100
        int prob = rand() % 100 + 1;
        cout << prob << endl;

        // If the probability meets each certain threshold - do the action 
        if (prob <= 60) {

            int randVecIndex = (rand() % 98);
            newLine.push_back(namesVec.at(randVecIndex));

        }
        if (prob <= 40){
            newLine.pop_front();
        }
        if (prob <= 20) {
            newLine.pop_back();
        }
        if (prob <= 10) {
            // pushing a VIP to the front
            int randVecIndex = (rand() % 98);
            newLine.push_front(namesVec.at(randVecIndex));

            // Removing a random person from line
            int dllLength = newLine.get_length();
            int randListIndex = rand() % dllLength;
            newLine.delete_pos(randListIndex);

        }
        if (prob > 60)
            cout << "   Line did not change!" << endl;
        

        newLine.print();

    }

    return 0;
}