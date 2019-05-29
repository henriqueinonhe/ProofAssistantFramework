#ifndef INFERENCERULE_H
#define INFERENCERULE_H

#include "inferenceprocedure.h"

class Proof;
class LineOfProof;
class QStringList;
class Parser;

class InferenceRule : public InferenceProcedure
{
public:
    virtual LineOfProof apply(const Parser &parser, const Proof &proof, const QStringList &argumentList) const = 0;

    virtual ~InferenceRule() = 0;

};



#endif // INFERENCERULE_H
