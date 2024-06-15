#ifndef PASSWORD_MODIFY_FUNC_H
#define PASSWORD_MODIFY_FUNC_H

#include <QWidget>
#include<QSqlQuery>
#include<QMessageBox>
#include<mysound.h>
namespace Ui {
class Password_modify_func;
}

class Password_modify_func : public QWidget
{
    Q_OBJECT

public:
    explicit Password_modify_func(QWidget *parent = nullptr);
    ~Password_modify_func();
    int user_id;
    MySound sound;
private slots:
    void on_pushButton_clicked();

private:
    Ui::Password_modify_func *ui;
};

#endif // PASSWORD_MODIFY_FUNC_H
