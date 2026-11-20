#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Student {
    string name;
    int age;
    int course;
};

template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node* next;

    Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
};

template <typename K, typename V>
class HashTable {
private:
    vector<Node<K, V>*> table;
    int capacity;

    int hash(const K& key) const {
        return static_cast<unsigned int>(key) % capacity;
    }

public:
    HashTable(int cap) : capacity(cap), table(cap, nullptr) {}

    void insert(const K& key, const V& value) {
        int index = hash(key);
        Node<K, V>* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        Node<K, V>* newNode = new Node<K, V>(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    V* find(const K& key) const {
        int index = hash(key);
        Node<K, V>* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return &current->value;
            }
            current = current->next;
        }
        return nullptr;
    }

    bool remove(const K& key) {
        int index = hash(key);
        Node<K, V>* current = table[index];
        Node<K, V>* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    void print() const {
        for (int i = 0; i < capacity; ++i) {
            cout << "[" << i << "]: ";
            Node<K, V>* current = table[i];
            while (current != nullptr) {
                cout << "{ID: " << current->key << ", "
                     << current->value.name << ", "
                     << current->value.age << " лет, "
                     << current->value.course << " курс}, ";
                current = current->next;
            }
            cout << "nullptr" << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    HashTable<int, Student> ht(7);

    ht.insert(101, {"Иванов Иван Иванович", 19, 2});
    ht.insert(108, {"Петрова Анна Сергеевна", 18, 1});
    ht.insert(205, {"Сидоров Алексей Петрович", 21, 4});

    ht.print();

    Student* s = ht.find(108);
    if (s != nullptr) {
        cout << endl << "Найден студент: " << s->name << ", курс " << s->course << endl;
    }

    return 0;
}
