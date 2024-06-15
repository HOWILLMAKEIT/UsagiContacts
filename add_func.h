#ifndef ADD_FUNC_H
#define ADD_FUNC_H

#include <QWidget>
#include<QDate>
#include <QFileDialog>
#include<QMessageBox>
#include"contact.h"
#include<QBuffer>
#include<mysound.h>
namespace Ui {
class Add_func;
}

class Add_func : public QWidget
{
    Q_OBJECT

public:
    explicit Add_func(QWidget *parent = nullptr);
    ~Add_func();
    void closeEvent(QCloseEvent *e);
    int user_id;
    QImage image;
    MySound sound;
signals:
    void closed();
private slots:
    void on_comboBox_activated(int index);

    //添加按钮
    void on_pushButton_clicked();

    void on_photo_pb_clicked();

private:
    Ui::Add_func *ui;
};

#endif // ADD_FUNC_H
