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
PyObject* MVector3new(PyTypeObject* type, PyObject* args, PyObject* kwds);
void MVector3init();
CVector3 MVector3ToVector3(MVector3* mpos);