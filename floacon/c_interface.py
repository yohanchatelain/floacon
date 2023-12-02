import ctypes

libpath = "libfloacon.so"


def load_library():
    return ctypes.cdll.LoadLibrary(libpath)
