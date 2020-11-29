import pytest
import cpplib

def test_hello():
    resp = cpplib.hello("Jeremy")
    assert resp == "Hello Jeremy"


def test_multiply():
    vec = cpplib.VectorDouble([0.0, 1.0, 2.0])
    resp = cpplib.multiply_by_scalar_double(vec, 2.0)
    assert list(resp) == [0.0, 2.0, 4.0]