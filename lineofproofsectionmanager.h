﻿#ifndef LINEOFPROOFSECTIONMANAGER_H
#define LINEOFPROOFSECTIONMANAGER_H

#include "lineofproofsection.h"
#include "tree.h"

class LineOfProofSectionManager
{
public:
    LineOfProofSectionManager();

    void addSection(const LineOfProofSection &section);

    LineOfProofSection getSection(const unsigned int beginIndex, const unsigned int endIndex) const;

private:
    Tree<LineOfProofSection> sections;
};

#endif // LINEOFPROOFSECTIONMANAGER_H
