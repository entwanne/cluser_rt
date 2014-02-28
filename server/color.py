class Color:
    def __init__(self, r=0, g=0, b=0):
        self.r, self.g, self.b = r, g, b
    def __int__(self):
        return self.r * 256 * 256 + self.g * 256 + self.b

WHITE = Color(255, 255, 255)
