#include "memio.h"
#include <QDir>

namespace MemIO{
    QString mainSaveFolder = "./saves";
    QString sessionsSavingFolder = "./saves/sessions";

void createFolderStructure(){
    // Check if main saving folder exists
    if(!QDir(mainSaveFolder).exists())
        QDir().mkdir(mainSaveFolder);

    // Check if sessions saving folder exists
    if(!QDir(sessionsSavingFolder).exists())
        QDir().mkdir(sessionsSavingFolder);
}

void saveOnDisk(const QDomElement &root, const QString &path){
    QDomDocument document("MyDocument");
    document.appendChild(root);

    QFile file(path + '/' + root.nodeValue() + ".xml");
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
    root.setNodeValue(session.getName());
    saveOnDisk(root, sessionsSavingFolder);
}

bool load(Session &session){
    QString filename = QFileDialog::getOpenFileName(nullptr,
                                                    "Choose session.",
                                                    MemIO::sessionsSavingFolder,
                                                    "XML files (*.xml)");
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug("Error opening session file.");
        return false;
    }
    QDomDocument document;
    document.setContent(&file);
    file.close();
    QDomElement node = document.firstChildElement();
    session.XmlDeserialize(node);
    return true;
}
}
