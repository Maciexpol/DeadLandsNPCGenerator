#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./src/sessions/sessionmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createConnections(const SessionManager &sessionManager) const;

private slots:

    void updateSessionInfo(const Session& session);

    void on_actionSessionNew_triggered();

    void on_actionSessionSave_triggered();

    void on_actionSessionClose_triggered();

    void on_actionSessionOpen_triggered();

signals:
    void createNewSession();
    void saveCurrentSession();
    void closeCurrentSession();
    void openNewSession();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
