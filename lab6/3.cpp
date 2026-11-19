#include <iostream>

using namespace std;

void print(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            int temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

void bubbleSortRecursive(int arr[], int n) {
    if (n <= 1) {
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            int temp = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = temp;
        }
    }
    bubbleSortRecursive(arr, n - 1);
}

int main() {
    setlocale(LC_ALL, "ru");
    
    const int n = 8;
    int original[n] = {5, 2, 9, 1, 7, 3, 8, 4};
    int a[n];
    int b[n];
    int c[n];

    for (int i = 0; i < n; i++) {
        a[i] = original[i];
        b[i] = original[i];
        c[i] = original[i];
    }

    cout << "Исходный массив: ";
    print(original, n);
    cout << endl;

    insertionSort(a, n);
    cout << "Сортировка вставками: ";
    print(a, n);

    selectionSort(b, n);
    cout << "Сортировка выбором: ";
    print(b, n);

    bubbleSortRecursive(c, n);
    cout << "Рекурсивная пузырьковая: ";
    print(c, n);

    return 0;
}