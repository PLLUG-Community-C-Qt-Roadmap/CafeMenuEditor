#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include<QVBoxLayout>
#include<QHBoxLayout>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
   QLabel* versionLabel = new QLabel(QString("%1 v. %2")
                   .arg(qApp->applicationName())
                   .arg(qApp->applicationVersion()));

    QHBoxLayout * upper = new QHBoxLayout();
    upper->setAlignment(Qt::AlignHCenter);
    upper->addWidget(versionLabel);

    QHBoxLayout * down = new QHBoxLayout();
    down->addWidget(ui->OKpushButton);
    down->setAlignment(Qt::AlignHCenter);


    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->addLayout(upper);
    mainLayout->addLayout(down);


    setLayout(mainLayout);

}

AboutDialog::~AboutDialog()
{
    delete ui;
}


void AboutDialog::on_OKpushButton_clicked()
{
    accept();
}
