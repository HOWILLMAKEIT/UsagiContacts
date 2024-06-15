#include "search_func.h"
#include "ui_search_func.h"

Search_func::Search_func(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Search_func)
{
    ui->setupUi(this);
}

Search_func::~Search_func()
{
    delete ui;
}

void Search_func::closeEvent(QCloseEvent *e)
{
    emit closed();
    e->accept();//关闭窗口
    delete this;//释放之前创建在堆区的Search_func指针的内存
}
