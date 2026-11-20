#include <iostream>
using namespace std;

int binarySearchReverse(const int arr[], int len, int target) {
    int left = 0;
    int right = len - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        }
        
        if (arr[mid] < target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}

int main() {
    setlocale(LC_ALL, "ru");
    
	int arr[12] = {78, 69, 67, 64, 52, 49, 42, 33, 25, 1, 0, -4};
	
	int res = binarySearchReverse(arr, 12, 42);
	cout << "Индекс искомого элемента: " << res;
	
    return 0;
}
