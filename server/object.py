import struct
import numpy
from numpy import linalg

from matrix import translation_matrix, rotation_matrix, scale_matrix, stretch_matrix
from textures import ColorTexture

class Object:
    def __init__(self, texture=None, color=0, x=0, y=0, z=0, rot_x=0, rot_y=0, rot_z=0, scale_x=1, scale_y=1, scale_z=1):
        self.texture = texture if texture is not None else ColorTexture(color)
        self._transform_matrix = numpy.matrix(numpy.identity(4))
        self.scale(scale_x, scale_y, scale_z)
        self.rotate('x', rot_x)
        self.rotate('y', rot_y)
        self.rotate('z', rot_z)
        self.translate(x, y, z)
    def __bytes__(self):
        fmt = '<3s' + ''.join(fmt for _, fmt in self.__properties__) + 'i'
        values = [self.__obj_name__] + \
                 [getattr(self, name) for name, _ in self.__properties__] + \
                 [int(self.texture_id)]
        b = struct.pack(fmt, *values)
        # Send transformation matrix and reverse transformation matrix
        b += bytes(self._transform_matrix)
        b += bytes(linalg.inv(self._transform_matrix))
        return b
    def transform(self, m):
        self._transform_matrix = m * self._transform_matrix
    def translate(self, x=0, y=0, z=0):
        if x or y or z:
            self.transform(translation_matrix(x, y, z))
        return self
    def rotate(self, axis, angle):
        if angle:
            self.transform(rotation_matrix(axis, angle))
        return self
    def scale(self, x=1, y=1, z=1):
        if x != 1 or y != 1 or z != 1:
            m = scale_matrix(x, y, z)
            self.transform(scale_matrix(x, y, z))
            pass
        return self
    def stretch(self, axis, angle_x=0, angle_y=0, angle_z=0):
        if angle_x or angle_y or angle_z:
            self.transform(stretch_matrix(axis, angle_x, angle_y, angle_z))
        return self
