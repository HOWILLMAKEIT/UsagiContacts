#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include"regist.h"
#include"mainfunc.h"
#include"mysound.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();
    int user_id;
    MySound sound;
private slots:
    void on_regist_pb_clicked();
    void on_show();

    void creat_mainfunc();

    void on_login_pb_clicked();
signals:
    void login_ready();//成功登录信号
private:
    Ui::Login *ui;
};


#endif // LOGIN_H
