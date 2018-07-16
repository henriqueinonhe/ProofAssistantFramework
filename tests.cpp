#include "catch.hpp"
#include "tree.h"
#include "type.h"
#include "logicalsystem.h"

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

    logicalSystem.setInferenceRulesPluginsDirPath("C:/Users/Henrique/Documents/Qt Projects/ProofAssistantFramework/plugins/InferenceRules");
    logicalSystem.addInferenceRulePluginName("LogosClassicalAndElimination.dll");

    CHECK_NOTHROW(logicalSystem.loadInferenceRules());

    CHECK(logicalSystem.getInferenceRules()[0]->name() == "And Elimination");
    CHECK(logicalSystem.getInferenceRules()[0]->callCommand() == "AndE");
    CHECK(logicalSystem.getInferenceRules()[0]->version() == 0);
}



//TEST_CASE("Dirty Fix")
//{
//    DirtyFix::fix();
//}
