#include "LogRecord.h"

#include <string>

extern char p_szDefaultPath[MAX_PATH]{0};

extern HANDLE hLogFile = INVALID_HANDLE_VALUE;

extern HANDLE hFileLastPointer = INVALID_HANDLE_VALUE;

int WARAPPDLL_API __stdcall InitLogger(char* p_PATH_szRoute){
    if(p_szDefaultPath == NULL){
        GetCurrentDirectoryA(NULL,p_szDefaultPath);

        sprintf(p_szDefaultPath+strlen(p_szDefaultPath),"\\Log");

        CreateDirectoryA(p_szDefaultPath,NULL);        

        SYSTEMTIME st;

        GetLocalTime(&st);

        sprintf(p_szDefaultPath+strlen(p_szDefaultPath),"\\log%2d%2d",st.wMonth,st.wDay);

        hLogFile = CreateFileA(p_szDefaultPath,
                                GENERIC_WRITE|GENERIC_READ,
                                0,
                                NULL,
                                NULL,
                                OPEN_ALWAYS,
                                NULL);
        
        if (hLogFile != INVALID_HANDLE_VALUE)
        {
            SetFilePointer(hFileLastPointer,0,NULL,FILE_END);

            return 0;
        }
        else
            return -1;        
    }
    SetFilePointer(hFileLastPointer,0,NULL,FILE_END);
    return 0;
}

int WARAPPDLL_API __stdcall ExecuteLogger(std::string& strContent){
    SYSTEMTIME st;

    GetLocalTime(&st);

    if (hLogFile && hFileLastPointer)
    {

        std::string strOutput;

        strOutput += std::to_string(st.wHour);

        strOutput.append(std::string(":") + std::to_string(st.wMinute));

        strOutput.append(std::string(":") + std::to_string(st.wSecond));

        strOutput.append("-->");

        strOutput += strContent.substr(0);

        strOutput.push_back('\n');

        const char* p_szLogContent = strOutput.c_str();

        DWORD dwSize = 0;

        bool bWriteStatus = WriteFile(hFileLastPointer,
                    p_szLogContent,
                    dwSize,
                    &dwSize,
                    NULL);
        
        SetFilePointer(hLogFile,0,NULL,FILE_END);

        return 0;
    }

    return -1;
}