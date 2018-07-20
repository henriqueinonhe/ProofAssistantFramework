QT += core
QT -= gui

CONFIG += c++11

TARGET = ProofAssistantFramework
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../Language/Parser \
               ../Language/Processors \
               ../Language/Processors/PreProcessors \
               ../Language/Processors/PostProcessors \
               ../Language/Token \
               ../Language/Type \
               ../Language/Utils

SOURCES += main.cpp \
    tests.cpp \
    ../Language/Parser/formula.cpp \
    ../Language/Parser/lexer.cpp \
    ../Language/Parser/parser.cpp \
    ../Language/Parser/parsingtree.cpp \
    ../Language/Parser/parsingtreeiterator.cpp \
    ../Language/Parser/parsingtreenode.cpp \
    ../Language/Parser/signature.cpp \
    ../Language/Parser/tablesignature.cpp \
    ../Language/Processors/PostProcessors/basicpostprocessor.cpp \
    ../Language/Processors/PreProcessors/basicpreprocessor.cpp \
    ../Language/Processors/PreProcessors/classicfunctionnotationpreprocessor.cpp \
    ../Language/Processors/basicprocessor.cpp \
    ../Language/Processors/basicprocessortokenrecord.cpp \
    ../Language/Processors/formatter.cpp \
    ../Language/Processors/stringprocessor.cpp \
    ../Language/Token/bindingrecord.cpp \
    ../Language/Token/bindingtoken.cpp \
    ../Language/Token/coretoken.cpp \
    ../Language/Token/punctuationtoken.cpp \
    ../Language/Token/token.cpp \
    ../Language/Token/tokenstring.cpp \
    ../Language/Token/variabletoken.cpp \
    ../Language/Type/type.cpp \
    ../Language/Type/typeparser.cpp \
    ../Language/Type/typeparsingtree.cpp \
    ../Language/Type/typeparsingtreeiterator.cpp \
    ../Language/Type/typeparsingtreenode.cpp \
    ../Language/Type/typetoken.cpp \
    ../Language/Type/typetokenstring.cpp \
    ../Language/Utils/dirtyfix.cpp \
    logicalsystem.cpp \
    theory.cpp \
    proof.cpp \
    lineofproof.cpp \
    prooflinks.cpp \
    inferencerule.cpp \
    proofassistant.cpp \
    justification.cpp \
    inferenceprocedure.cpp \
    inferencetactic.cpp \
    lineofproofsection.cpp \
    lineofproofsectionmanager.cpp \
    storagemanager.cpp \
    logicalsystemrecord.cpp \
    programmanager.cpp \
    theoryrecord.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    catch.hpp \
    ../Language/Parser/formula.h \
    ../Language/Parser/lexer.h \
    ../Language/Parser/parser.h \
    ../Language/Parser/parsingerrorexception.hpp \
    ../Language/Parser/parsingtree.h \
    ../Language/Parser/parsingtreeiterator.h \
    ../Language/Parser/parsingtreenode.h \
    ../Language/Parser/signature.h \
    ../Language/Parser/tablesignature.h \
    ../Language/Processors/PostProcessors/basicpostprocessor.h \
    ../Language/Processors/PreProcessors/basicpreprocessor.h \
    ../Language/Processors/PreProcessors/classicfunctionnotationpreprocessor.h \
    ../Language/Processors/basicprocessor.h \
    ../Language/Processors/basicprocessortokenrecord.h \
    ../Language/Processors/formatter.h \
    ../Language/Processors/stringprocessor.h \
    ../Language/Token/bindingrecord.h \
    ../Language/Token/bindingtoken.h \
    ../Language/Token/coretoken.h \
    ../Language/Token/punctuationtoken.h \
    ../Language/Token/token.h \
    ../Language/Token/tokenstring.h \
    ../Language/Token/variabletoken.h \
    ../Language/Type/type.h \
    ../Language/Type/typeparser.h \
    ../Language/Type/typeparsingerrorexception.h \
    ../Language/Type/typeparsingtree.h \
    ../Language/Type/typeparsingtreeiterator.h \
    ../Language/Type/typeparsingtreenode.h \
    ../Language/Type/typetoken.h \
    ../Language/Type/typetokenstring.h \
    ../Language/Utils/containerauxiliarytools.h \
    ../Language/Utils/dirtyfix.h \
    ../Language/Utils/parsingauxiliarytools.h \
    ../Language/Utils/pool.h \
    logicalsystem.h \
    theory.h \
    proof.h \
    lineofproof.h \
    prooflinks.h \
    inferencerule.h \
    tree.h \
    proofassistant.h \
    justification.h \
    inferenceprocedure.h \
    inferencetactic.h \
    lineofproofsection.h \
    lineofproofsectionmanager.h \
    storagemanager.h \
    logicalsystemrecord.h \
    programmanager.h \
    theoryrecord.h
