#include "database.h"

Database::Database(QObject *parent) : QObject(parent)
{

}

Database::~Database()
{
    closeDataBase();
}

void Database::connectToDataBase()
{
    qDebug() << QFile(QDir::currentPath() + "/data.db").exists();
    if(!QFile(QDir::currentPath() + "/data.db").exists())
        restoreDataBase();
    else
        openDataBase();
}

bool Database::insertIntoCoordinates(const QString &figure_, const int &x_, const int &y_)
{
    QSqlQuery query;

    query.prepare("INSERT INTO coordinates (figure, x, y)"
                  " VALUES (:figure_, :x_, :y_);");

    query.bindValue(":figure_", figure_);
    query.bindValue(":x_",       x_);
    query.bindValue(":y_",       y_);

    if (x_ < 0 || y_ < 0) {
        qDebug() << "error insert into coordinates";
        qDebug() << "non positive salary";
        return false;
    }

    if(!query.exec()) {
        qDebug() << "error insert into coordinates";
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool Database::updateCoordinates(const QString &figure_, const int &x_, const int &y_)
{
    QSqlQuery query;

    query.prepare("UPDATE coordinates set x = :x, "
                  "y = :y "
                  "where figure = :figure;");

    query.bindValue(":figure", figure_);
    query.bindValue(":x", x_);
    query.bindValue(":y", y_);

    if (x_ < 0 || y_ < 0) {
        qDebug() << "error update coordinates";
        qDebug() << "non positive coordinates";
        return false;
    }

    if(!query.exec()){
        qDebug() << "error update coordinates";
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool Database::removeRecord(QString table, const int id)
{
    QSqlQuery query;
    qDebug() << id;
    query.prepare("DELETE FROM " + table + " WHERE id = :ID ;");
    query.bindValue(":ID", id);
    qDebug() << query.executedQuery();
    if(!query.exec()){
        qDebug() << "error delete row " << table;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
    return false;
}

bool Database::openDataBase()
{

    db = QSqlDatabase::addDatabase("QSQLITE");

    db.database("qt_sql_default_connection", true);
    db.setDatabaseName(QDir::currentPath() + "/data.db");

    if(db.open()){
        QSqlQuery query1;
        query1.exec("PRAGMA foreign_keys = ON;");
        QSqlQuery query("PRAGMA foreign_keys;");
        while (query.next()) {
            QString country = query.value(0).toString();
            qDebug() << country;
        }
        return true;
    } else {
        return false;
    }
}

bool Database::restoreDataBase()
{
    if(openDataBase()){
        if(!createDB()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

void Database::closeDataBase()
{
    db.close();
}

bool Database::createDB()
{
    QSqlQuery query;
    query.exec("create table if not exists coordinates ("
               "id integer primary key autoincrement not null,"
               "figure varchar(50) unique not null,"
               "x integer NOT NULL,"
               "y integer NOT NULL);");
}

void Database::showTables()
{
    QStringList lst = db.tables();
    foreach (QString str, lst) {
        qDebug() << "Table:" << str;
    }
}
