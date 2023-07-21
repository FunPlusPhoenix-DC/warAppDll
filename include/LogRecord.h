#ifndef LOGRECORD_H_

#define LOGRECORD_H_

#endif

#include "pch.h"

#include <iostream>

#ifdef _cplusplus

extern "C"{

#endif  //begin to define

enum ErrorDefinition{
    Success = 0,
    Error,
    Warn,
};

int WARAPPDLL_API __stdcall ExecuteLogger(std::string& strContent);

int WARAPPDLL_API __stdcall InitLogger(char* p_PATH_szRoute);

#ifdef _cplusplus

}

#endif