import struct

class Texture:
    def __bytes__(self):
        fmt = '<3s' + ''.join(fmt for _, fmt in self.__properties__)
        values = [self.__txt_name__] + [getattr(self, name) for name, _ in self.__properties__]
        return struct.pack(fmt, *values)
    def __eq__(self, rhs):
        return  (self.__txt_name__ == rhs.__txt_name__
                 and all(getattr(self, name) == getattr(rhs, name)
                         for name, _ in self.__properties__))
