#include "lineofproofsection.h"
#include <QDataStream>
#include "qtclassesdeserialization.h"

LineOfProofSection::LineOfProofSection()
{

}

void LineOfProofSection::checkIndexesOverlap(const unsigned int beginIndex, const unsigned int endIndex) const
{
    if(beginIndex >=  endIndex)
    {
        throw std::invalid_argument("The begin index of the line of proof section must be less than"
                                    " the end index!");
    }
}

LineOfProofSection::LineOfProofSection::LineOfProofSection(const unsigned int beginIndex, const unsigned int endIndex, const QString &label, const bool collapsed) :
    beginIndex(beginIndex),
    endIndex(endIndex),
    label(label),
    collapsed(collapsed)
{
    checkIndexesOverlap(beginIndex, endIndex);
}

LineOfProofSection::LineOfProofSection(QDataStream &stream) :
    beginIndex(QtDeserialization::deserializeUInt(stream)),
    endIndex(QtDeserialization::deserializeUInt(stream)),
    label(QtDeserialization::deserializeQString(stream)),
    collapsed(QtDeserialization::deserializeBool(stream))
{

}

void LineOfProofSection::setIndexes(const unsigned int beginIndex, const unsigned int endIndex)
{
    checkIndexesOverlap(beginIndex, endIndex);

    this->beginIndex = beginIndex;
    this->endIndex = endIndex;
}

const QString &LineOfProofSection::getLabel() const
{
    return label;
}

void LineOfProofSection::setLabel(const QString &value)
{
    label = value;
}

bool LineOfProofSection::getCollapsed() const
{
    return collapsed;
}

void LineOfProofSection::setCollapsed(bool value)
{
    collapsed = value;
}

bool LineOfProofSection::indexesAreEqual(const LineOfProofSection &other) const
{
    return beginIndex == other.beginIndex && endIndex == other.endIndex;
}

bool LineOfProofSection::indexesAreProperlyContained(const LineOfProofSection &other) const
{
    return (beginIndex >= other.beginIndex && endIndex < other.endIndex) ||
           (beginIndex > other.beginIndex && endIndex <= other.endIndex);
}

bool LineOfProofSection::indexesContainProperly(const LineOfProofSection &other) const
{
    return (beginIndex <= other.beginIndex && endIndex > other.endIndex) ||
           (beginIndex < other.beginIndex && endIndex >= other.endIndex);
}

bool LineOfProofSection::indexesCross(const LineOfProofSection &other) const
{
    return (beginIndex < other.beginIndex &&
           endIndex >= other.beginIndex &&
           endIndex < other.endIndex) ||
           (beginIndex > other.beginIndex &&
            beginIndex <= other.endIndex &&
            endIndex > other.endIndex);
}

unsigned int LineOfProofSection::getEndIndex() const
{
    return endIndex;
}

unsigned int LineOfProofSection::getBeginIndex() const
{
    return beginIndex;
}


QDataStream &operator <<(QDataStream &stream, const LineOfProofSection &section)
{
    stream << section.beginIndex << section.endIndex << section.label << section.collapsed;
    return stream;
}

QDataStream &operator >>(QDataStream &stream, LineOfProofSection &section)
{
    stream >> section.beginIndex >> section.endIndex >> section.label >> section.collapsed;
    return stream;
}
