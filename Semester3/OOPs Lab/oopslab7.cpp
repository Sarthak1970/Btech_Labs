#include <iostream>
using namespace std;

template <typename T>
T findMax(T arr[], int size) {
    T max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

template <typename T>
class Rectangle {
private:
    T length;
    T width;
public:
    Rectangle(T l, T w) : length(l), width(w) {}

    T area() {
        return length * width;
    }

    T perimeter() {
        return 2 * (length + width);
    }

    void display() {
        cout << "Length: " << length << ", Width: " << width << endl;
    }
};

int main() {
    int intArr[] = {1, 5, 2, 9, 4};
    int intMax = findMax(intArr, 5);
    cout << "Maximum in integer array: " << intMax << endl;

    float floatArr[] = {1.1, 3.5, 2.2, 9.8, 4.3};
    float floatMax = findMax(floatArr, 5);
    cout << "Maximum in float array: " << floatMax << endl;

    char charArr[] = {'a', 'd', 'b', 'z', 'm'};
    char charMax = findMax(charArr, 5);
    cout << "Maximum in character array: " << charMax << endl;

    Rectangle<int> rectInt(10, 5);
    rectInt.display();
    cout << "Area (int): " << rectInt.area() << endl;
    cout << "Perimeter (int): " << rectInt.perimeter() << endl;

    Rectangle<float> rectFloat(10.5, 5.2);
    rectFloat.display();
    cout << "Area (float): " << rectFloat.area() << endl;
    cout << "Perimeter (float): " << rectFloat.perimeter() << endl;

    return 0;
}
