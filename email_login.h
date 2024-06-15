#ifndef EMAIL_LOGIN_H
#define EMAIL_LOGIN_H

#include <QWidget>
#include<QMessageBox>
#include<mysound.h>
namespace Ui {
class email_login;
}

class email_login : public QWidget
{
    Q_OBJECT

public:
    explicit email_login(QWidget *parent = nullptr);
    ~email_login();
    QString account;
    QString password;
    MySound sound;
signals:
    void login_ready();
private slots:
    void on_pushButton_clicked();

private:
    Ui::email_login *ui;
};

#endif // EMAIL_LOGIN_H
