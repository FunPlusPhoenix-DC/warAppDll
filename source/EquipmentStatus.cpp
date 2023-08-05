#include "EquipmentStatus.h"

#include "LogRecord.h"

void EquipmentProperties::SetEquipmentImgPath(const char * szPath)
{
    char szCurrentImgPath[MAX_PATH]{0};

    DWORD dwCurrentPath = sizeof(szCurrentImgPath);

    char* p_szCurrentImgPath = GetEquipmentImgPath();

    if(strcmp(p_szCurrentImgPath,szPath)){
        sprintf(p_PATH_EquipmentImg,"%s",szPath);
    }
}

char * EquipmentProperties::GetEquipmentImgPath()
{
    return this->p_PATH_EquipmentImg;
}

void EquipmentProperties::SetEquipmentName(const char * szName)
{
    if (strcmp(szName,p_szEquipmentName))
    {
        sprintf(this->p_szEquipmentName,"%s",szName);
    }    
}

char * EquipmentProperties::GetEquipmentName()
{
    return this->p_szEquipmentName;
}

EquipmentProperties::EquipmentProperties(){
    lpEquipmentStruct = new EquipmentStruct;

    lpEquipmentExtraAbility = new EquipmentExtraAbility;

    ::memset(lpEquipmentStruct,0,sizeof(EquipmentStruct));

    ::memset(lpEquipmentExtraAbility,0,sizeof(EquipmentExtraAbility));
}

EquipmentProperties::~EquipmentProperties(){
    delete[] lpEquipmentStruct;

    lpEquipmentStruct = NULL;

    delete[] lpEquipmentExtraAbility;

    lpEquipmentExtraAbility = NULL;

}