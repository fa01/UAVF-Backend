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

    query.prepare("INSERT INTO Mission (Name) VALUES (:name);");
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

    query.prepare("CREATE TABLE Mission(Name TEXT, ID INTEGER PRIMARY KEY);");
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'Mission': one might already exist.";
    }

    /*
    query.prepare("CREATE TABLE MissionPlanning(ID INTEGER PRIMARY KEY, Name TEXT);");
    if (!query.exec())
    {
        qDebug() << "Couldn't create the table 'Mission': one might already exist.";
    }
    */
}

