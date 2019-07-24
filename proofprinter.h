#ifndef PROOFPRINTER_H
#define PROOFPRINTER_H

class QDataStream;

class ProofPrinter
{
public:
    ProofPrinter() = default;
    ProofPrinter(QDataStream &);

protected:
    virtual void serialize(QDataStream &) const = 0;
    virtual void deserialize(QDataStream &) = 0;

    friend QDataStream &operator <<(QDataStream &, const ProofPrinter &);
    friend QDataStream &operator >>(QDataStream &, ProofPrinter &);
};
QDataStream &operator <<(QDataStream &, const ProofPrinter &);
QDataStream &operator >>(QDataStream &, ProofPrinter &);

#endif // PROOFPRINTER_H
