#include <iostream>
#include <vector>
#include "array_utils.h" // Include the user-defined header file

int main() {
    std::vector<int> arr = {10, 20, 30, 40, 50};

    // Use the functions from the ArrayUtils namespace
    double avg = ArrayUtils::average(arr);
    int maxVal = ArrayUtils::maximum(arr);

    std::cout << "Average: " << avg << std::endl;
    std::cout << "Maximum: " << maxVal << std::endl;

    return 0;
}
