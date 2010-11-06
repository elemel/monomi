from itertools import chain, izip
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
        return math.sqrt(self.squared_length)

    @property
    def squared_length(self):
        return self.dot(self)

    @property
    def normal(self):
        return Vector(self.y, -self.x)

    def __nonzero__(self):
        return self.x or self.y

    def __iter__(self):
        yield self.x
        yield self.y

    def __iadd__(self, vector):
        assert isinstance(vector, Vector)
        self.x += vector.x
        self.y += vector.y
        return self

    def __isub__(self, vector):
        assert isinstance(vector, Vector)
        self.x -= vector.x
        self.y -= vector.y
        return self

    def __imul__(self, f):
        assert isinstance(f, float)
        self.x *= f
        self.y *= f
        return self

    def __idiv__(self, f):
        assert isinstance(f, float)
        self.x /= f
        self.y /= f
        return self

    def __add__(self, vector):
        assert isinstance(vector, Vector)
        return Vector(self.x + vector.x, self.y + vector.y)

    def __sub__(self, vector):
        assert isinstance(vector, Vector)
        return Vector(self.x - vector.x, self.y - vector.y)

    def __mul__(self, f):
        assert isinstance(f, float)
        return Vector(self.x * f, self.y * f)

    def __rmul__(self, f):
        assert isinstance(f, float)
        return Vector(f * self.x, f * self.y)

    def __div__(self, f):
        assert isinstance(f, float)
        return Vector(self.x / f, self.y / f)

    def __neg__(self):
        return Vector(-self.x, -self.y)

    def __eq__(self, vector):
        assert isinstance(vector, Vector)
        return self.x == vector.x and self.y == vector.y

    def __ne__(self, vector):
        assert isinstance(vector, Vector)
        return self.x != vector.x or self.y != vector.y

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

    def dot(self, vector):
        assert isinstance(vector, Vector)
        return self.x * vector.x + self.y * vector.y

    def cross(self, vector):
        assert isinstance(vector, Vector)
        return self.x * vector.y - vector.x * self.y

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

    def __mul__(self, matrix):
        assert isinstance(matrix, Matrix)
        a1, b1, c1, d1, e1, f1 = self.abcdef
        a2, b2, c2, d2, e2, f2 = matrix.abcdef
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

    def __repr__(self):
        return ('Bounds(min_x=%r, min_y=%r, max_x=%r, max_y=%r)' %
                (self.min_x, self.min_y, self.max_x, self.max_y))

    def add(self, bounds):
        assert isinstance(bounds, Bounds)
        self.min_x = min(self.min_x, bounds.min_x)
        self.min_y = min(self.min_y, bounds.min_y)
        self.max_x = max(self.max_x, bounds.max_x)
        self.max_y = max(self.max_y, bounds.max_y)

    def intersects(self, bounds):
        assert isinstance(bounds, Bounds)
        return (self.min_x < bounds.max_x and bounds.min_x < self.max_x and
                self.min_y < bounds.max_y and bounds.min_y < self.max_y)

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

    def intersects(self, shape):
        raise NotImplementedError()

    def intersects_circle(self, circle):
        raise NotImplementedError()

    def intersects_polygon(self, polygon):
        raise NotImplementedError()

    def separate(self, shape):
        raise NotImplementedError()

    def separate_circle(self, circle):
        raise NotImplementedError()

    def separate_polygon(self, polygon):
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
    def squared_radius(self):
        return self.radius * self.radius

    @property
    def bounds(self):
        return Bounds(self.center.x - self.radius, self.center.y - self.radius,
                      self.center.x + self.radius, self.center.y + self.radius)

    def intersects(self, shape):
        assert isinstance(shape, Shape)
        return shape.intersects_circle(self)

    def intersects_circle(self, circle):
        assert isinstance(circle, Circle)
        radius_sum = self.radius + circle.radius
        squared_center_distance = (circle.center - self.center).squared_length
        return squared_center_distance < radius_sum * radius_sum

    def intersects_polygon(self, polygon):
        assert isinstance(polygon, Polygon)
        return polygon.intersects_circle(self)

    def intersects_point(self, point):
        return ((point - self.center).squared_length <
                (self.radius * self.radius))

    def intersects_edge(self, edge):
        vertex_1, vertex_2 = edge
        tangent = vertex_2 - vertex_1
        normal = tangent.normal
        normal.normalize()
        return (tangent.dot(self.center - vertex_1) > 0.0 and
                tangent.dot(self.center - vertex_2) < 0.0 and
                normal.dot(self.center - vertex_1) < self.radius * self.radius)

    def separate(self, shape):
        assert isinstance(shape, Shape)
        return shape.separate_circle(self)

    def separate_circle(self, circle):
        assert isinstance(circle, Circle)
        normal = circle.center - self.center
        center_distance = normal.normalize()
        distance = center_distance - (self.radius + circle.radius)
        return distance, normal

    def separate_polygon(self, polygon):
        assert isinstance(polygon, Polygon)
        return polygon.separate_circle(self)

    def contains_point(self, point):
        return ((point - self.center).squared_length <=
                (self.radius * self.radius))

    def contains_circle(self, circle):
        radius_diff = self.radius - circle.radius
        if radius_diff < 0.0:
            return False
        squared_center_distance = (circle.center - self.center).squared_length
        return squared_center_distance <= (radius_diff * radius_diff)

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

    @property
    def edges(self):
        return izip(self.vertices, self.vertices[1:] + self.vertices[:1])

    @property
    def tangents(self):
        return (v2 - v1 for v1, v2 in self.edges)

    @property
    def normals(self):
        return (t.normal for t in self.tangents)

    def intersects(self, shape):
        assert isinstance(shape, Shape)
        return shape.intersects_polygon(self)

    def intersects_circle(self, circle):
        assert isinstance(circle, Circle)
        return (self.intersects_point(circle.center) or
                any(circle.intersects_point(v) for v in self.vertices) or
                any(circle.intersects_edge(e) for e in self.edges))

    # Separating axis theorem.
    def intersects_polygon(self, polygon):
        assert isinstance(polygon, Polygon)
        return (not self.has_separating_edge(polygon) and
                not polygon.has_separating_edge(self))

    def has_separating_edge(self, polygon):
        assert isinstance(polygon, Polygon)
        return any(all((v2 - v1).cross(v) >= 0.0 for v in polygon.vertices)
                   for v1, v2 in self.edges)

    def separate(self, shape):
        assert isinstance(shape, Shape)
        return shape.separate_polygon(self)

    def separate_circle(self, circle):
        assert isinstance(circle, Circle)
        distance, normal = self.separate_point(circle.center)
        return distance - circle.radius, normal

    def separate_point(self, point):
        assert isinstance(point, Vector)
        return max(self.separate_point_generator(point))

    def separate_point_generator(self, point):
        assert isinstance(point, Vector)
        for i in xrange(len(self.vertices)):
            vertex_1 = self.vertices[i - 2]
            vertex_2 = self.vertices[i - 1]
            vertex_3 = self.vertices[i]
            tangent_1 = vertex_2 - vertex_1
            tangent_2 = vertex_3 - vertex_2
            offset_1 = point - vertex_1
            offset_2 = point - vertex_2
            if tangent_1.dot(offset_1) > 0.0:
                if tangent_1.dot(offset_2) > 0.0:
                    if tangent_2.dot(offset_2) > 0.0:
                        pass
                    else:
                        yield offset_2.normalize(), offset_2
                else:
                    normal = tangent_1.normal
                    normal.normalize()
                    distance = normal.dot(offset_1)
                    yield distance, normal

    def separate_polygon(self, polygon):
        assert isinstance(polygon, Polygon)
        distance_1, normal_1 = max(self.separate_edge(e) for e in polygon.edges)
        distance_2, normal_2 = max(polygon.separate_edge(e) for e in self.edges)
        return max((distance_1, normal_1),
                   (distance_2, -normal_2))

    def separate_edge(self, edge):
        vertex_1, vertex_2 = edge
        normal = (vertex_2 - vertex_1).normal
        normal.normalize()
        distance = min(normal.dot(v - vertex_1) for v in self.vertices)
        return distance, normal

    def intersects_point(self, point):
        assert isinstance(point, Vector)
        return not any((v2 - v1).cross(point - v1) >= 0.0
                       for v1, v2 in self.edges)

    def contains_point(self, point):
        assert isinstance(point, Vector)
        return not any((v2 - v1).cross(point - v1) > 0.0
                       for v1, v2 in self.edges)

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

    def match(self, masks):
        included = (self.mask & masks.include_mask or
                    masks.mask & self.include_mask)
        excluded = (self.mask & masks.exclude_mask or
                    masks.mask & self.exclude_mask)
        return included and not excluded

    def copy(self):
        return Masks(self.mask, self.include_mask, self.exclude_mask)

