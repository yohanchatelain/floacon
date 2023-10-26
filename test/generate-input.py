import numpy as np
import fp_format as fpfmt


def get_random_binary(n, fmt):
    random = np.random.rand(n)
    return fmt.cast(random)


def dump(inputs, inputs_file):
    with open(file=inputs_file, mode='w', encoding='utf-8') as fo:
        for b64 in inputs:
            b32 = float(np.float32(b64))
            fo.write(f'{b64.hex()} {b32.hex()}\n')


def generate_binary(n, dtype, inputs_file):
    if dtype in (np.float16, np.float32, np.float64):
        x = get_random_binary(n, dtype)
        dump(x, inputs_file)
    else:
        raise FormatNotSupported(f'Format not supported {dtype}')
