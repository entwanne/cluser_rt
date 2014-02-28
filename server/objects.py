import math

from object import Object

class Plane(Object):
    __obj_name__ = b'PLA'
    __properties__ = ()
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

class Sphere(Object):
    __obj_name__ = b'SPH'
    __properties__ = ()
    def __init__(self, r=1, **kwargs):
        kwargs['scale_x'] = kwargs.get('scale_x', 1) * r
        kwargs['scale_y'] = kwargs.get('scale_y', 1) * r
        kwargs['scale_z'] = kwargs.get('scale_z', 1) * r
        super().__init__(**kwargs)

class Cylinder(Object):
    __obj_name__ = b'CYL'
    __properties__ = ()
    def __init__(self, r=1, **kwargs):
        kwargs['scale_x'] = kwargs.get('scale_x', 1) * r
        kwargs['scale_y'] = kwargs.get('scale_y', 1) * r
        super().__init__(**kwargs)

class Cone(Object):
    __obj_name__ = b'CON'
    __properties__ = (('r_angle', 'd'),)
    def __init__(self, angle, **kwargs):
        self.angle = angle
        super().__init__(**kwargs)
    @property
    def r_angle(self):
        return math.radians(self.angle)
