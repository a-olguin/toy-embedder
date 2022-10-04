#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <stdio.h>

int main(int argc, char *argv[]){

    printf("Hello world! I'm a C program!\n");

    // Reference Embedding Python in Another Application. Locally, the docs were at file:///C:/Dev/Python-Docs/python-3.8.14-docs-html/extending/embedding.html

    // Very High Level Embedding
    Py_Initialize();
    PyRun_SimpleString("print(\"Hello world! I'm a python string!\")");
    if (Py_FinalizeEx() < 0){
        return 120;
    }
    return 0;
}