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



#endif // INFERENCERULE_H
