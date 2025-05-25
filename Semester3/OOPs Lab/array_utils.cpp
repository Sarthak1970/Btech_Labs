#include "array_utils.h"

namespace ArrayUtils {

// Function to calculate the average of an array
double average(const std::vector<int>& arr) {
    double sum = 0;
    for (int num : arr) {
        sum += num;
    }
    return arr.empty() ? 0 : sum / arr.size();
}

// Function to find the maximum in an array
int maximum(const std::vector<int>& arr) {
    if (arr.empty()) return 0; // Return 0 for empty array
    int maxVal = arr[0];
    for (int num : arr) {
        if (num > maxVal) {
            maxVal = num;
        }
    }
    return maxVal;
}

} // namespace ArrayUtils
