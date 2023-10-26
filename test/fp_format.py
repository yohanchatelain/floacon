import numpy as np
from decimal import (
    Decimal,
    Context,
    ROUND_HALF_EVEN,
    InvalidOperation,
    DivisionByZero,
    Overflow,
)
from enum import Enum


class FormatNotSupported(Exception):
    pass


class FormatClass(Enum):
    NAN = np.nan
    INF = np.inf
    NORMAL = 1
    SUBNORMAL = -1
    ZERO = 0


class DecimalFormat:
    def __init__(self, precision, exponent, context=None):
        self.__check_args(precision, exponent)
        self.precision = precision
        self.exponent = exponent
        self.context = context

    def __check_args(self, precision, exponent):
        if precision < 1:
            raise FormatNotSupported(
                "precision should be at least 2: {precision} given"
            )
        if exponent < 2:
            raise FormatNotSupported(
                "exponent size should be at least 2: {exponent} given"
            )

    def from_string(self, value):
        """
        TODO: implement
        """
        return str(value)

    @classmethod
    def fpclassify_binary_format(cls, binaryfmt, value):
        """
        Classify a Decimal number following BinaryFormat binaryfmt
        """
        context = Context(prec=1000)
        value10 = Decimal(value=value, context=context)
        if value10.is_zero():
            return FormatClass.ZERO
        if value10.is_nan():
            return FormatClass.NAN
        if abs(value10) > binaryfmt.largest_normal():
            return FormatClass.INF
        if abs(value10) < binaryfmt.smallest_subnormal():
            return FormatClass.ZERO
        if abs(value10) < binaryfmt.smallest_normal():
            return FormatClass.SUBNORMAL
        return FormatClass.NORMAL


