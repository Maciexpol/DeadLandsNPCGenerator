#include "traitwidget.h"

TraitWidget::TraitWidget(QString newName, qint16 newPoints, QString newDescription, TraitType type = TraitType::EDGE) {
    header = new QWidget();
    header->setMaximumHeight(35);

    header_layout = new QHBoxLayout();
    header->setLayout(header_layout);

    name = new QLabel();
    name->setWordWrap(true);
    name->setAlignment(Qt::AlignCenter);

    points = new QLabel();
    points->setWordWrap(true);
    points->setAlignment(Qt::AlignCenter);


    header_layout->addWidget(name);
    header_layout->addWidget(points);

    description = new QLabel();
    description->setWordWrap(true);

    description->setAlignment(Qt::AlignTop);

    this->addWidget(header);
    this->addWidget(description);

    if(type == TraitType::EDGE){
        name->setText("Edge: <b>" + newName + "</b>");
        points->setText("Points: <b>-" + QString::number(newPoints) + "</b>");
    }else{
        name->setText("Hindrance: <b>" + newName + "</b>");
        points->setText("Points: <b>" + QString::number(newPoints) + "</b>");
    }
    description->setText(newDescription);
}

TraitWidget::~TraitWidget(){
    name->setText("");
    description->setText("");
    points->setText("");
}
