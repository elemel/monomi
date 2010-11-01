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
        assert isinstance(other, Vector)
        self.x += other.x
        self.y += other.y
        return self

    def __isub__(self, other):
        assert isinstance(other, Vector)
        self.x -= other.x
        self.y -= other.y
        return self

    def __imul__(self, other):
        assert isinstance(other, float)
        self.x *= other
        self.y *= other
        return self

    def __idiv__(self, other):
        assert isinstance(other, float)
        self.x /= other
        self.y /= other
        return self

    def __add__(self, other):
        assert isinstance(other, Vector)
        return Vector(self.x + other.x, self.y + other.y)

    def __sub__(self, other):
        assert isinstance(other, Vector)
        return Vector(self.x - other.x, self.y - other.y)

    def __mul__(self, other):
        assert isinstance(other, float)
        return Vector(self.x * other, self.y * other)

    def __rmul__(self, other):
        assert isinstance(other, float)
        return Vector(other * self.x, other * self.y)

    def __div__(self, other):
        assert isinstance(other, float)
        return Vector(self.x / other, self.y / other)

    def __neg__(self):
        return Vector(-self.x, -self.y)

    def __eq__(self, other):
        assert isinstance(other, Vector)
        return self.x == other.x and self.y == other.y

    def __ne__(self, other):
        assert isinstance(other, Vector)
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
        return length

class Matrix(object):
    def __init__(self, a=1.0, b=0.0, c=0.0, d=1.0, e=0.0, f=0.0):
        assert isinstance(a, float)
        assert isinstance(b, float)
        assert isinstance(c, float)
        assert isinstance(d, float)
        assert isinstance(e, float)
        assert isinstance(f, float)
        self.abcdef = a, b, c, d, e, f

    def __repr__(self):
        return 'Matrix(a=%r, b=%r, c=%r, d=%r, e=%r, f=%r)' % self.abcdef

    def __mul__(self, other):
        assert isinstance(other, Matrix)
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
        assert isinstance(point, Vector)
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
        assert isinstance(min_x, float)
        assert isinstance(min_y, float)
        assert isinstance(max_x, float)
        assert isinstance(max_y, float)
        self.min_x = min_x
        self.min_y = min_y
        self.max_x = max_x
        self.max_y = max_y

    @property
    def bounds(self):
        return self

    def __repr__(self):
        return ('Bounds(min_x=%r, min_y=%r, max_x=%r, max_y=%r)' %
                (self.min_x, self.min_y, self.max_x, self.max_y))

    def add(self, other):
        assert isinstance(other, Bounds)
        self.min_x = min(self.min_x, other.min_x)
        self.min_y = min(self.min_y, other.min_y)
        self.max_x = max(self.max_x, other.max_x)
        self.max_y = max(self.max_y, other.max_y)

    def intersects(self, other):
        assert isinstance(other, Bounds)
        return (self.min_x < other.max_x and other.min_x < self.max_x and
                self.min_y < other.max_y and other.min_y < self.max_y)

    def add_point(self, point):
        assert isinstance(point, Vector)
        self.min_x = min(self.min_x, point.x)
        self.min_y = min(self.min_y, point.y)
        self.max_x = max(self.max_x, point.x)
        self.max_y = max(self.max_y, point.y)

    def contains_point(self, point):
        assert isinstance(point, Vector)
        return (self.min_x <= point.x <= self.max_x and
                self.min_y <= point.y <= self.max_y)

    def copy(self):
        return Bounds(self.min_x, self.min_y, self.max_x, self.max_y)

class Shape(object):
    @property
    def bounds(self):
        raise NotImplementedError()

    def copy(self):
        raise NotImplementedError()

class Circle(Shape):
    def __init__(self, center=Vector(), radius=1.0):
        assert isinstance(center, Vector)
        self.center = center.copy()
        self.radius = radius

    def __repr__(self):
        return 'Circle(center=%r, radius=%r)' % (self.center, self.radius)

    @property
    def bounds(self):
        radius = Vector(self.radius, self.radius)
        return Bounds(self.center.x - self.radius, self.center.y - self.radius,
                      self.center.x + self.radius, self.center.y + self.radius)

    def copy(self):
        return Circle(self.center, self.radius)

