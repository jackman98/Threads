#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QDir>

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = nullptr);
    ~Database();
    void connectToDataBase();

public slots:
    bool insertIntoCoordinates(const QString &figure_, const int &x_, const int &y_);
    bool updateCoordinates(const QString &figure_, const int &x_, const int &y_);

    bool removeRecord(QString table, const int id);
    void showTables();

private:
    QSqlDatabase db;

    bool createDB();
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
};

#endif // DATABASE_H
