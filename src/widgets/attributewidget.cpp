#include "attributewidget.h"

AttributeWidget::AttributeWidget(Dice dice, const ATTRIBUTES name, QVector<QString> inputNames){
    // translate name from enum to string
    const char* s = 0;
#define PROCESS_VAL(p) case(p): s = #p; break;
    switch(name){
        PROCESS_VAL(Cognition);
        PROCESS_VAL(Knowledge);
        PROCESS_VAL(Smarts);
        PROCESS_VAL(Deftness);
        PROCESS_VAL(Nimbleness);
        PROCESS_VAL(Vigor);
        PROCESS_VAL(Spirit);
        PROCESS_VAL(Mien);
        PROCESS_VAL(Quickness);
        PROCESS_VAL(Strength);
    }
#undef PROCESS_VAL

// ------------ Abilities Box -------------

     abilitiesBox = new QHBoxLayout();
     abilitiesNames = new QVBoxLayout();
     abilitiesLvl = new QVBoxLayout();


    // adding abilities labels to vectors
    for(auto & n : inputNames){
        QLabel *nameLabel = new QLabel();
        nameLabel->setText(n);
        nameLabel->setAlignment(Qt::AlignRight);
        namesVector.push_back(nameLabel);

        QLabel *lvlLabel = new QLabel();
        lvlLabel->setText("0");
        lvlLabel->setAlignment(Qt::AlignCenter);
        lvlVector.push_back(lvlLabel);
    }

    // adding labels from vectors
    for(auto & l : namesVector)
        abilitiesNames->addWidget(l);

    for(auto & l : lvlVector)
        abilitiesLvl->addWidget(l);

    // adding to abilities box
    abilitiesBox->addLayout(abilitiesNames);
    abilitiesBox->addLayout(abilitiesLvl);

// ------------ Header Box -------------

    headerBox = new QHBoxLayout();
    lvlSumBox = new QHBoxLayout();
    lvlSumText = new QLabel();
    lvlSumInput = new QLabel();
    spacer = new QLabel();
    diceInput = new QLabel();


    lvlSumText->setText("lvl points");
    lvlSumText->setAlignment(Qt::AlignLeft);
    lvlSumBox->addWidget(lvlSumText);

    lvlSumInput->setText("0");
    lvlSumInput->setAlignment(Qt::AlignRight);
    lvlSumBox->addWidget(lvlSumInput);

    headerBox->addWidget(spacer);
    headerBox->addWidget(diceInput);
    headerBox->addLayout(lvlSumBox);

// ------------ General Box -------------
    general = new QVBoxLayout();
    rerollButton = new QPushButton();

    general->addLayout(headerBox);
    general->addWidget(rerollButton);
    general->addLayout(abilitiesBox);

// ------------ Finish -------------

    setLayout(general);
    // Set name of Attribute box
    setTitle(s);
}
