from monomi import settings
from monomi.geometry import *

from contextlib import contextmanager
import pyglet
from pyglet.gl import *
import sys

class Enumeration(object):
    def __init__(self, names):
        self.names = list(names)
        self.values = range(len(self.names))
        for name, value in zip(self.names, self.values):
            setattr(self, name, value)

class DebugGraphics(object):
    def draw_polygon(self, polygon, stroke=None, fill=None):
        self.draw_vertices(polygon.vertices, stroke, fill)

    def draw_bounds(self, bounds, stroke=None, fill=None):
        vertices = [(bounds.min_x, bounds.min_y), (bounds.max_x, bounds.min_y),
                    (bounds.max_x, bounds.max_y), (bounds.min_x, bounds.max_y)]
        self.draw_vertices(vertices, stroke, fill)

    def draw_circle(self, circle, stroke=None, fill=None):
        vertices = list(self.generate_circle_vertices(circle))
        self.draw_vertices(vertices, stroke, fill)

    def generate_circle_vertices(self, circle,
                                 vertex_count=settings.circle_vertex_count):
        cx, cy = circle.center
        for i in xrange(vertex_count):
            angle = 2.0 * math.pi * float(i) / float(vertex_count)
            vx = cx + circle.radius * math.cos(angle)
            vy = cy + circle.radius * math.sin(angle)
            yield vx, vy

    def draw_vertices(self, vertices, stroke=None, fill=None):
        if stroke is None and fill is None:
            stroke = settings.debug_color
        if fill is not None:
            glColor3ub(*fill)
            glBegin(GL_POLYGON)
            for x, y in vertices:
                glVertex2f(x, y)
            glEnd()
        if stroke is not None:
            glColor3ub(*stroke)
            glBegin(GL_LINE_LOOP)
            for x, y in vertices:
                glVertex2f(x, y)
            glEnd()

class Actor(object):
    def __init__(self, game_engine):
        self.game_engine = game_engine
        self.game_engine.actors.append(self)

    def delete(self):
        self.game_engine.actors.remove(self)

    def step(self, dt):
        pass

    def draw(self):
        pass

    def debug_draw(self, debug_graphics):
        pass

LEVEL = """
 #
 #  @
##  #
######
"""

class LevelActor(Actor):
    def __init__(self, game_engine):
        super(LevelActor, self).__init__(game_engine)
        self.start_position = Vector()
        self.tiles = {}
        for row, line in enumerate(reversed(LEVEL.splitlines())):
            for col, char in enumerate(line):
                if not char.isspace():
                    self.tiles[col, row] = char
                    if char == '#':
                        key = self.game_engine.generate_key()
                        bounds = self.get_tile_bounds(col, row)
                        masks = 0, 0, 0
                        self.game_engine.grid.add(key, bounds, masks)
                    elif char == '@':
                        self.start_position = self.get_tile_center(col, row)

    def debug_draw(self, debug_graphics):
        for col, row in self.tiles:
            char = self.tiles[col, row]
            if char == '#':
                bounds = self.get_tile_bounds(col, row)
                debug_graphics.draw_bounds(bounds, stroke=(191, 191, 191))
            elif char == '@':
                pass

    def get_tile_center(self, col, row):
        return Vector(float(col) + 0.5, float(row) + 0.5)

    def get_tile_bounds(self, col, row):
        cx, cy = self.get_tile_center(col, row)
        return Bounds(cx - 0.5, cy - 0.5, cx + 0.5, cy + 0.5)

class CharacterActor(Actor):
    def __init__(self, game_engine, position=(0.0, 0.0), debug_color=None):
        super(CharacterActor, self).__init__(game_engine)
        self.circle = Circle(center=position, radius=0.75)
        self.debug_color = debug_color
        self.velocity = Vector()
        self.init_controls()

    def init_controls(self):
        self.left_control = False
        self.right_control = False
        self.up_control = False
        self.down_control = False
        self.jump_control = False

    def reset_controls(self):
        self.left_control = False
        self.right_control = False
        self.up_control = False
        self.down_control = False
        self.jump_control = False

    @property
    def position(self):
        return self.circle.center

    @position.setter
    def position(self, position):
        self.circle.center = position

    def step(self, dt):
        self.velocity += dt * self.game_engine.gravity
        self.position += dt * self.velocity

    def debug_draw(self, debug_graphics):
        debug_graphics.draw_circle(self.circle, stroke=self.debug_color)

