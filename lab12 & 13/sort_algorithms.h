//sort_algorithms.h
#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <vector>
#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct SortResult {
    double time;
    string name;
};

SortResult bubble_sort(vector<void*>& arr, int (*compare)(const void*, const void*));
SortResult quick_sort(vector<void*>& arr, int (*compare)(const void*, const void*));
SortResult selection_sort(vector<void*>& arr, int (*compare)(const void*, const void*));
SortResult insertion_sort(vector<void*>& arr, int (*compare)(const void*, const void*));
SortResult merge_sort(vector<void*>& arr, int (*compare)(const void*, const void*));

#endif
