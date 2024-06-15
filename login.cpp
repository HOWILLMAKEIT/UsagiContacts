#include "login.h"
#include "ui_login.h"
#include<QDebug>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(this,&Login::login_ready,&Login::creat_mainfunc);

}

Login::~Login()
{
    delete ui;
}

// 按下注册按钮，切换到regist 页面
void Login::on_regist_pb_clicked()
{
    sound.wula.play();
    this->hide();
    Regist *regist_page = new Regist();
    regist_page->show();


//连接regist_page 的 closed 信号和 login窗口对象的on_regist_closed槽函数
    connect(regist_page, &Regist::closed, this, &Login::on_show);


//连接regist_page 的 regist_ready 信号和 login窗口对象的on_regist_closed槽函数
    connect(regist_page, &Regist::regist_ready, this, &Login::on_show);

}

void Login::on_show()
{
    //刷新lineEdit
    ui->username_le->setText("");
    ui->password_le->setText("");
    this->show();

}

// Login成功后，转到这里
void Login::creat_mainfunc()
{

    this->hide();
    Mainfunc *mainfunc_page = new Mainfunc();
    mainfunc_page->user_id =this->user_id;

    mainfunc_page->init();
    mainfunc_page->show();

    connect(mainfunc_page,&Mainfunc::exit_account,this,&Login::on_show);

}


void Login::on_login_pb_clicked()
{
    QString username = ui->username_le->text();
    QString password = ui->password_le->text();
    if(!username.isEmpty() && !password.isEmpty())
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM accounts WHERE user_name = :username"); //预处理
        query.bindValue(":username", username);
        if (query.exec())
        {
            //定位到第一个结果集(第一行）
            if(query.next())
            {
                QString real_password = query.value("password").toString();
                if (password == real_password)
                {
                    // 密码正确-----------------------成功登录
                    sound.highest_yaha.play();
                   QMessageBox::information (this, "登录成功", "欢迎使用乌萨奇通讯录");
                   //存储登录账户的id字段
                   this->user_id = query.value("id").toInt();
                    qDebug()<<user_id;
                    emit login_ready();
                }
                else
                {
                    // 密码错误
                    sound.ha.play();
                   QMessageBox::warning(this, "登录失败", "密码不正确");
                }
            }
            else
            {
            sound.ha.play();
            QMessageBox::warning(this, "登录失败", "用户名不存在");
            }
        }
        //语句有问题
        else
        {
            qDebug()<<"查找用用户名失败";
        }
    }
    //有空的部分
    else
    {
        sound.ha.play();
        QMessageBox::warning(this, "错误", "用户名或密码不能为空");
    }
}

