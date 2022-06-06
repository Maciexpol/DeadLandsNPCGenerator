#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QObject>
#include <QProgressDialog>
#include <QInputDialog>
#include <QStringListModel>
#include "../memio.h"
#include "sessioncharacter.h"

/*!
 * \brief Core of the session system. Manages sessions.
 *
 * SessionManager enables session creation, deletion, closing, opening and saving.
 * It is also responsible for updating MainWindow with session information.
 *
 */
class SessionManager : public QObject, Serializable
{
    Q_OBJECT

private:
    QString defaultSessionName;
    //Session specific fields
    QString name;
    QString description;
    QDate creationDate;
    qint16 npcCount;
    QVector<SessionCharacter> characters;

    //Managing fields
    bool isActive;
    QStringListModel *characterModel;

    void setSessionData(QString newName, QString newDescription, QDate newDate, qint16 newCount);
    void createCharacterModel();
    void updateInfo();

public:
    SessionManager();
    ~SessionManager();

    QString getName() const{return this->name;};
    QString getDescription() const{return this->description;};
    QDate getCreationDate() const{return this->creationDate;};
    qint16 getNpcCount() const{return this->npcCount;};
    QStringListModel* getCharacterModel() const{return this->characterModel;};
    QVector<SessionCharacter> getCharacters() const{return this->characters;};

    QDomElement XmlSerialize() const override;
    void XmlDeserialize(const QDomElement &element) override;

public slots:
    void createNewSession();
    void openNewSession();
    //void deleteCurrentSession();
    void saveCurrentSession();
    void closeCurrentSession();
    void listDoubleClicked(const QModelIndex &index);

    //Character
    void addCharacter(const SessionCharacter &character);
    void deleteCharacterFromSession(QModelIndex);

signals:
    void linkCharacterList(QStringListModel*);
    void updateSessionInfo(SessionManager&);
    void tempStatusBar(QString);
    void loadCharacter(const SessionCharacter&);
};

#endif // SESSIONMANAGER_H
