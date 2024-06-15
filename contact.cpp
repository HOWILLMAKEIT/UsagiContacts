#include "contact.h"

Contact::Contact() {}

Classmate::Classmate() {}
void Classmate::add_contact(int id, QString name, QDate birth, QString phone, QString email, QString type, QString special_info,QVariant photo)
{
    this->user_id=id;
    this->name=name;
    this->birth=birth;
    this->phone=phone;
    this->email=email;
    this->type="同学";
    this->special_info=special_info;
    this->photo= photo;
    QSqlQuery query;
    query.prepare("INSERT INTO contacts (name, birth, phone, email, type, special_info, user_id,photo)"
                  " VALUES ( :name, :birth, :phone, :email, :type, :special_info, :user_id,:photo)");

    query.bindValue(":name",  this->name);
    query.bindValue(":birth", this-> birth);
    query.bindValue(":phone", this-> phone);
    query.bindValue(":email", this-> email);
    query.bindValue(":type",  this->type);
    query.bindValue(":special_info",  this->special_info);
    query.bindValue(":user_id", this->user_id);
    query.bindValue(":photo", this->photo);
    if(query.exec())
    {
        qDebug()<<"添加联系人成功";
    }
    else
    {
        qDebug()<<"添加联系人失败";
    }
}

Colleague::Colleague() {}
void Colleague::add_contact(int id, QString name, QDate birth, QString phone, QString email, QString type, QString special_info,QVariant photo)
{
    this->user_id=id;
    this->name=name;
    this->birth=birth;
    this->phone=phone;
    this->email=email;
    this->type="同事";
    this->special_info=special_info;
    this->photo= photo;
    QSqlQuery query;
    query.prepare("INSERT INTO contacts (name, birth, phone, email, type, special_info, user_id,photo)"
                  " VALUES ( :name, :birth, :phone, :email, :type, :special_info, :user_id,:photo)");

    query.bindValue(":name",  this->name);
    query.bindValue(":birth", this-> birth);
    query.bindValue(":phone", this-> phone);
    query.bindValue(":email", this-> email);
    query.bindValue(":type",  this->type);
    query.bindValue(":special_info",  this->special_info);
    query.bindValue(":user_id", this->user_id);
    query.bindValue(":photo", this->photo);
    if(query.exec())
    {
        qDebug()<<"添加联系人成功";
    }
    else
    {
        qDebug()<<"添加联系人失败";
    }
}

Friend::Friend() {}
void Friend::add_contact(int id, QString name, QDate birth, QString phone, QString email, QString type, QString special_info,QVariant photo)
{
    this->user_id=id;
    this->name=name;
    this->birth=birth;
    this->phone=phone;
    this->email=email;
    this->type="朋友";
    this->special_info=special_info;
    this->photo= photo;
    QSqlQuery query;
    query.prepare("INSERT INTO contacts (name, birth, phone, email, type, special_info, user_id,photo)"
                  " VALUES ( :name, :birth, :phone, :email, :type, :special_info, :user_id,:photo)");

    query.bindValue(":name",  this->name);
    query.bindValue(":birth", this-> birth);
    query.bindValue(":phone", this-> phone);
    query.bindValue(":email", this-> email);
    query.bindValue(":type",  this->type);
    query.bindValue(":special_info",  this->special_info);
    query.bindValue(":user_id", this->user_id);
    query.bindValue(":photo", this->photo);
    if(query.exec())
    {
        qDebug()<<"添加联系人成功";
    }
    else
    {
        qDebug()<<"添加联系人失败";
    }
}


Relative::Relative() {}
void Relative::add_contact(int id, QString name, QDate birth, QString phone, QString email, QString type, QString special_info,QVariant photo)
{
    this->user_id=id;
    this->name=name;
    this->birth=birth;
    this->phone=phone;
    this->email=email;
    this->type="亲戚";
    this->special_info=special_info;
    this->photo= photo;
    QSqlQuery query;
    query.prepare("INSERT INTO contacts (name, birth, phone, email, type, special_info, user_id,photo)"
                  " VALUES ( :name, :birth, :phone, :email, :type, :special_info, :user_id,:photo)");

    query.bindValue(":name",  this->name);
    query.bindValue(":birth", this-> birth);
    query.bindValue(":phone", this-> phone);
    query.bindValue(":email", this-> email);
    query.bindValue(":type",  this->type);
    query.bindValue(":special_info",  this->special_info);
    query.bindValue(":user_id", this->user_id);
    query.bindValue(":photo", this->photo);
    if(query.exec())
    {
        qDebug()<<"添加联系人成功";
    }
    else
    {
        qDebug()<<"添加联系人失败";
    }
}


Other_cnt::Other_cnt() {}
void Other_cnt::add_contact(int id, QString name, QDate birth, QString phone, QString email, QString type, QString special_info,QVariant photo)
{
    this->user_id=id;
    this->name=name;
    this->birth=birth;
    this->phone=phone;
    this->email=email;
    this->type=type;
    this->special_info=special_info;
    this->photo= photo;
    QSqlQuery query;
    query.prepare("INSERT INTO contacts (name, birth, phone, email, type, special_info, user_id,photo)"
                  " VALUES ( :name, :birth, :phone, :email, :type, :special_info, :user_id,:photo)");

    query.bindValue(":name",  this->name);
    query.bindValue(":birth", this-> birth);
    query.bindValue(":phone", this-> phone);
    query.bindValue(":email", this-> email);
    query.bindValue(":type",  this->type);
    query.bindValue(":special_info",  this->special_info);
    query.bindValue(":user_id", this->user_id);
    query.bindValue(":photo", this->photo);
    if(query.exec())
    {
        qDebug()<<"添加联系人成功";
    }
    else
    {
        qDebug()<<"添加联系人失败";
    }
}
