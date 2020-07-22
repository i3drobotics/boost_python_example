#include <boost/python.hpp>
#include <cstdlib> // setenv
#include <iostream>

using namespace boost::python;

void helloworld_iternal(){
    try {
        Py_Initialize();

        object main_module((
        handle<>(borrowed(PyImport_AddModule("__main__")))));

        object main_namespace = main_module.attr("__dict__");

        handle<> ignored(( PyRun_String( "print(\"Hello, World\")",
                                        Py_file_input,
                                        main_namespace.ptr(),
                                        main_namespace.ptr() ) ));
    } catch( error_already_set ) {
        PyErr_Print();
    }
}

void helloworld_external(){
    try {
        Py_Initialize();

        object main_module((
        handle<>(borrowed(PyImport_AddModule("__main__")))));

        object main_namespace = main_module.attr("__dict__");

        // >>> import Test
        std::cout << "importing test module..." << std::endl;
        object test_module = import("TestModule");

        // >>> test_class = TestModule.TestClass()
        std::cout << "intitalisign class..." << std::endl;
        object test_class = test_module.attr("TestClass")();

        // >>> TestClass.helloworld();
        std::cout << "running function..." << std::endl;
        test_class.attr("helloworld")();
    } catch( error_already_set ) {
        PyErr_Print();
    }
}

int main( int argc, char ** argv ) {
#ifdef _WIN32
    putenv("PYTHONPATH=.");
#endif
#ifdef linux
    setenv("PYTHONPATH", ".", 1);
#endif
    helloworld_iternal();
    helloworld_external();
}