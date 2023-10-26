import subprocess
import pytest
import fp_format as fpfmt

floacon_path = '../floacon'


def call_floacon(value, input_fmt, output_fmt):
    args = (f'{value} '
            f'{input_fmt.precision} {input_fmt.exponent} '
            f'{output_fmt.precision} {output_fmt.exponent} ')

    ret = subprocess.run(f"{floacon_path} {args}",
                         shell=True, capture_output=True, check=True)
    return ret.stdout.strip()


def run_test_binary64_to_binary32(value):
    return call_floacon(value, fpfmt.binary64, fpfmt.binary32)


def check_input(test_binary, line):
    input_value, output_value = line.strip().split()
    ret = test_binary(input_value)
    err_msg = f'Error: expected {output_value} does not match computed {ret}'
    assert float.fromhex(ret.decode()) == float.fromhex(output_value), err_msg


@pytest.mark.parametrize('format', [])
def test(inputs_file):
    with open(file=inputs_file, mode='r', encoding='utf-8') as fi:
        for line in fi:
            check_input(run_test_binary64_to_binary32, line)


if __name__ == '__main__':
    test('inputs.txt')
