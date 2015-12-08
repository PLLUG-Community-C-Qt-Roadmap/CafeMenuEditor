#include "editordelegate.h"
#include "ui_editordelegate.h"

#include "menu.h"
#include "menuitem.h"

EditorDelegate::EditorDelegate(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorDelegate)
{
    ui->setupUi(this);
    connect(ui->menuItemNameLineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(itemChanged()), Qt::UniqueConnection);
    connect(ui->menuItemDescriptionLineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(itemChanged()), Qt::UniqueConnection);
    connect(ui->menuItemPriceSpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(itemChanged()), Qt::UniqueConnection);
}

EditorDelegate::~EditorDelegate()
{
    delete ui;
}

void EditorDelegate::visit(MenuItem *item)
{
    blockSignals(true);

    clear();

    ui->stackedWidget->setCurrentWidget(ui->pageMenuItem);
    ui->menuItemNameLineEdit->setText(item->title().c_str());
    ui->menuItemDescriptionLineEdit->setText(item->description().c_str());
    ui->menuItemPriceSpinBox->setValue(item->price());

    mEditedMenuItem = item;

    blockSignals(false);
}

void EditorDelegate::visit(Menu *menu)
{
    blockSignals(true);

    clear();

    ui->stackedWidget->setCurrentWidget(ui->pageMenu);

    mEditedMenu = menu;

    blockSignals(false);
}

void EditorDelegate::clear()
{
    mEditedMenu = nullptr;
    mEditedMenuItem = nullptr;
}

void EditorDelegate::slotSave()
{
    if (mEditedMenuItem)
    {
        mEditedMenuItem->setTitle(ui->menuItemNameLineEdit->text().toStdString());
        mEditedMenuItem->setDescription(ui->menuItemDescriptionLineEdit->text().toStdString());
        mEditedMenuItem->setPrice(ui->menuItemPriceSpinBox->value());
    }
}
