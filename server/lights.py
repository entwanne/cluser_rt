from light import Light

class Ambiant(Light):
    __light_name__ = b'AMB'
    __properties__ = ()

class Diffuse(Light):
    __light_name__ = b'DIF'
    __properties__ = (('x', 'd'), ('y', 'd'), ('z', 'd'))
    def __init__(self, x, y, z, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.x, self.y, self.z = x, y, z

class Specular(Light):
    __light_name__ = b'SPE'
    __properties__ = (('x', 'd'), ('y', 'd'), ('z', 'd'))
    def __init__(self, x, y, z, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.x, self.y, self.z = x, y, z
