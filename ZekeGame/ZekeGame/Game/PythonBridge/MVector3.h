#pragma once


typedef struct
{
	PyObject_HEAD
	double x;
	double y;
	double z;
}MVector3;
PyObject* MSqrt(PyObject* mod, PyObject* v);
extern PyTypeObject MVector3Type;
void MVector3init();