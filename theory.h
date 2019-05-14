#ifndef THEORY_H
#define THEORY_H

#include "formula.h"
#include <QString>
#include "proof.h"
#include "parser.h"
#include "inferencetactic.h"
#include "signatureplugin.h"
#include "stringprocessorplugin.h"
#include "formatter.h"
#include <QDataStream>
#include "pluginwrapper.h"

typedef PluginWrapper<SignaturePlugin> SignaturePluginWrapper;
typedef PluginWrapper<InferenceTactic> InferenceTacticPluginWrapper;
typedef PluginWrapper<StringProcessorPlugin> StringProcessorPluginWrapper;
typedef PluginWrapper<StringProcessorPlugin> StringProcessorPluginWrapper;

class LogicalSystem;
class ProofAssistant;

class Theory
{
public:
    Theory(const LogicalSystem *logicalSystem, QDataStream &stream);

    const LogicalSystem *getParentLogic() const;

    QString getName() const;
    QString getDescription() const;
    Signature *getSignature();
    QLinkedList<Formula> getAxioms() const;

    void addInferenceTactic(const QString &pluginName);
    void removeInferenceTactic(const QString &pluginName);
    QVector<InferenceTacticPluginWrapper> getInferenceTactics() const;

    void addPreProcessor(const QString &pluginName);
    void removePreProcessor(const QString &pluginName);
    QVector<StringProcessorPluginWrapper> getPreProcessors() const;

    void addPostProcessor(const QString &pluginName);
    void removePostProcessor(const QString &pluginName);
    QVector<StringProcessorPluginWrapper> getPostProcessors() const;

    QVector<const Proof *> findProofsWithConclusion(const QString &formula) const;
    QVector<const Proof *> findProofsWithPremise(const QString &formula) const;

protected:
    Theory(const LogicalSystem * const parentLogic);
    Theory(const LogicalSystem * const parentLogic, const QString &name, const QString &description, const QLinkedList<Formula> &axioms);

    void loadSignaturePlugin();

    const LogicalSystem *parentLogic;

    QString name;
    QString description;
    unique_ptr<Parser> parser;
    SignaturePluginWrapper signaturePlugin;
    QLinkedList<Formula> axioms; //Linked list because there will be pointers pointing to axioms!

    QVector<InferenceTacticPluginWrapper> inferenceTactics;
    QVector<StringProcessorPluginWrapper> preProcessors;
    QVector<StringProcessorPluginWrapper> postProcessors;
    Formatter preFormatter;
    Formatter postFormatter;

    friend class ProofAssistant;
    friend class TheoryBuilder;
    friend class ProgramManager;
    friend QDataStream &operator <<(QDataStream &stream, const Theory &theory);
    friend QDataStream &operator >>(QDataStream &stream, Theory &theory);
};

QDataStream &operator <<(QDataStream &stream, const Theory &theory);
QDataStream &operator >>(QDataStream &stream, Theory &theory);

#endif // THEORY_H
