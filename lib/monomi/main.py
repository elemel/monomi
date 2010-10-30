from geometry import *

from contextlib import contextmanager
import pyglet
from pyglet.gl import *
import sys

class DebugGraphics(object):
    def draw_polygon(self, vertices):
        glBegin(GL_LINE_LOOP)
        for x, y in vertices:
            glVertex2f(x, y)
        glEnd()

    def draw_bounds(self, bounds):
        min_x, min_y, max_x, max_y = bounds
        vertices = [(min_x, min_y), (max_x, min_y),
                    (max_x, max_y), (min_x, max_y)]
        self.draw_polygon(vertices)

    def draw_circle(self, center, radius):
        cx, cy = center
        vertices = []
        vertex_count = 16
        for i in xrange(vertex_count):
            angle = 2.0 * math.pi * float(i) / float(vertex_count)
            vx = cx + radius * math.cos(angle)
            vy = cy + radius * math.sin(angle)
            vertices.append((vx, vy))
        self.draw_polygon(vertices)

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
        self.start = 0.0, 0.0
        self.tiles = {}
        for row, line in enumerate(reversed(LEVEL.splitlines())):
            for col, char in enumerate(line):
                if not char.isspace():
                    self.tiles[col, row] = char
                    if char == '@':
                        self.start = self.get_tile_center(col, row)
                    key = col, row
                    bounds = self.get_tile_bounds(col, row)
                    masks = (0, 0, 0)
                    self.game_engine.grid.add(key, bounds, masks)

    def debug_draw(self, debug_graphics):
        for col, row in self.tiles:
            char = self.tiles[col, row]
            if char == '#':
                bounds = self.get_tile_bounds(col, row)
                debug_graphics.draw_bounds(bounds)
            elif char == '@':
                pass

    def get_tile_center(self, col, row):
        return float(col) + 0.5, float(row) + 0.5

    def get_tile_bounds(self, col, row):
        cx, cy = self.get_tile_center(col, row)
        return cx - 0.5, cy - 0.5, cx + 0.5, cy + 0.5

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
        self.camera = Camera(window)
        self.actors = []
        self.time = 0.0
        self.grid = Grid(3.0, 3.0)
        level_actor = LevelActor(self)
        self.camera.position = level_actor.start

    def step(self, dt):
        self.time += dt

    def on_draw(self):
        self.window.clear()
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
        self.dt = 1.0 / 60.0
        self.max_dt = 1.0
        self.time = 0.0
        pyglet.clock.schedule_interval(self.step, 0.1 * self.dt)

    def delete(self):
        pyglet.clock.unschedule(self.step)

    def step(self, dt):
        self.time += min(dt, self.max_dt)
        while self.game_engine.time + self.dt < self.time:
            self.game_engine.step(self.dt)

    def on_draw(self):
        self.game_engine.on_draw()

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
