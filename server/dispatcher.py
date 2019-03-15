import zmq
import struct

class Dispatcher:
    def __init__(self, port, keys, key_fmt='i', welcome=b'', result_func=None):
        self.port = port
        self.ctx = zmq.Context()
        self.rep = self.ctx.socket(zmq.REP)
        self.rep.bind('tcp://*:{}'.format(self.port))
        self.keys = keys
        self.status_fmt = '<c'
        self.key_fmt = key_fmt
        self.msg_fmt = self.status_fmt + self.key_fmt
        self.welcome = welcome
        self.result_func = result_func
    def __del__(self):
        self.rep.close()
        self.ctx.term()
    def result(self, f):
        self.result_func = f
        return f
    def start(self):
        current = set()
        while self.keys or current:
            cmd = self.rep.recv()
            if cmd == b'hello':
                self.rep.send(self.welcome)
            elif cmd == b'ready':
                if self.keys:
                    key = self.keys.pop()
                    if not isinstance(key, tuple):
                        key = (key,)
                    current.add(key)
                    self.rep.send(struct.pack(self.msg_fmt, b'\0', *key))
                else:
                    self.rep.send(struct.pack(self.status_fmt, b'\1'))
            else:
                status = ord(struct.unpack_from(self.status_fmt, cmd)[0])
                key = struct.unpack_from(self.key_fmt, cmd[struct.calcsize(self.status_fmt):])
                current.remove(key)
                if status:
                    keys.add(key)
                    self.rep.send(b'pass')
                else:
                    if self.result_func:
                        val = cmd[struct.calcsize(self.msg_fmt):] # cmd without the key
                        args = key + (val,)
                        self.result_func(*args) # (*key, val)
                    if self.keys:
                        self.rep.send(b'ok')
                    else:
                        self.rep.send(b'end')
