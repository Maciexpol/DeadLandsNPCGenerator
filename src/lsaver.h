#ifndef LSAVER_H
#define LSAVER_H

#include <QtXml\QDomDocument>
#include <QString>
#include <QFile>

#include "./sessions/session.h"

/*!
 *  \brief Provides saving options for application elements
 *
 *  LSaver saves objects on disk using QDomDocument. It starts serialization
 *  of the objects and saves them in specific folders on user's disk.
 */
namespace LSaver{

    /*!
     * \brief Creates folder structure for entire programm
     */
    void createFolderStructure();

    /*!
     * \brief Writes serialized objects on disk.
     * \param root - root of the serialized tree
     * \param relativePath - relative path to where you would like to put
     * objects.
     */
    void saveOnDisk(const QDomElement &root, const QString relativePath);

    void save(const Session &session);
}

#endif // LSAVER_H
