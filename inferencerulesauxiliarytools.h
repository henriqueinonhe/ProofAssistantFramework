#ifndef INFERENCERULESAUXILIARYTOOLS_H
#define INFERENCERULESAUXILIARYTOOLS_H

class InferenceRuleArgumentPrototype;
class QString;
class Formula;
class Parser;
class QStringList;
template <class T> class QVector;

typedef InferenceRuleArgumentPrototype ArgumentPrototype;

namespace InferenceRulesAuxiliaryTools
{

void checkMainOperator(const QString &expectedMainOperator, const Formula &premiss, const unsigned int premissNumber);
void checkArgumentListPossibleValuesCompliance(const Parser &parser, const QStringList &argumentList, const QVector<ArgumentPrototype> &prototypes);
void checkArgumentListNumberCompliance(const QStringList &argumentList, const QVector<int> &possibleNumbers);
void checkArgumentListCompliance(const Parser &parser, const QStringList &argumentList, const QVector<ArgumentPrototype> &prototypes, const QVector<int> &possibleNumbers);

}

#endif // INFERENCERULESAUXILIARYTOOLS_H
