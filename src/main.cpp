#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <cstdlib> // setenv
#include <iostream>

namespace py = boost::python;
namespace np = boost::python::numpy;

void test_numpy(){  
    std::cout << "Testing numpy output..." << std::endl;
    py::object main_module((
    py::handle<>(py::borrowed(PyImport_AddModule("__main__")))));

    py::object main_namespace = main_module.attr("__dict__");

    // >>> import Test
    py::object test_module = py::import("TestModule");

    // >>> test_class = TestModule.TestClass()
    py::object test_class = test_module.attr("TestClass")();

    // create test array
    int data[] = {1,2,3,4,5};
    np::dtype dt = np::dtype::get_builtin<int>();
    py::tuple shape = py::make_tuple(5);
    py::tuple stride = py::make_tuple(sizeof(int));
    py::object own;
    np::ndarray np_indata = np::from_data(data,dt, shape,stride,own);

    // >>> TestClass.numpyout();
    py::object ret = test_class.attr("testnumpy")(np_indata);
    auto v = py::extract<np::ndarray>(ret);
    const np::ndarray& np_ret = v();
    int input_size = np_ret.shape(0);
    int* input_ptr = reinterpret_cast<int*>(np_ret.get_data());
    std::cout << "numpy output test complete." << std::endl;
}

void test_double(){
    std::cout << "Testing double I/O..." << std::endl;
    py::object main_module((
    py::handle<>(py::borrowed(PyImport_AddModule("__main__")))));

    py::object main_namespace = main_module.attr("__dict__");

    // >>> import Test
    py::object test_module = py::import("TestModule");

    // >>> test_class = TestModule.TestClass()
    py::object test_class = test_module.attr("TestClass")();

    // >>> TestClass.testint();
    py::object ret = test_class.attr("testfloat")(3.14);
    double v = py::extract<double>(ret);
    std::cout << "Value returned from testInt: " << v << std::endl;
    std::cout << "Double I/O test complete." << std::endl;
}

void test_int(){
    std::cout << "Testing integer I/O..." << std::endl;
    py::object main_module((
    py::handle<>(py::borrowed(PyImport_AddModule("__main__")))));

    py::object main_namespace = main_module.attr("__dict__");

    // >>> import Test
    py::object test_module = py::import("TestModule");

    // >>> test_class = TestModule.TestClass()
    py::object test_class = test_module.attr("TestClass")();

    // >>> TestClass.testint();
    py::object ret = test_class.attr("testint")(9000);
    int v = py::extract<int>(ret);
    std::cout << "Value returned from testInt: " << v << std::endl;
    std::cout << "Integer I/O test complete." << std::endl;
}

void helloworld_iternal(){
    py::object main_module((
    py::handle<>(py::borrowed(PyImport_AddModule("__main__")))));

    py::object main_namespace = main_module.attr("__dict__");

    py::handle<> ignored(( PyRun_String( "print(\"Hello, World\")",
                                    Py_file_input,
                                    main_namespace.ptr(),
                                    main_namespace.ptr() ) ));
}

void helloworld_external(){
    py::object main_module((
    py::handle<>(py::borrowed(PyImport_AddModule("__main__")))));

    py::object main_namespace = main_module.attr("__dict__");

    // >>> import Test
    py::object test_module = py::import("TestModule");

    // >>> test_class = TestModule.TestClass()
    py::object test_class = test_module.attr("TestClass")();

    // >>> TestClass.helloworld();
    test_class.attr("helloworld")();
}

int main( int argc, char ** argv ) {
#ifdef _WIN32
    putenv("PYTHONPATH=.");
#endif
#ifdef linux
    setenv("PYTHONPATH", ".", 1);
#endif
    try {
        Py_Initialize();
        np::initialize();

        test_int();
        test_double();
        test_numpy();
    } catch( py::error_already_set ) {
        PyErr_Print();
    }
}