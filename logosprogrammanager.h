#ifndef LOGOSPROGRAMMANAGER_H
#define LOGOSPROGRAMMANAGER_H

#include "programmanager.h"
#include "tablesignature.h"

class LogosProgramManager : public ProgramManager
{
public:
    LogosProgramManager();
    //Insert TableSignature specific control methods!

protected:
    TableSignature signature;
};

#endif // LOGOSPROGRAMMANAGER_H
