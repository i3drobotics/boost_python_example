#ifndef TESTPYHELPER_HPP
#define TESTPYHELPER_HPP
#pragma once

#include "pyhelper.hpp"
#include <iostream>

namespace pyh = pyhelper;
namespace py = pyh::py;
namespace np = pyh::np;

class TestPyHelper
{
public:
	TestPyHelper()
	{
		// initalise python
		pyh::initPython();
		// add current directory to python_path
		pyh::addToPythonPath(".");
		// get 'TestClass' from python script (TestModule.py)
		test_class = pyh::getPyClass("TestModule","TestClass");
	}

	void testAll(){
		helloworldInternal();
		helloworldExternal();
		testInt(9000);
		testChar('a');
		testDouble(3.14);
		testCStr("test");
		testString("test");
		int np_i [5] = {1,2,3,4,5};
		testIntArray_AsNumpy(np_i,5);
		char np_c [3] = {'a','b','c'};
		testCharArray_AsNumpy(np_c,3);
		double np_d [5] = {1.2,3.4,5.6,7.8,9.0};
		testDoubleArray_AsNumpy(np_d,5);
		std::vector<std::string> np_strs = {"one", "two", "three"};
		testStringVect_AsList(np_strs);
		/*
		char *np_chars[3] = {"one", "two", "three"};
		testCStrArray_AsNumpy(np_chars,3);
		std::string np_strs[3] = {"one", "two", "three"};
		testStringArray_AsNumpy(np_strs,3);
		std::vector<const char *> np_strs = {"one", "two", "three"};
		testStringVect_AsNumpy(np_strs);
		
		testCStringVect_AsNumpy(np_strs);
		*/
	}

	bool helloworldExternal(){
		std::cout << "Testing calling external script..." << std::endl;

		// TestClass.helloworld();
		if (pyhelper::hasattr(test_class,"helloworld")){
			test_class.attr("helloworld")();
			std::cout << "External script test complete." << std::endl;
			return true;
		} else {
			std::cout << "Not function named 'helloworld' found in class: " << std::endl;
			std::cout << "External script test failed." << std::endl;
			return false;
		}
	}

	bool helloworldInternal(){
		std::cout << "Testing generating python script internally..." << std::endl;

		pyh::py::object main_module((
		pyh::py::handle<>(pyh::py::borrowed(PyImport_AddModule("__main__")))));

		pyh::py::object main_namespace = main_module.attr("__dict__");

		pyh::py::handle<> ignored(( PyRun_String( "print(\"Hello, World\")",
										Py_file_input,
										main_namespace.ptr(),
										main_namespace.ptr() ) ));
		std::cout << "Internal script test complete." << std::endl;
		return true;
	}

	bool testInt(int value){
		std::cout << "Testing integer I/O..." << std::endl;

		// create test integer
		int test_int = value;
		// >>> TestClass.testint();
		if (pyhelper::hasattr(test_class,"testio")){
			py::object ret = test_class.attr("testio")(test_int);
			// get int from result
			int v = py::extract<int>(ret);
			// print result
			std::cout << "Value returned: " << v << std::endl;
			std::cout << "Integer I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Not function named 'testio' found in class: " << std::endl;
			std::cout << "Integer I/O test failed." << std::endl;
			return false;
		}
	}

	bool testChar(char value){
		std::cout << "Testing char I/O..." << std::endl;

		// create test char
		char test_char = value;
		// >>> TestClass.testchar();
		if (pyhelper::hasattr(test_class,"testio")){
			py::object ret = test_class.attr("testio")(test_char);
			// extract char from result
			char v = py::extract<char>(ret);
			// print result
			std::cout << "Value returned: " << v << std::endl;
			std::cout << "Char I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Not function named 'testio' found in class: " << std::endl;
			std::cout << "Char I/O test failed." << std::endl;
			return false;
		}
	}

	bool testDouble(double value){
		std::cout << "Testing double I/O..." << std::endl;

		// create test double
		double test_double = value;
		// >>> TestClass.testint();
		if (pyhelper::hasattr(test_class,"testio")){
			py::object ret = test_class.attr("testio")(test_double);
			// extract double from result
			double v = py::extract<double>(ret);
			// print result
			std::cout << "Value returned: " << v << std::endl;
			std::cout << "Double I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Not function named 'testio' found in class: " << std::endl;
			std::cout << "Double I/O test failed." << std::endl;
			return false;
		}
	}

	bool testCStr(char *value){
		std::cout << "Testing cstring I/O..." << std::endl;

		// create test c str
		char *test_char = value;
		std::string test_str = std::string(test_char);
		// >>> TestClass.testchar();
		if (pyhelper::hasattr(test_class,"testio")){
			py::object ret = test_class.attr("testio")(test_str);
			// extract char from result
			std::string v_str = py::extract<std::string>(ret);
			const char *v = v_str.c_str();
			// print result
			std::cout << "Value returned: " << v << std::endl;
			std::cout << "CString I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Not function named 'testio' found in class: " << std::endl;
			std::cout << "CString I/O test failed." << std::endl;
			return false;
		}
	}

