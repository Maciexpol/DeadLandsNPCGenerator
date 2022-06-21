#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>

#include "./src/sessions/sessionmanager.h"
#include "./src/widgets/attributewidget.h"
#include "./src/memio.h"
#include "./src/generator/attribute.h"
#include "src/generator/character.h"
#include "src/data/DataManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createConnections(const SessionManager &sessionManager,
                           const Character &character,
                           const DataManager &dataManager) const;

public slots:
    //
    void linkCharacterList(QStringListModel *list);
    void updateSessionInfo(const SessionManager& session);
    void updateCharacterInfo(const Character& character);
    void tempStatusBar(QString message);
    void updateConnectionStatus(QString message);

    //Sessions slots
    void on_actionSessionNew_triggered();
    void on_actionSessionSave_triggered();
    void on_actionSessionClose_triggered();
    void on_actionSessionOpen_triggered();
    void on_actionAdd_to_session_triggered();
    void on_addToSession_clicked();
    void on_deleteFromSession_clicked();

    void on_actionGeneratorUpdate_triggered();
    void on_actionGenerate_triggered();

    void on_rerollCharacter_clicked();

    void on_actionGeneratorConnect_triggered();

    QVector<QString> getViewListAttributesPriority();
    void updateOutputQueueAndDices(const QVector<ATTRIBUTES> &, const QVector<Dice> &);


signals:
    //Session manager signals
    void createNewSession();
    void saveCurrentSession();
    void closeCurrentSession();
    void openNewSession();

    //Character signals
    void addCharacterToSession();
    void deleteCharacterFromSession(QModelIndex);
    void reRollCharacter();

    //Database signals
    void updateGeneratorData();
    void openConnection();

private:
    Ui::MainWindow *ui;
    QLabel *connectionStatus;

    QVector<AttributeWidget*> attributesWidgetsVecotr;

    void updateOutputDices(const QVector<Dice> & );
    void updateOutputQueue(const QVector<ATTRIBUTES> &);

    void generateAttributesWidgets();

    void updateAttributesInfo();
    void updateTraitsInfo();
    void updateOverwievinfo();


};
#endif // MAINWINDOW_H