class BinaryFormat:
    def __init__(self, precision, exponent):
        self.__check_args(precision, exponent)
        self.precision = Decimal(precision)
        self.exponent = Decimal(exponent)

    def __check_args(self, precision, exponent):
        if precision < 1:
            raise FormatNotSupported(
                "precision should be at least 2: {precision} given"
            )
        if exponent < 2:
            raise FormatNotSupported(
                "exponent size should be at least 2: {exponent} given"
            )

    def exponent_max(self):
        return 2**self.exponent - 1

    def exponent_min(self):
        return 2 - 2 ** (self.exponent - 1)

    def exponent_max_normal(self):
        return self.exponent_max - 1

    def exponent_bias(self):
        return 2 ** (self.exponent - 1) - 1

    def largest_normal(self):
        return 2**self.exponent_max_normal * (2 - 2 ** (1 - self.precision))

    def largest_subnormal(self):
        return 2**self.exponent_min * (1 - 2 ** (1 - self.precision))

    def smallest_normal(self):
        return 2**self.exponent_min

    def smallest_subnormal(self):
        return 2 ** (self.exponent_min + 1 - self.precision)

    def decimal_precision(self):
        return (2**self.precision).log10().to_integral()

    def __is_c99hex_format(self, value):
        """
        C99 hex format:
            [+-]?0x1.[M]?p[+-]?[E]
        """
        if not isinstance(value, str):
            return False

        if value.startswith("+") or value.startswith("-"):
            value = value[1:]

        if not value.startswith("0x"):
            return False

        if "p" not in value:
            return False

        try:
            start, end = value.split("p")
        except ValueError:
            return False

        start = start[2:]
        try:
            implicit_bit, significant = start.split(".")
            if not implicit_bit.isdigit():
                return False
            try:
                int(significant, base=16)
            except ValueError:
                return False
        except ValueError:
            return False

        if end.startswith("+") or end.startswith("-"):
            end = end[1:]
        if not end.isnumeric():
            return False

        return True

    def __from_c99hex_format(self, value):
        if not self.__is_c99hex_format(value):
            raise FormatNotSupported(f"Trying to convert non c99hex value {value}")

        significand_position = value.find("x") + 1
        value = value[significand_position:]
        significand, exponent = value.split("p")
        significand = Decimal(significand)
        exponent = Decimal(exponent)
        return significand * 2**exponent

    def __to_c99bits_from_decimal(self, value):
        (sign, _, exponent10) = value.as_tuple()
        sign = "-" if sign else "+"
        if value.is_zero():
            return f"{sign}0x0.0p0"

        def convert_significand_part(significand):
            bits = ""
            i = 0
            while i < self.precision:
                significand %= 1
                significand *= 2
                bits += "1" if significand > 0 else "0"
                i += 1
            return bits.rstrip("0")

        def convert_coefficient_part(coefficient):
            bits = ""
            div = coefficient
            rem = 0
            while not div.is_zero():
                rem = div % 2
                div //= 2
                bits += str(rem)
            return bits

        if exponent10 < 0:
            significand2 = convert_significand_part(value)
            leading_zeroes = significand2.find("1")
            exponent2 = leading_zeroes + 1
        else:
            coefficient2 = convert_coefficient_part(int(value))
            significand2 = convert_significand_part(value % 1)
            exponent2 = len(coefficient2) - 1
            significand2 = coefficient2 + significand2

        msb = significand2[0]
        lsb = significand2[1:]

        return f"{sign}0x{msb}.{lsb}p{exponent2}"

    def __to_c99hex_from_decimal(self, value):
        bits = self.__to_c99bits_from_decimal(value)

        sign = ""
        if value.startswith("+") or value.startswith("-"):
            sign = value[0]

        significand_position = value.find("x") + 1
        bits = bits[significand_position:]
        significand, exp = bits.split("p")
        # Remove 1. part
        significand = significand[2:]

        hex_significand = ""
        for i in range(0, len(significand), 4):
            hex_significand += significand[i : i + 4].ljust(4, "0")

        return f"{sign}0x1.{hex_significand}p{exp}"

    def __to_c99hex_format(self, value):
        if isinstance(value, (int, float)):
            return float(value).hex()
        if isinstance(value, Decimal):
            return self.__to_c99hex_from_decimal(value)
        raise FormatNotSupported(
            f"Don't how to convert {type(value)} to c99hex ({value})"
        )

    def __to_c99bits_format(self, value):
        value = self.parse_value(value)
        if isinstance(value, (int, float)):
            value = Decimal(value)
        if isinstance(value, Decimal):
            return self.__to_c99bits_from_decimal(value)
        raise FormatNotSupported(
            f"Don't how to convert {type(value)} to c99bits ({value})"
        )

    def from_string(self, value):
        """
        Accepted format:
            - int
            - float
            - c99 bits
            - c99 hex
        """
        assert isinstance(value, str)
        if self.__is_c99hex_format(value):
            return self.__from_c99hex_format(value)
        if len(value) > 16:
            return Decimal(value)
        return float(value)

    def to_string(self, value, fmt="f"):
        value = self.parse_value(value)
        if fmt == "f":
            return str(value)
        if fmt == "a":
            return self.__to_c99hex_format(value)
        if fmt == "b":
            return self.__to_c99bits_format(value)
        raise FormatNotSupported(f"Unknown formatter {fmt} to format")

    def parse_value(self, value):
        """
        Parse value from possible formats:
        - int
        - float
        - string
        - Decimal
        """
        if isinstance(value, (int, float)):
            return float(value)
        if isinstance(value, str):
            return self.from_string(value)
        if isinstance(value, Decimal):
            return value
        raise FormatNotSupported(f"Unknown {type(value)} to parse")

    def fpclassify(self, value):
        value = self.parse_value(value)
        if isinstance(value, Decimal):
            return DecimalFormat.fpclassify_binary_format(self, value)

        klass = None
        if abs(value) > self.largest_normal():
            if np.isnan(value):
                klass = FormatClass.NAN
            else:
                klass = FormatClass.INF
        elif abs(value) < self.smallest_subnormal():
            klass = FormatClass.ZERO
        elif value == 0.0:
            klass = FormatClass.ZERO
        elif abs(value) < self.smallest_normal():
            klass = FormatClass.SUBNORMAL
        else:
            klass = FormatClass.NORMAL
        assert klass is not None
        return klass

    def is_zero(self, value):
        return self.fpclassify(value) == FormatClass.ZERO

    def is_infinite(self, value):
        return self.fpclassify(value) == FormatClass.INF

    def is_nan(self, value):
        return self.fpclassify(value) == FormatClass.NAN

    def is_subnormal(self, value):
        return self.fpclassify(value) == FormatClass.SUBNORMAL

    def is_normal(self, value):
        return self.fpclassify(value) == FormatClass.NORMAL

    def subnormalize(self, value):
        """
        Set extra trailing bits to zero
        """
        return value

    def cast(self, inputs):
        casted_inputs = []
        for i in map(self.parse_value, inputs):
            if self.is_subnormal(i):
                casted = self.subnormalize(i)
            elif self.is_nan(i):
                casted = FormatClass.NAN.value
            elif self.is_infinite(i):
                casted = FormatClass.INF.value
            elif self.is_zero(i):
                casted = FormatClass.ZERO.value
            else:
                casted = i
            casted_inputs.append(casted)
        return casted_inputs


class BinaryIEEE754Format(BinaryFormat):
    def __init__(self, dtype):
        finfo = np.finfo(dtype)
        super().__init__(finfo.nmant + 1, finfo.iexp)

    def cast(self, inputs):
        pass


binary16 = BinaryIEEE754Format(np.float16)
binary32 = BinaryIEEE754Format(np.float32)
binary64 = BinaryIEEE754Format(np.float64)
bfloat16 = BinaryFormat(8, 7)
