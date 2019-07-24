#include "proofprinter.h"


QDataStream &operator <<(QDataStream &stream, const ProofPrinter &printer)
{
    printer.serialize(stream);
    return stream;
}

QDataStream &operator >>(QDataStream &stream, ProofPrinter &printer)
{
    printer.deserialize(stream);
    return stream;
}
