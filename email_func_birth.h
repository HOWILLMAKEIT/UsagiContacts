#ifndef EMAIL_FUNC_BIRTH_H
#define EMAIL_FUNC_BIRTH_H

#include <QWidget>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QSortFilterProxyModel>
#include<QMenu>
#include<QAction>
#include<mysound.h>
namespace Ui {
class Email_func_birth;
}

class Email_func_birth : public QWidget
{
    Q_OBJECT

public:
    explicit Email_func_birth(QWidget *parent = nullptr);
    ~Email_func_birth();
    QSqlQueryModel * model;

    int user_id;
    MySound sound;
private slots:
    void on_pushButton_clicked();


private:
    Ui::Email_func_birth *ui;
};

#endif // EMAIL_FUNC_BIRTH_H
