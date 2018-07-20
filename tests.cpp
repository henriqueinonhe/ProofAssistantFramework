#include "catch.hpp"
#include "tree.h"
#include "type.h"
#include "logicalsystem.h"
#include "tablesignature.h"
#include "dirtyfix.h"
#include "lineofproofsection.h"
#include "lineofproofsectionmanager.h"
#include "storagemanager.h"
#include "programmanager.h"

TEST_CASE("Trees")
{
    SECTION("Trees Nodes methods work")
    {
        Tree<QString> tree;
        TreeIterator<QString> iter(&tree);

        CHECK(iter->coordinatesToString() == QString("()"));
        CHECK(iter->getHeight() == 0);
        CHECK(iter->isRoot());

        iter->appendChild("Hugabuga");
        iter.goToChild(0);

        CHECK(iter->coordinatesToString() == QString("(0)"));
        CHECK(iter->getHeight() == 1);

        iter.goToParent();

        CHECK(iter->coordinatesToString() == QString("()"));
        CHECK(iter->getHeight() == 0);

        iter->appendChild("bagabagabgab");
        iter.goToChild(1);

        CHECK(iter->coordinatesToString() == QString("(1)"));
        CHECK(iter->getHeight() == 1);

        iter->appendChild("heuase");
        iter.goToChild(0);

        CHECK(iter->coordinatesToString() == QString("(1,0)"));
        CHECK(iter->getHeight() == 2);

        iter.goToRoot();

        CHECK(iter->coordinatesToString() == QString("()"));
        CHECK(iter->isRoot());
    }

    SECTION("Tree methods and Tree Height")
    {
        Tree<QString> tree;
        TreeIterator<QString> iter(&tree);

        CHECK(iter.getTree().getHeight() == 0);

        iter->appendChild("xolob");

        CHECK(iter.getTree().getHeight() == 1);

        iter.goToChild(0);

        iter->appendChild("Sejiajse");

        CHECK(iter.getTree().getHeight() == 2);

        iter.goToParent();

        iter->appendChild("AJSWDUAShe");

        CHECK(iter.getTree().getHeight() == 2);
    }

    SECTION("Tree Iterator Paths")
    {
        Tree<QString> tree;
        TreeIterator<QString> iter(&tree);

        iter->appendChild("Xuleebi");
        iter->appendChild("ASKdas");

        iter.goToChild(1);

        iter->appendChild("Abacateiro");
        iter->appendChild("as asd 9 r4ja 09* 84~~çaç´a; das");

        iter.goToChild(0);

        iter->appendChild("test");
        iter->appendChild("wow");

        iter.goToRoot();
        iter.travelPath("(0)");
        CHECK(iter->coordinatesToString() == QString("(0)"));

        iter.goToRoot();
        iter.travelPath("(1)");
        CHECK(iter->coordinatesToString() == QString("(1)"));

        iter.goToRoot();
        iter.travelPath("(1,0)");
        CHECK(iter->coordinatesToString() == QString("(1,0)"));

        iter.goToRoot();
        iter.travelPath("(1,1)");
        CHECK(iter->coordinatesToString() == QString("(1,1)"));

        iter.goToRoot();
        iter.travelPath("(1,0,0)");
        CHECK(iter->coordinatesToString() == QString("(1,0,0)"));

        iter.goToRoot();
        iter.travelPath("(1,0,1)");
        CHECK(iter->coordinatesToString() == QString("(1,0,1)"));

        CHECK_THROWS(iter.travelPath("(0,0,)"));
        CHECK_THROWS(iter.travelPath("(00,)"));
        CHECK_THROWS(iter.travelPath("(0,0,)2"));
        CHECK_THROWS(iter.travelPath("(0,0,0"));
        CHECK_THROWS(iter.travelPath("0,0"));
    }
}

TEST_CASE("Logical Systems")
{
    LogicalSystem logicalSystem;

    logicalSystem.setWffType(Type("o"));

    logicalSystem.setInferenceRulesPluginsDirPath("C:/Users/Henrique/Documents/Qt Projects/ProofAssistantFramework/plugins/InferenceRules");
    logicalSystem.addInferenceRulePluginName("LogosClassicalAndElimination");

    CHECK_NOTHROW(logicalSystem.loadInferenceRules());

    CHECK(logicalSystem.getInferenceRules()[0]->name() == "And Elimination");
    CHECK(logicalSystem.getInferenceRules()[0]->callCommand() == "AndE");
    CHECK(logicalSystem.getInferenceRules()[0]->version() == 0);
    CHECK(logicalSystem.getInferenceRules()[0]->id() == "Logos Classical And Elimination");
}

