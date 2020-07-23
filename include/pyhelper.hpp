#ifndef PYHELPER_HPP
#define PYHELPER_HPP
#pragma once

#include "Python.h"
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>

#include <cstdlib> // setenv

namespace pyhelper
{
    namespace py = boost::python;
    namespace np = boost::python::numpy;

    template <class T>
    py::list toPythonList(std::vector<T> vector) {
        typename std::vector<T>::iterator iter;
        py::list list;
        for (iter = vector.begin(); iter != vector.end(); ++iter) {
            list.append(*iter);
        }
        return list;
    }

    template <class T>
    std::vector<T> toStdVector(py::list l) {
        py::ssize_t n = py::len(l);
        std::vector<T> vect;
        for(py::ssize_t i=0;i<n;i++) {
            py::object elem = l[i];
            T str = py::extract<T>(elem);
            vect.push_back(str);
        }
        return vect;
    }

    static bool hasattr(py::object o, const char* name) {
        return PyObject_HasAttrString(o.ptr(), name);
    }

    static void initPython(){
        try {
            Py_Initialize();
            np::initialize();
        } catch( py::error_already_set ) {
            PyErr_Print();
        }
    }

    static void addToPythonPath(char* path){
         #ifdef _WIN32
            std::string env = "PYTHONPATH="+std::string(path);
            putenv(env.c_str());
        #endif
        #ifdef linux
            setenv("PYTHONPATH", path, 1);
        #endif
    }

    static py::object getPyClass(char* py_module, char* py_class){
        py::object main_module((
        py::handle<>(py::borrowed(PyImport_AddModule("__main__")))));

        py::object main_namespace = main_module.attr("__dict__");

        // >>> import Test
        py::object test_module = py::import(py_module);

        // >>> test_class = TestModule.TestClass()
        py::object test_class = test_module.attr(py_class)();
        return test_class;
    }
}

#endif //PYHELPER_HPP