#ifndef EMAIL_FUNC_NORMAL_H
#define EMAIL_FUNC_NORMAL_H

#include <QWidget>
#include<QDate>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QSortFilterProxyModel>
#include<mysound.h>
namespace Ui {
class Email_func_normal;
}

class Email_func_normal : public QWidget
{
    Q_OBJECT

public:
    explicit Email_func_normal(QWidget *parent = nullptr);
    ~Email_func_normal();
    int user_id;
    QSqlQueryModel * model ;
    MySound sound ;
private slots:
    void on_pushButton_clicked();

private:
    Ui::Email_func_normal *ui;
};

#endif // EMAIL_FUNC_NORMAL_H
