#ifndef THEORYBUILDER_H
#define THEORYBUILDER_H

#include "theory.h"
#include "pluginmanager.h"
#include "pluginmanager.h"

typedef PluginWrapper<SignaturePlugin> SignaturePluginWrapper;

class TheoryBuilder
{
public:
    TheoryBuilder(LogicalSystem *parentLogic,
                  const QString &name,
                  const QString &description);

    Theory build();

    QString getName() const;
    QString getDescription() const;
    Signature *getSignature();

    void addAxiom(const QString &axiom);
    void removeAxiom(const QString &axiom);

protected:
    LogicalSystem *parentLogic;
    QString name;
    QString description;
    SignaturePluginWrapper signaturePlugin;
    unique_ptr<Parser> parser;
    QLinkedList<Formula> axioms;
private:
    void checkAxiomCollision(const Formula &newAxiom);
};

#endif // THEORYBUILDER_H
