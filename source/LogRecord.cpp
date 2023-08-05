#include "LogRecord.h"

#include <string>

extern char p_szDefaultPath[MAX_PATH];

HANDLE hLogFile;

HANDLE hFileLastPointer;

int WARAPPDLL_API __stdcall InitLogger(char* p_PATH_szRoute){

    char* p_szDefaultPath = new char[MAX_PATH];
    
    if(!p_szDefaultPath){
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
            hFileLastPointer = hLogFile;

            SetFilePointer(hFileLastPointer,0,NULL,FILE_END);

            return 0;
        }
        else
        {
            dwErrorState = LOGERROR_CANNOTSETLOGFILE;

            return -1;
        }                    
    }
    try
    {
        /* code */
        SetFilePointer(hFileLastPointer,0,NULL,FILE_END);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }    

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

        if (!bWriteStatus)
        {
            dwErrorState = LOGERROR_WRITEFILEERROR;

            return -1;
        }
        
        
        SetFilePointer(hFileLastPointer,0,NULL,FILE_END);

        return 0;
    }
    dwErrorState = LOGERROR_FILEPOINTERISNULL;

    return -1;
}

long WARAPPDLL_API __stdcall GetExternErrorCode(){
    return dwErrorState;
}

void WARAPPDLL_API __stdcall SetExternErrorCode(long& lErrorCode){
    dwErrorState = lErrorCode;
    return;
}