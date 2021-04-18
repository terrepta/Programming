#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const auto PI = 3.141592653589793;

enum coord_system {
    Cartesian,
    Polar
};

class Point {
private:
    double x, y;
    double r, phi;

public:
    Point(double a1 = 0, double a2 = 0, coord_system c_s = coord_system::Cartesian) {
        if (c_s == coord_system::Cartesian) {
            x = a1;
            y = a2;
            r = sqrt(x * x + y * y);
            phi = atan(y / x);
        }
        else {
            r = a1;
            phi = a2;
            x = cos(phi) * r;
            y = sin(phi) * r;
        }
    }

    const double deviation = 1e-10;

    bool operator==(const Point& coord) {
        if (abs(this->x - coord.x) < deviation &&
            abs(this->y - coord.y) < deviation)
            return true;
        else return false;
    }

    bool operator!=(const Point& coord) {
        return !(*this == coord);
    }

    friend ostream& operator<<(ostream& out, const Point& coord) {
        out << '(' << coord.x << ',' << coord.y << ')';
        return out;
    }

    friend istream& operator>>(istream& in, Point& coord) {
        char c1, c2, c3;
        in >> c1 >> coord.x >> c2 >> coord.y >> c3;
        return in;
    }

    double get_x() {
        return x;
    }

    double get_y() {
        return y;
    }

    double get_r() {
        return r;
    }

    double get_phi() {
        return phi;
    }

    void set_x(double x) {
        this->x = x;
    }

    void set_y(double y) {
        this->y = y;
    }

    void set_r(double r) {
        this->r = r;
    }

    void set_phi(double phi) {
        this->phi = phi;
    }

};

int main() {
    std::vector<Point> original;
    std::ifstream fin("data.txt");
    if (!fin.is_open()) {
        std::cout << "Can't open file" << std::endl;
        return 1;
    }
    else {
        while (!fin.eof()) {
            Point p;
            fin >> p;
            fin.ignore(2); // Точки разделены двумя символами ", "
            original.push_back(p);
        }
        fin.close();
    }

    std::vector<Point> simulacrum(original);
    for (auto& p : simulacrum) {
        std::cout << p;
        p.set_x(p.get_x() + 10);
        p.set_phi(p.get_phi() + 180 * PI / 180);
        p.set_y(-p.get_y());
        p.set_x(-p.get_x() - 10);
        std::cout << p << std::endl;
    }

    if (std::equal(original.begin(), original.end(), simulacrum.begin()))
        std::cout << "\nIt works!\n";
    else
        std::cout << "\nIt not works!\n";
}
