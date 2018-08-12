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
#include "pluginmanager.h"

class LogicalSystem;
class ProofAssistant;

class Theory
{
public:
    Theory(const LogicalSystem * const parentLogic);
    Theory(const LogicalSystem * const parentLogic,
           const QString &name,
           const QString &description,
           const QLinkedList<Formula> axioms,
           const QString &signaturePluginName,
           const QStringList &inferenceTacticsPluginsNameList,
           const QStringList &preProcessorPluginsNameList,
           const QStringList &postProcessorPluginsNameList);

    QLinkedList<Formula> getAxioms() const;

    const LogicalSystem *getParentLogic() const;
    void setParentLogic(const LogicalSystem * const value);

    const Signature *getSignature() const;

    Parser *getParser() const;

    QVector<const Proof *> findProofsWithConclusion(const QString &formula) const;
    QVector<const Proof *> findProofsWithPremise(const QString &formula) const;

    QVector<InferenceTactic *> getInferenceTactics() const;

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QStringList getInferenceTacticsPluginsNameList() const;

    QStringList getPreProcessorPluginsNameList() const;

    QStringList getPostProcessorPluginsNameList() const;

private:
    void serializePlugins(QDataStream &stream) const;
    void unserializePlugins(QDataStream &stream);

    void loadPlugins();

    const LogicalSystem *parentLogic;

    QString name;
    QString description;
    unique_ptr<Parser> parser;
    QLinkedList<Formula> axioms; //Linked list because there will be pointers pointing to axioms!
    QString signaturePluginName; //FIXME Move this to the logical system!
    QStringList inferenceTacticsPluginsNameList;
    QStringList preProcessorPluginsNameList;
    QStringList postProcessorPluginsNameList;

    //I'm using raw pointers here because QPluginLoader already deletes the plugin object when application terminates
    SignaturePlugin *signaturePlugin;
    QVector<InferenceTactic *> inferenceTactics;
    QVector<StringProcessorPlugin *> preProcessorPlugins;
    QVector<StringProcessorPlugin *> postProcessorPlugins;
    Formatter preFormatter;
    Formatter postFormatter;

    friend class ProofAssistant;
    friend QDataStream &operator <<(QDataStream &stream, const Theory &theory);
    friend QDataStream &operator >>(QDataStream &stream, Theory &theory);
};

QDataStream &operator <<(QDataStream &stream, const Theory &theory);
QDataStream &operator >>(QDataStream &stream, Theory &theory);

#endif // THEORY_H
