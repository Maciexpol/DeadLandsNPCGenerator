#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QObject>
#include <QProgressDialog>
#include <QInputDialog>
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

    void setActiveSession(const Session &session);

public:
    SessionManager();

    bool isActive() const{return this->_isActive;};
    Session getActiveSession() const{return this->activeSession;};

public slots:
    void createNewSession();
    void openNewSession();
    //void deleteCurrentSession();
    void saveCurrentSession();
    void closeCurrentSession();

signals:
    void updateSessionInfo(Session session);

};

#endif // SESSIONMANAGER_H
