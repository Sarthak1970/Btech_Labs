// //create a class rectangle having variables length and breath. create a default constructor that assigns intial values 1.00 and 1.00
// // parameterized constructor that assigns values based on the parameters passed
// // define a+ operator to add lengths and breaths of two rectangle objects to create a new rectangle using operator overloading
// //create two programs both named add both of which calculate sum of areas of two rectangle objects 
// //1st onr takes integer valuesand returns area in datatype int
// //2nd program takes float values and returns area in datatype float
#include <iostream>
using namespace std;

// class Rectangle {
// private:
//     float length;
//     float breadth;

// public:
//     // Default constructor
//     Rectangle() : length(1.00), breadth(1.00) {}

//     // Parameterized constructor
//     Rectangle(float length, float breadth) : length(length), breadth(breadth) {}

//     // Getter methods
//     float getLength() const { return length; }
//     float getBreadth() const { return breadth; }

//     // Operator overloading for +
//     Rectangle operator+(const Rectangle& other) const {
//         return Rectangle(length + other.length, breadth + other.breadth);
//     }

//     // Calculate area
//     float calculateArea() const { return length * breadth; }
// };

// // Function to calculate sum of areas of two rectangles (int version)
// int add(const Rectangle& rect1, const Rectangle& rect2) {
//     return static_cast<int>(rect1.calculateArea() + rect2.calculateArea());
// }

// // Function to calculate sum of areas of two rectangles (float version)
// float add(float rect1Length, float rect1Breadth, float rect2Length, float rect2Breadth) {
//     Rectangle rect1(rect1Length, rect1Breadth);
//     Rectangle rect2(rect2Length, rect2Breadth);
//     return rect1.calculateArea() + rect2.calculateArea();
// }

class Rectangle{
    int length;
    int breadth;

    public:
    friend Rectangle operator+(const Rectangle &r1,const Rectangle &r2);

    Rectangle(){
        length=1;
        breadth=1;
    }

    Rectangle(int l,int b){
        length=l;
        breadth=b;
    }

    int getLength(){
        return length;
    }

    int getBreadth(){
        return breadth;
    }
};

Rectangle operator+(const Rectangle &r1,const Rectangle &r2){
    Rectangle temp;
    temp.length=r1.length+r2.length;
    temp.breadth=r1.breadth+r2.breadth;
    return temp;
}

int main() {
    // Test the code
    Rectangle rect1(2, 3);
    Rectangle rect2(3, 2);

    Rectangle rect3 = rect1 + rect2; // Operator overloading
    cout << "Length of rect3: " << rect3.getLength() << endl;
    cout << "Breadth of rect3: " << rect3.getBreadth() << endl;

    // int sumOfAreasInt = add(rect1, rect2);
    // cout << "Sum of areas (int): " << sumOfAreasInt << endl;

    // float sumOfAreasFloat = add(2.5, 3.5, 1.5, 2.5);
    // cout << "Sum of areas (float): " << sumOfAreasFloat << endl;

    return 0;
}