	bool testString(std::string value){
		std::cout << "Testing string I/O..." << std::endl;

		// create test string
		std::string test_str = value;
		// >>> TestClass.testchar();
		if (pyhelper::hasattr(test_class,"testio")){
			py::object ret = test_class.attr("testio")(test_str);
			// extract char from result
			std::string v = py::extract<std::string>(ret);
			// print result
			std::cout << "Value returned: " << v << std::endl;
			std::cout << "String I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Not function named 'testio' found in class: " << std::endl;
			std::cout << "String I/O test failed." << std::endl;
			return false;
		}
	}

	bool testIntArray_AsNumpy(int* array,int length){  
		std::cout << "Testing integer array as numpy I/O..." << std::endl;

		// create test array
		np::dtype dt = np::dtype::get_builtin<int>();
		py::tuple shape = py::make_tuple(length);
		py::tuple stride = py::make_tuple(sizeof(int));
		py::object own;
		np::ndarray np_indata = np::from_data(array,dt, shape,stride,own);

		// >>> TestClass.numpyout();
		if (pyhelper::hasattr(test_class,"testio")){
			py::object ret = test_class.attr("testio")(np_indata);
			// extract numpy array from return object
			auto v = py::extract<np::ndarray>(ret);
			const np::ndarray& np_ret = v();
			// convert numpy array to int array
			Py_intptr_t input_size = np_ret.shape(0);
			int* input_ptr = reinterpret_cast<int*>(np_ret.get_data());
			// print result
			std::cout << "Value returned: ";
			std::cout << "[ ";
			for (Py_intptr_t i = 0; i < input_size; i++) 
				std::cout << input_ptr[i] << " ";
			std::cout << "]" << std::endl;
			std::cout << "Integer array as numpy I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Not function named 'testio' found in class: " << std::endl;
			std::cout << "Integer array as numpy I/O test failed." << std::endl;
			return false;
		}
	}

	bool testCharArray_AsNumpy(char* array,int length){  
		std::cout << "Testing char array as numpy I/O..." << std::endl;

		// create test array
		np::dtype dt = np::dtype::get_builtin<char>();
		py::tuple shape = py::make_tuple(length);
		py::tuple stride = py::make_tuple(sizeof(char));
		py::object own;
		np::ndarray np_indata = np::from_data(array,dt, shape,stride,own);

		// >>> TestClass.numpyout();
		if (pyhelper::hasattr(test_class,"testio")){
			py::object ret = test_class.attr("testio")(np_indata);
			auto v = py::extract<np::ndarray>(ret);
			const np::ndarray& np_ret = v();
			Py_intptr_t input_size = np_ret.shape(0);
			char* input_ptr = reinterpret_cast<char*>(np_ret.get_data());
			// print result
			std::cout << "Value returned: ";
			std::cout << "[ ";
			for (Py_intptr_t i = 0; i < input_size; i++) 
				std::cout << input_ptr[i] << " ";
			std::cout << "]" << std::endl;
			std::cout << "Char array as numpy I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Not function named 'testio' found in class: " << std::endl;
			std::cout << "Char array as numpy I/O test failed." << std::endl;
			return false;
		}
	}

	bool testDoubleArray_AsNumpy(double* array,int length){  
		std::cout << "Testing double array as numpy I/O..." << std::endl;

		// create test array
		np::dtype dt = np::dtype::get_builtin<double>();
		py::tuple shape = py::make_tuple(length);
		py::tuple stride = py::make_tuple(sizeof(double));
		py::object own;
		np::ndarray np_indata = np::from_data(array,dt, shape,stride,own);

		// >>> TestClass.numpyout();
		if (pyhelper::hasattr(test_class,"testio")){
			py::object ret = test_class.attr("testio")(np_indata);
			// extract numpy array from return object
			auto v = py::extract<np::ndarray>(ret);
			const np::ndarray& np_ret = v();
			// convert numpy array to int array
			Py_intptr_t input_size = np_ret.shape(0);
			double* input_ptr = reinterpret_cast<double*>(np_ret.get_data());
			// print result
			std::cout << "Value returned: ";
			std::cout << "[ ";
			for (Py_intptr_t i = 0; i < input_size; i++) 
				std::cout << input_ptr[i] << " ";
			std::cout << "]" << std::endl;
			std::cout << "Double array as numpy I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Not function named 'testio' found in class: " << std::endl;
			std::cout << "Double array as numpy I/O test failed." << std::endl;
			return false;
		}
	}

	bool testStringVect_AsList(std::vector<std::string> vect){
		std::cout << "Testing vector of strings as list I/O..." << std::endl;
		py::list py_list = pyh::toPythonList(vect);
		if (pyhelper::hasattr(test_class,"testio")){
			py::object ret = test_class.attr("testio")(py_list);
			// extract list from result
			py::list l = py::extract<py::list>(ret);
			// convert list to vector
			std::vector<std::string> v_ret = pyh::toStdVector<std::string>(l);
			// print result
			std::cout << "Value returned: ";
			std::cout << "[ ";
			for (std::vector<std::string>::iterator it = v_ret.begin() ; it != v_ret.end(); ++it)
    			std::cout << *it << " ";
			std::cout << "]" << std::endl;
			std::cout << "Vector of strings as list I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Not function named 'testio' found in class: " << std::endl;
			std::cout << "Vector of strings as list I/O test failed." << std::endl;
			return false;
		}
	}

	~TestPyHelper()
	{
	}

	pyh::py::object test_class;
};

#endif //TESTPYHELPER_HPP