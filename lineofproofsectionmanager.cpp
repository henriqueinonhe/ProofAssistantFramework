#include "lineofproofsectionmanager.h"

LineOfProofSectionManager::LineOfProofSectionManager()
{

}

void LineOfProofSectionManager::testForSiblingsIndexesCross(const LineOfProofSection &section, const unsigned int currentNodeIndex, TreeIterator<LineOfProofSection> iter)
{
    iter.goToParent();
    const unsigned int currentNodeAlreadyCheckedCompensation = 1;
    for(unsigned int index = currentNodeIndex + currentNodeAlreadyCheckedCompensation; index < iter->getChildrenNumber(); index++)
    {
        iter.goToChild(index);
        if(section.indexesCross(iter->getObj()))
        {
            throw std::invalid_argument("");
        }
        iter.goToParent();
    }
}

void LineOfProofSectionManager::addSection(const LineOfProofSection &section)
{
    //NOTE Maybe this needs to be better explained!
    //It is not trivial!

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
            testForSiblingsIndexesCross(section, currentNodeIndex, iter);
            iter->insertParent(section);
            return;
        }
        else if(section.indexesCross(currentNodeSection))
        {
            throw std::invalid_argument("Sections indexes cross!");
        }
        else
        {
            //Test next sibling
            iter.goToParent();
            currentNodeIndex++;
        }
    }
}

LineOfProofSection LineOfProofSectionManager::getSection(const unsigned int beginIndex, const unsigned int endIndex) const
{
    //TODO
    //The searching method is really close to the addSection method
    //I do not need this now, so I will wait till this is necessary!
}
