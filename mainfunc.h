#ifndef MAINFUNC_H
#define MAINFUNC_H

#include <QWidget>
#include"add_func.h"
#include"modify_func.h"
#include"QSqlQuery"
#include"QSqlQueryModel"
#include<QAction>
#include<qmenu.h>
#include<qicon.h>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include<QImage>
#include<name_modify_func.h>
#include<password_modify_func.h>
#include<delete_account.h>
#include<mysound.h>
namespace Ui {
class Mainfunc;
}

class Mainfunc : public QWidget
{
    Q_OBJECT

public:
    explicit Mainfunc(QWidget *parent = nullptr);
    ~Mainfunc();
    int user_id;//用户唯一标识
    QSqlQueryModel * qmodel  ;
    void init();
    // 用户头像
    void user_Avatar();
    QImage image;
    QMenu *user_Menu;//菜单
    QAction *user_Action1;
    QAction *user_Action2;
    QAction *user_Action3;
    QAction *user_Action4;
    QAction *user_Action5;


    //右键菜单
    void set_menu();
    QMenu *tableviewMenu;//菜单
    QAction *Action1;//菜单项
    QAction *Action2;
    Modify_func * modify_func =new Modify_func ;

    void closeEvent(QCloseEvent *e);

    MySound sound;

    Email_func * email_func_page = new Email_func();//生日查询页面 // 只需要一个
public slots:

    void Menu_Slot(QPoint p);//右键菜单槽函数
signals:
    void exit_account();
private slots:
    void on_add_buttom_clicked();
    void on_show() // 重新显示
    {
        this->show_cot();//在show之前先刷新table
        this->show();
    }
    void show_cot(); // 刷新




    void on_user_pb_clicked();

    void on_email_pb_clicked();

    void on_search_pb_8_clicked();

private:
    Ui::Mainfunc *ui;
};



#endif // MAINFUNC_H
