#ifndef THEORYBUILDER_H
#define THEORYBUILDER_H

#include "theory.h"
#include "pluginmanager.h"
#include "pluginmanager.h"

typedef PluginWrapper<SignaturePlugin> SignaturePluginWrapper;

class TheoryBuilder
{
public:
    TheoryBuilder(const LogicalSystem *parentLogic);
    TheoryBuilder(const LogicalSystem *parentLogic,
                  const QString &name,
                  const QString &description);

    Theory build() const;

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    Signature *getSignature();

    void addAxiom(const QString &axiom);
    void removeAxiom(const QString &axiom);

protected:
    const LogicalSystem *parentLogic;
    QString name;
    QString description;
    SignaturePluginWrapper signaturePlugin;
    unique_ptr<Parser> parser;
    QLinkedList<Formula> axioms;

private:
    void loadSignaturePlugin();
    void checkAxiomCollision(const Formula &newAxiom);
};

#endif // THEORYBUILDER_H
