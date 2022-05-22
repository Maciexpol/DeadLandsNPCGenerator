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

private slots:
    void on_actionSessionNew_triggered();

    void updateSessionInfo(Session session);

    void on_sessionNew_clicked();

    void on_sessionSave_clicked();

    void on_actionSessionSave_triggered();

signals:
    void createNewSession();
    void saveCurrentSession();

private:
    Ui::MainWindow *ui;
    SessionManager sessionManager;
};
#endif // MAINWINDOW_H
