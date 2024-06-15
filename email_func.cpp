#include "email_func.h"
#include "ui_email_func.h"

Email_func::Email_func(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Email_func)
{
    ui->setupUi(this);


    //添加page
    ui->stackedWidget->addWidget(&email_func_birth_page);// 此时email_func_birth_page的index为0
    ui->stackedWidget->addWidget(&email_func_normal_page);  // email_func_normal_page的 index为1]
    ui->stackedWidget->addWidget(&email_send_func_page);
    //管理按钮
    btnGroup.setExclusive(true);
    btnGroup.addButton(ui->birth_pb, 0);
    btnGroup.addButton(ui->normal_pb, 1);
    btnGroup.addButton(ui->email_pb, 2);
    //连接信号
    connect(&btnGroup, &QButtonGroup::buttonClicked, this, &Email_func::onButtonClicked);
    // 设置默认选中的页面
    btnGroup.button(0)->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);
}


// 适配器函数
void Email_func::onButtonClicked(QAbstractButton *button)
{
    sound.wula.play();
    int index = btnGroup.id(button);
    ui->stackedWidget->setCurrentIndex(index);
}




Email_func::~Email_func()
{
    delete ui;
}

void Email_func::init()
{

    this->email_func_birth_page.user_id=this->user_id;
    this->email_func_normal_page.user_id=this->user_id;
    this->email_send_func_page.user_id=this->user_id;

}
