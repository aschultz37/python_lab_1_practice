#define PY_SSIZE_T_CLEAN
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include "/gpfs/data/lundlab/austin/.conda/envs/my_base/lib/python3.10/site-packages/numpy/core/include/numpy/arrayobject.h"

static PyObject *creative_mean(PyObject *self, PyObject *args);
static PyObject *creative_var(PyObject *self, PyObject *args);

static PyMethodDef CreativeMethods[] = {
    {"mean", creative_mean, METH_VARARGS, "Find mean of array."},
    {"var", creative_var, METH_VARARGS, "Find variance of array."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef creativemodule = {
    PyModuleDef_HEAD_INIT,
    "creative",
    NULL, //no module documentation
    -1, //keep state in global var
    CreativeMethods
};

PyMODINIT_FUNC PyInit_creative(void){
    import_array();
    return PyModule_Create(&creativemodule);
}

static PyObject *creative_mean(PyObject *self, PyObject *args){
    PyObject *arg1 = NULL;
    double sum = 0;

    /* Parse Arguments */
    if(!PyArg_ParseTuple(args, "O", &arg1)){
        return NULL;
    }

    /* Get Array Iterators */
    PyArrayIterObject *iter = (PyArrayIterObject *)PyArray_IterNew(arg1);
    if(iter == NULL) return NULL;

    /* Compute Mean"  */
    while(iter->index < iter->size){ 
        double *tmp_data = (double *)PyArray_ITER_DATA(iter);
        sum += (*tmp_data);
        PyArray_ITER_NEXT(iter);
    }
    return PyFloat_FromDouble(sum / (double)iter->size);
}

static PyObject *creative_var(PyObject *self, PyObject *args){
    PyObject *arg1 = NULL;
    double sum = 0;

    /* Parse Arguments */
    if(!PyArg_ParseTuple(args, "O", &arg1)){
        return NULL;
    }

    /* Get Array Iterator */
    PyArrayIterObject *iter = (PyArrayIterObject *)PyArray_IterNew(arg1);
    if(iter == NULL) return NULL;

    /* Compute Mean"  */
    while(iter->index < iter->size){ 
        double *tmp_data = (double *)PyArray_ITER_DATA(iter);
        sum += (*tmp_data);
        PyArray_ITER_NEXT(iter);
    }

    double mean = sum / (double)iter->size;

    /* Compute Variance */
    PyArray_ITER_RESET(iter);
    sum = 0;
    while(iter->index < iter->size){
        double *tmp_data = (double *)PyArray_ITER_DATA(iter);
        double tmp_std = (*tmp_data) - mean;
        sum += (tmp_std * tmp_std);
        PyArray_ITER_NEXT(iter);
    }
    return PyFloat_FromDouble(sum / (double)iter->size);
}