#ifndef ATTRIBUTEWIDGET_H
#define ATTRIBUTEWIDGET_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "./src/generator/dice.h"
#include "./src/generator/attribute.h"


class AttributeWidget : public QGroupBox
{
    Q_OBJECT
private:
    QVBoxLayout *general;

        QHBoxLayout *headerBox;
            QHBoxLayout *lvlSumBox;
                QLabel *lvlSumText;
                QLabel *lvlSumInput;
            QLabel *spacer;
            QLabel *diceInput;

        QHBoxLayout *abilitiesBox;
            QVBoxLayout *abilitiesNames;
              QVector<QLabel*> namesVector;
            QVBoxLayout *abilitiesLvl;
              QVector<QLabel*> lvlVector;

        QPushButton *rerollButton;

public:
    AttributeWidget() {};
    AttributeWidget(ATTRIBUTES name, QVector<QString> abilitiesNames);

    void setDiceText(const QString & inputDice);
    void setLvlSumText(const QString & inputLvlSum);
    void setAbilitiesLvlsText(const QVector<QString> & inputLvls);

    void clearDiceText();
    void clearLvlSumText();
    void clearAbilitiesLvlsText();
    void clear();
};

#endif // ATTRIBUTEWIDGET_H
