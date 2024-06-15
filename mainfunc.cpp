#include "mainfunc.h"

#include "ui_mainfunc.h"

Mainfunc::Mainfunc(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Mainfunc)
{
    ui->setupUi(this);


}

Mainfunc::~Mainfunc()
{
    delete ui;

}
//重写关闭事件
void Mainfunc::closeEvent(QCloseEvent *e)
{
    // 保存便利贴
    QString memo = ui->plainTextEdit->toPlainText();
    QSqlQuery query;
    query.prepare("UPDATE accounts "
                  "SET memo=:memo "
                  " WHERE  id=:user_id ");
    query.bindValue(":memo",memo);
    query.bindValue(":user_id",this->user_id);
    query.exec();
    e->accept();//关闭窗口
    delete this;
}

void Mainfunc::init()
{
    this->show_cot();//刷新通讯录
    this->set_menu();//设定右键菜单 //因为table view  对象只有一个因此只需要调用一次
    //头像/头像菜单设置
    user_Avatar();

    // 便利贴设置
    QSqlQuery query;
    query.prepare("SELECT memo FROM accounts "
                  " WHERE  id=:user_id ");
    query.bindValue(":user_id",this->user_id);
    query.exec();
    query.next();
    QString memo = query.value(0).toString();
    ui->plainTextEdit->setPlainText(memo);
}

// 用户头像
void Mainfunc::user_Avatar()
{
    QSqlQuery query;
    query.prepare("SELECT photo "
                  "FROM accounts"
                  " WHERE id=:user_id");

    query.bindValue(":user_id", this->user_id);
    query.exec();
    query.next();
    QPixmap photo;
    photo.loadFromData(query.value(0).toByteArray(), "JPEG");
    image = photo.toImage();
    ui->image_label->setPixmap(photo);
    ui->image_label->setScaledContents(true);//自适应大小
    ui->image_label->setAlignment(Qt::AlignCenter); // 使图片在QLabel中居中显示


    this->user_Menu=new QMenu( ui->user_pb);
    user_Action1 = new QAction("修改头像",  ui->user_pb);
    user_Action2 = new QAction("修改用户名",  ui->user_pb);
    user_Action3 = new QAction("修改密码",  ui->user_pb);
    user_Action4 = new QAction("退出登录",  ui->user_pb);
    user_Action5 = new QAction("注销账号",  ui->user_pb);
    user_Menu->addAction(user_Action1);
    user_Menu->addAction(user_Action2);
    user_Menu->addAction(user_Action3);
    user_Menu->addAction(user_Action4);
    user_Menu->addAction(user_Action5);
    // user_Menu->setStyleSheet(" ") ; // 样式表


    //修改头像
    connect(user_Action1, &QAction::triggered,[=]()
            {
                sound.wula.play();

                // 打开文件对话框
                QString fileName = QFileDialog::getOpenFileName(this,
                                                                tr("Open Image"), "",
                                                                tr("Image Files (*.png *.jpg *.bmp)"));

                if (!fileName.isEmpty()) {
                    // 读取并显示图片
                    QImage image_temp(fileName);
                    image = image_temp ;
                    ui->image_label->setPixmap(QPixmap::fromImage(image));
                    ui->image_label->setScaledContents(true);//自适应大小
                    ui->image_label->setAlignment(Qt::AlignCenter); // 使图片在QLabel中居中显示
                }
                //图片处理
                QByteArray photo_data;
                QBuffer buffer(&photo_data);
                buffer.open(QIODevice::WriteOnly);
                this->image.save(&buffer, "JPEG",100); // 将图片的二进制数据写入photo_data
                // 检查图片数据大小
                int quality=90;
                while (photo_data.size() > 15.9 * 1024 * 1024)
                {
                    // 图片数据超过了最大允许大小
                    // 清空buffer
                    buffer.setData(QByteArray());
                    // 重新保存 quality  逐渐降低
                    image.save(&buffer, "JPEG",quality);
                    qDebug()<< quality ;
                    quality -= 10;
                }
                QVariant photo(photo_data);
                QSqlQuery query;
                query.prepare("UPDATE accounts "
                              "SET photo=:photo "
                              " WHERE  id=:user_id ");
                query.bindValue(":photo",photo);
                query.bindValue(":user_id",this->user_id);
                query.exec();

            });
    //修改用户名
    connect(user_Action2, &QAction::triggered,[=]()
            {
                sound.wula.play();
                Name_modify_func * name_modify_func_page=new Name_modify_func();
                name_modify_func_page->user_id=this->user_id;
                name_modify_func_page->init();
                name_modify_func_page->show();
            });
    //修改密码
    connect(user_Action3, &QAction::triggered,[=]()
            {
                sound.wula.play();
                Password_modify_func * password_modify_func=new Password_modify_func();
                password_modify_func->user_id=this->user_id;

                password_modify_func->show();
            });

    //退出登录: 保存便利贴-返回登录界面
    connect(user_Action4, &QAction::triggered,[=]()
            {
                sound.wula.play();
                QString memo = ui->plainTextEdit->toPlainText();
                QSqlQuery query;
                query.prepare("UPDATE accounts "
                              "SET memo=:memo "
                              " WHERE  id=:user_id ");
                query.bindValue(":memo",memo);
                query.bindValue(":user_id",this->user_id);
                query.exec();
                emit exit_account();
                this->hide();

            });

    //注销账号
    connect(user_Action5, &QAction::triggered,[=]()
            {
                sound.wula.play();
                Delete_account * delete_account_page= new Delete_account();
                delete_account_page->user_id=this->user_id;
                delete_account_page->show();
                connect(delete_account_page,&Delete_account::delete_account,[=]()
                {
                    // 先传递信号，再关闭界面
                    //close或导致对象的删除，删除了就没有exit_account信号了
                    emit exit_account();
                    this->close();
                });
            });

}

