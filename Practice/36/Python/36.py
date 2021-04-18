from enum import Enum
import math
import copy

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


with open('data.txt') as fin:
    original = [Point(p) for p in fin.readline().split(', ')]

simulacrum = copy.deepcopy(original)
for p in simulacrum:
    print(p, end='')
    p.set_x(p.get_x() + 10)
    p.set_phi(p.get_phi() + 180 * math.pi / 180)
    p.set_y(-p.get_y())
    p.set_x(-p.get_x() - 10)
    print(p)

print('\nIt works!\n' if simulacrum == original else '\nIt not works!\n')