#include <iostream>
#include <stdexcept>
#include <utility>


using namespace std;

template <typename T>
class Vector {
private:
    T* data;
    int size;
    int capacity;

    void quickSortImpl(int left, int right) {
        if (left >= right) return;
        
        int i = left;
        int j = right;
        T mid = data[(left + right) / 2];
        
        while (i <= j) {
            while (data[i] < mid) {
                ++i;
            }
            
            while (data[j] > mid) {
                --j;
            }
            
            if (i <= j) {
                swap(data[i], data[j]);
                ++i;
                --j;
            }
        }
        quickSortImpl(left, j);
        quickSortImpl(i, right);
    }

public:
    Vector() : data(nullptr), size(0), capacity(0) {}

    explicit Vector(int n) : data(new T[n]()), size(n), capacity(n) {}

    Vector(const Vector& other) : data(new T[other.capacity]), size(other.size), capacity(other.capacity) {
        for (int i = 0; i < size; ++i) data[i] = other.data[i];
    }

    Vector(Vector&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
        other.size = other.capacity = 0;
    }

    ~Vector() { delete[] data; }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            vector_swap(temp);
        }
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data;
            
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Индекс выходит за границы вектора");
        }
        return data[index];
    }
    
    const T& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Индекс выходит за границы вектора");
        }
        return data[index];
    }

    int getSize() const {
        return size;
    }
    
    int getCapacity() const {
        return capacity;
    }
    
    bool empty() const {
        return size == 0;
    }

    void reserve(int newCapacity) {
        if (newCapacity <= capacity) return;
        T* newData = new T[newCapacity];
        
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    void push_back(const T& value) {
        if (size >= capacity) {
            reserve((capacity == 0) ? 1 : capacity * 2);
        }
        
        data[size++] = value;
    }

    void pop_back() {
        if (empty()) {
            throw underflow_error("Вектор пуст");
        }
        
        --size;
    }

    void clear() {
        size = 0;
    }

    void vector_swap(Vector& other) noexcept {
        swap(data, other.data);
        swap(size, other.size);
        swap(capacity, other.capacity);
    }

    T* begin() {
        return data;
    }
    
    T* end() {
        return data + size;
    }
    
    const T* begin() const {
        return data;
    }
    
    const T* end() const {
        return data + size;
    }

    void quickSort() {
        if (size > 1) {
            quickSortImpl(0, size - 1);
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    Vector<int> v;
    for (int x : {5, 3, 8, 1, 9, 2, 7, 4, 6, 0}) {
        v.push_back(x);
    }

    cout << "Вектор v: ";
    for (int i : v) {
        cout << i << " ";
    }
    
    cout << "\nРазмер = " << v.getSize() << ", ёмкость = " << v.getCapacity() << endl;

    v.quickSort();
    cout << "Сортировка: ";
    for (int i : v) {
        cout << i << " ";
    }
    
    return 0;
}