void Mainfunc::on_user_pb_clicked()
{
    sound.wula.play();
   user_Menu->exec(QCursor::pos());//显示菜单
}



// 展示全部联系人
void Mainfunc::show_cot()
{

    QSqlQuery query;
    query.prepare("SELECT name, birth, phone, email, type, special_info FROM contacts WHERE user_id = :user_id");
    query.bindValue(":user_id", this->user_id);
    query.exec();
    //qDebug()<< this->user_id;
    this->qmodel = new QSqlQueryModel(this);
    //使用移动语义设置模型的数据
    qmodel->setQuery(std::move(query));
    //ui->contact_table->setModel(qmodel);

    ui->contact_table->setSortingEnabled(true);

    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(qmodel);

    sqlproxy->setHeaderData(0, Qt::Horizontal, "姓名");
    sqlproxy->setHeaderData(1, Qt::Horizontal, "生日");
    sqlproxy->setHeaderData(2, Qt::Horizontal, "电话号码");
    sqlproxy->setHeaderData(3, Qt::Horizontal, "邮箱");
    sqlproxy->setHeaderData(4, Qt::Horizontal, "分组");
    sqlproxy->setHeaderData(5, Qt::Horizontal, "备注");

    ui->contact_table->setModel(sqlproxy);
}

void Mainfunc::set_menu()
{
    //右键发送customContextMenuRequested 信号
    ui->contact_table->setContextMenuPolicy(Qt::CustomContextMenu);
    this->tableviewMenu = new QMenu( ui->contact_table); // menu的父类是tableview 对象

    Action1 = new QAction("查看", ui->contact_table);
    Action2 = new QAction("删除", ui->contact_table);

    //添加菜单项
    tableviewMenu->addAction(Action1);
    tableviewMenu->addAction(Action2);


    connect( ui->contact_table,&QTableView::customContextMenuRequested,this,&Mainfunc::Menu_Slot);
    connect(Action1, &QAction::triggered,modify_func,&Modify_func::Action1_Slot);
    connect(Action2, &QAction::triggered,modify_func,&Modify_func::Action2_Slot);

    modify_func->user_id=user_id;//传递user_id

    connect(modify_func, &Modify_func::delete_ready,this,&Mainfunc::show_cot); //删除成功后，刷新tableview
    connect(modify_func, &Modify_func::change_ready,this,&Mainfunc::show_cot); //修改成功后，刷新tableview
}


