#ifndef CONTACT_H
#define CONTACT_H
#include<QString>
#include<QDate>
#include<QSqlQuery> //查询数据库

class Contact
{
public:
    Contact();
    QString name;       // 姓名
    QDate birth;        // 出生日期
    QString phone;      // 电话号码
    QString email;      // 电子邮件
    QString type;       // 联系人类型（同学、同事、朋友、亲戚、其它）
    QString special_info;
    int user_id;        // 用户ID
    QVariant photo; //照片

    virtual void add_contact(int id, QString name, QDate birth,QString phone,QString email,QString type,QString special_info,QVariant photo)= 0;
};
class Friend: public Contact
{
public:
    Friend();
    void add_contact(int id, QString name, QDate birth,QString phone,QString email,QString type,QString special_info,QVariant photo) override ;
};
class Classmate : public Contact
{
public:
    Classmate();
    void add_contact(int id, QString name, QDate birth,QString phone,QString email,QString type,QString special_info,QVariant photo) override ;
};
class Colleague: public Contact
{
public:
    Colleague();
    void add_contact(int id, QString name, QDate birth,QString phone,QString email,QString type,QString special_info,QVariant photo) override ;
};
class Relative: public Contact
{
public:
    Relative();
    void add_contact(int id, QString name, QDate birth,QString phone,QString email,QString type,QString special_info,QVariant photo) override ;
};
class Other_cnt : public Contact
{
public:
    Other_cnt();
    void add_contact(int id, QString name, QDate birth,QString phone,QString email,QString type,QString special_info,QVariant photo) override ;
};

#endif // CONTACT_H
