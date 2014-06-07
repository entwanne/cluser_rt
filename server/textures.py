from texture import Texture

class ColorTexture(Texture):
    __txt_name__ = b'COL'
    __properties__ = (('color_int', 'i'),)
    def __init__(self, color=0):
        super().__init__()
        self.color = color

    @property
    def color_int(self):
        return int(self.color)

class Bicolor(Texture):
    __txt_name__ = b'BIC'
    __properties__ = (('color1_int', 'i'), ('color2_int', 'i'), ('vertical', '?'))
    def __init__(self, color1=0, color2=0, vertical=False):
        super().__init__()
        self.color1 = color1
        self.color2 = color2
        self.vertical = vertical

    @property
    def color1_int(self):
        return int(self.color1)

    @property
    def color2_int(self):
        return int(self.color2)