//接收鼠标右键信号
void Mainfunc::Menu_Slot(QPoint p)
{

    QModelIndex index = ui->contact_table->indexAt(p);//获取鼠标点击位置项的索引
    if(index.isValid())//检验数据项是否有效，空白处点击无菜单
    {
        Action1->setVisible(true);
        Action2->setVisible(true);
        QItemSelectionModel* selections =  ui->contact_table->selectionModel();//获取当前的选择模型
        QModelIndexList selected = selections->selectedIndexes();//返回当前选择的模型索引
        if(selected.count() ==1) //选择单个项目时
        {

        }
        else   //多选，不显示菜单项
        {
            Action1->setVisible(false);
            Action2->setVisible(false);
        }
        //先传递数据，再显示菜单
        QAbstractItemModel *model =  ui->contact_table->model(); // 获取 QTableView 的模型
        //传递当前模型和鼠标位置索引
        modify_func->model=model;
        modify_func->index=index;

        sound.wula.play();
        tableviewMenu->exec(QCursor::pos());//显示菜单
    }
}



//添加联系人
void Mainfunc::on_add_buttom_clicked()
{
    sound.wula.play();
    this->hide();
    Add_func *add_page = new Add_func();
    add_page->show();


    //user_id的传递
    add_page->user_id = this->user_id;
    //  connect(regist_page, &Regist::regist_ready, this, &Login::on_show);
    connect(add_page,&Add_func::closed,this,&Mainfunc::on_show);

}




//搜索功能
void Mainfunc::on_search_pb_8_clicked()
{
    sound.wula.play();
    //获取文本框内容
    QString search_info = ui->search_le_8->text();

    //根据文本框内容查询数据库(全局模糊查询)
    //如果search_info 为空，相当于SELECT  name, birth, phone, email, type, special_info FROM contacts 唯一的条件是user_id = %2，实现了刷新功能！
    QSqlQuery query;
    QString search = QString("SELECT  name, birth, phone, email, type, special_info FROM contacts WHERE "
                             "(name LIKE '%%1%' "
                             "or phone LIKE '%%1%' "
                             "or birth LIKE '%%1%' "
                             "or phone LIKE '%%1%' "
                             "or email LIKE '%%1%' "
                             "or type LIKE '%%1%' "
                             "or special_info LIKE '%%1%' )"
                             "AND user_id = %2" )
                            .arg(search_info)
                            .arg(this->user_id);


    if(!query.exec(search))
    {
        qDebug() << "查询信息语句错误";
    }


    this->qmodel = new QSqlQueryModel(this);
    qmodel->setQuery(std::move(query));


    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(qmodel);
    sqlproxy->setHeaderData(0, Qt::Horizontal, "姓名");
    sqlproxy->setHeaderData(1, Qt::Horizontal, "生日");
    sqlproxy->setHeaderData(2, Qt::Horizontal, "电话号码");
    sqlproxy->setHeaderData(3, Qt::Horizontal, "邮箱");
    sqlproxy->setHeaderData(4, Qt::Horizontal, "分组");
    sqlproxy->setHeaderData(5, Qt::Horizontal, "备注");
    ui->contact_table->setModel(sqlproxy);

}


//  生日查询界面
void Mainfunc::on_email_pb_clicked()
{
    sound.wula.play();

    email_func_page->show();

    email_func_page->user_id = this->user_id;
    email_func_page->init();

}






