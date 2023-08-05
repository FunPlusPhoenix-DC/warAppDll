#include "HeroStatus.h"

#include <stdio.h>

HeroMain::HeroMain(){
    lpMainProperties = new MainProperties;

    lpAbilityPoint = new AbilityPoint;

    lpNormalProperties = new NormalProperties;

    ::memset(lpMainProperties,0,sizeof(MainProperties));

    ::memset(lpAbilityPoint,0,sizeof(AbilityPoint));

    ::memset(lpNormalProperties,0,sizeof(NormalProperties));
}

HeroMain::~HeroMain(){
    delete[] lpMainProperties;
    
    lpMainProperties = NULL;

    delete[] lpAbilityPoint;

    lpAbilityPoint = NULL;

    delete[] lpNormalProperties;

    lpNormalProperties = NULL;
    
}

char* HeroMain::GetName(){
    return this->p_szHeroName;
}

void HeroMain::SetName(const char* szHeroName){
    sprintf(this->p_szHeroName,"%s",szHeroName);
    return;
}

void HeroMain::SetHeroImgPath(const char* szImgPath){
    sprintf(this->p_PATH_HeroImg,szImgPath);
    return;
}

char* HeroMain::GetHeroImgPath(){
    return this->p_PATH_HeroImg;
}