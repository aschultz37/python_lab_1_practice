from distutils.core import setup, Extension
module1 = Extension('creative', sources = ['creative_lab1.cpp'])
setup (name="Creative",
       version='1.2.2',
       description='Mean and var funcs',
       ext_modules=[module1])