#include "inferencerulesauxiliarytools.h"
#include "formula.h"
#include "parsingtree.h"
#include "parsingtreeconstiterator.h"
#include "inferenceruleargumentprototype.h"
#include <QString>
#include "parser.h"
#include "signature.h"

void InferenceRulesAuxiliaryTools::checkMainOperator(const QString &expectedMainOperator, const Formula &premiss, const unsigned int premissNumber)
{
    const ParsingTree tree = premiss.getParsingTree();
    ParsingTreeConstIterator iter(&tree);
    const unsigned int mainOperatorNodeIndex = 0;
    iter.goToChild(mainOperatorNodeIndex);

    const QString actualMainOperator = iter->getTokenString().formattedString();
    if(actualMainOperator != expectedMainOperator)
    {
        QString errorMsg;
        errorMsg += "Expected main operator for the premiss number ";
        errorMsg += QString::number(premissNumber);
        errorMsg += " was \"";
        errorMsg += expectedMainOperator;
        errorMsg += "\", but \"";
        errorMsg += actualMainOperator;
        errorMsg += "\" was found instead!";
        throw invalid_argument(errorMsg.toStdString());
    }
}

void InferenceRulesAuxiliaryTools::checkArgumentListCompliance(const Parser &parser, const QStringList &argumentList, const QVector<ArgumentPrototype> &prototypes, const QVector<int> &possibleNumbers)
{
    checkArgumentListNumberCompliance(argumentList, possibleNumbers);
    checkArgumentListPossibleValuesCompliance(parser, argumentList, prototypes);
}

void InferenceRulesAuxiliaryTools::checkArgumentListPossibleValuesCompliance(const Parser &parser, const QStringList &argumentList, const QVector<ArgumentPrototype> &prototypes)
{
    for(int index = 0; index < argumentList.size(); index++)
    {
        const QString argument = argumentList[index];
        const ArgumentPrototype prototype = prototypes[index];
        const int zeroIndexCompensation = 1;
        if(prototype.argumentClass == ArgumentPrototype::ArgumentClass::LineNumber)
        {
            if(argument.toInt() <= 0)
            {
                QString errorMsg;
                errorMsg += "Argument number ";
                errorMsg += QString::number(index + zeroIndexCompensation);
                errorMsg += " must be a line number and therefore must be a positive integer, but \"";
                errorMsg += argument;
                errorMsg += "\" was found!";
                throw invalid_argument(errorMsg.toStdString());
            }
        }
        else if(prototype.argumentClass == ArgumentPrototype::ArgumentClass::Parameter)
        {
            bool argumentComplies = false;
            const QStringList possibleValues = prototype.possibleValues;
            for(const QString &possibleValue : possibleValues)
            {
                if(argument == possibleValue)
                {
                    argumentComplies = true;
                }
            }
            if(!argumentComplies)
            {
                QString errorMsg;
                errorMsg += "Argument number ";
                errorMsg += QString::number(index + zeroIndexCompensation);
                errorMsg += "must be a parameter within the following set of possibilities: ";
                for(auto possibleValue = possibleValues.begin(); possibleValue != possibleValues.end() - 1; possibleValue++)
                {
                    errorMsg += "\"";
                    errorMsg += *possibleValue;
                    errorMsg += "\", ";
                }
                errorMsg += "\"";
                errorMsg += possibleValues.last();
                errorMsg += "\"!";
                throw invalid_argument(errorMsg.toStdString());
            }
        }
        else if(prototype.argumentClass == ArgumentPrototype::ArgumentClass::Formula)
        {
            try
            {
                parser.parse(argument);
            }
            catch(const invalid_argument &e)
            {
                QString errorMsg;
                errorMsg += "Argument number ";
                errorMsg += QString::number(index + zeroIndexCompensation);
                errorMsg += "must be a formula, but the following error happened: ";
                errorMsg += e.what();
                throw invalid_argument(errorMsg.toStdString());
            }
        }
        else if(prototype.argumentClass == ArgumentPrototype::ArgumentClass::Token)
        {
            try
            {
                parser.getSignature()->getTokenPointer(argument);
            }
            catch(const invalid_argument &e)
            {
                QString errorMsg;
                errorMsg += "Argument number ";
                errorMsg += QString::number(index + zeroIndexCompensation);
                errorMsg += "must be a formula, but the following error happened: ";
                errorMsg += e.what();
                throw invalid_argument(errorMsg.toStdString());
            }
        }
        else
        {
            return;
        }
    }
}

void InferenceRulesAuxiliaryTools::checkArgumentListNumberCompliance(const QStringList &argumentList, const QVector<int> &possibleNumbers)
{
    for(const int possibleNumber : possibleNumbers)
    {
        if(argumentList.size() == possibleNumber)
        {
            return;
        }
    }

    QString errorMsg;
    for(auto possibleNumber = possibleNumbers.begin(); possibleNumber != possibleNumbers.end() - 1; possibleNumber++)
    {
        errorMsg += QString::number(*possibleNumber);
        errorMsg += ", or ";
    }
    errorMsg += QString::number(possibleNumbers.last());
    errorMsg += " arguments were expected, but ";
    errorMsg += QString::number(argumentList.size());
    errorMsg += " were provided!";
    throw invalid_argument(errorMsg.toStdString());
}
