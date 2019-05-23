#include <Python.h>
#include <string>
#include <iostream>
#include <ECPoint/ECPoint.h>
#include <BigNumbers/BigNumbers.h>

struct module_state {
    PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif



static PyObject* wrap_addFromHex(PyObject* self, PyObject *args)
{
    char * argA; 
    char * argB; 

    if (!PyArg_ParseTuple(args, "ss", &argA, &argB))
        return NULL;

    ECPoint ecpointA, ecpointB;
    ecpointA.FromHex(argA);
    ecpointB.FromHex(argB);
    ECPoint ecpointC = ecpointA + ecpointB; 
    return Py_BuildValue("s", ecpointC.ToHex().c_str());
}

static PyObject* wrap_addFromHexWithCurveID(PyObject* self, PyObject *args)
{
    char * argA; 
    char * argB; 
    int curveID;

    if (!PyArg_ParseTuple(args, "ssi", &argA, &argB, &curveID))
        return NULL;
    ECPoint ecpointA(curveID), ecpointB(curveID);
    ecpointA.FromHex(argA);
    ecpointB.FromHex(argB);
    ECPoint ecpointC = ecpointA + ecpointB; 
    return Py_BuildValue("s", ecpointC.ToHex().c_str());
}

static PyObject* wrap_compare(PyObject* self, PyObject *args)
{
    char * argA; 
    char * argB; 

    if (!PyArg_ParseTuple(args, "ss", &argA, &argB))
        return NULL;

    ECPoint ecpointA, ecpointB;
    ecpointA.FromHex(argA);
    ecpointB.FromHex(argB);
    bool isSame = ecpointA == ecpointB;
    return Py_BuildValue("O", isSame == true ? Py_True: Py_False);
}



static PyObject* wrap_compareOnCurve(PyObject* self, PyObject *args)
{
    char * argA; 
    char * argB; 
    int curveID; 

    if (!PyArg_ParseTuple(args, "ssi", &argA, &argB,&curveID))
        return NULL;

    ECPoint ecpointA(curveID), ecpointB(curveID);
    ecpointA.FromHex(argA);
    ecpointB.FromHex(argB);
    bool isSame = ecpointA == ecpointB;
    return Py_BuildValue("O", isSame == true ? Py_True: Py_False);
}

static PyObject* wrap_doubleFromHex(PyObject* self, PyObject *args)
{
    char * argA; 

    if (!PyArg_ParseTuple(args, "s", &argA))
        return NULL;

    ECPoint ecpointA;
    ecpointA.FromHex(argA);
    ECPoint ecpointC = ecpointA.Double();
    return Py_BuildValue("s", ecpointC.ToHex().c_str());
}

static PyObject* wrap_doubleFromHexOnCurve(PyObject* self, PyObject *args)
{
    char * argA; 
    int curveID; 
    if (!PyArg_ParseTuple(args, "si", &argA,&curveID))
        return NULL;

    ECPoint ecpointA(curveID);
    ecpointA.FromHex(argA);
    ECPoint ecpointC = ecpointA.Double();
    return Py_BuildValue("s", ecpointC.ToHex().c_str());
}

static PyObject* wrap_invertFromHex(PyObject* self, PyObject *args)
{
    char * argA; 

    if (!PyArg_ParseTuple(args, "s", &argA))
        return NULL;

    ECPoint ecpointA;
    ecpointA.FromHex(argA);
    ecpointA.Invert();
    return Py_BuildValue("s", ecpointA.ToHex().c_str());
}

static PyObject* wrap_invertFromHexOnCurve(PyObject* self, PyObject *args)
{
    char * argA; 
    int curveID; 

    if (!PyArg_ParseTuple(args, "si", &argA,&curveID))
        return NULL;

    ECPoint ecpointA(curveID);
    ecpointA.FromHex(argA);
    ecpointA.Invert();
    return Py_BuildValue("s", ecpointA.ToHex().c_str());
}

static PyObject* wrap_checkInfinityFromHex(PyObject* self, PyObject *args)
{
    char * argA; 

    if (!PyArg_ParseTuple(args, "s", &argA))
        return NULL;

    ECPoint ecpointA;
    ecpointA.FromHex(argA);
    return Py_BuildValue("O", ecpointA.CheckInfinity()== true ? Py_True: Py_False);
}

static PyObject* wrap_checkInfinityFromHexOnCurve(PyObject* self, PyObject *args)
{
    char * argA; 
    int curveID; 

    if (!PyArg_ParseTuple(args, "si", &argA,&curveID))
        return NULL;

    ECPoint ecpointA(curveID);
    ecpointA.FromHex(argA);
    return Py_BuildValue("O", ecpointA.CheckInfinity()== true ? Py_True: Py_False);
}

static PyObject* wrap_checkOnCurveFromHex(PyObject* self, PyObject *args)
{
    char * argA;  
    if (!PyArg_ParseTuple(args, "s", &argA))
        return NULL;

    ECPoint ecpointA;
    ecpointA.FromHex(argA);
    return Py_BuildValue("O", ecpointA.CheckOnCurve()== true ? Py_True: Py_False);
}

static PyObject* wrap_checkOnCurveFromHexOnCurve(PyObject* self, PyObject *args)
{
    char * argA;  
    int curveID; 
    if (!PyArg_ParseTuple(args, "si", &argA,&curveID))
        return NULL;

    ECPoint ecpointA(curveID);
    ecpointA.FromHex(argA);
    return Py_BuildValue("O", ecpointA.CheckOnCurve()== true ? Py_True: Py_False);
}

static PyObject* wrap_GenerateRandomECHex(PyObject* self, PyObject *args)
{
    ECPoint ecpointA;
    ecpointA.SetRandom();
    return Py_BuildValue("s", ecpointA.ToHex ().c_str());
}

static PyObject* wrap_GenerateRandomECHexOnCurve(PyObject* self, PyObject *args)
{
    int argA; 
    if (!PyArg_ParseTuple(args, "i", &argA))
        return NULL;
    std::cout << "Creating a point with value " << argA << std::endl; 
    ECPoint ecpointA(argA);
    ecpointA.SetRandom();
    return Py_BuildValue("s", ecpointA.ToHex ().c_str());
}

static PyObject* wrap_GenerateECFromHex(PyObject* self, PyObject *args)
{
    char  * argA; 
    if (!PyArg_ParseTuple(args, "s", &argA))
        return NULL;
    ECPoint ecpointA;
    ecpointA.FromHex(argA) ; 
    return Py_BuildValue("s", ecpointA.ToHex ().c_str());
}

static PyObject* wrap_GenerateECFromHexOnCurve(PyObject* self, PyObject *args)
{
    char  * argA; 
    int argB; 
    if (!PyArg_ParseTuple(args, "si", &argA, &argB))
        return NULL;
    ECPoint ecpointA(argB);
    ecpointA.FromHex(argA) ; 
    return Py_BuildValue("s", ecpointA.ToHex ().c_str());
}

static PyObject* wrap_MultiplyScalarECM(PyObject* self, PyObject *args){
    char *ecPoint; 
    char * bigNumM; 
     if (!PyArg_ParseTuple(args, "ss", &ecPoint, &bigNumM))
        return NULL;
    
    ECPoint ecPointA; 
    ecPointA.FromHex(ecPoint); 
    
    ECPoint resECPt = ecPointA.MulHex(bigNumM, std::string ()) ; 
    
    return  Py_BuildValue("s", resECPt.ToHex ().c_str());
}
static PyObject*  wrap_MultiplyScalarECMOnCurve(PyObject* self, PyObject *args){
    char *ecPoint; 
    char * bigNumM; 
    int curveID; 
     if (!PyArg_ParseTuple(args, "ssi", &ecPoint, &bigNumM,&curveID))
        return NULL;
    
    ECPoint ecPointA(curveID); 
    ecPointA.FromHex(ecPoint); 
    
    ECPoint resECPt = ecPointA.MulHex(bigNumM, std::string ()) ; 
    
    return  Py_BuildValue("s", resECPt.ToHex ().c_str());
}

static PyObject*  wrap_MultiplyScalarECMN(PyObject* self, PyObject *args){
    char *ecPoint; 
    char * bigNumM; 
    char * bigNumN; 

     if (!PyArg_ParseTuple(args, "sss", &ecPoint, &bigNumM, &bigNumN))
        return NULL;
    
    ECPoint ecPointA; 
    ecPointA.FromHex(ecPoint); 
    
    ECPoint resECPt = ecPointA.MulHex(bigNumM, bigNumN) ; 
    
    return  Py_BuildValue("s", resECPt.ToHex ().c_str());
}

static PyObject*  wrap_MultiplyScalarECMNOnCurve(PyObject* self, PyObject *args){
    char *ecPoint; 
    char * bigNumM; 
    char * bigNumN; 
    int curveID; 

     if (!PyArg_ParseTuple(args, "sssi", &ecPoint, &bigNumM, &bigNumN,&curveID))
        return NULL;
    
    ECPoint ecPointA(curveID); 
    ecPointA.FromHex(ecPoint); 
    
    ECPoint resECPt = ecPointA.MulHex(bigNumM, bigNumN) ; 
    
    return  Py_BuildValue("s", resECPt.ToHex ().c_str());
}

static PyObject* wrap_GetAffineCoOrdinates(PyObject* self, PyObject *args){
    char *ecPoint; 

     if (!PyArg_ParseTuple(args, "s", &ecPoint))
        return NULL;
    
    ECPoint ecPointA; 
    ecPointA.FromHex(ecPoint); 
    
    std::pair<std::string,std::string> coords = ecPointA.GetAffineCoords_GFp();     
    return  Py_BuildValue("ss",coords.first.c_str(), coords.second.c_str());
}
static PyObject* wrap_GetAffineCoOrdinatesOnCurve(PyObject* self, PyObject *args){
    char *ecPoint; 
    int curveID; 
     if (!PyArg_ParseTuple(args, "si", &ecPoint,&curveID))
        return NULL;
    
    ECPoint ecPointA(curveID); 
    ecPointA.FromHex(ecPoint); 
    
    std::pair<std::string,std::string> coords = ecPointA.GetAffineCoords_GFp();     
    return  Py_BuildValue("ss",coords.first.c_str(), coords.second.c_str());
}

static PyMethodDef ModuleMethods[] =
{
    {"addFromHex", wrap_addFromHex, METH_VARARGS, "Add two ECPoints in hex with the default NID ==> NID_secp256k1"},
    {"addFromHexWithCurveID", wrap_addFromHexWithCurveID,METH_VARARGS, "Add two ECPoints in hex with the supplied curve IDs"},
    {"compare", wrap_compare, METH_VARARGS, "Compare two given ECPoints "},
    {"compareCurve", wrap_compareOnCurve, METH_VARARGS, "Compare two given ECPoints with a Curve ID"},
    {"doubleFromHex", wrap_doubleFromHex, METH_VARARGS, "Double the ECPoint in hex with the default NID ==> NID_secp256k1"},
    {"doubleFomHexCurve", wrap_doubleFromHexOnCurve, METH_VARARGS,"Double the ECPoint in hex with the given curve ID"},
    {"invertFromHex", wrap_invertFromHex, METH_VARARGS, "Invert the ECPoint in hex with the default NID ==> NID_secp256k1"},
    {"invertFromHexCurve",wrap_invertFromHexOnCurve, METH_VARARGS,"Invert the ECPoint in hex with the given curve ID"},
    {"checkInfinityFromHex", wrap_checkInfinityFromHex, METH_VARARGS, "Check if the given point is at infinity with default NID ==> NID_secp256k1"},
    {"checkInfinityFromHexCurve", wrap_checkInfinityFromHexOnCurve, METH_VARARGS, "Check if the given point is at infinity on the given curve ID"},
    {"CheckOnCurve", wrap_checkOnCurveFromHex, METH_VARARGS, "Check if the point is on the curve with the supplied NID default NID ==> NID_secp256k1"},
    {"checkOnCurveFromHexOnCurve",wrap_checkOnCurveFromHexOnCurve, METH_VARARGS, "Check if the point is on the curve with supplied curve ID"},
    {"GenerateRandomECHex", wrap_GenerateRandomECHex, METH_NOARGS ,"Generate a Random EC Point with default NID ==> NID_secp256k1"},
    {"GenerateRandomECHexOnCurve", wrap_GenerateRandomECHexOnCurve, METH_VARARGS ,"Generate a Random EC Point with supplied NID"},
    {"GenerateECHexFromHex", wrap_GenerateECFromHex, METH_VARARGS ,"Generate a EC Point from hex string with default NID ==> NID_secp256k1"},
    {"GenerateECHexFromHexOnCurve",wrap_GenerateECFromHexOnCurve, METH_VARARGS ,"Generate a EC Point from hex string with supplied NID"},
    {"MultiplyScalarM", wrap_MultiplyScalarECM, METH_VARARGS, "EC Point Scalar multiply with default NID => NID_secp256k1"},
    {"MultiplyScalarMOnCurve", wrap_MultiplyScalarECMOnCurve, METH_VARARGS, "EC Point Scalar multiply on curve with supplied ID"},
    {"MultiplyScalarMN", wrap_MultiplyScalarECMN, METH_VARARGS, "EC Point Scalar multiply with default NID => NID_secp256k1"},
    {"MultiplyScalarMNOnCurve", wrap_MultiplyScalarECMNOnCurve, METH_VARARGS, "EC Point Scalar multiply with supplied curve ID"},
    {"GetAffineCoOrdinates", wrap_GetAffineCoOrdinates, METH_VARARGS, "EC Point GetAffineCoOrdinates_GFp with default NID => NID_secp256k1"},
    {"GetAffineCoOrdinatesOnCurve", wrap_GetAffineCoOrdinatesOnCurve, METH_VARARGS, "EC Point GetAffineCoOrdinates_GFp with supplied curve"},
    {NULL, NULL, 0, NULL},
};
 
#if PY_MAJOR_VERSION >= 3

static int PyECPoint_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int PyECPoint_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}


static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "PyECPoint",
        NULL,
        sizeof(struct module_state),
        ModuleMethods,
        NULL,
        PyECPoint_traverse,
        PyECPoint_clear,
        NULL
};

#define INITERROR return NULL

PyMODINIT_FUNC
PyInit_PyECPoint(void)

#else
#define INITERROR return

void
initmyextension(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule("ECPointextension", myextension_methods);
#endif

    if (module == NULL)
        INITERROR;
    struct module_state *st = GETSTATE(module);

    st->error = PyErr_NewException("PyECPointextension.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR;
    }

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}