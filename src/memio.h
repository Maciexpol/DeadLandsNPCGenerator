#ifndef MEMIO_H
#define MEMIO_H

#include <QtXml\QDomDocument>
#include <QString>
#include <QFile>
#include <QFileDialog>

#include "./sessions/session.h"

/*!
 *  \brief Provides saving and reading options for application objects.
 *
 *  MemIO saves objects on disk using QDomDocument. It starts serialization
 *  of the objects and saves them in specific folders on user's drive.
 */
namespace MemIO{

    extern QString mainSaveFolder;
    extern QString sessionsSavingFolder;

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
     * \param session Session to save
     */
    void save(const Session &session);

    /*!
     * @brief Loads session from file.
     * @param session object on which deserialization will be performed.
     * @return Whether operation was successful or not.
     */
    bool load(Session &session);
}

#endif // MEMIO_H
