#ifndef EMAIL_SEND_FUNC_H
#define EMAIL_SEND_FUNC_H

#include "QAbstractItemModel"
#include <QWidget>
#include<QMessageBox>
#include<QSqlQuery>
#include <QTcpSocket>
#include<QByteArray>
#include<email_login.h>
#include<email.h>
#include<mysound.h>
namespace Ui {
class Email_send_func;
}

class Email_send_func : public QWidget
{
    Q_OBJECT

public:
    explicit Email_send_func(QWidget *parent = nullptr);
    ~Email_send_func();
    int user_id;
    Email email;
    email_login * email_login_page = new email_login();//只需要一个
    MySound sound;
public slots:


private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void send_email_success();
    void on_pushButton_clicked();

private:
    Ui::Email_send_func *ui;
};

#endif // EMAIL_SEND_FUNC_H
