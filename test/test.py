import subprocess

floacon_path = '../floacon'


class Format:
    def __init__(self, precision, exponent):
        self.precision = precision
        self.exponent = exponent


binary32 = Format(24, 8)
binary64 = Format(53, 11)


def call_floacon(value, input_fmt, output_fmt):
    args = (f'{value} '
            f'{input_fmt.precision} {input_fmt.exponent} '
            f'{output_fmt.precision} {output_fmt.exponent} ')

    ret = subprocess.run(f"{floacon_path} {args}",
                         shell=True, capture_output=True, check=True)
    return ret.stdout.strip()


def test_binary64_to_binary32(value, expected):
    return call_floacon(value, binary64, binary32)


def run(inputs_file):

    with open(inputs_file) as fi:
        for line in fi:
            input_value, output_value = line.strip().split()
            ret = test_binary64_to_binary32(input_value, output_value)
            if float.fromhex(ret.decode()) != float.fromhex(output_value):
                print(
                    f'Error: expected {output_value} does not match computed {ret}')


if __name__ == '__main__':
    run('inputs.txt')
