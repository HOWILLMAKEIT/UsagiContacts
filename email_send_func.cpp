#include "email_send_func.h"
#include "qregularexpression.h"
#include "ui_email_send_func.h"

Email_send_func::Email_send_func(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Email_send_func)
{
    ui->setupUi(this);
    connect(&email,&Email::send_ready,this,&Email_send_func::send_email_success);
    QString recipientName = "[姓名]";
    QString senderName = "[你的名字]";
    QString birthdayTemplate = QStringLiteral(R"(
亲爱的%1，

在这个特别的日子里，我想借着这封信向你表达我最真挚的祝福。今天是你的生日，愿你在这新的一年里，事事顺心，幸福快乐。

在此，我祝愿你生日快乐，愿你的人生道路一片光明，事业有成，家庭幸福，身体健康，万事如意！

%2
)");
    QString birthdayGreeting = birthdayTemplate.arg(recipientName).arg(senderName);
    ui->plainTextEdit->setPlainText(birthdayGreeting);
}

Email_send_func::~Email_send_func()
{
    delete ui;
}



//当QLineEdit中的文本改变时，发出此信号，text是新的文本。
void Email_send_func::on_lineEdit_textChanged(const QString &text)
{
    if(text.isEmpty())
    {
         ui->name_lb->setText("");
        QString recipientName = "[姓名]";
        QString senderName = "[你的名字]";
        QString birthdayTemplate = QStringLiteral(R"(
亲爱的%1，

在这个特别的日子里，我想借着这封信向你表达我最真挚的祝福。今天是你的生日，愿你在这新的一年里，事事顺心，幸福快乐。

在此，我祝愿你生日快乐，愿你的人生道路一片光明，事业有成，家庭幸福，身体健康，万事如意！

%2
)");
        QString birthdayGreeting = birthdayTemplate.arg(recipientName).arg(senderName);
        ui->plainTextEdit->setPlainText(birthdayGreeting);
        return ;
    }
    QSqlQuery query;
    query.prepare("SELECT name from contacts "
                  "WHERE email=:email AND user_id = :user_id ");
    query.bindValue(":email",text);
    query.bindValue(":user_id",this->user_id);
    query.exec();
    query.next();
    QString name= query.value(0).toString();
    ui->name_lb->setText(name);

    QString senderName = "[你的名字]";
    QString birthdayTemplate = QStringLiteral(R"(
亲爱的%1，

在这个特别的日子里，我想借着这封信向你表达我最真挚的祝福。今天是你的生日，愿你在这新的一年里，事事顺心，幸福快乐。

在此，我祝愿你生日快乐，愿你的人生道路一片光明，事业有成，家庭幸福，身体健康，万事如意！

%2
)");
    QString birthdayGreeting = birthdayTemplate.arg(name).arg(senderName);
    ui->plainTextEdit->setPlainText(birthdayGreeting);
}

void Email_send_func::send_email_success()
{
    sound.wulayaha.play();
    QMessageBox :: information ( this, "发送邮件","发送邮件成功");
    email_login_page->close();

}

// 发送邮件
void Email_send_func::on_pushButton_clicked()
{

    sound.wula.play();


    // 这里要小心多次连接问题
    static int check=0;
    if(check==0)
    {
        connect(email_login_page,&email_login::login_ready,[=]()
                {
                    QString  SenderEmail= email_login_page->account;
                    QString SenderPassword = email_login_page->password;

                    QRegularExpression regex("^(.+)@(.+)$");
                    QRegularExpressionMatch match = regex.match(SenderEmail);
                    QString domain = match.captured(2);
                    QString SmtpServer = "smtp."  +  domain;
                    QString ReceiveEmail=ui->lineEdit->text();
                    int SmtpPort =25;
                    QString SubjectTitle="生日快乐！";
                    QString Content=ui->plainTextEdit->toPlainText();

                    email.sendEmail(  SmtpServer,  SmtpPort, SenderEmail,  SenderPassword,  ReceiveEmail,  SubjectTitle,  Content);

                });
        check++;
    }
    email_login_page->show();



}

// QString SmtpServer, int SmtpPort,
//                    QString SenderEmail, QString SenderPassword, QString ReceiveEmail, QString SubjectTitle, QString Content);

