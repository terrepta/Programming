#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

double sqr(double a);
bool equal(double a, double b, double e = 1E-10);

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

class Vector {
private:
    Point unit;

public:
    Vector()
        : unit(1,0){}

    Vector(Point end)
        : unit(end.get_x(), end.get_y()) {}

    Vector(Point begin, Point end)
        : unit(end.get_x() - begin.get_x(), end.get_y() - begin.get_y()) {}

    bool operator==(const Vector vec) {
        return unit == vec.unit;
    }

    Vector operator-() {
        Point p = unit;
        p.set_x(-p.get_x());
        p.set_y(-p.get_y());
        return Vector(p);
    }

   Vector operator+(Vector vec) {
       Point p;
       p.set_x(unit.get_x() + vec.unit.get_x());
       p.set_y(unit.get_y() + vec.unit.get_y());
       return Vector(p);
   }

   Vector operator-(Vector vec) {
       Point p;
       p.set_x(unit.get_x() - vec.unit.get_x());
       p.set_y(unit.get_y() - vec.unit.get_y());
       return Vector(p);
   }

   Vector operator*(double factor) {
       Point p = unit;
       p.set_x(p.get_x() * factor);
       p.set_y(p.get_y() * factor);
       return Vector(p);
   }

   double length() {
       return unit.get_r();
   }

   double operator*(Vector vec) {
       return length() * vec.length() * cos(unit.get_phi() - vec.unit.get_phi());
   }
};

int main()
{
    Vector a(Point(1, 2)), b(Point(-2, 0), Point(-1, 2));
    if (a == b && b == a) cout << "Equality test passed\n";
    else cout << "Equality test failed\n";

    Vector na(Point(-1, -2)), ox(Point(1, 0)), nox(Point(-1, 0)), oy(Point(0, 1)), noy(Point(0, -1));
    if (a == -na && na == -a && -ox == nox && -oy == noy) cout << "Invert test passed\n";
    else cout << "Invert test failed\n";

    if (ox + oy + oy == a && -ox == -a + oy + oy) cout << "Summation test passed\n";
    else cout << "Summation test failed\n";

    if (-ox + oy == oy - ox && -oy + ox == ox - oy) cout << "Subtraction test passed\n";
    else cout << "Subtraction test failed\n";

    if (ox * 3 == ox + ox + ox &&
        oy * 3 == oy + oy + oy &&
        ox * (-3) == -ox - ox - ox &&
        oy * (-3) == -oy - oy - oy) cout << "Multiplication by number test passed\n";
    else cout << "Multiplication by number test failed\n";

    if (equal(ox.length(), 1) &&
        equal(oy.length(), 1) &&
        equal((ox * 3 + oy * 4).length(), 5)) cout << "Length test passed\n";
    else cout << "Length test failed\n";

    if (equal(ox * ox, sqr(ox.length())) &&
        equal(oy * oy, sqr(oy.length())) &&
        equal((ox * 3 + oy * 4) * (ox * 3 + oy * 4), sqr((ox * 3 + oy * 4).length()))) cout << "Multiplication by Vector test passed\n";
    else cout << "Multiplication by Vector test failed\n";
}

bool equal(double a, double b, double e) {
    if (-e < a - b && a - b < e) return true;
    else return false;
}

double sqr(double a) {
    return a * a;
}
