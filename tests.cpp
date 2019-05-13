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
#include <QBuffer>

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

class DummyInferenceRule : virtual public InferenceRule
{
public:
    QString name() const
    {
        return "Dummy Inference Rule";
    }
    QString callCommand() const
    {
        return "Dummy Call Command";
    }
    LineOfProof apply(const Proof &proof, const QStringList &argumentList) const
    {
        //Does Nothing
        return LineOfProof();
    }
};

class DummySignaturePlugin : virtual public SignaturePlugin
{
public:
    const Token *getTokenPointer(const QString &token) const
    {
        return signature->getTokenPointer(token);
    }

    void addToken(const Token &token) {
        //Do nothing
    }

    TableSignature *getSignature()
    {
        return signature;
    }

    void setSignature(TableSignature *value)
    {
        signature = value;
    }


protected:
    void serialize(QDataStream &stream) const
    {
        stream << *signature;
    }
    void unserialize(QDataStream &stream)
    {
        stream >> *signature;
    }

private:
    TableSignature *signature;

};

class DummyInferenceTactic : virtual public InferenceTactic
{
public:
    QString name() const
    {
        return "Dummy Inference Tactic";
    }
    QString callCommand() const
    {
        return "Dummy Call Command";
    }
    void apply(const ProofAssistant * const assistant, const QStringList &argumentList)
    {
        //Do Nothing
    }

    virtual ~DummyInferenceTactic() {}
};

class DummyPreProcessor : virtual public StringProcessorPlugin
{
public:
    DummyPreProcessor() :
        dummyAttribute(10)
    {

    }

    QString processString(const QString &string) const
    {
        //Do Nothing
        return QString();
    }
    QString toString() const
    {
        return "Dummy Pre Processor";
    }

    virtual ~DummyPreProcessor() {}

protected:
    void serialize(QDataStream &stream) const
    {
        stream << dummyAttribute;
    }
    void unserialize(QDataStream &stream)
    {
        stream >> dummyAttribute;
    }

private:
    int dummyAttribute;
};

class DummyPostProcessor : virtual public StringProcessorPlugin
{
public:
    DummyPostProcessor() :
        dummyAttribute(10)
    {

    }

    QString processString(const QString &string) const
    {
        //Do Nothing
        return QString();
    }
    QString toString() const
    {
        return "Dummy Post Processor";
    }

    virtual ~DummyPostProcessor() {}

protected:
    void serialize(QDataStream &stream) const
    {
        stream << dummyAttribute;
    }
    void unserialize(QDataStream &stream)
    {
        stream >> dummyAttribute;
    }

private:
    int dummyAttribute;
};

TEST_CASE("Plugin Wrapper")
{
    {
        PluginWrapper<SignaturePlugin> signature(StorageManager::signaturePluginPath("TableSignaturePlugin"));
        signature->addToken(CoreToken("a", Type("i")));
    }
    {
        PluginWrapper<SignaturePlugin> signature(StorageManager::signaturePluginPath("TableSignaturePlugin"));
        CHECK_NOTHROW(signature->addToken(CoreToken("a", Type("i"))));
    }
    {
        PluginWrapper<SignaturePlugin> signature(StorageManager::signaturePluginPath("TableSignaturePlugin"));
        signature->addToken(CoreToken("a", Type("i")));

        PluginWrapper<SignaturePlugin> signature2;
        signature2 = signature;
        CHECK_THROWS(signature2->addToken(CoreToken("a", Type("i"))));
    }
}

