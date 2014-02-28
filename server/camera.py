import struct

class Camera:
    def __init__(self, p, d):
        self.p, self.d = p, d
    def __bytes__(self):
        return struct.pack('<3dd', self.p[0], self.p[1], self.p[2], self.d)
