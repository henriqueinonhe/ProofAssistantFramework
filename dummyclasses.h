#ifndef DUMMYCLASSES_H
#define DUMMYCLASSES_H

#include "inferencerule.h"
#include "lineofproof.h"

class DummyInferenceRule : public InferenceRule
{


public:
    QString name() const
    {
        return "Dummy Inference Rule";
    }
    QString callCommand() const
    {
        return "Dummy Call Command";
    }

    // InferenceRule interface
public:
    LineOfProof apply(const Proof &proof, const QStringList &argumentList) const
    {

    }
};

#endif // DUMMYCLASSES_H
