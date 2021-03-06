#ifndef INFERENCETACTIC_H
#define INFERENCETACTIC_H

#include "inferenceprocedure.h"

class ProofAssistant;

class InferenceTactic : public InferenceProcedure
{
public:
    virtual void apply(const ProofAssistant * const assistant, const QStringList &argumentList) = 0;

    virtual ~InferenceTactic() = 0;

};

Q_DECLARE_INTERFACE(InferenceTactic, "InferenceTactic")

#endif // INFERENCETACTIC_H
