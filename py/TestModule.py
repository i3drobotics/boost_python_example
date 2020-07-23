import numpy as np

class TestClass():
    def helloworld(self):
        print ("Hello world")

    def testint(self,intIn):
        print("Value received in testint: {}".format(intIn))
        return intIn

    def testfloat(self,floatIn):
        print("Value received in testfloat: {}".format(floatIn))
        return floatIn

    def testnumpy(self,npIn):
        print("Value received in testnumpy: {}".format(npIn))
        return npIn