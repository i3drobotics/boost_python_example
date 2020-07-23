import numpy as np

class TestClass():
    def helloworld(self):
        print ("Hello world")

    def testio(self,v):
        print("Value received in testio:",v)
        return v


if __name__ == "__main__":
    t = TestClass()
    t.helloworld()