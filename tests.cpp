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
#include "pluginmanager.h"

TEST_CASE("File System Setup")
{
    QDir dir("C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox");
    dir.mkdir("data");
    dir.cd("data");
    dir.mkdir("Logical Systems");
    dir.cd("Logical Systems");
    QFile(dir.path() + "/logicalsystemsrecords.dat").open(QIODevice::WriteOnly);
}

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

TEST_CASE("Theory")
{
    QVector<shared_ptr<const InferenceRule>> vec;
    vec.push_back(make_shared<const DummyInferenceRule>());
    LogicalSystem logicalSystem("A", "A", vec, Type("o"));

    TheoryBuilder theoryBuilder(&logicalSystem, "Dummy Theory", "Lorem Ipsum", make_shared<TableSignature>());

    shared_ptr<Signature> signature = theoryBuilder.getSignature();
    signature->addToken(CoreToken("P", Type("o")));
    signature->addToken(CoreToken("~", Type("o->o")));

    theoryBuilder.addAxiom("P");
    theoryBuilder.addAxiom("(~ P)");
    CHECK_THROWS(theoryBuilder.addAxiom("(~ P")); //Testing anti axiom collision

    Theory theory = theoryBuilder.build();

    theory.getInferenceTactics().push_back(make_shared<DummyInferenceTactic>());
    theory.getPreProcessors().push_back(make_shared<DummyPreProcessor>());
    theory.getPostProcessors().push_back(make_shared<DummyPostProcessor>());

    CHECK(theory.getName() == "Dummy Theory");
    CHECK(theory.getDescription() == "Lorem Ipsum");
    CHECK(theory.getAxioms().first().formattedString() == "P");
    CHECK(theory.getAxioms().last().formattedString() == "(~ P)");
    CHECK(theory.getInferenceTactics()[0]->name() == "Dummy Inference Tactic");
    CHECK(theory.getInferenceTactics()[0]->callCommand() == "Dummy Call Command");
    CHECK(theory.getPreProcessors()[0]->toString() == "Dummy Pre Processor");
    CHECK(theory.getPostProcessors()[0]->toString() == "Dummy Post Processor");

    //Serialization
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QDataStream stream(&buffer);
    stream << theory;

    buffer.close();
    buffer.open(QIODevice::ReadOnly);
    shared_ptr<TableSignature> signature2 = make_shared<TableSignature>();
    QVector<shared_ptr<const InferenceTactic>> tactics;
    QVector<shared_ptr<StringProcessor>> preProcessors;
    QVector<shared_ptr<StringProcessor>> postProcessors;
    tactics.push_back(make_shared<DummyInferenceTactic>());
    preProcessors.push_back(make_shared<DummyPreProcessor>());
    postProcessors.push_back(make_shared<DummyPostProcessor>());
    Theory theory2(&logicalSystem, signature2, tactics, preProcessors, postProcessors, stream);

    CHECK(theory2.getName() == theory.getName());
    CHECK(theory2.getDescription() == theory.getDescription());
    CHECK(theory2.getAxioms().first().formattedString() == theory.getAxioms().first().formattedString());
    CHECK(theory2.getAxioms().last().formattedString() == theory.getAxioms().last().formattedString());
    CHECK(theory2.getInferenceTactics()[0]->name() == theory.getInferenceTactics()[0]->name());
    CHECK(theory2.getInferenceTactics()[0]->callCommand() == theory.getInferenceTactics()[0]->callCommand());
    CHECK(theory2.getPreProcessors()[0]->toString() == theory.getPreProcessors()[0]->toString());
    CHECK(theory2.getPostProcessors()[0]->toString() == theory.getPostProcessors()[0]->toString());
    CHECK(*theory2.getSignature()->getTokenPointer("P") == CoreToken("P", Type("o")));
    //Maybe I should test the other members as well like the parser
}

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

TEST_CASE("Plugins")
{
    //Inference Rule
    shared_ptr<const InferenceRule> rule = PluginManager::fetchPlugin<const InferenceRule>(StorageManager::inferenceRulePluginPath("DummyInferenceRulePlugin"));
    CHECK(rule->name() == "Dummy Inference Rule");
    CHECK(rule->callCommand() == "Dummy Call Command");

    //Signature
    shared_ptr<Signature> signature = PluginManager::fetchPlugin<Signature>(StorageManager::signaturePluginPath("TableSignaturePlugin"));
    CHECK_NOTHROW(signature->addToken(CoreToken("P", Type("o"))));
    CHECK_THROWS(signature->addToken(CoreToken("P", Type("o"))));
    CHECK(signature->getTokenPointer("P")->getString() == "P");
    CHECK(dynamic_cast<const CoreToken *>(signature->getTokenPointer("P"))->getType() == Type("o"));

    //Inference Tactic
    shared_ptr<const InferenceTactic> tactic = PluginManager::fetchPlugin<const InferenceTactic>(StorageManager::inferenceTacticPluginPath("DummyInferenceTactic"));
    CHECK(tactic->name() == "Dummy Inference Tactic");
    CHECK(tactic->callCommand() == "Dummy Call Command");

    //Pre Processor
    shared_ptr<StringProcessor> preProcessor = PluginManager::fetchPlugin<StringProcessor>(StorageManager::preProcessorPluginPath("DummyPreProcessorPlugin"));
    CHECK(preProcessor->toString() == "Dummy Pre Processor");

    //Post Processor
    shared_ptr<StringProcessor> postProcessor = PluginManager::fetchPlugin<StringProcessor>(StorageManager::postProcessorPluginPath("DummyPostProcessorPlugin"));
    CHECK(postProcessor->toString() == "Dummy Post Processor");
}