class Camera(object):
    def __init__(self, window):
        self.window = window
        self.position = 0.0, 0.0
        self.scale = 0.1
        self.half_width = 0.0
        self.half_height = 0.0
        self.on_resize(self.window.width, self.window.height)

    @contextmanager
    def manage_transform(self):
        glPushMatrix()
        glTranslatef(self.half_width, self.half_height, 0.0)
        scale = self.scale * min(self.half_width, self.half_height)
        glScalef(scale, scale, scale)
        x, y = self.position
        glTranslatef(-x, -y, 0.0)
        yield
        glPopMatrix()

    def on_resize(self, width, height):
        self.half_width = float(width // 2)
        self.half_height = float(height // 2)

class GameEngine(object):
    def __init__(self, window):
        self.window = window
        self.time = 0.0
        self.next_key = 0
        self.grid = Grid(settings.grid_cell_size)
        self.gravity = Vector(0.0, -10.0)
        self.camera = Camera(window)
        self.actors = []
        self.level_actor = LevelActor(self)
        self.player_actor = CharacterActor(self)
        self.player_actor.position = self.level_actor.start_position
        self.player_actor.debug_color = 0, 127, 255
        self.camera.position = self.player_actor.position

    def generate_key(self):
        key = self.next_key
        self.next_key += 1
        return key

    def step(self, dt):
        self.time += dt
        for actor in self.actors:
            actor.step(dt)

    def on_draw(self):
        self.debug_draw()

    def debug_draw(self):
        debug_graphics = DebugGraphics()
        with self.camera.manage_transform():
            self.debug_draw_grid(debug_graphics)
            self.debug_draw_actors(debug_graphics)

    def debug_draw_grid(self, debug_graphics):
        for col, row in self.grid.cells:
            bounds = self.grid.get_cell_bounds(col, row)
            debug_graphics.draw_bounds(bounds)
        for bounds in self.grid.bounds.itervalues():
            debug_graphics.draw_bounds(bounds)

    def debug_draw_actors(self, debug_graphics):
        for actor in self.actors:
            actor.debug_draw(debug_graphics)

    def on_resize(self, width, height):
        self.camera.on_resize(width, height)

class View(object):
    def on_draw(self):
        pass

    def on_resize(self, width, height):
        pass

class GameView(View):
    def __init__(self, window):
        self.window = window
        self.game_engine = GameEngine(self.window)
        self.dt = 1.0 / float(settings.fps)
        self.max_dt = 1.0
        self.time = 0.0
        if settings.debug_fps:
            self.clock_display = pyglet.clock.ClockDisplay()
        else:
            self.clock_display = None
        pyglet.clock.schedule_interval(self.step, 0.1 * self.dt)

    def delete(self):
        pyglet.clock.unschedule(self.step)

    def step(self, dt):
        self.time += min(dt, self.max_dt)
        while self.game_engine.time + self.dt < self.time:
            self.game_engine.step(self.dt)

    def on_draw(self):
        self.window.clear()
        self.game_engine.on_draw()
        if self.clock_display is not None:
            self.clock_display.draw()

    def on_resize(self, width, height):
        self.game_engine.on_resize(width, height)

class MyWindow(pyglet.window.Window):
    def __init__(self, **kwargs):
        super(MyWindow, self).__init__(**kwargs)
        self.view = GameView(self)

    def on_draw(self):
        self.view.on_draw()

    def on_resize(self, width, height):
        super(MyWindow, self).on_resize(width, height)
        self.view.on_resize(width, height)

def main():
    fullscreen = '--fullscreen' in sys.argv
    window = MyWindow(caption='Monomi', fullscreen=fullscreen, resizable=True)
    pyglet.app.run()

if __name__ == '__main__':
    main()
