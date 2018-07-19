#include "lineofproofsectionmanager.h"

LineOfProofSectionManager::LineOfProofSectionManager()
{

}

void LineOfProofSectionManager::addSection(const LineOfProofSection &section)
{
    TreeIterator<LineOfProofSection> iter(&sections);

    unsigned int currentNodeIndex = 0;

    while(true)
    {
        if(currentNodeIndex >= iter->getChildrenNumber())
        {
            iter->appendChild(section);
            return;
        }

        iter.goToChild(currentNodeIndex);

        const LineOfProofSection &currentNodeSection = iter->getObj();
        if(section.indexesAreEqual(currentNodeSection))
        {
            throw std::invalid_argument("There is already a section with these indexes!");
        }
        else if(section.indexesAreProperlyContained(currentNodeSection))
        {
            if(iter->isChildless())
            {
                iter->appendChild(section);
                return;
            }
            else
            {
                currentNodeIndex = 0;
                continue;
            }
        }
        else if(section.indexesContainProperly(currentNodeSection))
        {
            iter.goToParent();
            for(unsigned int index = currentNodeIndex; index < iter->getChildrenNumber(); index++)
            {
                iter.goToChild(index);
                if(section.indexesCross(iter->getObj()))
                {
                    throw std::invalid_argument("");
                }
                iter.goToParent();
            }
            iter.goToChild(currentNodeIndex);
            iter->insertChildVertically(section);
            return;
        }
        else if(section.indexesCross(currentNodeSection))
        {
            throw std::invalid_argument("Sections indexes cross!");
        }
        else
        {
            iter.goToParent();
            currentNodeIndex++;
        }
    }
}
