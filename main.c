#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <stdio.h>

// convenience printing function
void print_pycounters(PyObject* counter_a, PyObject* counter_b);

int main(int argc, char *argv[]){

    printf("Hello world! I'm a C program!\n");

    // Reference Embedding Python in Another Application. Locally, the docs were at file:///C:/Dev/Python-Docs/python-3.8.14-docs-html/extending/embedding.html

    // Very High Level Embedding
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    Py_SetProgramName(program);
    Py_Initialize();
    PyRun_SimpleString("print(\"Hello world! I'm a python string!\")");

    // High Level Embedding
    // do some manual path mangling in python because I can't be bothered to do string stuff in pure C
    // this is because of a strange behavior where the current directory is not prepended to system path on startup...
    PyRun_SimpleString("import sys\n"
    "sys.path.insert(0,'')");

    // load 2 python scripts, introducing functions and variables to interpretter. Check state after. 
    PyObject* module_one_name = PyUnicode_DecodeFSDefault("module_one");
    PyObject* module_two_name = PyUnicode_DecodeFSDefault("module_two");

    PyObject* module_one = PyImport_Import(module_one_name);
    PyObject* module_two = PyImport_Import(module_two_name);
    Py_DecRef(module_one_name); // decrement the PyObject holding the name since we're done with it
    Py_DecRef(module_two_name);

    PyObject* module_one_fn = NULL;
    PyObject* module_two_fn = NULL;
    if (module_one != NULL && module_two != NULL)
    {
        module_one_fn = PyObject_GetAttrString(module_one, "module_one_hello");
        module_two_fn = PyObject_GetAttrString(module_two, "module_two_hello");

        // print out module counters, expect first to be 0s
        print_pycounters(PyObject_GetAttrString(module_one, "module_one_counter"), PyObject_GetAttrString(module_two, "module_two_counter"));
        PyObject_CallObject(module_one_fn,NULL); // invoke the module functions
        PyObject_CallObject(module_two_fn,NULL);
        // print out counters again, expect first to be 1s
        print_pycounters(PyObject_GetAttrString(module_one, "module_one_counter"), PyObject_GetAttrString(module_two, "module_two_counter"));

        // lets simulate needing to update a module now
        Py_DecRef(module_one);
        Py_DecRef(module_one_fn);
        module_one = PyImport_Import(PyUnicode_DecodeFSDefault("module_one_update"));
        module_one_fn = PyObject_GetAttrString(module_one, "module_one_hello");
        PyObject_CallObject(module_one_fn,NULL);
        PyObject_CallObject(module_two_fn,NULL);
        print_pycounters(PyObject_GetAttrString(module_one, "module_one_counter"), PyObject_GetAttrString(module_two, "module_two_counter"));
    }
    
    
    
    // Boilerplate from examples to shut down
    PyMem_RawFree(program);
    if (Py_FinalizeEx() < 0){
        return 120;
    }
    return 0;
}


// you may notice this was called with repeated calls to PyObject_GetAttrString... that's because the underlying objects were changed so storing them in PyObject* would result in printing old values from old PyObject
void print_pycounters(PyObject* counter_a, PyObject* counter_b){
    long a = PyLong_AsLong(counter_a);
    long b = PyLong_AsLong(counter_b);
    printf("The counters are [%li,%li]\n", a,b);

}