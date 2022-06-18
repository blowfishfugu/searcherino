#include <Windows.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <Python.h>

PyObject* linsearch_impl(PyObject* /*module*/, PyObject* args)
{
	__int64 index = -1;
	PyObject* lst = nullptr;
	__int64 searchFor = -1;
	if (PyArg_ParseTuple(args, "O|L", &lst, &searchFor))
	{
		lst = PySequence_Fast(lst, "getting sequence failed");
		if (lst)
		{
			__int64 itemCount = PySequence_Fast_GET_SIZE(lst);
			for (__int64 i = 0; i < itemCount; i++)
			{
				PyObject* item = PySequence_Fast_GET_ITEM(lst, i);
				__int64 val = PyLong_AsLongLong(item);
				if (val == searchFor)
				{
					return PyLong_FromLongLong(i);
				}
			}
		}
	}
	return PyLong_FromLongLong(index);
}

PyObject* binsearch_impl(PyObject* /*module*/, PyObject* args)
{
	PyObject* lst = nullptr;
	__int64 searchFor = -1;
	if (PyArg_ParseTuple(args, "O|L", &lst, &searchFor))
	{
		lst = PySequence_Fast(lst, "getting sequence failed");
		if (lst)
		{
			__int64 minIndex = 0;
			__int64 maxIndex = PySequence_Fast_GET_SIZE(lst)-1;
			__int64 i = 0;
			while( maxIndex>=minIndex)
			{
				i = (maxIndex + minIndex) / 2;
				PyObject* item = PySequence_Fast_GET_ITEM(lst, i);
				__int64 val = PyLong_AsLongLong(item);
				
				if (val > searchFor)
				{
					maxIndex = i - 1;
				}
				else if (val < searchFor)
				{
					minIndex = i + 1;
				}
				else
				{
					return PyLong_FromLongLong(i);
				}
				
			}
			Py_DECREF(lst);
		}
	}
	return PyLong_FromLongLong(-1);
}

static PyMethodDef searcherino_methods[] = {
	// The first property is the name exposed to Python, fast_tanh
	// The second is the C++ function with the implementation
	{ "linearsearch_cpp", (PyCFunction)linsearch_impl, METH_VARARGS, nullptr },
	{ "binsearch_cpp", (PyCFunction)binsearch_impl, METH_VARARGS, nullptr },

	// Terminate the array with an object containing nulls.
	{ nullptr, nullptr, 0, nullptr }
};

static PyModuleDef searcherino_module = {
	PyModuleDef_HEAD_INIT,
	"searcherino",                        // Module name to use with Python import statements
	"Provides some functions, but faster?",  // Module description
	0,
	searcherino_methods                   // Structure that defines the methods of the module
};

PyMODINIT_FUNC PyInit_searcherino() {
	return PyModule_Create(&searcherino_module);
}