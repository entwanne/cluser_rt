import inspect
from typing import List


class MessageType(type):
    def __new__(cls, name, bases, namespace):
        # merge with parents?
        fields = namespace.pop('__annotations__', {})
        for field_type in fields.values():
            cls.check_field_type(field_type)
        namespace['__fields__'] = fields

        sig = inspect.Signature(parameters=(
            inspect.Parameter(
                name,
                inspect.Parameter.POSITIONAL_OR_KEYWORD,
                annotation=type_,
            )
            for name, type_ in fields.items()
        ))
        namespace['__signature__'] = sig

        if not '__init__' in namespace:
            def cls_init(self, *args, **kwargs):
                super(new_cls, self).__init__(*args, **kwargs)

            cls_init.__signature__ = sig
            namespace['__init__'] = cls_init

        new_cls = super().__new__(cls, name, bases, namespace)
        return new_cls

    @classmethod
    def check_field_type(cls, field_type):
        #if (not isinstance(field_type, cls)
        #    #and field_type not in (int, float, str, list)):
        #    and field_type not in (int, float, str)): # + allow restricted lists: List[int], List[XMessage]
        #    raise ValueError(f'Type {field_type} is not allowed in message class')
        if field_type in (int, float, str):
            return
        if isinstance(field_type, cls):
            return

        origin = getattr(field_type, '__origin__', None)
        if origin == list:
            elem_type, = field_type.__args__
            return cls.check_field_type(elem_type)

        raise ValueError(f'Type {field_type} is not allowed in message class')


class Message(metaclass=MessageType):
    def __init__(self, *args, **kwargs):
        super().__init__()
        bound = self.__signature__.bind(*args, **kwargs)
        for name, value in zip(self.__fields__, bound.args):
            setattr(self, name, value)

    def __setattr__(self, name, value):
        type_ = self.__fields__.get(name)
        if type_ is None:
            raise AttributeError(f'Attribute {name} not found')

        #origin = getattr(type_, '__origin__', None)
        #if origin == list and 
        #if not isinstance(value, type_):
        #    raise ValueError(f'Incompatible type for {name} field, {type_} expected')
        if not self.check_type(type_, value):
            raise ValueError(f'Incompatible type for {name} field, {type_} expected, got {type(value).__name__}')
        super().__setattr__(name, value)

    @classmethod
    def check_type(cls, type_, value):
        origin = getattr(type_, '__origin__', None)
        if origin == list:
            if not isinstance(value, list):
                return False
            elem_type, = type_.__args__
            return all(cls.check_type(elem_type, elem) for elem in value)

        return isinstance(value, type_)

    def __repr__(self):
        params = ', '.join(
            f'{name}={getattr(self, name)!r}' for name in self.__fields__
        )
        return f'{type(self).__qualname__}({params})'

    def to_tuple(self):
        values = (getattr(self, field) for field in self.__fields__)
        return tuple(
            value.to_tuple() if isinstance(value, Message) else value
            for value in values
        )

    def to_dict(self):
        values = ((field, getattr(self, field)) for field in self.__fields__)
        return {
            field: value.to_dict() if isinstance(value, Message) else value
            for field, value in values
        }

    @classmethod
    def from_tuple(cls, values):
        values = (
            field_type.from_tuple(value) if isinstance(field_type, MessageType) else value
            for value, field_type in zip(values, cls.__fields__.values())
        )
        return cls(*values)

    @classmethod
    def from_dict(cls, values):
        for field, field_type in cls.__fields__.items():
            if isinstance(field_type, MessageType) and field in values:
                values[field] = field_type.from_dict(values[field])
        return cls(**values)


class Protocol:
    @classmethod
    def serialize(cls, message: Message) -> bytes:
        raise NotImplementedError

    @classmethod
    def unserialize(cls, msg_type: MessageType, data: bytes) -> Message:
        raise NotImplementedError

    # + write functions

    # No, only functions to handle Message classes
    # + type-checking on Message class (at creation of classes to check that all fields are int/float/string/list/Message & at instanciation time to check args with class definition)

# + Add Protocol implementations with struct & json


import json

class JSONProtocol(Protocol):
    @classmethod
    def serialize(cls, message: Message) -> bytes:
        return json.dumps(message.to_dict()).encode()

    @classmethod
    def unserialize(cls, msg_type: MessageType, data: bytes) -> Message:
        doc = json.loads(data.decode())
        return msg_type.from_dict(doc)


import struct

class StructProtocol(Protocol):
    @classmethod
    def serialize(cls, message: Message) -> bytes:
        return cls._serialize_tuple(message.to_tuple())

    @classmethod
    def unserialize(cls, msg_type: MessageType, data: bytes) -> Message:
        msg, data = cls._unserialize_from(msg_type, data)
        if data:
            raise ValueError('Remaining data')
        return msg

    @classmethod
    def _serialize_tuple(cls, values):
        data = b''
        for value in values:
            if isinstance(value, int):
                data += struct.pack('<i', value)
            elif isinstance(value, float):
                data += struct.pack('<i', value)
            elif isinstance(value, str):
                value = value.encode()
                fmt = '<i{}s'.format(len(value))
                data += struct.pack(fmt, len(value), value)
            elif isinstance(value, list):
                data += struct.pack('<i', len(value))
                data += cls._serialize_tuple(value)
            else:
                data += cls._serialize_tuple(value)
        return data

    @classmethod
    def _unserialize_from(cls, type_, data):
        origin = getattr(type_, '__origin__', None)
        if type_ == int:
            fmt = '<i'
            value, = struct.unpack_from(fmt, data)
            return value, data[struct.calcsize(fmt):]
        elif type_ == float:
            fmt = '<f'
            value, = struct.unpack_from(fmt, data)
            return value, data[struct.calcsize(fmt):]
        elif type_ == str:
            size, data = cls._unserialize_from(int, data)
            fmt = '<{}s'.format(size)
            value, = struct.unpack_from(fmt, data)
            value = value.decode()
            return value, data[struct.calcsize(fmt):]
        elif origin == list:
            elem_type, = type_.__args__
            fmt = '<i'
            size, = struct.unpack_from(fmt, data)
            data = data[struct.calcsize(fmt):]
            values = []
            for _ in range(size):
                elem, data = cls._unserialize_from(elem_type, data)
                values.append(elem)
            return values, data
        else:
            values = []
            for field_type in type_.__fields__.values():
                value, data = cls._unserialize_from(field_type, data)
                values.append(value)
            return type_(*values), data
