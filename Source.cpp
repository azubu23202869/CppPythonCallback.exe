#pragma warning(disable:4996)
#include <Python.h>
#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
int main()
{
    PyObject* pModule, * pFunc;
    PyObject* pArgs, * pRet;
    Py_SetPythonHome((wchar_t*)L"C:\\Users\\azubu\\AppData\\Local\\Programs\\Python\\Python37\\");

    if (PyErr_Occurred()) {
        PyErr_PrintEx(0);
        PyErr_Clear(); // this will reset the error indicator so you can run Python code again
    }
    Py_Initialize();
    if (!Py_IsInitialized())
    {
        cout << "Initialize failed!" << endl;
        return 0;
    }

    //PyRun_SimpleString("exec(open('realsense_recorder.py', encoding = 'utf-8').read())");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("import os");
    PyRun_SimpleString("os.chdir('./')");   //定位到.py工作目錄下
    //PyRun_SimpleString("print(os.listdir())");  //顯示工作路徑查看是否定位成功
    PyRun_SimpleString("if not hasattr(sys, 'argv'):\n\tsys.argv = ['']");  //如果沒有引用c++的int main中的參數需要加上這一句話
    pModule = PyImport_ImportModule("realsense_recorder");
    if (!pModule) {
        printf("Can't open python file\n");

        return -1;

    }
    pFunc = PyObject_GetAttrString(pModule, "__name__");
    if (!pFunc) {
        printf("Get function main failed\n");

        return -1;
    }
    pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, Py_BuildValue("s", " --record_imgs"));
    pRet = PyEval_CallObject(pFunc, pArgs);
  
    if (PyRun_SimpleString("exec(open('realsense_recorder.py', encoding = 'utf-8').read())") == NULL)
    {
        printf("FK\n");
        return -1;
    }

    Py_Finalize();
    return 0;
}

