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
typedef PluginWrapper<InferenceTactic> InferenceTacticPlugin;

class LogicalSystem;
class ProofAssistant;

class Theory
{
public:
    Theory(const LogicalSystem * const parentLogic, QDataStream &stream);

    const LogicalSystem *getParentLogic() const;

    QVector<const Proof *> findProofsWithConclusion(const QString &formula) const;
    QVector<const Proof *> findProofsWithPremise(const QString &formula) const;

    QString getName() const;
    QString getDescription() const;
    Signature *getSignature();
    QLinkedList<Formula> getAxioms() const;

    QVector<InferenceTacticPlugin> getInferenceTactics() const;

    QVector<StringProcessorPlugin *> getPreProcessors() const;
    void setPreProcessors(const QVector<StringProcessorPlugin *> &value);

    QVector<StringProcessorPlugin *> getPostProcessors() const;
    void setPostProcessors(const QVector<StringProcessorPlugin *> &value);

    QString getSignaturePluginName() const;
    void setSignaturePluginName(const QString &value);

protected:
    Theory(const LogicalSystem * const parentLogic);
    Theory(const LogicalSystem * const parentLogic,
           const QString &name,
           const QString &description,
           const QLinkedList<Formula> &axioms);

    void serializePlugins(QDataStream &stream) const;
    void unserializePlugins(QDataStream &stream);

    void loadSignaturePlugin();
//    void loadPlugins();

    void setName(const QString &value);
    void setDescription(const QString &value);
    void setAxioms(const QLinkedList<Formula> &value);

    const LogicalSystem *parentLogic;

    QString name;
    QString description;
    unique_ptr<Parser> parser;
    SignaturePluginWrapper signaturePlugin;
    QLinkedList<Formula> axioms; //Linked list because there will be pointers pointing to axioms!

    //I'm using raw pointers here because QPluginLoader already deletes the plugin object when application terminates
    QVector<InferenceTacticPlugin> inferenceTactics;
    QVector<StringProcessorPlugin *> preProcessors;
    QVector<StringProcessorPlugin *> postProcessors;
    Formatter preFormatter;
    Formatter postFormatter;

    friend class ProofAssistant;
    friend class TheoryBuilder;
    friend class ProgramManager;
    friend QDataStream &operator <<(QDataStream &stream, const Theory &theory);
   // friend QDataStream &operator >>(QDataStream &stream, Theory &theory);
};

QDataStream &operator <<(QDataStream &stream, const Theory &theory);
//QDataStream &operator >>(QDataStream &stream, Theory &theory);

#endif // THEORY_H