TEST_CASE("Framework Integration")
{
    ProgramManager manager;

    SECTION("Logical System")
    {
        CHECK(StorageManager::retrieveLogicalSystemsRecords().isEmpty());

        //Create Logical System
        QStringList inferenceRulesNamesList;
        inferenceRulesNamesList << "DummyInferenceRulePlugin";
        manager.createLogicalSystem("First Order Logic",
                                    "Predicate Logic With Quantifiers",
                                    inferenceRulesNamesList,
                                    Type("o"));

        const LogicalSystemRecord logicalSystemRecord = StorageManager::retrieveLogicalSystemsRecords().first();

        CHECK(logicalSystemRecord.getName() == "First Order Logic");
        CHECK(logicalSystemRecord.getDescription() == "Predicate Logic With Quantifiers");

        //Load Logical System
        manager.loadLogicalSystem("First Order Logic");
        LogicalSystem *ptr = manager.getActiveLogicalSystem();

        CHECK(ptr->getName() == "First Order Logic");
        CHECK(ptr->getDescription() == "Predicate Logic With Quantifiers");
        CHECK(ptr->getInferenceRules()[0]->name() == "Dummy Inference Rule");
        CHECK(ptr->getInferenceRules()[0]->callCommand() == "Dummy Call Command");
        CHECK(ptr->getWffType() == Type("o"));

        //Remove Logical System
        manager.removeLogicalSystem("First Order Logic");

        CHECK(StorageManager::retrieveLogicalSystemsRecords().isEmpty());
        CHECK(!QDir("C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/Logical Systems/First Order Logic").exists());

        SECTION("Failing to Create Logical System")
        {
            QStringList inferenceList;
            inferenceList << "YadayadaRule";
            CHECK_THROWS_WITH(manager.createLogicalSystem("Name", "Description", inferenceList, Type("o")), "The plugin at \"C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Inference Rules/YadayadaRule.dll\" couldn't be loaded!");
            CHECK(!QDir("C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data/Logical Systems/Name").exists());
        }
    }

    SECTION("Theory")
    {
        //Setup

        QStringList inferenceRulesNamesList;
        inferenceRulesNamesList << "DummyInferenceRulePlugin";
        manager.createLogicalSystem("Propositional Logic",
                                    "Classical Propositional Logic",
                                    inferenceRulesNamesList,
                                    Type("o"));

        manager.loadLogicalSystem("Propositional Logic");

        CHECK(StorageManager::retrieveTheoriesRecords("Propositional Logic").isEmpty());

        //Create Theory
        shared_ptr<Signature> signature = PluginManager::fetchPlugin<Signature>(StorageManager::signaturePluginPath("TableSignaturePlugin"));
        TheoryBuilder builder(manager.getActiveLogicalSystem(), signature);
        builder.setName("Graph Theory");
        builder.setDescription("Some graph theory.");
        builder.getSignature()->addToken(CoreToken("P", Type("o")));
        builder.getSignature()->addToken(CoreToken("~", Type("o->o")));
        builder.addAxiom("P");
        builder.addAxiom("(~ (~ P))");

        manager.createTheory(builder, TheoryPluginsRecord("TableSignaturePlugin"));

        const TheoryRecord record = StorageManager::retrieveTheoriesRecords("Propositional Logic").first();
        CHECK(record.getName() == "Graph Theory");
        CHECK(record.getDescription() == "Some graph theory.");

        manager.loadTheory("Graph Theory");
        Theory *theory = manager.getActiveTheory();
        CHECK(theory->getName() == "Graph Theory");
        CHECK(theory->getDescription() == "Some graph theory.");
        CHECK(theory->getAxioms().first().formattedString() == "P");
        CHECK(theory->getAxioms().last().formattedString() == "(~ (~ P))");
        CHECK(theory->getSignature()->getTokenPointer("P")->getString() == "P");
        CHECK(dynamic_cast<const CoreToken *>(theory->getSignature()->getTokenPointer("P"))->getType() == Type("o"));
    }

}

TEST_CASE("File System Teardown")
{
    QDir("C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data").removeRecursively();
}

TEST_CASE("Dirty Fix")
{
    DirtyFix::fix();
}