class Polygon(Shape):
    def __init__(self, vertices):
        self.vertices = list(v.copy() for v in vertices)

    def __repr__(self):
        return 'Polygon(%r)' % self.vertices

    @property
    def bounds(self):
        bounds = Bounds()
        for vertex in self.vertices:
            bounds.add_point(vertex)
        return bounds

    def copy(self):
        return Polygon(self.vertices)

class Masks(object):
    def __init__(self, mask=~0, include_mask=~0, exclude_mask=0):
        assert isinstance(mask, int)
        assert isinstance(include_mask, int)
        assert isinstance(exclude_mask, int)
        self.mask = mask
        self.include_mask = include_mask
        self.exclude_mask = exclude_mask

    def __repr__(self):
        return ('Masks(mask=0x%x, include_mask=0x%x, exclude_mask=0x%x)' %
                (self.mask, self.include_mask, self.exclude_mask))

    def match(self, other):
        included = (self.mask & other.include_mask or
                    other.mask & self.include_mask)
        excluded = (self.mask & other.exclude_mask or
                    other.mask & self.exclude_mask)
        return included and not excluded

    def copy(self):
        return Masks(self.mask, self.include_mask, self.exclude_mask)

class Grid(object):
    def __init__(self, cell_size=1.0):
        self.cell_size = cell_size
        self.shapes = {}
        self.bounds = {}
        self.masks = {}
        self.seeds = set()
        self.cells = defaultdict(set)

    def add_shape(self, key, shape, masks):
        assert isinstance(shape, Shape)
        assert isinstance(masks, Masks)
        self.remove(key)
        self.shapes[key] = shape.copy()
        self.add_bounds(key, shape.bounds)
        self.add_masks(key, masks)

    def add_bounds(self, key, bounds):
        assert isinstance(bounds, Bounds)
        bounds = bounds.copy()
        self.bounds[key] = bounds
        min_col, min_row, max_col, max_row = self.hash_bounds(bounds)
        for col in xrange(min_col, max_col + 1):
            for row in xrange(min_row, max_row + 1):
                self.cells[col, row].add(key)

    def add_masks(self, key, masks):
        assert isinstance(masks, Masks)
        masks = masks.copy()
        self.masks[key] = masks
        if masks.include_mask:
            self.seeds.add(key)

    def remove(self, key):
        self.shapes.pop(key, 0)
        self.remove_bounds(key)
        self.remove_masks(key)

    def remove_bounds(self, key):
        bounds = self.bounds.pop(key, None)
        if bounds is not None:
            min_col, min_row, max_col, max_row = self.hash_bounds(bounds)
            for col in xrange(min_col, max_col + 1):
                for row in xrange(min_row, max_row + 1):
                    cell = self.cells[col, row]
                    cell.remove(key)
                    if not cell:
                        del self.cells[col, row]

    def remove_masks(self, key):
        self.seeds.discard(key)
        self.masks.pop(key, None)

    def hash_bounds(self, bounds):
        min_col = int(round(bounds.min_x / self.cell_size))
        min_row = int(round(bounds.min_y / self.cell_size))
        max_col = int(round(bounds.max_x / self.cell_size))
        max_row = int(round(bounds.max_y / self.cell_size))
        return min_col, min_row, max_col, max_row

    def query(self, bounds, masks):
        for key in self.masks:
            if (bounds.intersects(self.bounds[key]) and
                masks.match(self.masks[key])):
                yield key

    def query_all(self):
        for key_a in self.seeds:
            for key_b in self.masks:
                if key_a < key_b or key_b not in self.seeds:
                    if self.match_keys(key_a, key_b):
                        yield key_a, key_b

    def match_keys(self, key_a, key_b):
        return (self.match_masks(self.masks[key_a], self.masks[key_b]) and
                self.bounds[key_a].intersects(self.bounds[key_b]))

    def match_masks(self, masks_a, masks_b):
        mask_a, include_mask_a, exclude_mask_a = masks_a
        mask_b, include_mask_b, exclude_mask_b = masks_b
        include = mask_a & include_mask_b or mask_b & include_mask_a
        exclude = mask_a & exclude_mask_b or mask_b & exclude_mask_a
        return include and not exclude

    def get_cell_bounds(self, col, row):
        min_x = self.cell_size * (float(col) - 0.5)
        min_y = self.cell_size * (float(row) - 0.5)
        max_x = self.cell_size * (float(col) + 0.5)
        max_y = self.cell_size * (float(row) + 0.5)
        return Bounds(min_x, min_y, max_x, max_y)

