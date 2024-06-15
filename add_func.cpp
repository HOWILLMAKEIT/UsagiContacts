#include "add_func.h"
#include "qevent.h"
#include "ui_add_func.h"

Add_func::Add_func(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Add_func)
{
    ui->setupUi(this);
    ui->newtype_lb->setVisible(false);
    ui->newtype_le->setVisible(false);


    // 头像初始化
    image= QImage(":/image/微信图片_20240524115747.png");
    ui->image_lable->setPixmap(QPixmap::fromImage(image));
    ui->image_lable->setScaledContents(true);//自适应大小
    ui->image_lable->setAlignment(Qt::AlignCenter); // 使图片在QLabel中居中显示
}

Add_func::~Add_func()
{
    delete ui;
}
void Add_func::closeEvent(QCloseEvent *e)
{

    emit closed();
    e->accept();//关闭窗口
    delete this;
}




void Add_func::on_comboBox_activated(int index)
{
    QString Text;
    ui->newtype_lb->setVisible(false);
    ui->newtype_le->setVisible(false);
    switch(index)
    {
    case 0 :

        Text="备注";
        break;
    case 1:
        Text="学校名称";
        break;
    case 2:
        Text="单位名称";
        break;
    case 3:
        Text="称呼";
        break;
    case 4:
        Text="认识地点";
        break;
    case 5:
        ui->newtype_lb->setVisible(true);
        ui->newtype_le->setVisible(true);
        Text="备注";
        break;
    }

    //设定”备注” label的内容
    ui->label_6->setText(Text);
}


 //添加按钮
void Add_func::on_pushButton_clicked()
{
    int index=ui->comboBox->currentIndex();
    QString name = ui->name_le->text();
    QString phone = ui->phone_le->text();
    QDate birth=ui->dateEdit->date();
    QString email = ui->email_le->text();
    QString type=ui->newtype_le->text();
    QString special_info=ui->specialinfo_le->text();
    Contact * new_contact;

    //id
    int id = this->user_id;

    //姓名不能为空
    if(name.isEmpty())
    {
        sound.ha.play();
        QMessageBox::warning(this, "添加失败", "联系人姓名不能为空");
        return;
    }


    //邮箱不为空要检测是否符合邮箱格式
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if( !email.isEmpty()&& !regex.match(email).hasMatch())
    {
        sound.ha.play();
        QMessageBox::warning(this, "添加失败", "邮箱格式错误");
        return;
    }


    if(special_info.size()>255 )
    {
        sound.ha.play();
        QMessageBox::warning(this, "添加失败", "备注内容过长");
        return;
    }



    //图片
    // image -> 二进制
    QByteArray photo_data;
    QBuffer buffer(&photo_data);
    buffer.open(QIODevice::WriteOnly);
    this->image.save(&buffer, "JPEG",85); // 将图片的二进制数据写入photo_data

    // 检查图片数据大小
    // 15.9 * 1024 * 1024 是因为 mediun blob 最大是 15.9Mb
    int quality=80;
    while (photo_data.size() > 15.9 * 1024 * 1024)
    {
        // 清空buffer
        buffer.setData(QByteArray());
        // 重新保存     quality逐渐降低
        image.save(&buffer, "JPEG",quality);
        qDebug()<< quality ;
        quality -= 10;
    }
    QVariant photo(photo_data); // QVariant是一个可以存储大多数Qt数据类型的通用容器类






    switch(index)
    {
    case 0://不分组
        new_contact=new Other_cnt;
        break;
    case 1: //同学
        new_contact=new Classmate;
        break;
    case 2://同事
        new_contact=new Colleague;
        break;
    case 3://亲戚
        new_contact=new Relative;
        break;
    case 4://朋友
        new_contact=new Friend;
        break;
    case 5:// 其他
        new_contact=new Other_cnt;
        break;
    }

    //利用多态
    new_contact->add_contact(id,name,birth,phone,email,type,special_info,photo);


    //注意，如果用户选择了默认的四个分组，这里的type是空的

    sound.yaha.play();
    QMessageBox::information(this,"添加联系人","添加联系人成功！");

}


void Add_func::on_photo_pb_clicked()
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
        ui->image_lable->setPixmap(QPixmap::fromImage(image));
        ui->image_lable->setScaledContents(true);//自适应大小
        ui->image_lable->setAlignment(Qt::AlignCenter); // 使图片在QLabel中居中显示
    }

}

