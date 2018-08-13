#ifndef INFERENCEPROCEDURE_H
#define INFERENCEPROCEDURE_H

#include <QString>
#include "proof.h"

class InferenceProcedure
{
public:
    virtual QString name() const = 0;
    virtual QString callCommand() const = 0;
};


#endif // INFERENCEPROCEDURE_H
