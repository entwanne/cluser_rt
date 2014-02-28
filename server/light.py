import struct

from color import Color, WHITE

class Light:
    def __init__(self, color=WHITE, intensity=1):
        self.color=color
        self.intensity = intensity
    def __bytes__(self):
        fmt = '<3s' + ''.join(fmt for _, fmt in self.__properties__) + 'id'
        values = [self.__light_name__] + \
                 [getattr(self, name) for name, _ in self.__properties__] + \
                 [int(self.color), self.intensity]
        return struct.pack(fmt, *values)
