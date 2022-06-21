#ifndef TRAITWIDGET_H
#define TRAITWIDGET_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

enum TraitType {
    EDGE = 0,
    HINDRANCE = 1
};

class TraitWidget : public QVBoxLayout
{
    Q_OBJECT
private:
    QWidget* header;
        QHBoxLayout* header_layout;
            QLabel* name;
            QLabel* points;

    QLabel* description;

public:
    TraitWidget(){};
    ~TraitWidget();
    TraitWidget(QString name, qint16 points, QString description, TraitType);
};

#endif // TRAITWIDGET_H
