from contextlib import contextmanager
import pyglet
from pyglet.gl import *
import sys

class Actor(object):
    def __init__(self, game_engine):
        self.game_engine.actors.append(self)

    def delete(self):
        self.game_engine.actors.remove(self)

    def step(self, dt):
        pass

    def draw(self):
        pass

class Camera(object):
    def __init__(self, window):
        self.window = window
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

    def delete(self):
        pass

    def step(self, dt):
        self.time += dt

    def on_draw(self):
        self.window.clear()
        with self.camera.manage_transform():
            self.draw_actors()

    def draw_actors(self):
        glBegin(GL_LINE_LOOP)
        glVertex2f(-1.0, -1.0)
        glVertex2f(1.0, -1.0)
        glVertex2f(1.0, 1.0)
        glVertex2f(-1.0, 1.0)
        glEnd()

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
