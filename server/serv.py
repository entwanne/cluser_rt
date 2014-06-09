#!/usr/bin/env python

from dispatcher import Dispatcher
from scene import Scene
from camera import Camera
from lights import *
from objects import *
from textures import *
from color import Color

width, height = 800, 600

scene = Scene(Camera((0, -80, 20), 60), (80, 60), (width, height))

scene.add_light(Ambiant(intensity=0.2))
scene.add_light(Diffuse(-20, -40, 20, intensity=0.8))
scene.add_light(Diffuse(40, 40, 5, intensity=0.4))
scene.add_light(Specular(-20, -40, 20, intensity=0.6))

#scene.add_object(Sphere(10, x=50, y=30, scale_z=1.5, color=Color(r=255)))
scene.add_object(Sphere(10, x=50, y=30, scale_z=1.5, texture=Bicolor(Color(255, 255, 255), Color(r=255), True)))
scene.add_object(Sphere(3, z=20, scale_x=5, color=Color(g=255)))
scene.add_object(Sphere(5, color=Color(r=255, b=255)).stretch('x', angle_y=60))
scene.add_object(Plane(z=-10, color=Color(255, 255, 255)))
scene.add_object(Plane(z=80, color=Color(255, 255, 255)))
scene.add_object(Plane(x=-80, rot_y=90, color=Color(b=255)))
scene.add_object(Plane(x=80, rot_y=90, color=Color(b=255)))
scene.add_object(Plane(y=100, rot_x=90, color=Color(r=255, g=255)))
#scene.add_object(Cylinder(5, x=-80, y=100, color=Color(b=255)))
scene.add_object(Cylinder(5, x=-80, y=100, texture=Bicolor(Color(g=255), Color(b=255), True)))
scene.add_object(Cylinder(5, x=80, y=100, color=Color(b=255)))
#scene.add_object(Cone(10, color=Color(r=128, g=128, b=128)))
scene.add_object(Cone(10, texture=Bicolor(Color(r=128, g=128, b=128), Color(255, 128, 0))))

nb_lines_chunk = 50
dispatch = Dispatcher(61385, set(i for i in range(height) if i % nb_lines_chunk == 0), key_fmt='i')

dispatch.welcome = bytes(scene)

data = {}
@dispatch.result
def result(ys, chunk):
    data[ys] = chunk

# Lumière: ensemble de 2 composants:
# - méthode C de calcul de la couleur en un point d'un objet
# - méthode I de calcul d'intensité en un point (renvoie un nombre positif)

# Ainsi, un objet O de la scène sera éclairé par diverses sources lumineuses L1, L2 et L3 par exemple
# Pour chaque lumière k, on calcule Ck = Lk.C(O) et Ik = Lk.I(D, P, N)
# (D, P et N sont respectivement le vecteur de visée, le point d'impact et la normale en ce point)
# Puis on calcule C = SUM(Ck * Ik for each k) = (C1 * I1) + (C2 * I2) + (C3 * I3)
# Enfin, chaque composante de C est recalculée proprotionnellement de façon à ce qu'aucune ne dépasse 255
# Par exemple avec (510, 100, 100), on obtiendrait (255, 50, 50)

# Exemples:

# Lumière ambiante
# C(O) = couleur_fixe AND O.couleur  # couleur_fixe est une constante de cette lumière
# I(D, P, N) = 1

# Lumière diffuse
# C(O) = couleur_fixe AND O.couleur
# I(D, P, N) = max(0, cos((N, (spot_position - P))))  # cosinus entre la normale et le vecteur point-spot, ramené à 0 si négatif

# Lumière spéculaire
# C(0) = couleur_fixe * O.specularite  # O.specularite étant un coeffcicient de spécularité compris entre 0 et 1
# I(D, P, N) = cosinus entre D et le vecteur réfléchi depuis la lumière -> entre 0 et 1

# LASER
# C(0) = couleur_fixe
# I(D, P, N) = intensite si dans l'angle de visée du laser, 0 sinon  # intensite > 1 pour un réel effet LASER, dépend peut-être un peu de l'angle avec la normale aussi

import struct

import sfml as sf
def calc_img(filename):
    img = sf.Image.create(width, height, sf.Color.BLACK)
    for ys, chunk in data.items():
        chunk = [ord(i) for i in struct.unpack('{}c'.format(4 * width * nb_lines_chunk), chunk)]
        chunk.reverse()
        for y in range(ys, ys + nb_lines_chunk):
            for x in range(width):
                b, g, r, _ = [chunk.pop() for i in range(4)]
                img[x, y] = sf.Color(r, g, b)
    img.to_file(filename)

import time
def timeit(method, *args, **kwargs):
    ts = time.time()
    result = method(*args, **kwargs)
    te = time.time()
    print('{:.2f} sec'.format(te-ts))
    return result

timeit(dispatch.start)

calc_img('toto.png')
