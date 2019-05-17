#ifndef INFERENCEPROCEDURE_H
#define INFERENCEPROCEDURE_H

#include <QString>

class InferenceProcedure
{
public:
    virtual QString name() const = 0;
    virtual QString callCommand() const = 0;

    virtual ~InferenceProcedure() = 0;

};

Q_DECLARE_INTERFACE(InferenceProcedure, "InferenceProcedure")

#endif // INFERENCEPROCEDURE_H
