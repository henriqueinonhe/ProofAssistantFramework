#ifndef LINEOFPROOFSECTION_H
#define LINEOFPROOFSECTION_H

#include <QString>

class LineOfProofSection
{
public:
    LineOfProofSection();

    LineOfProofSection(const unsigned int beginIndex,
                       const unsigned int endIndex,
                       const QString &label,
                       const bool collapsed = true);

    LineOfProofSection(QDataStream &stream);

    void setIndexes(const unsigned int beginIndex, const unsigned int endIndex);
    unsigned int getBeginIndex() const;
    unsigned int getEndIndex() const;

    const QString &getLabel() const;
    void setLabel(const QString &value);

    bool getCollapsed() const;
    void setCollapsed(bool value);

    bool indexesAreEqual(const LineOfProofSection &other) const;
    bool indexesAreProperlyContained(const LineOfProofSection &other) const;
    bool indexesContainProperly(const LineOfProofSection &other) const;
    bool indexesCross(const LineOfProofSection &other) const;

private:
    void checkIndexesOverlap(const unsigned int beginIndex, const unsigned int endIndex) const;

    unsigned int beginIndex;
    unsigned int endIndex;
    QString label;
    bool collapsed;

    friend QDataStream &operator <<(QDataStream &stream, const LineOfProofSection &section);
    friend QDataStream &operator >>(QDataStream &stream, LineOfProofSection &section);
};

QDataStream &operator <<(QDataStream &stream, const LineOfProofSection &section);
QDataStream &operator >>(QDataStream &stream, LineOfProofSection &section);

#endif // LINEOFPROOFSECTION_H
