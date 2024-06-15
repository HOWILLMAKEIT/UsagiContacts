#ifndef EMAIL_FUNC_H
#define EMAIL_FUNC_H

#include <QWidget>
#include<email_func_birth.h>
#include<email_func_normal.h>
#include<email_send_func.h>
#include<QButtonGroup>
#include <QPropertyAnimation>
#include<QAbstractButton>
#include<mysound.h>
namespace Ui {
class Email_func;
}

class Email_func : public QWidget
{
    Q_OBJECT

public:
    explicit Email_func(QWidget *parent = nullptr);
    ~Email_func();
    int user_id ;
    Email_func_birth email_func_birth_page;
    Email_func_normal email_func_normal_page;
    Email_send_func  email_send_func_page;
    QButtonGroup  btnGroup;
    MySound sound;
    void init();

public slots:
    void  onButtonClicked(QAbstractButton *button);

private:
    Ui::Email_func *ui;
};

#endif // EMAIL_FUNC_H
