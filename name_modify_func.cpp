#include "name_modify_func.h"
#include "ui_name_modify_func.h"

Name_modify_func::Name_modify_func(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Name_modify_func)
{
    ui->setupUi(this);

}

Name_modify_func::~Name_modify_func()
{
    delete ui;
}

//  初始化用户名le的显示
void Name_modify_func::init()
{
    QSqlQuery query;
    query.prepare("SELECT user_name FROM  accounts "
                  "WHERE id=:user_id");
    query.bindValue(":user_id",this->user_id);
    query.exec();
    query.next();
    QString user_name= query.value(0).toString();
    ui->name_le->setText(user_name);

}


void Name_modify_func::on_pushButton_clicked()
{

    QString user_name= ui->name_le->text();
    QString password = ui->password_le->text();
    QSqlQuery query;
    query.prepare("SELECT password FROM  accounts "
                  "WHERE id=:user_id");
    query.bindValue(":user_id",this->user_id);
    query.exec();
    query.next();
    QString real_password = query.value(0).toString();
    if(real_password!=password)
    {
        sound.ha.play();
       QMessageBox::warning(this, "修改失败", "密码错误");
    }
    else
    {
        //查看是否有相同的用户名
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT user_name FROM accounts WHERE user_name = :username");
        checkQuery.bindValue(":username", user_name);
        checkQuery.exec();
        if(checkQuery.next()) //如果已经有这个用户名
        {
            sound.ha.play();
            QMessageBox::warning(this, "修改失败", "用户名已存在");

            return ; //不运行下面的代码
        };

        query.prepare("UPDATE accounts "
                      "SET user_name=:user_name "
                      " WHERE  id=:user_id ");
        query.bindValue(":user_name",user_name);
        qDebug()<<user_name;
        query.bindValue(":user_id",this->user_id);
        query.exec();
        sound.yaha.play();
        QMessageBox::information(this, "修改用户名", "修改成功");

        //关闭修改页面
        this->close();
    }
}
