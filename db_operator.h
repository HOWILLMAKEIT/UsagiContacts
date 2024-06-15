#ifndef DB_OPERATOR_H
#define DB_OPERATOR_H

#include <QObject>
#include<QSqlDatabase>//连接数据库
#include<QSqlQuery>//查询数据库
#include<QMessageBox>

class db_operator : public QObject
{
    Q_OBJECT
public:
    explicit db_operator(QObject *parent = nullptr);
    //整个项目有且仅有instance 这一个db_operator 对象
    static db_operator& getInstance()
    {
        static db_operator instance;
        return instance ;
    }
    void init();//初始化 | 连接数据库 |在main函数的最开始调用

signals:

private:
    QSqlDatabase m_db;//连接数据库
};

#endif // DB_OPERATOR_H
