#ifndef SEARCH_FUNC_H
#define SEARCH_FUNC_H

#include <QWidget>
#include<QCloseEvent>
namespace Ui {
class Search_func;
}

class Search_func : public QWidget
{
    Q_OBJECT

public:
    explicit Search_func(QWidget *parent = nullptr);
    ~Search_func();
    void closeEvent(QCloseEvent *e);
signals:
    void closed();   //关闭注册窗口的信号
private:
    Ui::Search_func *ui;
};

#endif // SEARCH_FUNC_H
