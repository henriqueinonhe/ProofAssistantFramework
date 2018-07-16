#ifndef INFERENCERULE_H
#define INFERENCERULE_H

#include <QString>
#include "proof.h"

class InferenceRule
{
public:
    InferenceRule();
    virtual void apply(Proof &proof, const QStringList &argumentList) = 0;
    virtual QString name() const = 0;
    virtual QString callCommand() const = 0;
};

Q_DECLARE_INTERFACE(InferenceRule, "InferenceRule")

#endif // INFERENCERULE_H
