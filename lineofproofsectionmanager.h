#ifndef LINEOFPROOFSECTIONMANAGER_H
#define LINEOFPROOFSECTIONMANAGER_H

#include "lineofproofsection.h"
#include "tree.h"
#include <QDataStream>

class LineOfProofSectionManager
{
public:
    LineOfProofSectionManager();

    void addSection(const LineOfProofSection &section);
    LineOfProofSection getSection(const unsigned int beginIndex, const unsigned int endIndex) const;

private:
    void testForSiblingsIndexesCross(const LineOfProofSection &section, const unsigned int currentNodeIndex, TreeIterator<LineOfProofSection> iter);

    Tree<LineOfProofSection> sections;

    friend QDataStream &operator <<(QDataStream &stream, const LineOfProofSectionManager &sectionManager);
    friend QDataStream &operator >>(QDataStream &stream, LineOfProofSectionManager &sectionManager);
};

QDataStream &operator <<(QDataStream &stream, const LineOfProofSectionManager &sectionManager);
QDataStream &operator >>(QDataStream &stream, LineOfProofSectionManager &sectionManager);

#endif // LINEOFPROOFSECTIONMANAGER_H
