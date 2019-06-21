#include "stdafx.h"
#include "include/structmember.h"
#include "MVector3.h"




PyTypeObject MVector3Type = {
	PyVarObject_HEAD_INIT(NULL,0)
};


static PyMemberDef MVector3Members[] =
{
	{(char*)"x",T_FLOAT,offsetof(MVector3,x),0,(char*)""},
	{(char*)"y",T_FLOAT,offsetof(MVector3,y),0,(char*)""},
	{(char*)"z",T_FLOAT,offsetof(MVector3,z),0,(char*)""},
	{NULL}
};

static PyObject* MVector3new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	MVector3* self;
	self = (MVector3*)type->tp_alloc(type, 0);
	if (self != NULL) {
		self->x = 0.f;
		self->y = 0.f;
		self->z = 0.f;
	}
	return (PyObject*)self;
}

int MVvector3Initialize(MVector3* self, PyObject* args, PyObject* kwds)
{
	static char* kwlist[] = { (char*)"x", (char*)"y", (char*)"z", NULL };

	if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist, &self->x, &self->y, &self->z))
		return -1;
	return 0;
}

void MVector3Destruct(MVector3* self)
{
	Py_TYPE(self)->tp_free((PyObject*)self);
}

void MVector3setVector(MVector3* self, PyObject* xyz)
{
	self->x = PyFloat_AsDouble(PyTuple_GetItem(xyz, 0));
	self->y = PyFloat_AsDouble(PyTuple_GetItem(xyz, 1));
	self->z = PyFloat_AsDouble(PyTuple_GetItem(xyz, 2));
}

/*
加算オペレーター
*/
MVector3* MVector3__add__(MVector3* self, MVector3* right)
{
	MVector3* res;
	res = (MVector3*)(MVector3Type.tp_alloc(&MVector3Type, 0));
	if (res != NULL) {
		res->x = self->x+right->x;
		res->y = self->y + right->y;
		res->z = self->z + right->z;
	}
	return res;
}

/*
減算オペレーター
*/
MVector3* MVector3__sub__(MVector3* self, MVector3* right)
{
	MVector3* res;
	res = (MVector3*)(MVector3Type.tp_alloc(&MVector3Type, 0));
	if (res != NULL) {
		res->x = self->x - right->x;
		res->y = self->y - right->y;
		res->z = self->z - right->z;
	}
	return res;
}

/*
距離を出す
*/
PyFloatObject* MVector3Lenght(MVector3* self)
{
	PyFloatObject* res = (PyFloatObject*)(PyFloat_Type.tp_alloc(&PyFloat_Type, 0));
	res->ob_fval = sqrt(self->x * self->x + self->y * self->y + self->z * self->z);
	return res;
}

/*
ノーマライズ
*/
void MVector3Normalize(MVector3* self)
{
	float len = sqrt(self->x * self->x + self->y * self->y + self->z * self->z);
	self->x /= len;
	self->y /= len;
	self->z /= len;
}

static PyMethodDef MVector3Methods[] =
{
	{"SetVector",(PyCFunction)MVector3setVector,METH_VARARGS,""},
	{"__add__",(PyCFunction)MVector3__add__,METH_VARARGS,""},
	{"__sub__",(PyCFunction)MVector3__sub__,METH_VARARGS,""},
	{"Lenght",(PyCFunction)MVector3Lenght,METH_NOARGS,""},
	{"Normalize",(PyCFunction)MVector3Normalize,METH_NOARGS,""},
	{NULL}
};

void MVector3init()
{
	MVector3Type.tp_name = "SendGame.Vector3";
	MVector3Type.tp_doc = "";
	MVector3Type.tp_basicsize = sizeof(MVector3);
	MVector3Type.tp_itemsize = 0;
	MVector3Type.tp_flags = Py_TPFLAGS_DEFAULT;
	MVector3Type.tp_new = PyType_GenericNew;

	MVector3Type.tp_members = MVector3Members;
	MVector3Type.tp_new = MVector3new;
	MVector3Type.tp_init = (initproc)MVvector3Initialize;
	MVector3Type.tp_dealloc = (destructor)MVector3Destruct;
	
}

//平方根求める
PyObject* MSqrt(PyObject* mod, PyObject* v)
{
	int r = 1;
	int i = PyFloat_AsDouble(v);
	for (int j = 0; j < 32; j++)
	{
		r = (r + i / r) / 2;
	}

	PyObject* res = PyFloat_FromDouble(r);

	return res;
}
