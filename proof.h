#ifndef PROOF_H
#define PROOF_H

#include "lineofproofsectionmanager.h"
#include "formula.h"

class Formula;
class ProofAssistant;
class QDataStream;
class LineOfProof;
class Justification;
template <class> class PluginFactoryInterface;

class Proof
{
public:
    Proof &operator =(const Proof&) = delete;
    Proof &operator =(Proof &&) = delete;
    ~Proof() noexcept = default;

    template<class ProofSubclass>
    static shared_ptr<Proof> createNewProof(const uint id,
                                            const QString &name,
                                            const QString &description,
                                            const QVector<Formula> &premises,
                                            const Formula &conclusion)
    {
        auto instance = shared_ptr<ProofSubclass>(new ProofSubclass(id,
                                                                    name,
                                                                    description,
                                                                    premises,
                                                                    conclusion));
        instance->insertPremisesAsLinesOfProof();
        instance->additionalSetup();
        return instance;
    }

    Proof(QDataStream &stream, Signature * const signature);

    bool isFinished() const;

    QString getName() const;
    void setName(const QString &value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QVector<Formula> getPremises() const;

    Formula getConclusion() const;

    QVector<const LineOfProof *> getLinesOfProof() const;
    const LineOfProof &getLineOfProof(const int lineNumber) const;
    void setComment(const unsigned int lineNumber, const QString &comment);

    bool getLinkedWithAxioms() const;
    unsigned int getId() const;

protected:
    Proof() = default; //For plugin load testing purposes
    Proof(const Proof &) = default;
    Proof(Proof &&) = delete;

    Proof(const uint id,
          const QString &name,
          const QString &description,
          const QVector<Formula> &premises,
          const Formula &conclusion);

    virtual void serialize(QDataStream &stream) const;

private:
    void addLineOfProof(const shared_ptr<LineOfProof> &lineOfProof);
    void insertPremisesAsLinesOfProof();
    virtual void additionalSetup();
    virtual bool isFinishedAdditionalChecks() const;
    virtual shared_ptr<LineOfProof> createLineOfProof(const Formula &premiss, const Justification &justification) const;

    unsigned int id;
    QString name;
    QString description;
    QVector<Formula> premises;
    Formula conclusion;

protected:
    QVector<shared_ptr<LineOfProof>> linesOfProof;

private:
    LineOfProofSectionManager sectioning;
    bool linkedWithAxioms = false;

    friend class ProofAssistant;
    friend QDataStream &operator <<(QDataStream &stream, const Proof &proof);
    friend class PluginFactoryInterface<Proof>;
    friend class ProofTester;
};

QDataStream &operator <<(QDataStream &stream, const Proof &proof);

#endif // PROOF_H
