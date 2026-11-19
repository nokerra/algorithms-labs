#include <iostream>
#include <string>

using namespace std;

template <typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
int partition(T arr[], int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swapValues(arr[i], arr[j]);
        }
    }
    swapValues(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
void quickSort(T arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

template <typename T>
void merge(T arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    T* L = new T[n1];
    T* R = new T[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}

template <typename T>
void mergeSort(T arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

template <typename T>
void heapify(T arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        swapValues(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

template <typename T>
void heapSort(T arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swapValues(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

template <typename T>
void print(T arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <typename T>
void copyArray(T src[], T dst[], int n) {
    for (int i = 0; i < n; i++) {
        dst[i] = src[i];
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    
    const int n = 10;

    int intArr[n] = {64, 34, 25, 12, 22, 11, 90, 5, 77, 1};
    double doubleArr[n] = {3.5, 1.2, 9.8, 2.1, 7.7, 0.5, 4.4, 6.6, 8.9, 2.3};
    string stringArr[n] = {"banana", "apple", "cherry", "lemon", "mango", "orange"};

    int intCopy[n];
    double doubleCopy[n];
    string stringCopy[n];

    cout << "int" << endl;
    cout << "Исходный: ";
    print(intArr, n);

    copyArray(intArr, intCopy, n);
    quickSort(intCopy, 0, n - 1);
    cout << "Quick Sort: ";
    print(intCopy, n);

    copyArray(intArr, intCopy, n);
    mergeSort(intCopy, 0, n - 1);
    cout << "Merge Sort: ";
    print(intCopy, n);

    copyArray(intArr, intCopy, n);
    heapSort(intCopy, n);
    cout << "Heap Sort:  ";
    print(intCopy, n);
    cout << endl;

    cout << "double" << endl;
    cout << "Исходный: ";
    print(doubleArr, n);

    copyArray(doubleArr, doubleCopy, n);
    quickSort(doubleCopy, 0, n - 1);
    cout << "Quick Sort: ";
    print(doubleCopy, n);

    copyArray(doubleArr, doubleCopy, n);
    mergeSort(doubleCopy, 0, n - 1);
    cout << "Merge Sort: ";
    print(doubleCopy, n);

    copyArray(doubleArr, doubleCopy, n);
    heapSort(doubleCopy, n);
    cout << "Heap Sort:  ";
    print(doubleCopy, n);
    cout << endl;

    cout << "string" << endl;
    cout << "Исходный: ";
    print(stringArr, n);

    copyArray(stringArr, stringCopy, n);
    quickSort(stringCopy, 0, n - 1);
    cout << "Quick Sort: ";
    print(stringCopy, n);

    copyArray(stringArr, stringCopy, n);
    mergeSort(stringCopy, 0, n - 1);
    cout << "Merge Sort: ";
    print(stringCopy, n);

    copyArray(stringArr, stringCopy, n);
    heapSort(stringCopy, n);
    cout << "Heap Sort:  ";
    print(stringCopy, n);

    return 0;
}