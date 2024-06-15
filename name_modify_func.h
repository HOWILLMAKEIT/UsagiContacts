#ifndef NAME_MODIFY_FUNC_H
#define NAME_MODIFY_FUNC_H

#include <QWidget>
#include<QSqlQuery>
#include<QMessageBox>
#include<mysound.h>
namespace Ui {
class Name_modify_func;
}

class Name_modify_func : public QWidget
{
    Q_OBJECT

public:
    explicit Name_modify_func(QWidget *parent = nullptr);
    ~Name_modify_func();
    int user_id;
    void init();
    MySound sound;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Name_modify_func *ui;
};

#endif // NAME_MODIFY_FUNC_H
