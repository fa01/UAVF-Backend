#include <QCoreApplication>
#include "dbmanager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    DbManager db;

    return a.exec();
}
