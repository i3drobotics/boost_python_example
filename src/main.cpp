#include <boost/python.hpp>

namespace python = boost::python;

int main(int argc, char **argv)
{
    Py_Initialize();
    python::object main_module = python::import("__main__");
    python::object main_namespace = main_module.attr("__dict__");

    python::object ignored = exec("hello = file('hello.txt', 'w')\n"
                        "hello.write('Hello world!')\n"
                        "hello.close()",
                        main_namespace);
}