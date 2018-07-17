#ifndef INFERENCERULE_H
#define INFERENCERULE_H

#include <QString>
#include "proof.h"
#include "inferenceprocedure.h"

class InferenceRule : virtual public InferenceProcedure
{
public:
    virtual void apply(Proof &proof, const QStringList &argumentList) = 0;
};

Q_DECLARE_INTERFACE(InferenceRule, "InferenceRule")

#endif // INFERENCERULE_H
