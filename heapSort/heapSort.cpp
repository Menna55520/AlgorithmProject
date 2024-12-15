#include <iostream>
#include <vector>

using namespace std;

// Function to heapify a subtree rooted at index `i`
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;            // Initialize largest as root
    int left = 2 * i + 1;       // Left child
    int right = 2 * i + 2;      // Right child

    // Check if left child exists and is greater than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Check if right child exists and is greater than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root, swap and heapify the affected subtree
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Function to build a max-heap
void buildMaxHeap(vector<int>& arr, int n) {
    // Start from the last non-leaf node and call heapify for each node
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Function to perform Heap Sort
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Step 1: Build a max-heap
    buildMaxHeap(arr, n);

    // Step 2: Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        // Move the root (maximum element) to the end
        swap(arr[0], arr[i]);

        // Call heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

// Main function to test the Heap Sort implementation
int main() {
    vector<int> arr = { 12, 11, 13, 5, 6, 7 };

    cout << "Original array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // Perform Heap Sort
    heapSort(arr);

    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
