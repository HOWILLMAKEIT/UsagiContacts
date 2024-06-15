#include "modify_func.h"
#include "ui_modify_func.h"

Modify_func::Modify_func(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Modify_func)
{
    ui->setupUi(this);

}

Modify_func::~Modify_func()
{
    delete ui;
}

//数据初始化
void Modify_func::data_init()
{
    int row = index.row();
    name = model->data(model->index(row,0)).toString();
    birth  = model->data(model->index(row,1)).toDate();
    phone = model->data(model->index(row,2)).toString();
    email = model->data(model->index(row,3)).toString();
    type = model->data(model->index(row,4)).toString();
    special_info=model->data(model->index(row,5)).toString();
}

//显示查看页面
void Modify_func::Action1_Slot( )
{
    data_init();
    QSqlQuery query;
    ui->name_le->setText(name);
    ui->dateEdit->setDate(birth);
    ui->phone_le->setText(phone);
    ui->email_le->setText(email);
    ui->type_le->setText(type);
    ui->plainTextEdit->setPlainText(special_info);
    query.prepare("SELECT photo "
                  "FROM contacts"
                  " WHERE  name=:name AND  birth=:birth AND  phone=:phone AND email=:email AND type=:type AND special_info=:special_info AND user_id=:user_id ");

    query.bindValue(":name", name);
    query.bindValue(":birth",  birth);
    query.bindValue(":phone",  phone);
    query.bindValue(":email",  email);
    query.bindValue(":type",  type);
    query.bindValue(":special_info", special_info);
    query.bindValue(":user_id", this->user_id);
    query.exec();
    query.next();

    //image 的初始化在这里！
    QPixmap photo;
    photo.loadFromData(query.value(0).toByteArray(), "JPEG");
    image = photo.toImage();
    ui->image_lable->setPixmap(photo);
    ui->image_lable->setScaledContents(true);//自适应大小
    ui->image_lable->setAlignment(Qt::AlignCenter); // 使图片在QLabel中居中显示

    this->show();



}
//删除
void Modify_func::Action2_Slot( )
{
    data_init();
    QSqlQuery query;
    query.prepare("SELECT  id, name, birth, phone, email, type, special_info, user_id "
                  "FROM contacts"
                  " WHERE  name=:name AND  birth=:birth AND  phone=:phone AND email=:email AND type=:type AND special_info=:special_info AND user_id=:user_id ");

    query.bindValue(":name", name);
    query.bindValue(":birth",  birth);
    query.bindValue(":phone",  phone);
    query.bindValue(":email",  email);
    query.bindValue(":type",  type);
    query.bindValue(":special_info", special_info);
    query.bindValue(":user_id", this->user_id);

    query.exec();// 查询

    //如果有完全相同的联系人，只删除一个！
    if(query.next())
    {
        //获取contacts表中这一行数据的id
        int id = query.value(0).toInt();
        qDebug()<<id;
        // 删除语句
        QString deleteSql = QString("DELETE FROM contacts WHERE id = %1").arg(id);
        if(query.exec(deleteSql))//删除
        {
            qDebug()<<"删除成功";
            emit this->delete_ready();
        }

    }
    else
    {
        qDebug()<<"没有在数据库中找到指定待删除对象!";
    }

}
//保存按钮  //读取信息，录入数据
void Modify_func::on_pushButton_clicked()
{
    QString name_change = ui->name_le->text();
    QString phone_change = ui->phone_le->text();
    QDate birth_change=ui->dateEdit->date();
    QString email_change = ui->email_le->text();
    QString type_change=ui->type_le->text();
    QString special_info_change=ui->plainTextEdit->toPlainText();

    data_init();
    QSqlQuery query;
    //姓名不能为空
    if(name_change.isEmpty())
    {
        sound.ha.play();
        QMessageBox::warning(this, "保存失败", "联系人姓名不能为空");
        return;
    }


    //邮箱不为空要检测是否符合邮箱格式
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if( !email_change.isEmpty()&& !regex.match(email_change).hasMatch())
    {
        sound.ha.play();
        QMessageBox::warning(this, "保存失败", "邮箱格式错误");
        return;
    }

    if(special_info_change.size()>255 )
    {
        sound.ha.play();
        QMessageBox::warning(this, "保存失败", "备注内容过长");
        return;
    }


    query.prepare("UPDATE contacts "
                  "SET name = :name_change, birth = :birth_change, phone = :phone_change, email = :email_change, type = :type_change, special_info = :special_info_change, photo= :photo "
                  " WHERE  name=:name_before AND  birth=:birth_before AND  phone=:phone_before AND email=:email_before AND type=:type_before AND special_info=:special_info_before AND user_id=:user_id ");
    query.bindValue(":name_change", name_change);
    query.bindValue(":birth_change",  birth_change);
    query.bindValue(":phone_change",  phone_change);
    query.bindValue(":email_change",  email_change);
    query.bindValue(":type_change",  type_change);
    query.bindValue(":special_info_change", special_info_change);

    query.bindValue(":user_id", this->user_id);

    query.bindValue(":name_before", name);
    query.bindValue(":birth_before",  birth);
    query.bindValue(":phone_before",  phone);
    query.bindValue(":email_before",  email);
    query.bindValue(":type_before",  type);
    query.bindValue(":special_info_before", special_info);

    // image -> 二进制
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
        // 重新保存   逐渐降低quality
        image.save(&buffer, "JPEG",quality);
        qDebug()<< quality ;
        quality -= 10;
    }
    QVariant photo(photo_data);
    query.bindValue(":photo", photo);


    query.exec();// 修改
    emit this->change_ready();
    sound.yaha.play();
    QMessageBox :: information (this,"保存","保存成功");

}

//修改头像
void Modify_func::on_photo_pb_clicked()
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

