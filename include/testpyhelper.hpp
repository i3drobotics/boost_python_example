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

		std::vector<int> v_i = {1,2,3,4,5};
		testIntVect_AsList(v_i);
		std::vector<char> v_c = {'a','b','c'};
		testCharVect_AsList(v_c);
		std::vector<double> v_d = {1.2,3.4,5.6,7.8,9.0};
		testDoubleVect_AsList(v_d);
		std::vector<std::string> v_str = {"one", "two", "three"};
		testStringVect_AsList(v_str);
		
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
			std::cout << "No function named 'helloworld' found in class: " << std::endl;
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

	template <class T>
	bool testT(T value){
		// create test integer
		T test_int = value;
		// >>> TestClass.testint();
		if (pyhelper::hasattr(test_class,"testio")){
			py::object ret = test_class.attr("testio")(test_int);
			// get int from result
			T v = py::extract<T>(ret);
			// print result
			std::cout << "Value returned: " << v << std::endl;
			//check value in and out are equal
			if (v == value){
				return true;
			} else {
				std::cout << "Input value ( " << value << " ) doesn't match output value ( " << v << " )" << std::endl;
				return false;
			}
		} else {
			std::cout << "Not function named 'testio' found in class: " << std::endl;
			return false;
		}
	}

	template <class T>
	bool testArray_AsNumpy(T* array, int length){  
		// create test array
		np::dtype dt = np::dtype::get_builtin<T>();
		py::tuple shape = py::make_tuple(length);
		py::tuple stride = py::make_tuple(sizeof(T));
		py::object own;
		np::ndarray np_indata = np::from_data(array,dt, shape,stride,own);

		// >>> TestClass.numpyout();
		if (pyhelper::hasattr(test_class,"testio")){
			py::object ret = test_class.attr("testio")(np_indata);
			// extract numpy array from return object
			auto v = py::extract<np::ndarray>(ret);
			const np::ndarray& np_ret = v();
			// convert numpy array to int array
			Py_intptr_t ret_size = np_ret.shape(0);
			T* ret_array = reinterpret_cast<T*>(np_ret.get_data());
			// print result
			std::cout << "Value returned: ";
			std::cout << "[ ";
			for (Py_intptr_t i = 0; i < ret_size; i++) 
				std::cout << ret_array[i] << " ";
			std::cout << "]" << std::endl;
			//check array in and out are the same size
			int in_array_size = sizeof(array) / sizeof(T);
			int out_array_size = sizeof(ret_array) / sizeof(T);
			if (in_array_size != out_array_size){
				std::cout << "Input value size ( " << in_array_size << " ) doesn't match output value size ( " << out_array_size << " )" << std::endl;
				return false; 
			}
			// TODO check values are equal
			return true;
		} else {
			std::cout << "Not function named 'testio' found in class: " << std::endl;
			return false;
		}
	}

	template <class T>
	bool testVect_AsList(std::vector<T> vect){
		py::list py_list = pyh::toPythonList(vect);
		if (pyhelper::hasattr(test_class,"testio")){
			py::object ret = test_class.attr("testio")(py_list);
			// extract list from result
			py::list l = py::extract<py::list>(ret);
			// convert list to vector
			std::vector<T> v_ret = pyh::toStdVector<T>(l);
			// print result
			std::cout << "Value returned: ";
			std::cout << "[ ";
			for (std::vector<T>::iterator it = v_ret.begin() ; it != v_ret.end(); ++it)
    			std::cout << *it << " ";
			std::cout << "]" << std::endl;
			//check vector in and out are the same size
			if (vect.size() != v_ret.size()){
				std::cout << "Input value size ( " << vect.size() << " ) doesn't match output value size ( " << v_ret.size() << " )" << std::endl;
				return false;
			}
			// TODO check values are equal
			return true;
		} else {
			std::cout << "Not function named 'testio' found in class: " << std::endl;
			return false;
		}
	}

	bool testInt(int value){
		std::cout << "Testing integer I/O..." << std::endl;
		if (testT(value)){
			std::cout << "Integer I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Integer I/O test failed." << std::endl;
			return false;
		}
	}

	bool testChar(char value){
		std::cout << "Testing char I/O..." << std::endl;
		if (testT(value)){
			std::cout << "Char I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Char I/O test failed." << std::endl;
			return false;
		}
	}

	bool testDouble(double value){
		std::cout << "Testing double I/O..." << std::endl;
		if (testT(value)){
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
		if (testT(std::string(value))){
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
		if (testT(value)){
			std::cout << "String I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Not function named 'testio' found in class: " << std::endl;
			std::cout << "String I/O test failed." << std::endl;
			return false;
		}
	}

	bool testIntArray_AsNumpy(int* array, int length){
		std::cout << "Testing integer array as numpy I/O..." << std::endl;
		if (testArray_AsNumpy(array,length)){
			std::cout << "Integer array as numpy I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Integer array I/O test failed." << std::endl;
			return false;
		}
	}

	bool testCharArray_AsNumpy(char* array, int length){  
		std::cout << "Testing char array as numpy I/O..." << std::endl;
		if (testArray_AsNumpy(array,length)){
			std::cout << "Char array as numpy I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Char array as numpy I/O test failed." << std::endl;
			return false;
		}
	}

	bool testDoubleArray_AsNumpy(double* array, int length){  
		std::cout << "Testing double array as numpy I/O..." << std::endl;
		if (testArray_AsNumpy(array,length)){
			std::cout << "Double array as numpy I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Double array as numpy I/O test failed." << std::endl;
			return false;
		}
	}

	bool testIntVect_AsList(std::vector<int> vect){
		std::cout << "Testing integer vector as list I/O..." << std::endl;
		if (testVect_AsList(vect)){
			std::cout << "Integer vector as list I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Integer vector as list I/O test failed." << std::endl;
			return false;
		}
	}

	bool testCharVect_AsList(std::vector<char> vect){
		std::cout << "Testing char vector as list I/O..." << std::endl;
		if (testVect_AsList(vect)){
			std::cout << "Char vector as list I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Char vector as list I/O test failed." << std::endl;
			return false;
		}
	}

	bool testDoubleVect_AsList(std::vector<double> vect){
		std::cout << "Testing double vector as list I/O..." << std::endl;
		if (testVect_AsList(vect)){
			std::cout << "Double vector as list I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "Double vector as list I/O test failed." << std::endl;
			return false;
		}
	}

	bool testStringVect_AsList(std::vector<std::string> vect){
		std::cout << "Testing string vector as list I/O..." << std::endl;
		if (testVect_AsList(vect)){
			std::cout << "String vector as list I/O test complete." << std::endl;
			return true;
		} else {
			std::cout << "String vector as list I/O test failed." << std::endl;
			return false;
		}
	}

	~TestPyHelper()
	{
	}

	pyh::py::object test_class;
};

#endif //TESTPYHELPER_HPP