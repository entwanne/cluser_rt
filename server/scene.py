import struct

class Scene:
    def __init__(self, cam, size, definition):
        self.cam = cam
        self.size, self.definition = size, definition
        self.lights = set()
        self.objects = set()
    def __bytes__(self):
        textures = []
        for obj in self.objects:
            if obj.texture not in textures:
                textures.append(obj.texture)
            obj.texture_id = textures.index(obj.texture)
        r = bytes(self.cam)
        r += struct.pack('2i', *self.size)
        r += struct.pack('2i', *self.definition)
        r += struct.pack('i', len(textures))
        r += b''.join(bytes(txt) for txt in textures)
        r += struct.pack('i', len(self.lights))
        r += b''.join(bytes(light) for light in self.lights)
        r += struct.pack('i', len(self.objects))
        r += b''.join(bytes(obj) for obj in self.objects)
        return r
    def add_object(self, obj):
        self.objects.add(obj)
    def add_light(self, light):
        self.lights.add(light)
