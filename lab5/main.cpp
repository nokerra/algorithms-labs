#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

// Стек

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infixToPostfix(const string& expr) {
    stack<char> st;
    string out;
    for (char ch : expr) {
        if (ch == ' ') {
            continue;
        }
        
        if (ch >= '0' && ch <= '9') {
            out += ch;
            out += ' ';
        } else if (ch == '(') {
            st.push(ch);
        } else if (ch == ')') {
            while (!st.empty() && st.top() != '(') {
                out += st.top();
                out += ' ';
                st.pop();
            }
            st.pop();
        } else {
            while (!st.empty() && st.top() != '(' && priority(st.top()) >= priority(ch)) {
                out += st.top(); out += ' ';
                st.pop();
            }
            st.push(ch);
        }
    }
    while (!st.empty()) {
        out += st.top(); out += ' ';
        st.pop();
    }
    return out;
}

// Очередь

queue<int> join(queue<int> q1, queue<int> q2) {
    queue<int> result;
    while (!q1.empty() || !q2.empty()) {
        if (!q1.empty()) {
            result.push(q1.front());
            q1.pop();
        }
        
        if (!q2.empty()) {
            result.push(q2.front());
            q2.pop();
        }
    }
    return result;
}

// Дек

vector<int> slidingWindowMin(const vector<int>& a, int k) {
    deque<int> dq;
    vector<int> res;
    for (int i = 0; i < (int)a.size(); i++) {
        while (!dq.empty() && a[dq.back()] >= a[i])
            dq.pop_back();
        dq.push_back(i);

        if (dq.front() <= i - k) {
            dq.pop_front();
        }
        
        if (i >= k - 1) {
            res.push_back(a[dq.front()]);
        }
    }
    return res;
}

// Приоритетная очередь

struct GreaterInt {
    bool operator()(int a, int b) const {
        return a > b;
    }
};

class FixedPriorityQueue {
private:
    vector<int> heap;
    int capacity;

public:
    explicit FixedPriorityQueue(int c) : capacity(c) {
        if (c <= 0) {
            throw invalid_argument("Вместимость должна быть больше 0");
        }
    }

    bool full() const {
        return heap.size() >= capacity;
    }
    
    bool empty() const {
        return heap.empty();
    }
    
    int size() const {
        return (int)heap.size();
    }

    void push(int value) {
        GreaterInt cmp;
        if (!full()) {
            heap.push_back(value);
            push_heap(heap.begin(), heap.end(), cmp);
        } else if (value > heap.front()) {
            pop_heap(heap.begin(), heap.end(), cmp);
            heap.back() = value;
            push_heap(heap.begin(), heap.end(), cmp);
        }
    }

    int top() const {
        if (empty()) {
            throw underflow_error("Очередь пуста");
        }
        
        return heap.front();
    }

    int pop() {
        GreaterInt cmp;
        if (empty()) {
            throw underflow_error("Очередь пуста");
        }
        
        pop_heap(heap.begin(), heap.end(), cmp);
        int v = heap.back();
        heap.pop_back();
        return v;
    }
};


int main() {
    cout << "Стек" << endl;
    cout << "Было: 3 + 4 * 2" << endl;
    cout << "Стало:" << infixToPostfix("3 + 4 * 2") << endl;

    cout << "Очередь" << endl;
    queue<int> q1, q2;
    for (int x : {1, 3, 5}) {
        q1.push(x);
    }
    
    for (int x : {2, 4, 6, 8}) {
        q2.push(x);
    }
    
    queue<int> result = join(q1, q2);
    while (!result.empty()) {
        cout << result.front() << " ";
        result.pop();
    }
    
    cout << endl;

    cout << "Дек" << endl;
    vector<int> a = {4, 2, 12, 11, -5, 6, 3, 8};
    
    cout << "Массив: ";
    for (int x : a) {
        cout << x << " ";
    }
    
    cout << endl << "Минимумы: ";
    for (int x : slidingWindowMin(a, 3)) {
        cout << x << " ";
    }
    
    cout << endl;

    cout << "Приоритетная очередь" << endl;
    FixedPriorityQueue pq(3);
    for (int x : {5, 1, 9, 3, 7, 2, 8}) {
        pq.push(x);
    }
    
    cout << "Из потока [5 1 9 3 7 2 8] сохранено: ";
    while (!pq.empty()) {
        cout << pq.pop() << " ";
    }

    return 0;
}
