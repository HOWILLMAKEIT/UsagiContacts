#include "email_func_normal.h"
#include "ui_email_func_normal.h"

Email_func_normal::Email_func_normal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Email_func_normal)
{
    ui->setupUi(this);
    ui->spinBox_3->setRange(0,31);
}

Email_func_normal::~Email_func_normal()
{
    delete ui;
}

void Email_func_normal::on_pushButton_clicked()
{
    sound.wula.play();
    QString days = ui->spinBox_3->text();
    int daysInt = days.toInt();
    //往前后各数daysInt天
    QSqlQuery query;
    QDate currentDate = QDate::currentDate();
    QDate past_searchDate = currentDate.addDays(-daysInt);
    QDate future_searchDate = currentDate.addDays(daysInt);
    if(past_searchDate.year()==currentDate.year()&&future_searchDate.year()==currentDate.year()){
        query.prepare("SELECT name, birth, phone, email, type FROM contacts WHERE user_id = :user_id"
                      "AND "
                      "(DATE_FORMAT(birth,'%m%d') BETWEEN DATE_FORMAT(CURDATE()-INTERVAL :days DAY,'%m%d') AND DATE_FORMAT(CURDATE()+INTERVAL :days DAY,'%m%d'))");
    }else //跨年
    {
        query.prepare("SELECT name, birth, phone, email, type FROM contacts WHERE user_id = :user_id"
                      "AND "
                      "((DATE_FORMAT(birth,'%m%d') BETWEEN DATE_FORMAT(CURDATE()-INTERVAL :days DAY,'%m%d') AND STR_TO_DATE('12.31','%m.%d')))"
                      "OR"
                      "(DATE_FORMAT(birth,'%m%d') BETWEEN STR_TO_DATE('1.1','%m.%d') AND DATE_FORMAT(CURDATE()+INTERVAL :days DAY,'%m%d'))");
    }
    query.bindValue(":user_id", this->user_id);
    query.bindValue(":days", daysInt);
    query.exec();
    this->model = new QSqlQueryModel(this);
    model->setQuery(std::move(query));
    ui->tableView->setSortingEnabled(true);
    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(model);
    sqlproxy->setHeaderData(0, Qt::Horizontal, "姓名");
    sqlproxy->setHeaderData(1, Qt::Horizontal, "生日");
    sqlproxy->setHeaderData(2, Qt::Horizontal, "电话号码");
    sqlproxy->setHeaderData(3, Qt::Horizontal, "邮箱");
    sqlproxy->setHeaderData(4, Qt::Horizontal, "分组");
    ui->tableView->setModel(sqlproxy);


}





