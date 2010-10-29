import math

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

class BoundingBox(object):
    def __init__(self, min_x=float('inf'), min_y=float('inf'),
                 max_x=float('-inf'), max_y=float('-inf')):
        self.min_x = min_x
        self.min_y = min_y
        self.max_x = max_x
        self.max_y = max_y

    def __repr__(self):
        return ('BoundingBox(min_x=%r, min_y=%r, max_x=%r, max_y=%r)' %
                (self.min_x, self.min_y, self.max_x, self.max_y))

    def add_point(self, point):
        x, y = point
        self.min_x = min(self.min_x, x)
        self.min_y = min(self.min_y, y)
        self.max_x = max(self.max_x, x)
        self.max_y = max(self.max_y, y)

    def add(self, other):
        self.min_x = min(self.min_x, other.min_x)
        self.min_y = min(self.min_y, other.min_y)
        self.max_x = max(self.max_x, other.max_x)
        self.max_y = max(self.max_y, other.max_y)

    def contains_point(self, point):
        x, y = point
        return (self.min_x <= x and x <= self.max_x and
                self.min_y <= y and y <= self.max_y)

    def intersects(self, other):
        return (self.min_x <= other.max_x and other.min_x <= self.max_x and
                self.min_y <= other.max_y and other.min_y <= self.max_y)

class Shape(object):
    def get_bounding_box(self, matrix):
        raise NotImplementedError()

class Circle(Shape):
    def __init__(self, center=(0.0, 0.0), radius=1.0):
        self.center = center
        self.radius = radius

    def get_bounding_box(self, matrix):
        pass

class ConvexPolygon(Shape):
    def __init__(self, vertices):
        self.vertices = list(vertices)

class Grid(object):
    def __init__(self):
        self.bounds = {}
        self.masks = {}
        self.seeds = set()

    def add(self, key, bounds, masks):
        self.remove(key)
        min_x, min_y, max_x, max_y = bounds
        mask, include_mask, exclude_mask = masks
        self.bounds[key] = bounds
        self.masks[key] = masks
        if include_mask:
            self.seeds.add(key)

    def remove(self, key):
        self.seeds.discard(key, None)
        self.masks.pop(key, None)
        self.bounds.pop(key, None)

    def query(self, bounds, masks):
        for key in self.masks:
            if (self.match_masks(masks, self.masks[key]) and
                self.match_bounds(bounds, self.bounds[key])):
                yield key

    def query_all(self):
        for key_1 in self.seeds:
            for key_2 in self.masks:
                if key_1 < key_2 or key_2 not in self.seeds:
                    if self.match_keys(key_1, key_2):
                        yield key_1, key_2

    def match_keys(self, key_1, key_2):
        return (self.match_masks(self.masks[key_1], self.masks[key_2]) and
                self.match_bounds(self.bounds[key_1], self.bounds[key_2]))

    def match_masks(self, masks_1, masks_2):
        mask_1, include_mask_1, exclude_mask_1 = masks_1
        mask_2, include_mask_2, exclude_mask_2 = masks_2
        include = mask_1 & include_mask_2 or mask_2 & include_mask_1
        exclude = mask_1 & exclude_mask_2 or mask_2 & exclude_mask_1
        return include and not exclude

    def match_bounds(self, bounds_1, bounds_2):
        min_x_1, min_y_1, max_x_1, max_y_1 = bounds_1
        min_x_2, min_y_2, max_x_2, max_y_2 = bounds_2
        return (min_x_1 <= max_x_2 and min_x_2 <= max_x_1 and
                min_y_1 <= max_y_2 and min_y_2 <= max_y_1)
