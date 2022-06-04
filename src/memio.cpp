#include "memio.h"

namespace MemIO{
    QString mainSaveFolder = "./saves";
    QString sessionsSavingFolder = "./saves/sessions";
    QString charactersSavingFolder = "./saves/characters";

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

void save(const Character &character){
    if(!character.XmlValidate()){
        //TODO: IDK if I have to check this tbh, better leave it here for now
        QMessageBox message;
        message.setText("Cannot save character.");
        message.exec();
        return;
    }
    QDomDocument doc("MyDocument");
    QDomElement root = character.XmlSerialize(doc);
    root.setNodeValue(QString::number(character.getUniqueID()));
    saveToFile(root, charactersSavingFolder);
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

bool load(Character &character, const QString &characterUniqueID){
    QFile file(charactersSavingFolder + "/" + characterUniqueID);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug("Error opening character file.");
        return false;
    }
    QDomDocument doc;
    doc.setContent(&file);
    file.close();
    QDomElement node= doc.firstChildElement();
    character.XmlDeserialize(node);
    return true;
}

    QVector<QVector<QString>> loadAbilities(){
        QDomDocument readerDoc;
        QFile file(":/files/attributes.xml");
        if(!file.open(QIODevice::ReadOnly)){
            qDebug("Error loading file!");
            return {};
        }
        readerDoc.setContent(&file);
        file.close();

        QDomElement attributes = readerDoc.documentElement();
        QVector<QVector<QString>> attributesVector;

        // For each attribute
        QDomElement attribute = attributes.firstChildElement();
        while(!attribute.isNull()){
            QVector<QString> abilities;
            QDomElement ability = attribute.firstChildElement();
            while(!ability.isNull()){
                abilities.append(ability.attribute("name", ""));
                ability = ability.nextSiblingElement();
            }
            attributesVector.append(abilities);
            attribute = attribute.nextSiblingElement();
        }
        return attributesVector;
    }

QVector<QVector<QString>> loadAbilities(){
    QDomDocument readerDoc;
    QFile file(":/files/attributes.xml");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug("Error loading file!");
        return {};
    }
    readerDoc.setContent(&file);
    file.close();

    QDomElement attributes = readerDoc.documentElement();
    QVector<QVector<QString>> attributesVector;

    // For each attribute
    QDomElement attribute = attributes.firstChildElement();
    while(!attribute.isNull()){
        QVector<QString> abilities;
        QDomElement ability = attribute.firstChildElement();
        while(!ability.isNull()){
            abilities.append(ability.attribute("name", ""));
            ability = ability.nextSiblingElement();
        }
        attributesVector.append(abilities);
        attribute = attribute.nextSiblingElement();
    }
    return attributesVector;
}
}
