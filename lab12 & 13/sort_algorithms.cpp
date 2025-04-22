//sort_algorithms.cpp
#include "sort_algorithms.h"

// Comparison function for integers
int compare_int(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Comparison function for strings
int compare_string(const void* a, const void* b) {
    return (*(string*)a).compare(*(string*)b);
}

// Bubble sort
SortResult bubble_sort(vector<void*>& arr, int (*compare)(const void*, const void*)) {
    auto start = high_resolution_clock::now();
    
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (compare(arr[j], arr[j + 1]) > 0) {
                void* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    
    auto end = high_resolution_clock::now();
    return {duration<double>(end - start).count(), "Bubble Sort"};
}

// Quick sort
int partition(vector<void*>& arr, int low, int high, int (*compare)(const void*, const void*)) {
    void* pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; ++j) {
        if (compare(arr[j], pivot) <= 0) {
            ++i;
            void* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    void* temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quick_sort_helper(vector<void*>& arr, int low, int high, int (*compare)(const void*, const void*)) {
    if (low < high) {
        int pi = partition(arr, low, high, compare);
        quick_sort_helper(arr, low, pi - 1, compare);
        quick_sort_helper(arr, pi + 1, high, compare);
    }
}

SortResult quick_sort(vector<void*>& arr, int (*compare)(const void*, const void*)) {
    auto start = high_resolution_clock::now();
    quick_sort_helper(arr, 0, arr.size() - 1, compare);
    auto end = high_resolution_clock::now();
    return {duration<double>(end - start).count(), "Quick Sort"};
}

// Selection sort
SortResult selection_sort(vector<void*>& arr, int (*compare)(const void*, const void*)) {
    auto start = high_resolution_clock::now();
    
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (compare(arr[j], arr[min_idx]) < 0) {
                min_idx = j;
            }
        }
        void* temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
    
    auto end = high_resolution_clock::now();
    return {duration<double>(end - start).count(), "Selection Sort"};
}

// Insertion sort
SortResult insertion_sort(vector<void*>& arr, int (*compare)(const void*, const void*)) {
    auto start = high_resolution_clock::now();
    
    for (size_t i = 1; i < arr.size(); ++i) {
        void* key = arr[i];
        int j = i - 1;
        while (j >= 0 && compare(arr[j], key) > 0) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
    
    auto end = high_resolution_clock::now();
    return {duration<double>(end - start).count(), "Insertion Sort"};
}

// Merge sort
void merge(vector<void*>& arr, int left, int mid, int right, int (*compare)(const void*, const void*)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<void*> L(arr.begin() + left, arr.begin() + left + n1);
    vector<void*> R(arr.begin() + mid + 1, arr.begin() + mid + 1 + n2);
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (compare(L[i], R[j]) <= 0) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void merge_sort_helper(vector<void*>& arr, int left, int right, int (*compare)(const void*, const void*)) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_helper(arr, left, mid, compare);
        merge_sort_helper(arr, mid + 1, right, compare);
        merge(arr, left, mid, right, compare);
    }
}

SortResult merge_sort(vector<void*>& arr, int (*compare)(const void*, const void*)) {
    auto start = high_resolution_clock::now();
    merge_sort_helper(arr, 0, arr.size() - 1, compare);
    auto end = high_resolution_clock::now();
    return {duration<double>(end - start).count(), "Merge Sort"};
} 