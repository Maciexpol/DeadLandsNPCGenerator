#include "lsaver.h"
#include <QDir>

namespace LSaver{

void createFolderStructure(){
    QString mainSaveFolder = "saves";
    QString sessionsSavingFolder = "sessions";

    // Check if main saving folder exists
    if(!QDir("./" + mainSaveFolder).exists())
        QDir().mkdir("./" + mainSaveFolder);

    // Check if sessions saving folder exists
    if(!QDir("./" + mainSaveFolder + '/' + sessionsSavingFolder).exists())
        QDir().mkdir("./" + mainSaveFolder + '/' + sessionsSavingFolder);
}

void saveOnDisk(const QDomElement &root, const QString relativePath){
    QDomDocument document("MyDocument");
    document.appendChild(root);

    QFile file("./saves/" + relativePath + '/' + root.nodeValue() + ".xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug("Failed to open device for writing");
        return;
    }
    QTextStream stream(&file);
    stream << document.toString();
    file.close();
    qDebug("Saved session on disk");
}

void save(const Session &session){
    QDomDocument doc("MyDocument");
    QDomElement root = session.XmlSerialize(doc);
    root.setNodeValue("session-" + session.getName());
    saveOnDisk(root, "sessions");
}
}
