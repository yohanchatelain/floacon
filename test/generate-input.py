import numpy as np
import sys


def get_random_binary64(n):
    return np.random.rand(n)


def dump(inputs):
    with open('inputs.txt', 'w') as fo:
        for b64 in inputs:
            b32 = float(np.float32(b64))
            fo.write(f'{b64.hex()} {b32.hex()}\n')


if '__main__' == __name__:
    n = int(sys.argv[1])
    x = get_random_binary64(n)
    dump(x)
