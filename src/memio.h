#ifndef MEMIO_H
#define MEMIO_H

#include <QtXml\QDomDocument>
#include <QString>
#include <QFile>
#include <QFileDialog>

/*!
 *  \brief Provides saving and reading options for application objects.
 *
 *  MemIO saves objects on disk using QDomDocument. It starts serialization
 *  of the objects and saves them in specific folders on user's drive.
 */
namespace MemIO{

    extern QString mainSaveFolder;
    extern QString sessionsSavingFolder;
    extern QString charactersSavingFolder;

    /*!
     * \brief Creates folder structure for entire program
     */
    void createFolderStructure();

    /*!
     * \brief Writes serialized objects to file.
     * \param root Root of the serialized tree
     * \param path Path to where object should be saved. Usage of MemIO variables is
     * recommended.
     */
    bool saveToFile(const QDomElement &root, const QString &path);

    /*!
     * \brief Saves session to file
     * \param node Serialized session to save
     */
    bool saveSession(QDomElement node);

    /*!
     * \brief Saves character to file
     * \param node Serialized character to save
     */
    bool saveCharacter(QDomElement node);

    /*!
     * @brief Loads session from file.
     * @param filename name of the file in which wanted session is stored (normally it will be session name)
     * @return Serialized session object
     */
    QDomElement loadSession(QString &fileName);

    //TODO: ADD BETTER OPIS
    /*!
     * @brief Loads character from file.
     * @param character object on which deserialization will be performed.
     * @param characterUniqueID unique ID of wanted character
     * @return Serialized character object
     */
    QDomElement load(QString &uniqueID);

    QVector<QVector<QString>> loadAbilities();

}

#endif // MEMIO_H
