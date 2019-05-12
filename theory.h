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


class LogicalSystem;
class ProofAssistant;

class Theory
{
public:
    Theory(const LogicalSystem * const parentLogic);
    Theory(const LogicalSystem * const parentLogic,
           const QString &name,
           const QString &description,
           SignaturePlugin * const signaturePlugin,
           const QLinkedList<Formula> &axioms);
    Theory(const LogicalSystem * const parentLogic,
           QDataStream &stream,
           SignaturePlugin * const signaturePlugin,
           const QVector<InferenceTactic *> &inferenceTactics,
           const QVector<StringProcessorPlugin *> &preProcessors,
           const QVector<StringProcessorPlugin *> &postProcessors);

    const LogicalSystem *getParentLogic() const;
    void setParentLogic(const LogicalSystem * const value);

    QVector<const Proof *> findProofsWithConclusion(const QString &formula) const;
    QVector<const Proof *> findProofsWithPremise(const QString &formula) const;

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    const Signature *getSignature() const;
    SignaturePlugin *getSignaturePlugin();
    void setSignaturePlugin(SignaturePlugin * const value);

    QLinkedList<Formula> getAxioms() const;
    void setAxioms(const QLinkedList<Formula> &value);

    QVector<InferenceTactic *> getInferenceTactics() const;
    void setInferenceTactics(const QVector<InferenceTactic *> &value);

    QVector<StringProcessorPlugin *> getPreProcessors() const;
    void setPreProcessors(const QVector<StringProcessorPlugin *> &value);

    QVector<StringProcessorPlugin *> getPostProcessors() const;
    void setPostProcessors(const QVector<StringProcessorPlugin *> &value);



private:
    void serializePlugins(QDataStream &stream) const;
    void unserializePlugins(QDataStream &stream);

//    void loadPlugins();

    const LogicalSystem *parentLogic;

    QString name;
    QString description;
    unique_ptr<Parser> parser;
    SignaturePlugin *signaturePlugin;
    QLinkedList<Formula> axioms; //Linked list because there will be pointers pointing to axioms!

    //I'm using raw pointers here because QPluginLoader already deletes the plugin object when application terminates
    QVector<InferenceTactic *> inferenceTactics;
    QVector<StringProcessorPlugin *> preProcessors;
    QVector<StringProcessorPlugin *> postProcessors;
    Formatter preFormatter;
    Formatter postFormatter;

    friend class ProofAssistant;
    friend QDataStream &operator <<(QDataStream &stream, const Theory &theory);
   // friend QDataStream &operator >>(QDataStream &stream, Theory &theory);
};

QDataStream &operator <<(QDataStream &stream, const Theory &theory);
//QDataStream &operator >>(QDataStream &stream, Theory &theory);

#endif // THEORY_H