TEST_CASE("Framework Components")
{
    QStringList inferenceRulesNamesList;
    inferenceRulesNamesList << "LogosClassicAndElimination";

    LogicalSystem logicalSystem("Dummy Logical System",
                                "Lorem Ipsum",
                                inferenceRulesNamesList,
                                "TableSignaturePlugin",
                                Type("o"));

//    SECTION("Logical System")
//    {
//        SECTION("Basic")
//        {
            CHECK(logicalSystem.getName() == "Dummy Logical System");
            CHECK(logicalSystem.getDescription() == "Lorem Ipsum");
            CHECK(logicalSystem.getInferenceRules()[0]->name() == "And Elimination");
            CHECK(logicalSystem.getInferenceRules()[0]->callCommand() == "AndE");
            CHECK(logicalSystem.getSignatureName() == "TableSignaturePlugin");
            CHECK(logicalSystem.getWffType() == Type("o"));
//        }

//        SECTION("Serialization")
//        {
            QBuffer buffer;
            buffer.open(QIODevice::WriteOnly);
            QDataStream stream(&buffer);

            logicalSystem.serialize(stream);

            buffer.close();
            buffer.open(QIODevice::ReadOnly);
            LogicalSystem logicalSystem2(stream);

            CHECK(logicalSystem2.getName() == "Dummy Logical System");
            CHECK(logicalSystem2.getDescription() == "Lorem Ipsum");
            CHECK(logicalSystem2.getInferenceRules()[0]->name() == "And Elimination");
            CHECK(logicalSystem2.getInferenceRules()[0]->callCommand() == "AndE");
            CHECK(logicalSystem2.getSignatureName() == "TableSignaturePlugin");
            CHECK(logicalSystem2.getWffType() == Type("o"));
//        }
//    }


    SECTION("Logical System Record")
    {
        QString signatureName = "Dummy Signature";

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
}

TEST_CASE("Framework Components (some bug, needs to split test case)")
{
    LogicalSystem logicalSystem("A", "A", QStringList(), "TableSignaturePlugin", Type("o"));

    TheoryBuilder theoryBuilder(&logicalSystem, "Dummy Theory", "Lorem Ipsum");

    QVector<InferenceTactic *> tactics;
    QVector<StringProcessorPlugin *> preProcessors;
    QVector<StringProcessorPlugin *> postProcessors;


    unique_ptr<InferenceTactic> tactic(new DummyInferenceTactic);
    unique_ptr<StringProcessorPlugin> preProcessor(new DummyPreProcessor);
    unique_ptr<StringProcessorPlugin> postProcessor(new DummyPostProcessor);

    Signature *signature = theoryBuilder.getSignature();
    signature->addToken(CoreToken("P", Type("o")));
    signature->addToken(CoreToken("~", Type("o->o")));


    theoryBuilder.addAxiom("P");
    theoryBuilder.addAxiom("(~ P)");
    CHECK_THROWS(theoryBuilder.addAxiom("(~ P"));

    tactics.push_back(tactic.get());
    preProcessors.push_back(preProcessor.get());
    postProcessors.push_back(postProcessor.get());

    Theory theory = theoryBuilder.build();
    theory.setPreProcessors(preProcessors);
    theory.setPostProcessors(postProcessors);

    SECTION("Theory")
    {
        SECTION("Basic")
        {
            CHECK(theory.getName() == "Dummy Theory");
            CHECK(theory.getDescription() == "Lorem Ipsum");
            CHECK(theory.getAxioms().first().formattedString() == "P");
            CHECK(theory.getAxioms().last().formattedString() == "(~ P)");
            //CHECK(theory.getInferenceTactics()[0]->name() == "Dummy Inference Tactic");
            //CHECK(theory.getInferenceTactics()[0]->callCommand() == "Dummy Call Command");
            CHECK(theory.getPreProcessors()[0]->toString() == "Dummy Pre Processor");
            CHECK(theory.getPostProcessors()[0]->toString() == "Dummy Post Processor");
        }

//        SECTION("Serialization")
//        {
//            QBuffer buffer;
//            buffer.open(QIODevice::WriteOnly);
//            QDataStream stream(&buffer);

//            stream << theory;

//            Theory theory2(&logicalSystem);

//            buffer.close();
//            buffer.open(QIODevice::ReadOnly);
//            stream >> theory2;

//        }
    }


}

TEST_CASE("Plugins")
{
    SECTION("SignaturePlugin")
    {
        QPluginLoader loader("C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Signatures/TableSignaturePlugin.dll");
        CHECK(loader.load());

        SignaturePlugin *ptr = qobject_cast<SignaturePlugin *>(loader.instance());
        ptr->addToken(CoreToken("Chabaduba", Type("i")));
        CHECK(ptr->getTokenPointer("Chabaduba")->tokenClass() == "CoreToken");
    }
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



TEST_CASE("Proofs")
{
    //TODO Gotta test those proofs really hard!
}

//TEST_CASE("Program Manager and Storage Manager")
//{
//    StorageManager::setRootPath("C:/Users/Henrique/Documents/Qt Projects/ProofAssistantFramework");

//    CHECK(StorageManager::getRootPath() == "C:/Users/Henrique/Documents/Qt Projects/ProofAssistantFramework");

//    ProgramManager manager;

//    SECTION("Logical System Management")
//    {
//        QStringList inferenceRulesNameList;
//        inferenceRulesNameList << "rule1" << "rule2" << "rule3";

//        CHECK_NOTHROW(manager.createLogicalSystem("Pure First Order Logic",
//                                                  "First order logic without equality or functions.",
//                                                  "TableSignaturePlugin",
//                                                  inferenceRulesNameList,
//                                                  Type("o")));

//        CHECK_NOTHROW(manager.loadLogicalSystem("Pure First Order Logic"));
//        CHECK(manager.getActiveLogicalSystem()->getName() == "Pure First Order Logic");
//        CHECK(manager.getActiveLogicalSystem()->getDescription() == "First order logic without equality or functions.");
//        CHECK(manager.getActiveLogicalSystem()->getSignaturePluginName() == "TableSignaturePlugin");
//        CHECK(manager.getActiveLogicalSystem()->getInferenceRulesPluginsNames() == inferenceRulesNameList);
//        CHECK(manager.getActiveLogicalSystem()->getWffType() == Type("o"));

//        CHECK_THROWS(manager.createLogicalSystem("Pure First Order Logic",
//                                                 "First order logic without equality or functions.",
//                                                 "TableSignaturePlugin",
//                                                 inferenceRulesNameList,
//                                                 Type("o")));

//        CHECK_NOTHROW(manager.removeLogicalSystem("Pure First Order Logic"));
//    }

//    SECTION("Theory Management")
//    {
//        //Logical System Setup
//        QStringList inferenceRulesNameList;
//        inferenceRulesNameList << "rule1" << "rule2" << "rule3";

//        manager.createLogicalSystem("Pure First Order Logic",
//                                    "First order logic without equality or functions.",
//                                    "TableSignaturePlugin",
//                                    inferenceRulesNameList,
//                                    Type("o"));

//        manager.loadLogicalSystem("Pure First Order Logic");

//        CHECK_NOTHROW(manager.loadLogicalSystem("Pure First Order Logic"));

//        //Theory
//        //This is temporary
//        TableSignature signature;
//        signature.addToken(CoreToken("P", Type("o")));
//        signature.addToken(CoreToken("~", Type("o->o")));

//        Parser parser(&signature, Type("o"));

//        QLinkedList<Formula> axiomsList;
////        axiomsList.push_back(parser.parse("P"));
////        axiomsList.push_back(parser.parse("(~ P)"));
////        axiomsList.push_back(parser.parse("(~(~ P))"));

//        QStringList dummyInferenceTacticsPluginNameList;
//        QStringList dummyPreProcessorsPluginNameList;
//        QStringList dummyPostProcessorsPluginNameList;

//        CHECK_NOTHROW(manager.createTheory("Dummy Theory",
//                                           "This is just an ordinary dummy theory.",
//                                           axiomsList,
//                                           dummyInferenceTacticsPluginNameList,
//                                           dummyPreProcessorsPluginNameList,
//                                           dummyPostProcessorsPluginNameList));

//        CHECK_THROWS(manager.createTheory("Dummy Theory",
//                                          "This is just an ordinary dummy theory.",
//                                          axiomsList,
//                                          dummyInferenceTacticsPluginNameList,
//                                          dummyPreProcessorsPluginNameList,
//                                          dummyPostProcessorsPluginNameList));

//        CHECK_NOTHROW(manager.loadTheory("Dummy Theory"));

//        CHECK(manager.getActiveTheory()->getName() == "Dummy Theory");
//        CHECK(manager.getActiveTheory()->getDescription() == "This is just an ordinary dummy theory.");
//        CHECK(manager.getActiveTheory()->getAxioms() == axiomsList);
//        CHECK(manager.getActiveTheory()->getInferenceTacticsPluginsNameList() == QStringList());
//        CHECK(manager.getActiveTheory()->getPreProcessorPluginsNameList() == QStringList());
//        CHECK(manager.getActiveTheory()->getPostProcessorPluginsNameList() == QStringList());

//        CHECK_NOTHROW(manager.removeTheory("Dummy Theory"));

//        //Cleanup
//        manager.removeLogicalSystem("Pure First Order Logic");
//    }

//    SECTION("Proof Management")
//    {

//    }

//}

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

TEST_CASE("Framework Integration")
{
    ProgramManager manager;

    CHECK(StorageManager::retrieveLogicalSystemsRecords().isEmpty());

    //Create Logical System
    QStringList inferenceRulesNamesList;
    inferenceRulesNamesList << "LogosClassicAndElimination";
    manager.createLogicalSystem("First Order Logic",
                                "Predicate Logic With Quantifiers",
                                "Table Signature",
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
    CHECK(ptr->getSignatureName() == "Table Signature");
    CHECK(ptr->getInferenceRules()[0]->name() == "And Elimination");
    CHECK(ptr->getInferenceRules()[0]->callCommand() == "AndE");
    CHECK(ptr->getWffType() == Type("o"));

    //Remove Logical System
    manager.removeLogicalSystem("First Order Logic");

    CHECK(StorageManager::retrieveLogicalSystemsRecords().isEmpty());
    CHECK(!QDir("C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/Logical Systems/First Order Logic").exists());

    SECTION("Failing to Create Logical System")
    {
        QStringList inferenceList;
        inferenceList << "YadayadaRule";
        CHECK_THROWS_WITH(LogicalSystem("Name", "Description", inferenceList, "Signature", Type("o")), "Couldn't load plugin named \"C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Inference Rules/YadayadaRule.dll\".");
        CHECK(!QDir("C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data/Logical Systems/Name").exists());
    }
}

TEST_CASE("Dirty Fix")
{
    DirtyFix::fix();
}



