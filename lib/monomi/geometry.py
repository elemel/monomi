from collections import defaultdict
import math

class Vector(object):
    __slots__ = 'x', 'y'

    def __init__(self, x=0.0, y=0.0):
        self.x = x
        self.y = y

    def __repr__(self):
        return 'Vector(%r, %r)' % (self.x, self.y)

    @property
    def length(self):
        return math.sqrt(self.x * self.x + self.y * self.y)

    @property
    def squared_length(self):
        return self.x * self.x + self.y * self.y

    def __nonzero__(self):
        return self.x or self.y

    def __iter__(self):
        yield self.x
        yield self.y

    def __iadd__(self, other):
        self.x += other.x
        self.y += other.y
        return self

    def __isub__(self, other):
        self.x -= other.x
        self.y -= other.y
        return self

    def __imul__(self, other):
        self.x *= other
        self.y *= other
        return self

    def __idiv__(self, other):
        self.x /= other
        self.y /= other
        return self

    def __add__(self, other):
        return Vector(self.x + other.x, self.y - other.y)

    def __sub__(self, other):
        return Vector(self.x - other.x, self.y - other.y)

    def __mul__(self, other):
        return Vector(self.x * other, self.y * other)

    def __rmul__(self, other):
        return Vector(other * self.x, other * self.y)

    def __div__(self, other):
        return Vector(self.x / other, self.y / other)

    def __neg__(self):
        return Vector(-self.x, -self.y)

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __ne__(self, other):
        return self.x != other.x or self.y != other.y

    def __hash__(self):
        return hash((self.x, self.y))

    def __abs__(self):
        return self.length

    def copy(self):
        return Vector(self.x, self.y)

    def normalize(self):
        length = self.length
        if length:
            self /= length

class Matrix(object):
    def __init__(self, a=1.0, b=0.0, c=0.0, d=1.0, e=0.0, f=0.0):
        self.abcdef = a, b, c, d, e, f

    def __repr__(self):
        return 'Matrix(%r, %r, %r, %r, %r, %r)' % self.abcdef

    def __mul__(self, other):
        a1, b1, c1, d1, e1, f1 = self.abcdef
        a2, b2, c2, d2, e2, f2 = other.abcdef
        a3 = a1 * a2 + c1 * b2
        b3 = b1 * a2 + d1 * b2
        c3 = a1 * c2 + c1 * d2
        d3 = b1 * c2 + d1 * d2
        e3 = a1 * e2 + c1 * f2 + e1
        f3 = b1 * e2 + d1 * f2 + f1
        return Matrix(a3, b3, c3, d3, e3, f3)

    def transform_point(self, point):
        x, y = point
        a, b, c, d, e, f = self.abcdef
        return a * x + c * y + e, b * x + d * y + f

    def copy(self):
        return Matrix(*self.abcdef)

    @classmethod
    def create_translate(cls, translation):
        tx, ty = translation
        return cls(1.0, 0.0, 0.0, 1.0, tx, ty)

    @classmethod
    def create_scale(cls, scale):
        if isinstance(scale, float):
            sx = sy = scale
        else:
            sx, sy = scale
        return cls(sx, 0.0, 0.0, sy, 0.0, 0.0)

    @classmethod
    def create_rotate(cls, angle):
        cos_angle = math.cos(angle)
        sin_angle = math.sin(angle)
        return cls(cos_angle, sin_angle, -sin_angle, cos_angle, 0.0, 0.0)

class Bounds(object):
    def __init__(self, min_x=float('inf'), min_y=float('inf'),
                 max_x=float('-inf'), max_y=float('-inf')):
        self.min_x = min_x
        self.min_y = min_y
        self.max_x = max_x
        self.max_y = max_y

    def __repr__(self):
        return ('Bounds(min_x=%r, min_y=%r, max_x=%r, max_y=%r)' %
                (self.min_x, self.min_y, self.max_x, self.max_y))

    def add_point(self, point):
        px, py = point
        self.min_x = min(self.min_x, px)
        self.min_y = min(self.min_y, py)
        self.max_x = max(self.max_x, px)
        self.max_y = max(self.max_y, py)

    def add(self, other):
        self.min_x = min(self.min_x, other.min_x)
        self.min_y = min(self.min_y, other.min_y)
        self.max_x = max(self.max_x, other.max_x)
        self.max_y = max(self.max_y, other.max_y)

    def contains_point(self, point):
        px, py = point
        return (self.min_x <= px <= self.max_x and
                self.min_y <= py <= self.max_y)

    def intersects(self, other):
        return (self.min_x < other.max_x and other.min_x < self.max_x and
                self.min_y < other.max_y and other.min_y < self.max_y)

