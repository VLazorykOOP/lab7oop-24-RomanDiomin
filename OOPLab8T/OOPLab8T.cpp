#include <iostream>
using namespace std;

class Base {
public:
    int baseData;

    Base(int bd) : baseData(bd) {}
    virtual ~Base() {}
};

class D1 : public Base {
public:
    int d1Data;

    D1(int bd, int d1d) : Base(bd), d1Data(d1d) {}
};

class D2 : public Base, public D1 {
public:
    int d2Data;

    D2(int bd, int d2d, int d1, int d2) : Base(bd), d2Data(d2d), D1(d1, d2) {}
};

class D3 : public Base {
public:
    int d3Data;

    D3(int bd, int d3d) : Base(bd), d3Data(d3d) {}
};

class D4 : public D3 {
public:
    int d4Data;

    D4(int bd, int d3d, int d4d) : D3(bd, d3d), d4Data(d4d) {}
};

class D5 : public D3, public D2 {
public:
    int d5Data;

    D5(int bd, int d3d, int d2d, int d5d, int d1, int d2) : D3(bd, d3d), D2(bd, d2d, d1, d2), d5Data(d5d) {}
};


class Figure {
public:
    virtual double perimeter() const = 0;
};

class Rectangle : public Figure {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double perimeter() const override {
        return 2 * (width + height);
    }
};

class Circle : public Figure {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double perimeter() const override {
        return 2 * 3.14 * radius;
    }
};

class RightTriangle : public Figure {
private:
    double side1;
    double side2;
    double hypotenuse;

public:
    RightTriangle(double s1, double s2, double hyp) : side1(s1), side2(s2), hypotenuse(hyp) {}

    double perimeter() const override {
        return side1 + side2 + hypotenuse;
    }
};

class Trapezoid : public Figure {
private:
    double base1;
    double base2;
    double side1;
    double side2;

public:
    Trapezoid(double b1, double b2, double s1, double s2) : base1(b1), base2(b2), side1(s1), side2(s2) {}

    double perimeter() const override {
        return base1 + base2 + side1 + side2;
    }
};


class Person {
protected:
    string name;
    int age;

public:
    Person(const string& n, int a) : name(n), age(a) {}

    virtual ~Person() {}

    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    friend ostream& operator<<(ostream& os, const Person& person) {
        os << "Name: " << person.name << ", Age: " << person.age;
        return os;
    }

    friend istream& operator>>(istream& is, Person& person) {
        cout << "Enter name: ";
        is >> person.name;
        cout << "Enter age: ";
        is >> person.age;
        return is;
    }
};

class Woman : virtual public Person {
protected:
    string gender;

public:
    Woman(const string& n, int a, const string& g) : Person(n, a), gender(g) {}

    void display() const override {
        cout << "Name: " << name << ", Age: " << age << ", Gender: " << gender << endl;
    }

    friend ostream& operator<<(ostream& os, const Woman& woman) {
        os << static_cast<const Person&>(woman) << ", Gender: " << woman.gender;
        return os;
    }

    friend istream& operator>>(istream& is, Woman& woman) {
        is >> static_cast<Person&>(woman);
        cout << "Enter gender: ";
        is >> woman.gender;
        return is;
    }
};

class Employee : virtual public Person {
protected:
    string position;

public:
    Employee(const string& n, int a, const string& pos) : Person(n, a), position(pos) {}

    void display() const override {
        cout << "Name: " << name << ", Age: " << age << ", Position: " << position << endl;
    }

    friend ostream& operator<<(ostream& os, const Employee& employee) {
        os << static_cast<const Person&>(employee) << ", Position: " << employee.position;
        return os;
    }

    friend istream& operator>>(istream& is, Employee& employee) {
        is >> static_cast<Person&>(employee);
        cout << "Enter position: ";
        is >> employee.position;
        return is;
    }
};

class EmployeeWoman : public Woman, public Employee {
public:
    EmployeeWoman(const string& n, int a, const string& g, const string& pos)
        : Person(n, a), Woman(n, a, g), Employee(n, a, pos) {}

    void display() const override {
        cout << "Name: " << name << ", Age: " << age << ", Gender: " << gender
            << ", Position: " << position << endl;
    }

    friend ostream& operator<<(ostream& os, const EmployeeWoman& employeeWoman) {
        os << static_cast<const Person&>(employeeWoman) << ", Gender: " << employeeWoman.gender
            << ", Position: " << employeeWoman.position;
        return os;
    }

    friend istream& operator>>(istream& is, EmployeeWoman& employeeWoman) {
        is >> static_cast<Person&>(employeeWoman);
        cout << "Enter gender: ";
        is >> employeeWoman.gender;
        cout << "Enter position: ";
        is >> employeeWoman.position;
        return is;
    }
};

int main() {
    int task;
    cout << "Enter task: ";
    cin >> task;
    switch (task)
    {
    case 1: {
        Base b(10);
        D1 d1(20, 30);
        D2 d2(40, 50, 34, 43);
        D3 d3(60, 70);
        D4 d4(80, 90, 100);
        D5 d5(110, 120, 130, 140, 21, 32);

        cout << "Size of Base object: " << sizeof(b) << endl;
        cout << "Size of D1 object: " << sizeof(d1) << endl;
        cout << "Size of D2 object: " << sizeof(d2) << endl;
        cout << "Size of D3 object: " << sizeof(d3) << endl;
        cout << "Size of D4 object: " << sizeof(d4) << endl;
        cout << "Size of D5 object: " << sizeof(d5) << endl;

        break;
    }
    case 2: {
        Rectangle rect(4, 5);
        Circle circle(3);
        RightTriangle triangle(3, 4, 5);
        Trapezoid trapezoid(3, 5, 4, 6);

        cout << "Perimeter of rectangle: " << rect.perimeter() << endl;
        cout << "Perimeter of circle: " << circle.perimeter() << endl;
        cout << "Perimeter of right triangle: " << triangle.perimeter() << endl;
        cout << "Perimeter of trapezoid: " << trapezoid.perimeter() << endl;
        break;
    }
    case 3: {
        Person person("John", 30);
        cout << "Person: " << person << endl;

        Woman woman("Alice", 25, "female");
        cout << "Woman: " << woman << endl;

        Employee employee("Bob", 40, "Manager");
        cout << "Employee: " << employee << endl;

        EmployeeWoman employeeWoman("Mary", 35, "female", "CEO");
        cout << "EmployeeWoman: " << employeeWoman << endl;
        break;
    }
    }
    return 0;
}

