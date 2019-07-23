#include "catch.hpp"
#include "tree.h"
#include "type.h"
#include "logicalsystem.h"
#include "tablesignature.h"
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
#include "prooflinks.h"
#include "proofrecord.h"
#include "proof.h"
#include "justification.h"
#include "proofassistant.h"
#include "basicpreprocessor.h"
#include "basicpostprocessor.h"
#include "stringprocessormanager.h"
#include "programassistant.h"
#include "logicalsystemassistant.h"
#include "theoryassistant.h"

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

    SECTION("Tree Siblings Navigation")
    {
        iter->appendChild("Jaggers");
        iter->appendChild("Freigers");
        iter->appendChild("Fronkers");

        iter.goToChild(0);
        iter.goToNextSibling();
        CHECK(iter->getObj() == "Freigers");

        iter.goToNextSibling();
        CHECK(iter->getObj() == "Fronkers");

        iter.goToPreviousSibling();
        CHECK(iter->getObj() == "Freigers");

        iter.goToPreviousSibling();
        CHECK(iter->getObj() == "Jaggers");
    }

    SECTION("Serialization")
    {

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

    TheoryBuilder theoryBuilder(&logicalSystem, make_shared<TableSignature>(), "Dummy Theory", "Lorem Ipsum");

    shared_ptr<Signature> signature = theoryBuilder.getSignature();
    TableSignature *tableSignature = static_cast<TableSignature *>(signature.get());
    tableSignature->addToken(CoreToken("P", Type("o")));
    tableSignature->addToken(CoreToken("~", Type("o->o")));

    theoryBuilder.addAxiom("P");
    theoryBuilder.addAxiom("(~ P)");
    CHECK_THROWS(theoryBuilder.addAxiom("(~ P)")); //Testing anti axiom collision

    Theory theory = theoryBuilder.build();

    theory.getInferenceTactics().push_back(make_shared<DummyInferenceTactic>());
    theory.getPreFormatter().addProcessor(make_shared<DummyPreProcessor>(signature.get()));
    theory.getPostFormatter().addProcessor(make_shared<DummyPostProcessor>(signature.get()));

    CHECK(theory.getName() == "Dummy Theory");
    CHECK(theory.getDescription() == "Lorem Ipsum");
    CHECK(theory.getAxioms().first().formattedString() == "P");
    CHECK(theory.getAxioms().last().formattedString() == "(~ P)");
    CHECK(theory.getInferenceTactics()[0]->name() == "Dummy Inference Tactic");
    CHECK(theory.getInferenceTactics()[0]->callCommand() == "Dummy Call Command");
    CHECK(theory.getPreFormatter().getProcessors()[0]->toString() == "Dummy Pre Processor");
    CHECK(theory.getPostFormatter().getProcessors()[0]->toString() == "Dummy Post Processor");

    //Serialization
    QBuffer theoryBuffer;
    QBuffer pluginsBuffer;
    theoryBuffer.open(QIODevice::WriteOnly);
    pluginsBuffer.open(QIODevice::WriteOnly);
    QDataStream theoryStream(&theoryBuffer);
    QDataStream pluginsStream(&pluginsBuffer);
    theoryStream << theory;
    pluginsStream << *theory.getSignature();

    theoryBuffer.close();
    pluginsBuffer.close();
    theoryBuffer.open(QIODevice::ReadOnly);
    pluginsBuffer.open(QIODevice::ReadOnly);
    shared_ptr<TableSignature> signature2 = make_shared<TableSignature>(pluginsStream);
    QVector<shared_ptr<const InferenceTactic>> tactics;
    QVector<shared_ptr<StringProcessor>> preProcessors;
    QVector<shared_ptr<StringProcessor>> postProcessors;
    tactics.push_back(make_shared<DummyInferenceTactic>());
    preProcessors.push_back(make_shared<DummyPreProcessor>(signature.get()));
    postProcessors.push_back(make_shared<DummyPostProcessor>(signature.get()));
    Theory theory2(&logicalSystem, signature2, tactics, preProcessors, postProcessors, theoryStream);

    CHECK(theory2.getName() == theory.getName());
    CHECK(theory2.getDescription() == theory.getDescription());
    CHECK(theory2.getAxioms().first().formattedString() == theory.getAxioms().first().formattedString());
    CHECK(theory2.getAxioms().last().formattedString() == theory.getAxioms().last().formattedString());
    CHECK(theory2.getInferenceTactics()[0]->name() == theory.getInferenceTactics()[0]->name());
    CHECK(theory2.getInferenceTactics()[0]->callCommand() == theory.getInferenceTactics()[0]->callCommand());
    CHECK(theory2.getPreFormatter().getProcessors()[0]->toString() == theory.getPreFormatter().getProcessors()[0]->toString());
    CHECK(theory2.getPostFormatter().getProcessors()[0]->toString() == theory.getPostFormatter().getProcessors()[0]->toString());
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

TEST_CASE("Proof Links")
{
    TableSignature signature;
    signature.addToken(CoreToken("P", Type("o")));
    signature.addToken(CoreToken("~", Type("o->o")));
    signature.addToken(CoreToken("v", Type("[o,o]->o")));
    Parser parser(&signature, Type("o"));

    QVector<unsigned int> vec{0,1,2,3};
    ProofLinks link(Formula("(v P (~ P))", parser), vec);
    CHECK(link.getFormula() == "(v P (~ P))");
    CHECK(link.getLinkedProofsIds() == vec);
    link.addLinkedProofId(34);
    CHECK(link.getLinkedProofsIds() == vec + QVector<unsigned int>({34}));

    //Serialization
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QDataStream stream(&buffer);
    stream << link;
    buffer.close();

    buffer.open(QIODevice::ReadOnly);
    ProofLinks link2(stream);
    CHECK(link2.getFormula() == link.getFormula());
    CHECK(link2.getLinkedProofsIds() == link.getLinkedProofsIds());
}

TEST_CASE("Proof Records")
{
    TableSignature signature;
    signature.addToken(CoreToken("A", Type("o")));
    signature.addToken(CoreToken("B", Type("o")));
    signature.addToken(CoreToken("->", Type("[o,o]->o")));
    Parser parser(&signature, Type("o"));

    ProofLinks premiss1(parser.parse("A"), QVector<uint>{0}), premiss2(parser.parse("(-> A B)"), QVector<uint>());
    ProofLinks conclusion (parser.parse("B"), QVector<uint>{3});
    QVector<ProofLinks> premises;
    premises.push_back(premiss1);
    premises.push_back(premiss2);
    ProofRecord record(0, "Dummy Proof", "Lorem Ipsum", premises, conclusion);

    CHECK(record.getId() == 0);
    CHECK(record.getName() == "Dummy Proof");
    CHECK(record.getDescription() == "Lorem Ipsum");
    CHECK(record.getPremisesLinks() == premises);
    CHECK(record.getConclusionLinks() == conclusion);
    CHECK(record.getProofIsDone() == false);

    record.addPremissLinkId(Formula("(->     A B)", parser), 23);
    record.addConclusionLinkId(10);
    CHECK(record.getPremisesLinks()[1].getLinkedProofsIds() == premises[1].getLinkedProofsIds() + QVector<unsigned int>({23}));
    CHECK(record.getConclusionLinks().getLinkedProofsIds() == QVector<unsigned int>({3, 10}));

    //Serialization
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QDataStream stream(&buffer);
    stream << record;
    buffer.close();

    buffer.open(QIODevice::ReadOnly);
    ProofRecord record2(stream);
    CHECK(record2.getId() == record.getId());
    CHECK(record2.getName() == record.getName());
    CHECK(record2.getDescription() == record.getDescription());
    CHECK(record2.getPremisesLinks() == record.getPremisesLinks());
    CHECK(record2.getConclusionLinks() == record.getConclusionLinks());
    CHECK(record2.getProofIsDone() == record.getProofIsDone());
}

TEST_CASE("Justification")
{
    Justification justification("Dummy Call Command", QStringList{"Dummy Arg1", "Dummy Arg2"});
    CHECK(justification.getInferenceRuleCallCommand() == "Dummy Call Command");
    CHECK(justification.getArgumentList() == QStringList{"Dummy Arg1", "Dummy Arg2"});

    //Serialization
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QDataStream stream(&buffer);
    stream << justification;
    buffer.close();

    buffer.open(QIODevice::ReadOnly);
    Justification justification2(stream);
    CHECK(justification2.getInferenceRuleCallCommand() == justification.getInferenceRuleCallCommand());
    CHECK(justification2.getArgumentList() == justification.getArgumentList());
    CHECK(justification2 == justification);
}

TEST_CASE("Line of Proof")
{
    TableSignature signature;
    signature.addToken(CoreToken("P", Type("o")));
    signature.addToken(CoreToken("->", Type("[o,o]->o")));
    Parser parser(&signature, Type("o"));
    Formula formula(parser.parse("(-> P P)"));
    Justification justification("Dummy Call Command", QStringList({"Dummy Arg1, Dummy Arg2"}));

    LineOfProof lineOfProof(formula, justification, "Dummy Comment");
    CHECK(lineOfProof.getFormula() == formula);
    CHECK(lineOfProof.getJustification() == justification);
    CHECK(lineOfProof.getComment() == "Dummy Comment");

    //Serialization
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QDataStream stream(&buffer);
    stream << lineOfProof;
    buffer.close();

    buffer.open(QIODevice::ReadOnly);
    LineOfProof lineOfProof2(stream, &signature);
    CHECK(lineOfProof2.getFormula() == lineOfProof.getFormula());
    CHECK(lineOfProof2.getJustification() == lineOfProof.getJustification());
    CHECK(lineOfProof2.getComment() == lineOfProof.getComment());
}


TEST_CASE("Proofs")
{
    TableSignature signature;
    signature.addToken(CoreToken("P", Type("o")));
    signature.addToken(CoreToken("->", Type("[o,o]->o")));
    Parser parser(&signature, Type("o"));
    Formula premiss1(parser.parse("P"));
    Formula premiss2(parser.parse("(-> P P)"));
    Formula conclusion(parser.parse("P"));
    QVector<Formula> premises;
    premises.push_back(premiss1);
    premises.push_back(premiss2);

    const auto proof = Proof::createNewProof<Proof> (0, "Dummy Proof", "Lorem Ipsum", premises, conclusion);
    CHECK(proof->getId() == 0);
    CHECK(proof->getName() == "Dummy Proof");
    CHECK(proof->getDescription() == "Lorem Ipsum");
    CHECK(proof->getPremises() == premises);
    CHECK(proof->getConclusion() == conclusion);
    CHECK(proof->getLinkedWithAxioms() == false);
    CHECK(proof->isFinished() == false);
    CHECK(proof->getLinesOfProof()[0]->getFormula() == premiss1);
    CHECK(proof->getLinesOfProof()[0]->getJustification() == Justification("Premiss", QStringList()));
    CHECK(proof->getLinesOfProof()[0]->getComment() == "");
    CHECK(proof->getLinesOfProof()[1]->getFormula() == premiss2);
    CHECK(proof->getLinesOfProof()[1]->getJustification() == Justification("Premiss", QStringList()));
    CHECK(proof->getLinesOfProof()[1]->getComment() == "");

    //const auto lineOfProof = make_shared<LineOfProof>(premiss1, Justification("Dummy Call Command", QStringList({"Arg1"})), "Dummy Comment");
    //proof.addLineOfProof(lineOfProof); Coupled with Proof Assistant
    //CHECK(proof.getLinesOfProof().last() == lineOfProof); Coupled with Proof Assistant
    //CHECK(proof->isFinished() == true);

    //Serialization
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QDataStream stream(&buffer);
    stream << *proof;
    buffer.close();

    buffer.open(QIODevice::ReadOnly);
    Proof proof2(stream, &signature);
    CHECK(proof2.getId() == proof->getId());
    CHECK(proof2.getName() == proof->getName());
    CHECK(proof2.getPremises() == proof->getPremises());
    CHECK(proof2.getConclusion() == proof->getConclusion());
    CHECK(*proof2.getLinesOfProof()[0] == *proof->getLinesOfProof()[0]);
    CHECK(*proof2.getLinesOfProof()[1] == *proof->getLinesOfProof()[1]);
    CHECK(proof2.getLinkedWithAxioms() == proof->getLinkedWithAxioms());
    CHECK(proof2.isFinished() == proof->isFinished());
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

TEST_CASE("String Processor Manager")
{
    //Enviroment Setup
    TableSignature signature;
    signature.addToken(CoreToken("P", Type("o")));
    signature.addToken(CoreToken("Q", Type("o")));
    signature.addToken(CoreToken("^", Type("[o,o]->o")));
    signature.addToken(CoreToken("->", Type("[o,o]->o")));
    signature.addToken(CoreToken("~", Type("o->o")));

    shared_ptr<BasicPreProcessor> preProcessor = make_shared<BasicPreProcessor>(&signature);
    preProcessor->addTokenRecord("->", 1);
    preProcessor->addTokenRecord("^", 1);
    preProcessor->addTokenRecord("~", 0);

    shared_ptr<BasicPostProcessor> postProcessor = make_shared<BasicPostProcessor>(&signature);
    postProcessor->addTokenRecord("->", 1);
    postProcessor->addTokenRecord("^", 1);
    postProcessor->addTokenRecord("~", 0);


    //Testing
    StringProcessorManager manager;
    QVector<shared_ptr<StringProcessor>> processorList({preProcessor, postProcessor, postProcessor, preProcessor, postProcessor});
    manager.addProcessor(preProcessor);
    manager.addProcessor(postProcessor);

    CHECK(manager.format("P ^ ~ Q -> ~ Q ^ P") == "P ^ ~ Q -> ~ Q ^ P");

    manager.toggleProcessor(1);
    CHECK(manager.format("P ^ ~ Q -> ~ Q ^ P") == "(-> (^ P (~ Q)) (^ (~ Q) P))");

    manager.turnOnProcessor(1);
    manager.turnOffProcessor(0);
    CHECK(manager.format("(-> (^ P (~ Q)) (^ (~ Q) P))").toStdString() == "P ^ ~ Q -> ~ Q ^ P");

    manager.toggleProcessor(0);

    //Serialization
    QBuffer buffer;
    QDataStream stream(&buffer);
    buffer.open(QIODevice::WriteOnly);
    stream << manager;

    buffer.close();
    buffer.open(QIODevice::ReadOnly);
    StringProcessorManager manager2(stream, processorList);
    CHECK(manager2.format("P ^ ~ Q -> ~ Q ^ P") == "P ^ ~ Q -> ~ Q ^ P");
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

    CHECK(StorageManager::signaturePluginsDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Signatures");
    CHECK(StorageManager::inferenceRulePluginsDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Inference Rules");
    CHECK(StorageManager::inferenceTacticPluginsDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Inference Tactics");
    CHECK(StorageManager::preProcessorPluginsDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Pre Processors");
    CHECK(StorageManager::postProcessorPluginsDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Post Processors");
    CHECK(StorageManager::proofPluginsDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Proofs");
    CHECK(StorageManager::proofPrinterPluginsDirPath() == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Proof Printers");

    CHECK(StorageManager::signaturePluginPath("DummySignaturePlugin") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Signatures/DummySignaturePlugin.dll");
    CHECK(StorageManager::inferenceRulePluginPath("DummyInferenceRule") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Inference Rules/DummyInferenceRule.dll");
    CHECK(StorageManager::inferenceTacticPluginPath("DummyInferenceTactic") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Inference Tactics/DummyInferenceTactic.dll");
    CHECK(StorageManager::preProcessorPluginPath("DummyPreProcessor") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Pre Processors/DummyPreProcessor.dll");
    CHECK(StorageManager::postProcessorPluginPath("DummyPostProcessor") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Post Processors/DummyPostProcessor.dll");
    CHECK(StorageManager::proofPluginPath("Dummy Proof") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Proofs/Dummy Proof.dll");
    CHECK(StorageManager::proofPrinterPluginPath("Dummy Printer") == "C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Proofs/Dummy Printer.dll");

    CHECK(StorageManager::signaturePluginsList() == QStringList({"AutomaticPropositionalLogicSignature.dll", "TableSignaturePlugin.dll"}));
    //CHECK(StorageManager::inferenceRulesPluginsList() == QStringList({"DummyInferenceRulePlugin.dll"})); FIXME!
    CHECK(StorageManager::inferenceTacticsPluginsList() == QStringList({"DummyInferenceTactic.dll"}));
    CHECK(StorageManager::preProcessorPluginsList() == QStringList({"DummyPreProcessorPlugin.dll"}));
    CHECK(StorageManager::postProcessorPluginsList() == QStringList({"DummyPostProcessorPlugin.dll"}));
    CHECK(StorageManager::signaturePluginExists("TableSignaturePlugin"));
    CHECK(StorageManager::inferenceRulePluginExists("DummyInferenceRulePlugin"));
    CHECK(StorageManager::inferenceTacticPluginExists("DummyInferenceTactic"));
    CHECK(StorageManager::preProcessorPluginExists("DummyPreProcessorPlugin"));
    CHECK(StorageManager::postProcessorPluginExists("DummyPostProcessorPlugin"));
}

TEST_CASE("Plugins")
{
    //Inference Rule
    shared_ptr<const InferenceRule> rule = PluginManager::fetchPlugin<const InferenceRule>(StorageManager::inferenceRulePluginPath("DummyInferenceRulePlugin"));
    CHECK(rule->name() == "Dummy Inference Rule");
    CHECK(rule->callCommand() == "Dummy Call Command");

    //Signature
    shared_ptr<Signature> signature = PluginManager::fetchPlugin<Signature>(StorageManager::signaturePluginPath("TableSignaturePlugin"));
    TableSignature *tableSignature = static_cast<TableSignature *>(signature.get());
    CHECK_NOTHROW(tableSignature->addToken(CoreToken("P", Type("o"))));
    CHECK_THROWS(tableSignature->addToken(CoreToken("P", Type("o"))));
    CHECK(signature->getTokenPointer("P")->getString() == "P");
    CHECK(static_cast<const CoreToken *>(signature->getTokenPointer("P"))->getType() == Type("o"));

    //Inference Tactic
    shared_ptr<const InferenceTactic> tactic = PluginManager::fetchPlugin<const InferenceTactic>(StorageManager::inferenceTacticPluginPath("DummyInferenceTactic"));
    CHECK(tactic->name() == "Dummy Inference Tactic");
    CHECK(tactic->callCommand() == "Dummy Call Command");

    //Pre Processor
    shared_ptr<StringProcessor> preProcessor = PluginManager::fetchPlugin(StorageManager::preProcessorPluginPath("DummyPreProcessorPlugin"), signature.get());
    CHECK(preProcessor->toString() == "Dummy Pre Processor");

    //Post Processor
    shared_ptr<StringProcessor> postProcessor = PluginManager::fetchPlugin(StorageManager::postProcessorPluginPath("DummyPostProcessorPlugin"), signature.get());
    CHECK(postProcessor->toString() == "Dummy Post Processor");
}

TEST_CASE("Framework Integration I")
{
    ProgramAssistant programAssistant;

    SECTION("Logical System")
    {
        CHECK(StorageManager::retrieveLogicalSystemsRecords().isEmpty());

        //Create Logical System
        QStringList inferenceRulesNamesList;
        inferenceRulesNamesList << "DummyInferenceRulePlugin";
        programAssistant.createLogicalSystem("First Order Logic",
                                             "Predicate Logic With Quantifiers",
                                             inferenceRulesNamesList,
                                             "TableSignaturePlugin",
                                             "",
                                             "DummyProofPrinter",
                                             Type("o"));

        const auto logicalSystemRecord = StorageManager::retrieveLogicalSystemsRecords().first();

        CHECK(logicalSystemRecord.getName() == "First Order Logic");
        CHECK(logicalSystemRecord.getDescription() == "Predicate Logic With Quantifiers");

        //Load Logical System
        auto logicalSystemAssistant = programAssistant.loadLogicalSystem("First Order Logic");
        const auto &activeSystem = logicalSystemAssistant.getActiveLogicalSystem();

        CHECK(activeSystem.getName() == "First Order Logic");
        CHECK(activeSystem.getDescription() == "Predicate Logic With Quantifiers");
        CHECK(activeSystem.getInferenceRules()[0]->name() == "Dummy Inference Rule");
        CHECK(activeSystem.getInferenceRules()[0]->callCommand() == "Dummy Call Command");
        CHECK(activeSystem.getWffType() == Type("o"));

        //Remove Logical System
        programAssistant.removeLogicalSystem("First Order Logic");

        CHECK(StorageManager::retrieveLogicalSystemsRecords().isEmpty());
        CHECK(!QDir("C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/Logical Systems/First Order Logic").exists());

        SECTION("Failing to Create Logical System")
        {
            QStringList inferenceList;
            inferenceList << "YadayadaRule";
            CHECK_THROWS_WITH(programAssistant.createLogicalSystem("Name", "Description", inferenceList, "TableSignature", "", "DummyProofPrinter", Type("o")), "The plugin at \"C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/plugins/Inference Rules/YadayadaRule.dll\" couldn't be loaded!");
            CHECK(!QDir("C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data/Logical Systems/Name").exists());
        }
    }

//    SECTION("Theory")
//    {
//        //Setup
//        QStringList inferenceRulesNamesList;
//        inferenceRulesNamesList << "DummyInferenceRulePlugin";
//        programAssistant.createLogicalSystem("Propositional Logic",
//                                    "Classical Propositional Logic",
//                                    inferenceRulesNamesList,
//                                    "TableSignaturePlugin",
//                                    "",
//                                    Type("o"));

//        programAssistant.loadLogicalSystem("Propositional Logic");

//        CHECK(StorageManager::retrieveTheoriesRecords("Propositional Logic").isEmpty());

//        //Create Theory
//        shared_ptr<Signature> signature = PluginManager::fetchPlugin<Signature>(StorageManager::signaturePluginPath("TableSignaturePlugin"));
//        TheoryBuilder builder(programAssistant.getActiveLogicalSystem(), signature);
//        builder.setName("Graph Theory");
//        builder.setDescription("Some graph theory.");
//        TableSignature *tableSignature = static_cast<TableSignature *>(builder.getSignature().get());
//        tableSignature->addToken(CoreToken("P", Type("o")));
//        tableSignature->addToken(CoreToken("~", Type("o->o")));
//        builder.addAxiom("P");
//        builder.addAxiom("(~ (~ P))");

//        manager.createTheory(builder, TheoryPluginsRecord());

//        CHECK(StorageManager::retrieveCurrentProofId("Propositional Logic", "Graph Theory") == 0);

//        const TheoryRecord record = StorageManager::retrieveTheoriesRecords("Propositional Logic").first();
//        CHECK(record.getName() == "Graph Theory");
//        CHECK(record.getDescription() == "Some graph theory.");

//        manager.loadTheory("Graph Theory");
//        Theory *theory = manager.getActiveTheory();
//        CHECK(theory->getName() == "Graph Theory");
//        CHECK(theory->getDescription() == "Some graph theory.");
//        CHECK(theory->getAxioms().first().formattedString() == "P");
//        CHECK(theory->getAxioms().last().formattedString() == "(~ (~ P))");
//        CHECK(theory->getSignature()->getTokenPointer("P")->getString() == "P");
//        CHECK(static_cast<const CoreToken *>(theory->getSignature()->getTokenPointer("P"))->getType() == Type("o"));

//        //Repeating load theory
//        manager.loadTheory("Graph Theory");
//        theory = manager.getActiveTheory();
//        CHECK(theory->getName() == "Graph Theory");
//        CHECK(theory->getDescription() == "Some graph theory.");
//        CHECK(theory->getAxioms().first().formattedString() == "P");
//        CHECK(theory->getAxioms().last().formattedString() == "(~ (~ P))");
//        CHECK(theory->getSignature()->getTokenPointer("P")->getString() == "P");
//        CHECK(static_cast<const CoreToken *>(theory->getSignature()->getTokenPointer("P"))->getType() == Type("o"));

//        CHECK_THROWS(manager.removeTheory("Some Theory"));
//        CHECK_NOTHROW(manager.removeTheory("Graph Theory"));
//        CHECK(!QDir(StorageManager::theoryDirPath("Propositional Logic", "Graph Theory")).exists());

//        //Cleanup
//        manager.removeLogicalSystem("Propositional Logic");
//    }

//    SECTION("Proof")
//    {
//        //Setup
//        //Create Logical System
//        QStringList inferenceRulesNamesList;
//        inferenceRulesNamesList << "DummyInferenceRulePlugin";
//        manager.createLogicalSystem("Propositional Logic",
//                                    "Classical Propositional Logic",
//                                    inferenceRulesNamesList,
//                                    "TableSignaturePlugin",
//                                    "",
//                                    Type("o"));

//        manager.loadLogicalSystem("Propositional Logic");

//        CHECK(StorageManager::retrieveTheoriesRecords("Propositional Logic").isEmpty());

//        //Create Theory
//        shared_ptr<Signature> signature = PluginManager::fetchPlugin<Signature>(StorageManager::signaturePluginPath("TableSignaturePlugin"));
//        TheoryBuilder builder(manager.getActiveLogicalSystem(), signature);
//        builder.setName("Graph Theory");
//        builder.setDescription("Some graph theory.");
//        TableSignature *tableSignature = static_cast<TableSignature *>(builder.getSignature().get());
//        tableSignature->addToken(CoreToken("P", Type("o")));
//        tableSignature->addToken(CoreToken("~", Type("o->o")));
//        builder.addAxiom("P");
//        builder.addAxiom("(~ (~ P))");

//        manager.createTheory(builder, TheoryPluginsRecord());
//        manager.loadTheory("Graph Theory");

//        //Create Proof
//        manager.createProof("Dummy Proof", "Lorem Ipsum", QStringList({"P"}), "P");
//        ProofAssistant proofAssistant = manager.loadProof(0);
//        const Proof &proof = proofAssistant.getProof();
//        CHECK(proof.getName() == "Dummy Proof");
//        CHECK(proof.getDescription() == "Lorem Ipsum");
//        CHECK(proof.getPremises()[0].formattedString() == "P");
//        CHECK(proof.getConclusion().formattedString() == "P");
//        CHECK(proof.isFinished());
//        CHECK(proof.getLinesOfProof().size() == 1);
//        CHECK(proof.getLinesOfProof()[0]->getFormula().formattedString() == "P");
//        CHECK(proof.getLinesOfProof()[0]->getJustification() == Justification("Premiss", QStringList()));
//        CHECK(proof.getLinesOfProof()[0]->getComment() == "");
//        proofAssistant.setLineOfProofComment(0, "Dummy Comment");
//        CHECK(proofAssistant.getProof().getLinesOfProof()[0]->getComment() == "Dummy Comment");

//        manager.saveProof(proofAssistant);
//        CHECK(manager.loadProof(0).getProof().getLinesOfProof()[0]->getComment() == "Dummy Comment");
//    }

}

//TEST_CASE("Framework Integration II")
//{
//    //Testing A Propositional Logic Setup
//    ProgramManager manager;

//    //Logical System Setup
//    QStringList inferenceRules;
//    inferenceRules << "PropositionalAndEliminationPlugin";
//    inferenceRules << "PropositionalAndIntroductionPlugin";
//    inferenceRules << "PropositionalOrEliminationPlugin";
//    inferenceRules << "PropositionalOrIntroductionPlugin";
//    inferenceRules << "PropositionalBiconditionalEliminationPlugin";
//    inferenceRules << "PropositionalBiconditionalIntroductionPlugin";
//    inferenceRules << "PropositionalDoubleNegationEliminationPlugin";
//    inferenceRules << "PropositionalNegationIntroductionPlugin";
//    inferenceRules << "PropositionalImplicationIntroductionPlugin";
//    inferenceRules << "PropositionalModusPonensPlugin";
//    inferenceRules << "PropositionalHypothesisIntroductionPlugin";
//    manager.createLogicalSystem("Propositional Logic2",
//                                "Just a normal propositional logic system.",
//                                inferenceRules,
//                                "AutomaticPropositionalLogicSignature",
//                                "",
//                                Type("o"));
//    manager.loadLogicalSystem("Propositional Logic2");

//    //Setup Theory
//    shared_ptr<Signature> signature = PluginManager::fetchPlugin<Signature>(StorageManager::signaturePluginPath("AutomaticPropositionalLogicSignature"));
//    TheoryBuilder builder(manager.getActiveLogicalSystem(),
//                          signature,
//                          "First Theory",
//                          "Just a testing theory.");
//    builder.addAxiom("A");
//    builder.addAxiom("B");

//    TheoryPluginsRecord pluginsRecords;
//    manager.createTheory(builder, pluginsRecords);
//    manager.loadTheory("First Theory");

//    //Proofs
//    manager.createProof("Proof 1", "", QStringList({"A"}), "A");
//    manager.createProof("Proof 2", "", QStringList({"B"}), "B");
//    manager.createProof("Proof 3", "", QStringList({"A", "B"}), "(^ A B)");
//    manager.createProof("Proof 4", "", QStringList({"(^ A B)"}), "(v A B)");
//    manager.createProof("Proof 5", "", QStringList({"(v A B)", "(~ B)"}), "A");
//    manager.createProof("Proof 6", "", QStringList({"A"}), "(v A B)");
//    manager.createProof("Proof 7", "", QStringList({"B"}), "(v A B)");

//    //Testing IDs
//    CHECK(manager.loadProof(0).getProof().getName() == "Proof 1");
//    CHECK(manager.loadProof(1).getProof().getName() == "Proof 2");
//    CHECK(manager.loadProof(2).getProof().getName() == "Proof 3");
//    CHECK(manager.loadProof(3).getProof().getName() == "Proof 4");
//    CHECK(manager.loadProof(4).getProof().getName() == "Proof 5");
//    CHECK(manager.loadProof(5).getProof().getName() == "Proof 6");
//    CHECK(manager.loadProof(6).getProof().getName() == "Proof 7");

//    //Testing Proof Links
//    QVector<ProofRecord> proofRecords = StorageManager::retrieveProofsRecords(manager.getActiveLogicalSystem()->getName(), manager.getActiveTheory()->getName());

//    //Proof 1
//    //Premises
//    CHECK(proofRecords[0].getPremisesLinks()[0].getFormula() == "A");
//    CHECK(proofRecords[0].getPremisesLinks()[0].getLinkedProofsIds() == QVector<unsigned int>({4}));

//    //Conclusion
//    CHECK(proofRecords[0].getConclusionLinks().getFormula() == "A");
//    CHECK(proofRecords[0].getConclusionLinks().getLinkedProofsIds() == QVector<unsigned int>({2, 5}));

//    //Proof 2
//    //Premises
//    CHECK(proofRecords[1].getPremisesLinks()[0].getFormula() == "B");
//    CHECK(proofRecords[1].getPremisesLinks()[0].getLinkedProofsIds() == QVector<unsigned int>({}));

//    //Conclusion
//    CHECK(proofRecords[1].getConclusionLinks().getFormula() == "B");
//    CHECK(proofRecords[1].getConclusionLinks().getLinkedProofsIds() == QVector<unsigned int>({2, 6}));

//    //Proof 3
//    //Premises
//    CHECK(proofRecords[2].getPremisesLinks()[0].getFormula() == "A");
//    CHECK(proofRecords[2].getPremisesLinks()[0].getLinkedProofsIds() == QVector<unsigned int>({0, 4}));
//    CHECK(proofRecords[2].getPremisesLinks()[1].getFormula() == "B");
//    CHECK(proofRecords[2].getPremisesLinks()[1].getLinkedProofsIds() == QVector<unsigned int>({1}));

//    //Conclusion
//    CHECK(proofRecords[2].getConclusionLinks().getFormula() == "(^ A B)");
//    CHECK(proofRecords[2].getConclusionLinks().getLinkedProofsIds() == QVector<unsigned int>({3}));

//    //Proof 4
//    //Premises
//    CHECK(proofRecords[3].getPremisesLinks()[0].getFormula() == "(^ A B)");
//    CHECK(proofRecords[3].getPremisesLinks()[0].getLinkedProofsIds() == QVector<unsigned int>({2}));

//    //Conclusion
//    CHECK(proofRecords[3].getConclusionLinks().getFormula() == "(v A B)");
//    CHECK(proofRecords[3].getConclusionLinks().getLinkedProofsIds() == QVector<unsigned int>({4}));

//    //Proof 5
//    //Premises
//    CHECK(proofRecords[4].getPremisesLinks()[0].getFormula() == "(v A B)");
//    CHECK(proofRecords[4].getPremisesLinks()[0].getLinkedProofsIds() == QVector<unsigned int>({3, 5, 6}));
//    CHECK(proofRecords[4].getPremisesLinks()[1].getFormula() == "(~ B)");
//    CHECK(proofRecords[4].getPremisesLinks()[1].getLinkedProofsIds() == QVector<unsigned int>({}));

//    //Conclusion
//    CHECK(proofRecords[4].getConclusionLinks().getFormula() == "A");
//    CHECK(proofRecords[4].getConclusionLinks().getLinkedProofsIds() == QVector<unsigned int>({0, 2, 5}));

//    //Proof 6
//    //Premises
//    CHECK(proofRecords[5].getPremisesLinks()[0].getFormula() == "A");
//    CHECK(proofRecords[5].getPremisesLinks()[0].getLinkedProofsIds() == QVector<unsigned int>({0, 4}));

//    //Conclusion
//    CHECK(proofRecords[5].getConclusionLinks().getFormula() == "(v A B)");
//    CHECK(proofRecords[5].getConclusionLinks().getLinkedProofsIds() == QVector<unsigned int>({4}));

//    //Proof 7
//    //Premises
//    CHECK(proofRecords[6].getPremisesLinks()[0].getFormula() == "B");
//    CHECK(proofRecords[6].getPremisesLinks()[0].getLinkedProofsIds() == QVector<unsigned int>({1}));

//    //Conclusion
//    CHECK(proofRecords[6].getConclusionLinks().getFormula() == "(v A B)");
//    CHECK(proofRecords[6].getConclusionLinks().getLinkedProofsIds() == QVector<unsigned int>({4}));
//}

TEST_CASE("File System Teardown")
{
    QDir("C:/Users/Henrique/Desktop/Proof Assistant Framework Sandbox/data").removeRecursively();
}




