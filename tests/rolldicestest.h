#ifndef ROLLDICESTEST_H
#define ROLLDICESTEST_H

#include <QObject>
#include <QtTest/QtTest>
#include "src/generator/rolldices.h"

class RollDicesTest : public QObject
{
    Q_OBJECT
public:
    explicit RollDicesTest(QObject *parent = nullptr);

signals:

private slots:
    void compare();
    void cardsTranslation();
    void dicesGenerating();
    void basicDeckSize();

    void numbersTranslation();
    void cardsRolling();
    void cardsSelection();
    void sortingCards();
};

QTEST_MAIN(RollDicesTest)
//#include "rolldicestest.moc"

#endif // ROLLDICESTEST_H
