#include "adddialog.h"
#include "ui_adddialog.h"

#include "menu.h"
#include "menuitem.h"

enum MenuItemType{MenuType = 0, MenuItemType};

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog),
    mRoot{nullptr},
    mNewItem{nullptr},
    mParent{nullptr}
{
    ui->setupUi(this);
    setWindowTitle("Add...");

    ui->typeComboBox->addItem("Menu Item", MenuItemType);
    ui->typeComboBox->addItem("Menu", MenuType);

    connect(ui->backPushButton, SIGNAL(clicked(bool)), this, SLOT(slotBackClicked()), Qt::UniqueConnection);
    connect(ui->cancelPushButton_2, SIGNAL(clicked(bool)), this, SLOT(slotCancelClicked()), Qt::UniqueConnection);
    connect(ui->nextPushButton, SIGNAL(clicked(bool)), this, SLOT(slotNextClicked()), Qt::UniqueConnection);
    connect(ui->okPushButton, SIGNAL(clicked(bool)), this, SLOT(slotOkClicked()), Qt::UniqueConnection);
    connect(ui->widget, SIGNAL(itemChanged()), this, SLOT(slotChanged()), Qt::UniqueConnection);
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::setMenu(Composite *menu)
{
    mRoot = menu;
    ui->parentComboBox->setMenu(menu);
}

Composite *AddDialog::newMenuItem() const
{
    return mNewItem;
}

void AddDialog::showEvent(QShowEvent *)
{
    clear();

    showPage1();
}

void AddDialog::slotBackClicked()
{
    showPage1();

    clear();
}

void AddDialog::slotCancelClicked()
{
    ui->widget->clear();

    reject();
}

void AddDialog::slotNextClicked()
{
    switch (ui->typeComboBox->currentData().toInt())
    {
    case MenuType:
        mNewItem = new Menu("");
        break;
    case MenuItemType:
        mNewItem = new MenuItem("", 0.0);
        break;
    default:
        break;
    }

    if (mNewItem)
    {
        mParent = ui->parentComboBox->currentMenuItem();
        mNewItem->accept(ui->widget);
        showPage2();
    }
}

void AddDialog::slotOkClicked()
{
    mParent->addSubitem(mNewItem);
    ui->widget->slotSave();
    accept();
}

void AddDialog::slotChanged()
{
    ui->okPushButton->setEnabled(true);
}

void AddDialog::showPage1()
{
    ui->stackedWidget->setCurrentWidget(ui->addPage1);
    ui->backPushButton->setVisible(false);
    ui->nextPushButton->setVisible(true);
    ui->okPushButton->setVisible(false);
}

void AddDialog::showPage2()
{
    ui->stackedWidget->setCurrentWidget(ui->addPage2);
    ui->backPushButton->setVisible(true);
    ui->nextPushButton->setVisible(false);
    ui->okPushButton->setVisible(true);
    ui->okPushButton->setEnabled(true);
}

void AddDialog::clear()
{
    if (mNewItem)
    {
        mParent = nullptr;
        delete mNewItem;
        ui->widget->clear();
    }
}
