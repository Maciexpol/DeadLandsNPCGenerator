#include "overview.h"


Overview::Overview()
{
    rollOverview();
}

void Overview::rollOverview() {
    QSqlDatabase db = QSqlDatabase::database("local");
    std::cout << db.isOpen() << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<qint16> num(18, 90);

    //Randomize age
    this->age = num(gen);

    //Check if roll data is available
    if(!db.open()){
        qDebug("NO connection.");
        //There is no connection to database
        //TODO: add temp prompt that there is no connection
        first_name = "DEFAULT";
        last_name = "DEFAULT";
        occupation = "DEFAULT";
        origin = "DEFAULT";
        return;
    }
    qDebug("CONNECTED");
    QSqlQuery query( db);
    int size;

    //Generate origin
    //TODO: Set uniform to match number of records in origins
    num = std::uniform_int_distribution<qint16> (1, 2);
    qint16 originID = num(gen);
    //There are no records in database with originID other than 1 at this moment
    originID = 1;
    query.exec("SELECT origin FROM origins WHERE id=" + QString::number(originID) + ";");
    query.next();
    origin = query.value(0).toString();

    //Generate occupation
    num = std::uniform_int_distribution<qint16> (1, 966);
    qint16 occupationID = num(gen);
    //std::cout << "Occupation ID: " << occupationID << std::endl;
    query.exec("SELECT occupation FROM occupations WHERE id=" + QString::number(occupationID) + ";");
    //std::cout << "Occupation, num rows affected: " << query.numRowsAffected() << std::endl;
    query.next();
    occupation = query.value(0).toString();

    //Generate gender
    //TODO: Maybe there will be more genders in the future, randomize from list
    num = std::uniform_int_distribution<qint16> (0, 1);
    auto genderID = static_cast<qint8>(num(gen));
    gender = genderID;

    //Generate first name
    query.exec("SELECT COUNT(*) FROM first_names WHERE origin_id=" + QString::number(originID) + " AND gender=" + QString::number(genderID) + ";");
    query.next();
    size = query.value(0).toInt();
    std::cout << "First name, size: " << size << std::endl;
    query.exec("SELECT first_name FROM first_names WHERE origin_id=" + QString::number(originID) + " AND gender=" + QString::number(genderID) + ";");
    num = std::uniform_int_distribution<qint16> (0, size-1);
    qint16 index = num(gen);
    query.next();
    if(query.isSelect()){
        if(query.seek(index)){
            first_name = query.value(0).toString();
        }else{
            //Failder to retrieve data, query on first element
            //TODO: Implement error handling
            return;
        }
    }else{
        //TODO: Cokolwiek to ma nie robić
        return;
    }

    //Generate last name
    query.exec("SELECT COUNT(*) FROM last_names WHERE origin_id=" + QString::number(originID) + ";");
    query.next();
    size = query.value(0).toInt();
    query.exec("SELECT last_name FROM last_names WHERE origin_id=" + QString::number(originID) + ";");
    std::cout << "Last name, size: " << size<< std::endl;
    num = std::uniform_int_distribution<qint16> (0, size-1);
    index = num(gen);
    query.next();
    if(query.isSelect()){
        if(query.seek(index)){
            last_name = query.value(0).toString();
        }else{
            //Failder to retrieve data, query on first element
            //TODO: Implement error handling
            return;
        }
    }else{
        //TODO: Cokolwiek to ma nie robić
        return;
    }
}

QDomElement Overview::XmlSerialize() const {
    QDomElement element = QDomDocument().createElement("overview");

    element.setAttribute("first_name", this->first_name);
    element.setAttribute("last_name", this->last_name);
    element.setAttribute("occupation", this->occupation);
    element.setAttribute("origin", this->origin);
    element.setAttribute("age", this->age);
    element.setAttribute("gender", this->gender);
    return element;
}

void Overview::XmlDeserialize(const QDomElement &element) {
    this->first_name = element.attribute("first_name", "UNKNOWN");
    this->last_name = element.attribute("last_name", "UNKNOWN");
    this->occupation = element.attribute("occupation", "UNKNOWN");
    this->origin = element.attribute("origin", "UNKNOWN");
    this->age = static_cast<qint16>(element.attribute("age", "0").toInt());
    this->gender = static_cast<qint8>(element.attribute("gender", "0").toInt());
}
