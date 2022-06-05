#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QObject>
#include <QProgressDialog>
#include <QInputDialog>
#include <QStringListModel>
#include "../memio.h"
#include "session.h"

/*!
 * \brief Core of the session system. Manages sessions.
 *
 * SessionManager enables session creation, deletion, closing, opening and saving.
 * It is also responsible for updating MainWindow with session information.
 *
 */
class SessionManager : public QObject
{
    Q_OBJECT

private:
    bool _isActive;
    Session activeSession;
    Session placeholderSession;
    QStringListModel *listModel;

    void setActiveSession(const Session &session);

public:
    SessionManager();
    ~SessionManager();

    bool isActive() const{return this->_isActive;};
    Session getActiveSession() const{return this->activeSession;};

    void createListModel();

public slots:
    void createNewSession();
    void openNewSession();
    //void deleteCurrentSession();
    void saveCurrentSession();
    void closeCurrentSession();

    //Character
    void addCharacterToSession(const qint32 &id, const QString &name);

signals:
    void updateSessionInfo(Session, QStringListModel*);

};

#endif // SESSIONMANAGER_H
