from enum import Enum

class Type(Enum):
    first = 'first'
    second = 'second'
    third = 'third'

    def __str__(self):
        return str(self.value).capitalize()
    
    @classmethod
    def list(cls):
        return {t.value: str(t) for t in cls}
        #return list(map(lambda c: c.value, cls))

if __name__ == '__main__':
    my_type = Type('first')

    print(my_type)

    print(Type.list())
