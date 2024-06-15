#include "email_func_birth.h"
#include "email_func_birth.h"
#include "ui_email_func_birth.h"

Email_func_birth::Email_func_birth(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Email_func_birth)
{
    ui->setupUi(this);
    ui->year_sb->setRange(0,2024);
    ui->month_sb->setRange(0,12);
    ui->day_sb->setRange(0,31);
}

Email_func_birth::~Email_func_birth()
{
    delete ui;
}

void Email_func_birth::on_pushButton_clicked()
{
    sound.wula.play();
    QString year = ui->year_sb->text();
    QString month = ui->month_sb->text();
    QString day = ui->day_sb->text();
    QString whereClause = "WHERE user_id = :user_id";
    QVariant yearValue, monthValue, dayValue;

    if (year != "0")
    {
        whereClause += " AND YEAR(birth) = :year";
        yearValue = year;
    }

    if (month != "0")
    {
        whereClause += " AND MONTH(birth) = :month";
        monthValue = month;
    }

    if (day != "0")
    {
        whereClause += " AND DAY(birth) = :day";
        dayValue = day;
    }

    QSqlQuery query;
    query.prepare("SELECT name, birth, phone, email, type "
                  "FROM contacts "
                  + whereClause);
    query.bindValue(":user_id", this->user_id);

    if (year != "0") query.bindValue(":year", yearValue);
    if (month != "0") query.bindValue(":month", monthValue);
    if (day != "0") query.bindValue(":day", dayValue);

    query.exec();

    this->model = new QSqlQueryModel(this);
    //使用移动语义设置模型的数据
    model->setQuery(std::move(query));
    //ui->contact_table->setModel(qmodel);

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


