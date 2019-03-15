#!/usr/bin/env python

import struct

import zmq


def read_from(fmt, buff):
    size = struct.calcsize(fmt)
    val = struct.unpack_from(fmt, buff)
    return val, buff[size:]


ctx = zmq.Context()
req = ctx.socket(zmq.REQ)
req.connect('tcp://localhost:61385')

req.send(b'hello')
scene = req.recv()
_, scene = read_from('<3dd', scene)
_, scene = read_from('2i', scene)
(width, height), scene = read_from('2i', scene)

while True:
    req.send(b'ready')
    msg = req.recv()

    (status,), msg = read_from('<c', msg)
    if status == b'\1':
        break

    (key,), msg = read_from('<i', msg)

    size = 4 * 50 * width
    fmt = f'<ci{size}s'
    req.send(struct.pack(fmt, b'\0', key, b'\xff'*size))

    req.recv()

# Add protocol module (in both Python & C++) that allows having protocol in one place (and then change from struct to jsonif needed)
