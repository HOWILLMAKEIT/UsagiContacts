#include "login.h"
#include <QApplication>
#include"db_operator.h"
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login w;


    db_operator::getInstance().init();
    w.show();
    return a.exec();
}
