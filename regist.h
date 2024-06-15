#ifndef REGIST_H
#define REGIST_H

#include <QWidget>
#include<QCloseEvent>
#include<QMessageBox>
#include"db_operator.h"
#include<QImage>
#include<QFileDialog>
#include<QBuffer>
#include<mysound.h>
namespace Ui {
class Regist;
}

class Regist : public QWidget
{
    Q_OBJECT

public:
    explicit Regist(QWidget *parent = nullptr);
    ~Regist();
    void closeEvent(QCloseEvent *e);
    QImage  image;
    MySound sound ;
signals:
    void closed();   //关闭注册窗口的信号
    void regist_ready();//注册成功
private slots:
    void on_pushButton_clicked();

    void on_image_pb_clicked();

private:
    Ui::Regist *ui;
};

#endif // REGIST_H
