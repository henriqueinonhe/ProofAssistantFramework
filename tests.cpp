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
#include "theorybuilder.h"
#include "coretoken.h"
#include "inferencerule.h"
#include "logicalsystemrecord.h"
#include "theoryrecord.h"
#include "dummyclasses.h"
#include <QBuffer>

TEST_CASE("Trees")
{
    Tree<QString> tree;
    TreeIterator<QString> iter(&tree);

    SECTION("Trees Nodes methods work")
    {
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

TEST_CASE("Logical System")
{
    QVector<shared_ptr<const InferenceRule>> vec;
    vec.push_back(make_shared<DummyInferenceRule>());

    LogicalSystem logicalSystem("Dummy Logical System",
                                "Lorem Ipsum",
                                vec,
                                Type("o"));

    CHECK(logicalSystem.getName() == "Dummy Logical System");
    CHECK(logicalSystem.getDescription() == "Lorem Ipsum");
    CHECK(logicalSystem.getInferenceRules()[0]->name() == "Dummy Inference Rule");
    CHECK(logicalSystem.getInferenceRules()[0]->callCommand() == "Dummy Call Command");
    CHECK(logicalSystem.getWffType() == Type("o"));

    //Serialization
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QDataStream stream(&buffer);

    stream << logicalSystem;

    buffer.close();
    buffer.open(QIODevice::ReadOnly);
    LogicalSystem logicalSystem2(stream, vec);

    CHECK(logicalSystem2.getName() == logicalSystem.getName());
    CHECK(logicalSystem2.getDescription() == logicalSystem.getDescription());
    CHECK(logicalSystem2.getInferenceRules()[0]->callCommand() == logicalSystem.getInferenceRules()[0]->callCommand());
    CHECK(logicalSystem2.getInferenceRules()[0]->name() == logicalSystem.getInferenceRules()[0]->name());
    CHECK(logicalSystem2.getWffType() == logicalSystem.getWffType());
}

TEST_CASE("Logical System Record")
{
    LogicalSystemRecord record("Dummy Logical System", "Lorem Ipsum");

    CHECK(record.getName() == "Dummy Logical System");
    CHECK(record.getDescription() == "Lorem Ipsum");

    //Serialization
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QDataStream stream(&buffer);

    stream << record;

    buffer.close();
    buffer.open(QIODevice::ReadOnly);
    LogicalSystemRecord record2;

    stream >> record2;

    CHECK(record2.getName() == "Dummy Logical System");
    CHECK(record2.getDescription() == "Lorem Ipsum");
}

//TEST_CASE("Theory")
//{
//    LogicalSystem logicalSystem("A", "A", QStringList(), "TableSignaturePlugin", Type("o"));
//    TheoryBuilder theoryBuilder(&logicalSystem, "Dummy Theory", "Lorem Ipsum");

//    Signature *signature = theoryBuilder.getSignature();
//    signature->addToken(CoreToken("P", Type("o")));
//    signature->addToken(CoreToken("~", Type("o->o")));

//    theoryBuilder.addAxiom("P");
//    theoryBuilder.addAxiom("(~ P)");
//    CHECK_THROWS(theoryBuilder.addAxiom("(~ P")); //Testing anti axiom collision

//    Theory theory = theoryBuilder.build();

//    CHECK_NOTHROW(theory.addInferenceTactic("DummyInferenceTacticPlugin"));
//    CHECK_THROWS(theory.addInferenceTactic("DummyInferenceTacticPlugin"));
//    CHECK_NOTHROW(theory.removeInferenceTactic("DummyInferenceTacticPlugin"));
//    CHECK(theory.getInferenceTactics().isEmpty());
//    CHECK_THROWS(theory.removeInferenceTactic("DummyInferenceTacticPlugin"));
//    CHECK_NOTHROW(theory.addInferenceTactic("DummyInferenceTacticPlugin"));

//    CHECK_NOTHROW(theory.addPreProcessor("DummyPreProcessorPlugin"));
//    CHECK_THROWS(theory.addPreProcessor("DummyPreProcessorPlugin"));
//    CHECK_NOTHROW(theory.removePreProcessor("DummyPreProcessorPlugin"));
//    CHECK(theory.getPreProcessors().isEmpty());
//    CHECK_THROWS(theory.removePreProcessor("DummyPreProcessorPlugin"));
//    CHECK_NOTHROW(theory.addPreProcessor("DummyPreProcessorPlugin"));

//    CHECK_NOTHROW(theory.addPostProcessor("DummyPostProcessorPlugin"));
//    CHECK_THROWS(theory.addPostProcessor("DummyPostProcessorPlugin"));
//    CHECK_NOTHROW(theory.removePostProcessor("DummyPostProcessorPlugin"));
//    CHECK(theory.getPostProcessors().isEmpty());
//    CHECK_THROWS(theory.removePostProcessor("DummyPostProcessorPlugin"));
//    CHECK_NOTHROW(theory.addPostProcessor("DummyPostProcessorPlugin"));

//    CHECK(theory.getName() == "Dummy Theory");
//    CHECK(theory.getDescription() == "Lorem Ipsum");
//    CHECK(theory.getAxioms().first().formattedString() == "P");
//    CHECK(theory.getAxioms().last().formattedString() == "(~ P)");
//    CHECK(theory.getInferenceTactics()[0]->name() == "Dummy Inference Rule");
//    CHECK(theory.getInferenceTactics()[0]->callCommand() == "DM");
//    CHECK(theory.getPreProcessors()[0]->toString() == "Dummy Pre Processor Plugin");
//    CHECK(theory.getPostProcessors()[0]->toString() == "Dummy Post Processor Plugin");

//    //Serialization
//    QBuffer buffer;
//    buffer.open(QIODevice::WriteOnly);
//    QDataStream stream(&buffer);
//    stream << theory;

//    buffer.close();
//    buffer.open(QIODevice::ReadOnly);
//    Theory theory2(&logicalSystem, stream);

//    CHECK(theory2.getName() == "Dummy Theory");
//    CHECK(theory2.getDescription() == "Lorem Ipsum");
//    CHECK(theory2.getAxioms().first().formattedString() == "P");
//    CHECK(theory2.getAxioms().last().formattedString() == "(~ P)");
//    CHECK(theory2.getInferenceTactics()[0]->name() == "Dummy Inference Rule");
//    CHECK(theory2.getInferenceTactics()[0]->callCommand() == "DM");
//    CHECK(theory2.getPreProcessors()[0]->toString() == "Dummy Pre Processor Plugin");
//    CHECK(theory2.getPostProcessors()[0]->toString() == "Dummy Post Processor Plugin");
//    CHECK(*theory2.getSignature()->getTokenPointer("P") == CoreToken("P", Type("o")));
//    //Maybe I should test the other members as well like the parser
//}

TEST_CASE("Theory Records")
{
    TheoryRecord record("Dummy Theory", "Lorem Ipsum");

    CHECK(record.getName() == "Dummy Theory");
    CHECK(record.getDescription() == "Lorem Ipsum");

    //Serialization
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QDataStream stream(&buffer);

    stream << record;

    buffer.close();
    buffer.open(QIODevice::ReadOnly);
    LogicalSystemRecord record2;

    stream >> record2;

    CHECK(record2.getName() == record.getName());
    CHECK(record2.getDescription() == record.getDescription());
}

//TEST_CASE("Plugins")
//{
//    //Signature Plugin
//    QPluginLoader loader("C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Signatures/TableSignaturePlugin.dll");
//    CHECK(loader.load());

//    SignaturePlugin *ptr = qobject_cast<SignaturePlugin *>(loader.instance());
//    ptr->addToken(CoreToken("Chabaduba", Type("i")));
//    CHECK(ptr->getTokenPointer("Chabaduba")->tokenClass() == "CoreToken");
//}

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


TEST_CASE("Storage Manager")
{
    StorageManager::setRootPath("C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox");

    CHECK(StorageManager::getRootPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox");
    CHECK(StorageManager::storageDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data");
    CHECK(StorageManager::logicalSystemsDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data/Logical Systems");
    CHECK(StorageManager::logicalSystemsRecordsPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data/Logical Systems/logicalsystemsrecords.dat");
    CHECK(StorageManager::logicalSystemDirPath("Dummy Logical System") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data/Logical Systems/Dummy Logical System");
    CHECK(StorageManager::logicalSystemDataFilePath("Dummy Logical System") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data/Logical Systems/Dummy Logical System/logicalsystem.dat");
    CHECK(StorageManager::theoriesDirPath("Dummy Logical System") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data/Logical Systems/Dummy Logical System/Theories");
    CHECK(StorageManager::theoriesRecordsPath("Dummy Logical System") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data/Logical Systems/Dummy Logical System/Theories/theoriesrecords.dat");
    CHECK(StorageManager::theoryDirPath("Dummy Logical System", "Dummy Theory") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data/Logical Systems/Dummy Logical System/Theories/Dummy Theory");
    CHECK(StorageManager::theoryDataFilePath("Dummy Logical System", "Dummy Theory") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data/Logical Systems/Dummy Logical System/Theories/Dummy Theory/theory.dat");
    CHECK(StorageManager::proofsDirPath("Dummy Logical System", "Dummy Theory") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data/Logical Systems/Dummy Logical System/Theories/Dummy Theory/Proofs");
    CHECK(StorageManager::proofsRecordsFilePath("Dummy Logical System", "Dummy Theory") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data/Logical Systems/Dummy Logical System/Theories/Dummy Theory/Proofs/proofsrecords.dat");
    CHECK(StorageManager::pluginsDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins");
    CHECK(StorageManager::signaturesPluginsDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Signatures");
    CHECK(StorageManager::inferenceRulesPluginsDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Inference Rules");
    CHECK(StorageManager::inferenceTacticsPluginsDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Inference Tactics");
    CHECK(StorageManager::preProcessorsPluginsDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Pre Processors");
    CHECK(StorageManager::postProcessorsPluginsDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Post Processors");
    CHECK(StorageManager::signaturePluginPath("DummySignaturePlugin") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Signatures/DummySignaturePlugin.dll");
    CHECK(StorageManager::inferenceRulePluginPath("DummyInferenceRule") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Inference Rules/DummyInferenceRule.dll");
    CHECK(StorageManager::inferenceTacticPluginPath("DummyInferenceTactic") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Inference Tactics/DummyInferenceTactic.dll");
    CHECK(StorageManager::preProcessorPluginPath("DummyPreProcessor") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Pre Processors/DummyPreProcessor.dll");
    CHECK(StorageManager::postProcessorPluginPath("DummyPostProcessor") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Post Processors/DummyPostProcessor.dll");
}

//TEST_CASE("Framework Integration")
//{
//    ProgramManager manager;

//    SECTION("Logical System")
//    {
//        CHECK(StorageManager::retrieveLogicalSystemsRecords().isEmpty());

//        //Create Logical System
//        QStringList inferenceRulesNamesList;
//        inferenceRulesNamesList << "LogosClassicAndElimination";
//        manager.createLogicalSystem("First Order Logic",
//                                    "Predicate Logic With Quantifiers",
//                                    "Table Signature",
//                                    inferenceRulesNamesList,
//                                    Type("o"));

//        const LogicalSystemRecord logicalSystemRecord = StorageManager::retrieveLogicalSystemsRecords().first();

//        CHECK(logicalSystemRecord.getName() == "First Order Logic");
//        CHECK(logicalSystemRecord.getDescription() == "Predicate Logic With Quantifiers");

//        //Load Logical System
//        manager.loadLogicalSystem("First Order Logic");
//        LogicalSystem *ptr = manager.getActiveLogicalSystem();

//        CHECK(ptr->getName() == "First Order Logic");
//        CHECK(ptr->getDescription() == "Predicate Logic With Quantifiers");
//        CHECK(ptr->getSignatureName() == "Table Signature");
//        CHECK(ptr->getInferenceRules()[0]->name() == "And Elimination");
//        CHECK(ptr->getInferenceRules()[0]->callCommand() == "AndE");
//        CHECK(ptr->getWffType() == Type("o"));

//        //Remove Logical System
//        manager.removeLogicalSystem("First Order Logic");

//        CHECK(StorageManager::retrieveLogicalSystemsRecords().isEmpty());
//        CHECK(!QDir("C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/Logical Systems/First Order Logic").exists());

//        SECTION("Failing to Create Logical System")
//        {
//            QStringList inferenceList;
//            inferenceList << "YadayadaRule";
//            CHECK_THROWS_WITH(LogicalSystem("Name", "Description", inferenceList, "Signature", Type("o")), "Couldn't load plugin named \"C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Inference Rules/YadayadaRule.dll\".");
//            CHECK(!QDir("C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data/Logical Systems/Name").exists());
//        }
//    }

//    SECTION("Theory")
//    {
//        //Setup
//        ProgramManager manager;

//        QStringList inferenceRulesNamesList;
//        inferenceRulesNamesList << "LogosClassicAndElimination";
//        manager.createLogicalSystem("Propositional Logic",
//                                    "Classical Propositional Logic",
//                                    "TableSignaturePlugin",
//                                    inferenceRulesNamesList,
//                                    Type("o"));

//        manager.loadLogicalSystem("Propositional Logic");

//        CHECK(StorageManager::retrieveTheoriesRecords("Propositional Logic").isEmpty());

//        //Create Theory
//        TheoryBuilder builder(manager.getActiveLogicalSystem());
//        builder.setName("Graph Theory");
//        builder.setDescription("Some graph theory.");
//        builder.getSignature()->addToken(CoreToken("P", Type("o")));
//        builder.getSignature()->addToken(CoreToken("~", Type("o->o")));
//        builder.addAxiom("P");
//        builder.addAxiom("(~ (~ P))");

//        manager.createTheory(builder);

//        const TheoryRecord record = StorageManager::retrieveTheoriesRecords("Propositional Logic").first();
//        CHECK(record.getName() == "Graph Theory");
//        CHECK(record.getDescription() == "Some graph theory.");

//        Theory *theory = manager.getActiveTheory();
//    }

//}

TEST_CASE("Dirty Fix")
{
    DirtyFix::fix();
}



