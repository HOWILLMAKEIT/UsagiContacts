#include "delete_account.h"
#include "ui_delete_account.h"

Delete_account::Delete_account(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Delete_account)
{
    ui->setupUi(this);
}

Delete_account::~Delete_account()
{
    delete ui;
}

void Delete_account::on_pushButton_clicked()
{
    QString password = ui->lineEdit->text();\
    QSqlQuery query;
    query.prepare("SELECT password FROM accounts "
                  "WHERE id = :user_id ");
    query.bindValue(":user_id",this->user_id);
    query.exec();
    query.next();
    if(query.value(0).toString() != password)
    {
        sound.ha.play();
        QMessageBox:: warning(this,"注销失败","密码错误！");
        return;
    }
    query.prepare("DELETE FROM accounts "
                  "WHERE id = :user_id ");
    query.bindValue(":user_id",this->user_id);
    query.exec();
    emit delete_account();
    this->close();
    sound.wula.play();
    QMessageBox:: information (this,"注销","注销成功!");
}

