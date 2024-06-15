#include "password_modify_func.h"
#include "ui_password_modify_func.h"

Password_modify_func::Password_modify_func(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Password_modify_func)
{
    ui->setupUi(this);
}

Password_modify_func::~Password_modify_func()
{
    delete ui;
}

void Password_modify_func::on_pushButton_clicked()
{

    QString password1 = ui->lineEdit->text();
    QString password2 = ui->lineEdit_2->text();
    QString password3 = ui->lineEdit_3->text();
    QSqlQuery query;
    query.prepare("SELECT password FROM  accounts "
                  "WHERE id=:user_id");
    query.bindValue(":user_id",this->user_id);
    query.exec();
    query.next();
    if(query.value(0).toString() != password1  )
    {
        sound.ha.play();
        QMessageBox::warning(this, "修改失败", "密码错误");
        return ;
    }
    if(password2 != password3)
    {
        sound.ha.play();
        QMessageBox::warning(this, "修改失败", "两次输入的密码不一致");
        return ;
    }
    query.prepare("UPDATE accounts "
                  "SET password=:password "
                  " WHERE  id=:user_id ");
    query.bindValue(":password",password2);
    query.bindValue(":user_id",this->user_id);
    query.exec();
    sound.yaha.play();
    QMessageBox::information (this, "修改密码", "修改成功！");

}

