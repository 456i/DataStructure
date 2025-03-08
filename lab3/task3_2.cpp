#include <iostream>
#include <vector>

using namespace std;

// Функция для нахождения медианы
double findMedian(vector<int>& nums) {
    int n = nums.size();

    if (n % 2 == 1) {
        return nums[n / 2]; // Нечётное количество элементов
    }
    else {
        return (nums[n / 2 - 1] + nums[n / 2]) / 2.0; // Чётное количество элементов
    }
}

int main() {
    vector<int> numbers;
    int num;

    cout << "Enter numbers (type -1 to finish): ";
    while (cin >> num && num != -1) {
        numbers.push_back(num);
    }

    if (numbers.empty()) {
        cout << "No numbers entered!" << endl;
    }
    else {
        cout << "Median: " << findMedian(numbers) << endl;
    }

    return 0;
}