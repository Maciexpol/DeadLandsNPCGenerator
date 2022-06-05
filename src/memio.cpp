#include "memio.h"

class Character;
class Session;

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

    //Check if characters saving folder exists
    if(!QDir(charactersSavingFolder).exists())
        QDir().mkdir(charactersSavingFolder);
}

bool saveToFile(const QDomElement &root, const QString &path){
    QDomDocument document("doc");
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

bool saveSession(QDomElement node){
    return saveToFile(node, sessionsSavingFolder);
}

bool saveCharacter(QDomElement node){
    return saveToFile(node, charactersSavingFolder);
}

QDomElement loadSession(QString &fileName){
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug("Error opening session file.");
        return {};
    }
    QDomDocument document;
    document.setContent(&file);
    file.close();
    return document.firstChildElement();
}

QDomElement loadCharacter(QString &uniqueID){
//    QFile file(charactersSavingFolder + "/" + characterUniqueID);
//    if(!file.open(QIODevice::ReadOnly)){
//        qDebug("Error opening character file.");
//        return false;
//    }
//    QDomDocument doc;
//    doc.setContent(&file);
//    file.close();
//    QDomElement node= doc.firstChildElement();
//    character.XmlDeserialize(node);
//    return true;
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