class Grid(object):
    def __init__(self, cell_size=1.0):
        self.cell_size = cell_size
        self.shapes = {}
        self.bounds = {}
        self.indices = {}
        self.masks = {}
        self.seeds = set()
        self.cells = {}

    def add(self, key, bounds, masks):
        assert isinstance(bounds, Bounds)
        assert isinstance(masks, Masks)
        self.add_bounds(key, bounds)
        self.add_masks(key, masks)

    def add_bounds(self, key, bounds):
        assert isinstance(bounds, Bounds)
        bounds = bounds.copy()
        self.bounds[key] = bounds
        new_indices = self.hash_bounds(bounds)
        old_indices = self.indices.get(key, (0, 0, 0, 0))
        if new_indices != old_indices:
            new_min_col, new_min_row, new_max_col, new_max_row = new_indices
            old_min_col, old_min_row, old_max_col, old_max_row = old_indices

            # Add key to cells that have not been occupied before.
            for col in xrange(new_min_col, new_max_col):
                for row in xrange(new_min_row, new_max_row):
                    if not (old_min_col <= col < old_max_col and
                            old_max_row <= row < old_max_row):
                        self.add_key_to_cell(key, col, row)

            # Remove key from cells that are no longer occupied.
            for col in xrange(old_min_col, old_max_col):
                for row in xrange(old_min_row, old_max_row):
                    if not (new_min_col <= col < new_max_col and
                            new_max_row <= row < new_max_row):
                        self.remove_key_from_cell(key, col, row)

            self.indices[key] = new_indices

    def add_key_to_cell(self, key, col, row):
        if (col, row) not in self.cells:
            self.cells[col, row] = []
        self.cells[col, row].append(key)

    def add_masks(self, key, masks):
        assert isinstance(masks, Masks)
        masks = masks.copy()
        self.masks[key] = masks
        if masks.include_mask:
            self.seeds.add(key)
        else:
            self.seeds.discard(key)

    def remove(self, key):
        self.remove_bounds(key)
        self.remove_masks(key)

    def remove_bounds(self, key):
        del self.bounds[key]
        min_col, min_row, max_col, max_row = self.indices.pop(key)
        for col in xrange(min_col, max_col):
            for row in xrange(min_row, max_row):
                self.remove_key_from_cell(key, col, row)

    def remove_key_from_cell(self, key, col, row):
        self.cells[col, row].remove(key)
        if not self.cells[col, row]:
            del self.cells[col, row]

    def remove_masks(self, key):
        del self.masks[key]
        self.seeds.discard(key)

    def hash_bounds(self, bounds):
        assert isinstance(bounds, Bounds)
        min_col = int(round(bounds.min_x / self.cell_size))
        min_row = int(round(bounds.min_y / self.cell_size))
        max_col = int(round(bounds.max_x / self.cell_size)) + 1
        max_row = int(round(bounds.max_y / self.cell_size)) + 1
        return min_col, min_row, max_col, max_row

    def query(self, bounds, masks):
        assert isinstance(bounds, Bounds)
        assert isinstance(masks, Masks)
        for key in self.masks:
            if (masks.match(self.masks[key]) and
                bounds.intersects(self.bounds[key])):
                yield key

    def query_all(self):
        for key_a in self.seeds:
            for key_b in self.masks:
                if key_a < key_b or key_b not in self.seeds:
                    if self.match_keys(key_a, key_b):
                        yield key_a, key_b

    def match_keys(self, key_a, key_b):
        return (self.masks[key_a].match(self.masks[key_b]) and
                self.bounds[key_a].intersects(self.bounds[key_b]))

    def get_cell_bounds(self, col, row):
        min_x = self.cell_size * (float(col) - 0.5)
        min_y = self.cell_size * (float(row) - 0.5)
        max_x = self.cell_size * (float(col) + 0.5)
        max_y = self.cell_size * (float(row) + 0.5)
        return Bounds(min_x, min_y, max_x, max_y)

