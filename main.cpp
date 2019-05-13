#include <QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>

#include "myserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    QSqlDatabase users_and_hosts = QSqlDatabase::addDatabase("QMYSQL");
//    users_and_hosts.setDatabaseName("Driver={MySQL ODBC 8.0 Unicode Driver};DATABASE = testdb;");
//    users_and_hosts.setUserName("root");
//    users_and_hosts.setPassword("2708tjlfe");
//    if (!users_and_hosts.open())
//    {
//        qDebug() << users_and_hosts.lastError().text();
//    } else {
//        qDebug("seccuss");
//    }

//    users_and_hosts.
//    users_and_hosts.exec();

    MyServer sd(nullptr);

//#include "mainwindow.h"
//#include <QApplication>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
//}



    return a.exec();
}
