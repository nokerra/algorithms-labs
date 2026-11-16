#include <iostream>
#include <stdexcept>
#include <vector>
#include <utility>


using namespace std;

template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int count;
    
public:
    SinglyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    
    ~SinglyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }
    
    void push_front(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        if (tail == nullptr) {
            tail = newNode;
        }
        count++;
    }
    
    void pop_front() {
        if (head == nullptr) {
            throw underflow_error("Список пуст");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
        
        if (head == nullptr) {
            tail = nullptr;
        }
    }
    
    int size() const {
        return count;
    }
    
    bool isPalindrome() {
        if (head == nullptr) {
            throw underflow_error("Список пуст");
        }
        
        vector<T> values;
        Node* current = head;
        while (current != nullptr) {
            values.push_back(current->data);
            current = current->next;
        }

        int left = 0;
        int right = values.size() - 1;
        while (left < right) {
            if (values[left] != values[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
};

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int count;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    
    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }
    
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }
    
    void pop_back() {
        if (tail == nullptr) {
            throw underflow_error("Список пуст");
        }
        Node* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        count--;
    }
    
    int size() const {
        return count;
    }

    void swapPairs() {
        if (count < 2) {
            throw underflow_error("Список слишком мал");
        }
        Node* current = head;
        while (current != nullptr && current->next != nullptr) {
            swap(current->data, current->next->data);
            current = current->next->next;
        }
    }

    void print() const {
        for (Node* curr = head; curr != nullptr; curr = curr->next) {
            cout << curr->data << " ";
        }
        cout << "\n";
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    SinglyLinkedList<int> singleList;
    for (int x : {1, 2, 3, 2, 1}) {
        singleList.push_front(x);
    }
    
    cout << "Односвязный список (размер " << singleList.size() << ") - палиндром: " << singleList.isPalindrome() << endl;


    DoublyLinkedList<int> doublyList;
    for (int x : {1, 2, 3, 4}) {
        doublyList.push_back(x);
    }
    
    cout << "Двусвязный список до swapPairs: ";
    doublyList.print();
    doublyList.swapPairs();
    cout << "После swapPairs: ";
    doublyList.print();

    return 0;
}