TEST_CASE("Theories")
{
    LogicalSystem logicalSystem;
    logicalSystem.setWffType(Type("o"));

    Theory theory(&logicalSystem);

    CHECK_THROWS(theory.addAxiom("P"));

    theory.setParentLogic(&logicalSystem);

    CHECK_THROWS(theory.addAxiom("P"));

    TableSignature *signature = new TableSignature;

    signature->addToken(CoreToken("P", Type("o")));
    signature->addToken(CoreToken("&", Type("[o,o]->o")));
    signature->addToken(CoreToken("~", Type("o->o")));

    theory.setSignature(signature);

    CHECK_NOTHROW(theory.addAxiom("P"));
    CHECK_NOTHROW(theory.addAxiom("(& P P)"));
    CHECK_NOTHROW(theory.removeAxiom("P"));
    CHECK_NOTHROW(theory.removeAxiom("(& P P)"));

    CHECK(theory.getAxioms().isEmpty());
}

TEST_CASE("Line of Proof Section")
{
    LineOfProofSection section1(4, 12, ""), section2(2, 14, ""), section3(3, 11, "");

    CHECK_THROWS(LineOfProofSection(3, 2, ""));
    CHECK_THROWS(LineOfProofSection(234, 123, ""));
    CHECK_THROWS(LineOfProofSection(43, 23, ""));

    CHECK(section1.indexesAreEqual(section1));
    CHECK(section2.indexesAreEqual(section2));
    CHECK(section3.indexesAreEqual(section3));
    CHECK(!section1.indexesAreEqual(section2));
    CHECK(!section1.indexesAreEqual(section3));

    CHECK(section1.indexesAreProperlyContained(section2));
    CHECK(section2.indexesContainProperly(section1));
    CHECK(!section2.indexesAreProperlyContained(section1));
    CHECK(!section1.indexesContainProperly(section2));

    CHECK(section1.indexesCross(section3));
    CHECK(section3.indexesCross(section1));
    CHECK(LineOfProofSection(1, 3, "").indexesCross(LineOfProofSection(3, 5, "")));
    CHECK(LineOfProofSection(3, 5, "").indexesCross(LineOfProofSection(1, 3, "")));
    CHECK(!section1.indexesCross(section2));
    CHECK(!section2.indexesCross(section1));
}

TEST_CASE("Line of Proof Section Manager")
{
    LineOfProofSectionManager sectionManager;

    CHECK_NOTHROW(sectionManager.addSection(LineOfProofSection(1, 6, "")));
    CHECK_NOTHROW(sectionManager.addSection(LineOfProofSection(8, 9, "")));
    CHECK_NOTHROW(sectionManager.addSection(LineOfProofSection(3, 4, "")));
    CHECK_NOTHROW(sectionManager.addSection(LineOfProofSection(7, 9, "")));
    CHECK_NOTHROW(sectionManager.addSection(LineOfProofSection(5, 6, "")));
    CHECK_NOTHROW(sectionManager.addSection(LineOfProofSection(2, 4, "")));

    //Fail due to equal indexes
    CHECK_THROWS(sectionManager.addSection(LineOfProofSection(1, 6, "")));
    CHECK_THROWS(sectionManager.addSection(LineOfProofSection(3, 4, "")));

    //Fail due to crossing indexes
    CHECK_THROWS(sectionManager.addSection(LineOfProofSection(1, 7, "")));
    CHECK_THROWS(sectionManager.addSection(LineOfProofSection(2, 7, "")));
}

TEST_CASE("Program Manager and Storage Manager")
{
    StorageManager::setRootPath("C:/Users/Henrique/Documents/Qt Projects/ProofAssistantFramework");

    CHECK(StorageManager::getRootPath() == "C:/Users/Henrique/Documents/Qt Projects/ProofAssistantFramework");

    ProgramManager manager;

    QStringList inferenceRulesNameList;
    inferenceRulesNameList << "rule1" << "rule2" << "rule3";

    CHECK_NOTHROW(manager.createLogicalSystem("Pure First Order Logic",
                                              "First order logic without equality or functions.",
                                              inferenceRulesNameList,
                                              Type("o")));

    CHECK_NOTHROW(manager.loadLogicalSystem("Pure First Order Logic"));
    CHECK(manager.getActiveLogicalSystem()->getName() == "Pure First Order Logic");
    CHECK(manager.getActiveLogicalSystem()->getDescription() == "First order logic without equality or functions.");
    CHECK(manager.getActiveLogicalSystem()->getInferenceRulesPluginsNames() == inferenceRulesNameList);
    CHECK(manager.getActiveLogicalSystem()->getWffType() == Type("o"));

    CHECK_THROWS(manager.createLogicalSystem("Pure First Order Logic",
                                             "First order logic without equality or functions.",
                                             inferenceRulesNameList,
                                             Type("o")));

    CHECK_NOTHROW(manager.removeLogicalSystem("Pure First Order Logic"));
}

TEST_CASE("Dirty Fix")
{
    DirtyFix::fix();
}
