from enum import Enum
import math

def equal(a, b, e=1E-10):
    if -e < a - b < e: return True
    else: return False

class CoordSystem(Enum):
    Cartesian = auto()
    Polar = auto()

class Point:
    def __init__(self, a1 = 0, a2 = 0, coord_system = CoordSystem.Cartesian):
        if type(a1) == str:
            s = a1
            comma = a1.find(",")
            a1 = s[1:comma - 1]
            a2 = s[comma + 1:len(s) - 2]

        if coord_system == CoordSystem.Cartesian:
            self.x = a1
            self.y = a2
            self.r = (a1 * a1 + a2 * a2) ** (1/2)
            self.phi = atan(a2 / a1)
        else:
            self.r = a1
            self.phi = a2
            self.x = a1 * cos(a2)
            self.y = a1 * sin(a2)

    deviation = 1e-10

    def __eq__(self, coord):
        return (abs(self.x - coord.x) < deviation and abs(self.y - coord.y) < deviation)
   
    def __ne__(self, coord):
        return not self == coord

    def __repr__(self):
        return f'({self.x},{self.y})'

    def __str__(self):
        return f'({self.x},{self.y})'

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

    def get_r(self):
        return self.r

    def get_phi(self):
        return self.phi

    def set_x(self, x):
        self.x = x

    def set_y(self, y):
        self.y = y

    def set_r(self, r):
        self.r = r

    def set_phi(self, phi):
        self.phi = phi

class Vector:
    unit: Point
    def __init__(self, begin = None, end = None):
        if begin == None and end == None:
            self.unit = Point(1, 0)

        elif begin == None and end != None:
            self.unit = end
        elif begin != None and end == None:
            self.unit = begin
        else:
            self.unit = Point(end.get_x() - begin.get_x(), end.get_y() - begin.get_y())

    def __eq__(self, other):
        return self.unit == other.unit

    def __neg__(self):
        return Vector(Point(-self.unit.get_x(), -self.unit.get_y()))

    def __add__(self, other):
        p = Point()
        p.set_x(self.unit.get_x() + other.unit.get_x())
        p.set_y(self.unit.get_y() + other.unit.get_y())
        return Vector(p)

    def __sub__(self, other):
        p = Point()
        p.set_x(self.unit.get_x() - other.unit.get_x())
        p.set_y(self.unit.get_y() - other.unit.get_y())
        return Vector(p)

    def __mul__(self, other):
        if type(other) == float or type(other) == int:
            p = Point()
            p.set_x(self.unit.get_x() * other)
            p.set_y(self.unit.get_y() * other)
            return Vector(p)
        else:
            return self.length() * other.length() * cos( self.unit.get_phi() - other.unit.get_phi())

    def length(self):
        return self.unit.get_r()

a = Vector(Point(1, 2))
b = Vector(Point(-2, 0), Point(-1, 2))
if a == b and b == a: print('Equality test passed')
else: print('Equality test failed')
  
na  = Vector(Point(-1, -2))
ox  = Vector(Point( 1,  0))
nox = Vector(Point(-1,  0))
oy  = Vector(Point( 0,  1))
noy = Vector(Point( 0, -1))
if a == -na and na == -a and -ox == nox and -oy == noy: print('Invert test passed')
else: print('Invert test failed')
  
if ox + oy + oy == a and -ox == -a + oy + oy: print('Summation test passed')
else: print('Summation test failed')
  
if -ox + oy == oy - ox and -oy + ox == ox - oy: print('Subtraction test passed')
else: print('Subtraction test failed')
  
if (ox * 3 == ox + ox + ox and
    oy * 3 == oy + oy + oy and
    ox * (-3) == -ox - ox - ox and
    oy * (-3) == -oy - oy - oy): print('Multiplication by number test passed')
else: print('Multiplication by number test failed')
  
if (equal(ox.length(), 1) and
    equal(oy.length(), 1) and
    equal((ox * 3 + oy * 4).length(), 5)): print('Length test passed')
else: print('Length test failed')
  
if (equal(ox*ox, ox.length()**2) and
    equal(oy*oy, oy.length()**2) and
    equal((ox*3 + oy*4)*(ox*3 + oy*4), (ox*3 + oy*4).length()**2)): print('Multiplication by Vector test passed')
else: print('Multiplication by Vector test failed')