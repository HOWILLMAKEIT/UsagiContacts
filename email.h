#ifndef EMAIL_H
#define EMAIL_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
class Email : public QObject
{
    Q_OBJECT
public:
    explicit Email(QObject *parent = nullptr);
    void sendEmail(QString SmtpServer, int SmtpPort,
                   QString SenderEmail, QString SenderPassword, QString ReceiveEmail, QString SubjectTitle, QString Content);

signals:
    void send_ready();
};

#endif // EMAIL_H
