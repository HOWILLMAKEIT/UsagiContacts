#ifndef DELETE_ACCOUNT_H
#define DELETE_ACCOUNT_H

#include <QWidget>
#include<QSqlQuery>
#include<QMessageBox>
#include<mysound.h>
namespace Ui {
class Delete_account;
}

class Delete_account : public QWidget
{
    Q_OBJECT

public:
    explicit Delete_account(QWidget *parent = nullptr);
    ~Delete_account();
    int user_id;
    MySound sound;
signals:
    void delete_account();
private slots:
    void on_pushButton_clicked();

private:
    Ui::Delete_account *ui;
};

#endif // DELETE_ACCOUNT_H
