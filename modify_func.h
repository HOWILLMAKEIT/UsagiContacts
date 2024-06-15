#ifndef MODIFY_FUNC_H
#define MODIFY_FUNC_H

#include <QWidget>
#include<QAbstractItemModel>
#include<QDate>
#include<QSqlQuery>
#include <QFileDialog>
#include<Qmessagebox>
#include<QBuffer>
#include<email_func.h>
#include<mysound.h>
namespace Ui {
class Modify_func;
}

class Modify_func : public QWidget
{
    Q_OBJECT

public:
    explicit Modify_func(QWidget *parent = nullptr);
    ~Modify_func();
    QAbstractItemModel *model;
    QModelIndex index;
    int user_id;//用户唯一标识
    QImage image ;
    QString name;
    QDate birth;
    QString phone;
    QString email;
    QString type;
    QString special_info;
    void data_init();//数据初始化
    MySound sound;
public slots:
    void Action1_Slot();//菜单项槽函数
    void Action2_Slot();

signals:

    void delete_ready();
    void change_ready();
private slots:
    void on_pushButton_clicked();

    void on_photo_pb_clicked();


private:
    Ui::Modify_func *ui;
};

#endif // MODIFY_FUNC_H
