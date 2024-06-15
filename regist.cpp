#include "regist.h"
#include "ui_regist.h"

Regist::Regist(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Regist)
{
    ui->setupUi(this);
    //头像初始化
    image= QImage (":/image/微信图片_20240524115747.png");
    ui->image_label->setPixmap(QPixmap::fromImage(image));
    ui->image_label->setScaledContents(true);//自适应大小
    ui->image_label->setAlignment(Qt::AlignCenter); // 使图片在QLabel中居中显示
}

Regist::~Regist()
{
    delete ui;
}


//重写关闭事件
void Regist::closeEvent(QCloseEvent *e)
{

    emit closed();//发出closed（）信号
    e->accept();//关闭窗口
    delete this;//释放之前创建在堆区的Regist指针的内存
}


//添加图片
void Regist::on_image_pb_clicked()
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
}


void Regist::on_pushButton_clicked()
{


    QString username = ui->username_le->text();
    QString pwd_1 = ui->pwd_le1->text();
    QString pwd_2 = ui->pwd_le2->text();
    if (!username.isEmpty() && !pwd_1.isEmpty() && !pwd_2.isEmpty())
    {
        if(pwd_1 == pwd_2)
        {
        //查看是否有相同的用户名a
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT user_name FROM accounts WHERE user_name = :username");
        checkQuery.bindValue(":username", username);
        checkQuery.exec();
            if(!checkQuery.next())  //查询结果为空- 不存在相同的用户名
            {
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
                QString memo  = "";
                query.prepare("INSERT INTO accounts (user_name, password, photo,memo) VALUES (:username, :password,:photo,:memo)");
                query.bindValue(":username", username);
                query.bindValue(":password", pwd_1);
                query.bindValue(":photo", photo);
                query.bindValue(":memo", memo);
                if (query.exec())
                {
                    sound.yaha.play();
                    QMessageBox::information (this, "注册", "注册成功！");
                    emit regist_ready();
                    this->close();
                }
                //输入语句执行失败
                else
                {
                    qDebug() << "Insert failed";
                }
            }
            //已经存在相同的用户名
            else
            {
                sound.ha.play();
                QMessageBox::warning(this, "注册失败", "用户名已存在");
            }

        }
        //两次输入的密码不同
        else
        {
            sound.ha.play();
            QMessageBox::warning(this, "注册失败", "两次输入的密码不一致");

        }
    }
    else
    {
        sound.ha.play();
        QMessageBox::warning(this, "注册失败", "用户名或密码不能为空");
    }
}


