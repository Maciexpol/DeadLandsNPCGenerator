#include "attributewidget.h"

AttributeWidget::AttributeWidget(const ATTRIBUTES name, QVector<QString> inputNames){
    // translate name from enum to string
    enumName = name;
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
        nameLabel->setFixedHeight(maxLabelSize);
        namesVector.push_back(nameLabel);

        QLabel *lvlLabel = new QLabel();
        lvlLabel->setText("0");
        lvlLabel->setAlignment(Qt::AlignCenter);
        lvlLabel->setStyleSheet("font-weight: bold;");
        lvlLabel->setFixedHeight(maxLabelSize);
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

    spacer = new QLabel();
    diceInput = new QLabel();

    if(inputNames.length() > 0){
        lvlSumBox = new QHBoxLayout();
        lvlSumText = new QLabel();
        lvlSumInput = new QLabel();

        lvlSumText->setText("<i>lvl points</i>");
        lvlSumText->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
        lvlSumBox->addWidget(lvlSumText);

        lvlSumInput->setText("0");
        lvlSumInput->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
        lvlSumInput->setStyleSheet("font-weight: bold;");
        lvlSumBox->addWidget(lvlSumInput);

        headerBox->addWidget(spacer);
    }


    diceInput->setText("0d0");
    diceInput->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    diceInput->setStyleSheet("font-weight: bold;");

    headerBox->addWidget(diceInput);

    if(inputNames.length() > 0)
        headerBox->addLayout(lvlSumBox);


// ------------ General Box -------------
    general = new QVBoxLayout();

    general->addLayout(headerBox);

    // -- reroll button --
    _hasAbilities = false;
    if(inputNames.length() > 1){
        _hasAbilities = true;
        rerollButton = new QPushButton();
        rerollButton->setText("Roll Points Distribution");
        general->addWidget(rerollButton);
    }

    general->addLayout(abilitiesBox);


// ------------ Finish -------------

    setLayout(general);
    QSizePolicy n = QSizePolicy();
    n.setHorizontalPolicy(QSizePolicy::Policy::Preferred);
    n.setVerticalPolicy(QSizePolicy::Policy::Fixed);
    setSizePolicy(n);
    // Set name of Attribute
    QString title;
    title.append(s);
    setTitle(title);
    setAlignment(Qt::AlignCenter);
}

void AttributeWidget::setDiceText(const QString & inputDice){
    diceInput->setText(inputDice);
}

void AttributeWidget::setLvlSumText(const QString & inputLvlSum){
    lvlSumInput->setText(inputLvlSum);
}

void AttributeWidget::setAbilitiesLvlsText(const QVector<QString> & inputLvls){
    for(qint16 i = 0; i < lvlVector.length(); i++){
        lvlVector[i]->setText(inputLvls[i]);
    }
}

void AttributeWidget::clearDiceText(){
    setDiceText("0d0");
}

void AttributeWidget::clearLvlSumText(){
    setLvlSumText("0");
}

void AttributeWidget::clearAbilitiesLvlsText(){
    QVector<QString> temp;
    for(qint16 i = 0; i < lvlVector.length(); i++){
        temp.append("0");
    }

    setAbilitiesLvlsText(temp);
}

void AttributeWidget::clear(){
    clearDiceText();
    clearLvlSumText();
//    clearAbilitiesLvlsText();
}

void AttributeWidget::buttonEmitter(){
    emit rollSpecificAbility(enumName);
}

void AttributeWidget::connectButton(const Character & character){
    qDebug("WYPIERDALAM SIE 1 2 3");
    QObject::connect(rerollButton, &QPushButton::clicked, this, &AttributeWidget::buttonEmitter);
    QObject::connect(this, &AttributeWidget::rollSpecificAbility, &character, &Character::rollSpecificAbility);
}