class Shape(object):
    def get_bounds(self, matrix):
        raise NotImplementedError()

class Circle(Shape):
    def __init__(self, center=(0.0, 0.0), radius=1.0):
        self.center = center
        self.radius = radius

    def get_bounds(self, matrix):
        pass

class Polygon(Shape):
    def __init__(self, vertices):
        self.vertices = list(vertices)

class Grid(object):
    def __init__(self, cell_size=1.0):
        self.cell_size = cell_size
        self.bounds = {}
        self.masks = {}
        self.seeds = set()
        self.cells = defaultdict(set)

    def add(self, key, bounds, masks):
        self.remove(key)
        self.add_bounds(key, bounds)
        self.add_masks(key, masks)

    def add_bounds(self, key, bounds):
        self.bounds[key] = bounds
        min_col, min_row, max_col, max_row = self.hash_bounds(bounds)
        for col in xrange(min_col, max_col + 1):
            for row in xrange(min_row, max_row + 1):
                self.cells[col, row].add(key)

    def add_masks(self, key, masks):
        self.masks[key] = masks
        mask, include_mask, exclude_mask = masks
        if include_mask:
            self.seeds.add(key)

    def remove(self, key):
        self.remove_bounds(key)
        self.remove_masks(key)

    def remove_bounds(self, key):
        bounds = self.bounds.pop(key, None)
        if bounds is not None:
            min_col, min_row, max_col, max_row = self.hash_bounds(bounds)
            for col in xrange(min_col, max_col + 1):
                for row in xrange(min_row, max_row + 1):
                    self.cells[col, row].remove(key)

    def remove_masks(self, key):
        self.seeds.discard(key)
        self.masks.pop(key, None)

    def hash_bounds(self, bounds):
        min_col, min_row = self.hash_point((bounds.min_x, bounds.min_y))
        max_col, max_row = self.hash_point((bounds.max_x, bounds.max_y))
        return min_col, min_row, max_col, max_row

    def hash_point(self, point):
        px, py = point
        col = int(round(px / self.cell_size))
        row = int(round(py / self.cell_size))
        return col, row

    def query(self, bounds, masks):
        for key in self.masks:
            if (self.match_masks(masks, self.masks[key]) and
                self.match_bounds(bounds, self.bounds[key])):
                yield key

    def query_all(self):
        for key_a in self.seeds:
            for key_b in self.masks:
                if key_a < key_b or key_b not in self.seeds:
                    if self.match_keys(key_a, key_b):
                        yield key_a, key_b

    def match_keys(self, key_a, key_b):
        return (self.match_masks(self.masks[key_a], self.masks[key_b]) and
                self.match_bounds(self.bounds[key_a], self.bounds[key_b]))

    def match_masks(self, masks_a, masks_b):
        mask_a, include_mask_a, exclude_mask_a = masks_a
        mask_b, include_mask_b, exclude_mask_b = masks_b
        include = mask_a & include_mask_b or mask_b & include_mask_a
        exclude = mask_a & exclude_mask_b or mask_b & exclude_mask_a
        return include and not exclude

    def match_bounds(self, bounds_a, bounds_b):
        min_xa, min_ya, max_xa, max_ya = bounds_b
        min_xb, min_yb, max_xb, max_yb = bounds_b
        return (min_xa <= max_xb and min_xb <= max_xa and
                min_ya <= max_yb and min_yb <= max_ya)

    def get_cell_bounds(self, col, row):
        min_x = self.cell_size * (float(col) - 0.5)
        min_y = self.cell_size * (float(row) - 0.5)
        max_x = self.cell_size * (float(col) + 0.5)
        max_y = self.cell_size * (float(row) + 0.5)
        return Bounds(min_x, min_y, max_x, max_y)

