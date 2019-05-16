#ifndef INFERENCERULE_H
#define INFERENCERULE_H

#include "inferenceprocedure.h"

class Proof;
class LineOfProof;
class QStringList;

class InferenceRule : public InferenceProcedure
{
public:
    virtual LineOfProof apply(const Proof &proof, const QStringList &argumentList) const = 0;

};

Q_DECLARE_INTERFACE(InferenceRule, "InferenceRule")

#endif // INFERENCERULE_H
