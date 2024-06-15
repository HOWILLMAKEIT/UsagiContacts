#include "email.h"

Email::Email(QObject *parent)
    : QObject{parent}
{}

void Email::sendEmail(QString SmtpServer, int SmtpPort,  QString SenderEmail, QString SenderPassword, QString ReceiveEmail, QString SubjectTitle, QString Content)
{

        // Connect to the SMTP server
        QTcpSocket socket;	//连接方式。这里选用TCP方式
        socket.connectToHost(SmtpServer, SmtpPort);
        if (!socket.waitForConnected())
        {
            qDebug() << "Failed to connect to SMTP server.";
            return;
        }
        else
            qDebug() << "Success to connect to SMTP server.";

        // Read the welcome message from the server
        if (!socket.waitForReadyRead())
        {
            qDebug() << "Failed to receive welcome message from SMTP server.";
            return;
        }
        QByteArray response = socket.readAll();
        qDebug() << response;

        // Send the EHLO command
        socket.write("EHLO localhost\r\n");
        if (!socket.waitForBytesWritten())
        {
            qDebug() << "Failed to send EHLO command to SMTP server.";
            return;
        }
        if (!socket.waitForReadyRead())
        {
            qDebug() << "Failed to receive EHLO command response from SMTP server.";
            return;
        }
        response = socket.readAll();
        qDebug() << response;

        // Send the authentication login command and credentials
        socket.write("AUTH LOGIN\r\n");
        if (!socket.waitForBytesWritten())
        {
            qDebug() << "Failed to send AUTH LOGIN command to SMTP server.";
            return;
        }
        if (!socket.waitForReadyRead())
        {
            qDebug() << "Failed to receive AUTH LOGIN command response from SMTP server.";
            return;
        }
        response = socket.readAll();
        qDebug() << response;

        QByteArray encodedEmail = SenderEmail.toUtf8().toBase64();
        QByteArray encodedPassword = SenderPassword.toUtf8().toBase64();

        socket.write(encodedEmail + "\r\n");
        if (!socket.waitForBytesWritten())
        {
            qDebug() << "Failed to send encoded email to SMTP server.";
            return;
        }
        if (!socket.waitForReadyRead())
        {
            qDebug() << "Failed to receive email authentication response from SMTP server.";
            return;
        }
        response = socket.readAll();
        qDebug() << response;

        socket.write(encodedPassword + "\r\n");
        if (!socket.waitForBytesWritten())
        {
            qDebug() << "Failed to send encoded password to SMTP server.";
            return;
        }
        if (!socket.waitForReadyRead())
        {
            qDebug() << "Failed to receive password authentication response from SMTP server.";
            return;
        }
        response = socket.readAll();
        qDebug() << response;

        // Send the MAIL FROM command
        socket.write(QString("MAIL FROM:<%1>\r\n").arg(SenderEmail).toUtf8());
        if (!socket.waitForBytesWritten())
        {
            qDebug() << "Failed to send MAIL FROM command to SMTP server.";
            return;
        }
        if (!socket.waitForReadyRead())
        {
            qDebug() << "Failed to receive MAIL FROM command response from SMTP server.";
            return;
        }
        response = socket.readAll();
        qDebug() << response;

        // Send the RCPT TO command
        socket.write(QString("RCPT TO:<%1>\r\n").arg(ReceiveEmail).toUtf8());
        if (!socket.waitForBytesWritten())
        {
            qDebug() << "Failed to send RCPT TO command to SMTP server.";
            return;
        }
        if (!socket.waitForReadyRead())
        {
            qDebug() << "Failed to receive RCPT TO command response from SMTP server.";
            return;
        }
        response = socket.readAll();
        qDebug() << response;

        // Send the DATA command
        socket.write("DATA\r\n");
        if (!socket.waitForBytesWritten())
        {
            qDebug() << "Failed to send DATA command to SMTP server.";
            return;
        }
        if (!socket.waitForReadyRead())
        {
            qDebug() << "Failed to receive DATA command response from SMTP server.";
            return;
        }
        response = socket.readAll();
        qDebug() << response;

        // Send the message headers and body
        QString message = "To: " + ReceiveEmail + "\r\n";
        message += "From: " + SenderEmail + "\r\n";
        message += "Subject: " + SubjectTitle + "\r\n";
        message += "Content-Type: text/plain; charset=\"utf-8\"\r\n\r\n";
        message += Content + "\r\n";

        socket.write(message.toUtf8());
        socket.write(".\r\n");
        if (!socket.waitForBytesWritten())
        {
            qDebug() << "Failed to send message to SMTP server.";
            return;
        }
        qDebug() << "Message sent successfully.";

        emit send_ready();
        // Quit the session
        socket.write("QUIT\r\n");
        socket.waitForBytesWritten();

        // Close the connection
        socket.close();
}
