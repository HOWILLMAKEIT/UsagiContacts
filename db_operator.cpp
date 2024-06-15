#include "db_operator.h"

db_operator::db_operator(QObject *parent)
    : QObject{parent}
{}

void db_operator::init()
{
    // 创建数据库连接
    m_db.setHostName("                      ");
    m_db.setPort(3306);
    m_db.setUserName("          ");
    m_db.setPassword("          ");
    m_db.setDatabaseName("addressbook");


    // 尝试连接数据库
    if (!m_db.open())
    {
        qDebug() << "Error: Failed to connect to the database";

    }
    else {
        qDebug() << "Database connected successfully";
    }
}
