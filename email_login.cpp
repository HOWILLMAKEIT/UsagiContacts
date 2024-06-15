#include "email_login.h"
#include "qregularexpression.h"
#include "ui_email_login.h"

email_login::email_login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::email_login)
{
    ui->setupUi(this);
}

email_login::~email_login()
{
    delete ui;
}

void email_login::on_pushButton_clicked()
{


    account= ui->account_le->text();
    password= ui->password_le->text();


    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if( !account.isEmpty()&& !regex.match(account).hasMatch())
    {
        sound.ha.play();
        QMessageBox::warning(this, "登录失败", "邮箱格式错误");
        return;
    }
    //授权码不能为空
    if(password.isEmpty())
    {
        sound.ha.play();
        QMessageBox::warning(this, "登录失败", "授权码不能为空");
        return;
    }
    emit login_ready();
}

