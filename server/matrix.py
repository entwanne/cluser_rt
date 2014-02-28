import math
import numpy

def translation_matrix(x, y, z):
    m = numpy.matrix(numpy.identity(4))
    m[0, 3] = x
    m[1, 3] = y
    m[2, 3] = z
    return m

def rotation_matrix(axis, angle):
    angle = math.radians(angle)
    indices = {
        'x': (2, 1, 0),
        'y': (2, 0, 1),
        'z': (1, 0, 2)
    }
    a, b, c = indices[axis]
    m = numpy.matrix(numpy.zeros((4, 4)))
    m[a, a] = math.cos(angle)
    m[a, b] = math.sin(angle)
    m[b, a] = -math.sin(angle)
    m[b, b] = math.cos(angle)
    m[c, c] = 1
    m[3, 3] = 1
    return m

def scale_matrix(x, y, z):
    m = numpy.matrix(numpy.identity(4))
    m[0, 0] = x
    m[1, 1] = y
    m[2, 2] = z
    return m

def stretch_matrix(axis, angle_x, angle_y, angle_z):
    angles = (math.radians(angle_x), math.radians(angle_y), math.radians(angle_z))
    indices = {
        'x': (0, 1, 2),
        'y': (1, 0, 2),
        'z': (2, 0, 1)
    }
    a, b, c = indices[axis]
    m = numpy.matrix(numpy.identity(4))
    m[a, b] = math.tan(angles[b])
    m[a, c] = math.tan(angles[c])
    return m
