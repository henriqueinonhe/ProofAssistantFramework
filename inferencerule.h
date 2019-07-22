#ifndef INFERENCERULE_H
#define INFERENCERULE_H

#include "inferenceprocedure.h"

class Proof;
class LineOfProof;
class QStringList;
class Parser;

namespace std
{
    template <class> class shared_ptr;
}

class InferenceRule : public InferenceProcedure
{
public:
    virtual std::shared_ptr<LineOfProof> apply(const Parser &parser, Proof &proof, const QStringList &argumentList) const = 0;

    virtual ~InferenceRule() = 0;

};



#endif // INFERENCERULE_H
