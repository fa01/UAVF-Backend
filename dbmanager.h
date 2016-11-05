#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

/**
 * Class: DBManager
 * Date: Fall 2016
 * Credits: Aung(David) Moe, Rayan Ahmed
 *
 * Database system for logging system information from the drones for the UAVF project.
 *
 * Required: SQLite
 *
 * Can follow instructions from: https://github.com/katecpp/sql_with_qt
 *
 */
class vector;

class DbManager
{
public:
    ////=== Constructors ===////

    // Sets up a connection with db from 'file' and opens it
    DbManager(const QString& path = "./UAVFDatabase.db");
    // Closes the db connection
    ~DbManager();


    ////=== Accessors ===////

    bool isOpen() const;
    vector<string> getAllMissions() const;


    ////=== Mutators ===////

    bool createMission(const QString& name);
    void clearAllData();
    bool AddValues(QList<Protocol::Waypoint>* wp);




private:
    QSqlDatabase m_db;

    ////=== Private Helper Methods ===////

    // Create required tables for UAVF if it doesn't already exist
    // Caller: constructor.
    void createTablesIfDoesntExist();
};

#endif // DBMANAGER_H
