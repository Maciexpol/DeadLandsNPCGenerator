#include "memio.h"
#include <QDir>
#include <QMessageBox>

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

bool saveToFile(const QDomElement &root, const QString &path){
    QDomDocument document("MyDocument");
    document.appendChild(root);

    QFile file(path + '/' + root.nodeValue() + ".xml");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug("Failed to open device for writing");
        return false;
    }
    QTextStream stream(&file);
    stream << document.toString();
    file.close();
    qDebug("Saved on disk");
    return true;
}

void save(const Session &session){
    if(!session.XmlValidate()){
        QMessageBox message;
        message.setText("Cannot save session, check if name is present.");
        message.exec();
        return;
    }
    QDomDocument doc("MyDocument");
    QDomElement root = session.XmlSerialize(doc);
    root.setNodeValue(session.getName());
    saveToFile(root, sessionsSavingFolder);
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
