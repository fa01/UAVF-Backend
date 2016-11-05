#include <dbmanager.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DbManager::DbManager(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
        qDebug() << "Error: connection with database fail";
    }
    else
    {
        qDebug() << "Database: connection ok";
    }

    this->createTablesIfDoesntExist();
}

DbManager::~DbManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}

bool DbManager::createMission(const QString& name)
{
    bool success = false;
    QSqlQuery query;

    query.prepare("INSERT INTO flightinfo(Name) VALUES (:name);");
    query.bindValue(":name", name);
    if (!query.exec())
    {
        qDebug() << "Couldn't create a mission with name: " << name;
        success = true;
    }

    return success;
}


void DbManager::createTablesIfDoesntExist()
{
    QSqlQuery query;

    query.prepare("CREATE TABLE flightinfo(Name TEXT, ID INTEGER PRIMARY KEY);");
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'Mission': one might already exist.";
    }

    /*
    query.prepare("CREATE TABLE flightinfo(ID INTEGER PRIMARY KEY, Name TEXT);");
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'Mission': one might already exist.";
    }
    */
}




/*
typedef struct
{
    double lat = 0;
    double lon = 0;
    float alt = 0;
    float speed = 0;
} Waypoint;
*/

bool DbManager::AddValues(QList<Protocol::Waypoint>* wp){
    bool succeeded = false;
    Protocol::Waypoint temp;
    for (int i = 0; i < wp->size(); i++){
        temp = wp->at(i);
        QSqlQuery query;
        query.prepare("INSERT INTO flightinfo (lat) VALUES (:lat)");
        query.addBindValue(":lat", temp.lat);
        query.prepare("INSERT INTO flightinfo (lon) VALUES (:lon)");
        query.addBindValue(":lon", temp.lon);
        query.prepare("INSERT INTO flightinfo (alt) VALUES (:alt)");
        query.addBindValue(":alt", temp.alt);
        query.prepare("INSERT INTO flightinfo (speed) VALUES (:speed)");
        query.addBindValue(":speed", temp.speed);

        if(query.exec())
        {
            succeeded = true;
        }
        else
        {
            qDebug() << "addValues error:  " << query.lastError();
        }
    }

    return succeeded;

}

