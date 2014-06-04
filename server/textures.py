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
