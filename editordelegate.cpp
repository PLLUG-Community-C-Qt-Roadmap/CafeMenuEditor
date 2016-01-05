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
    connect(ui->discountCheckBox, SIGNAL(stateChanged(int)), this, SIGNAL(itemChanged()), Qt::UniqueConnection);
    connect(ui->discountSpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(itemChanged()), Qt::UniqueConnection);
    connect(ui->discountCheckBox, SIGNAL(toggled(bool)), ui->discountSpinBox, SLOT(setEnabled(bool)), Qt::UniqueConnection);
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

    ui->discountCheckBox->setChecked(false);
    ui->discountCheckBox->setEnabled(false);
    ui->discountSpinBox->setValue(0.0);

    mEditedMenuItem = item;

    blockSignals(false);
}

void EditorDelegate::visit(DiscountMenuItem * item)
{
    blockSignals(true);

    clear();

    ui->stackedWidget->setCurrentWidget(ui->pageMenuItem);
    ui->menuItemNameLineEdit->setText(item->title().c_str());
    ui->menuItemDescriptionLineEdit->setText(item->description().c_str());
    ui->menuItemPriceSpinBox->setValue(item->price());

    ui->discountCheckBox->setEnabled(true);
    if(item->discount() != 0.0)
        ui->discountCheckBox->setChecked(true);
    ui->discountSpinBox->setValue(item->discount());

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

    // evil stuff incoming
    // due to our weird design we have menu items new-ed before we know if they would have a discount
    // so we have discount checkbox after the type of the item is decided

    // to fix this we can:
    // 1. Add other item type like Discount Menu Item
    //    but then what is the purpose of the checkbox?


    // 2. All items created are DiscountMenuItems
    //    however we also have old hardcoded MenuItems that we may want to edit
    //    and we can't add a discount to them
    //    so we need to check if we are saving a discount menu item

    //    to avoid dynamic cast we can also use a second mEditedMenuItem pointer member - like mEditedDiscountMenuItem
    //    or use visitor pattern again - now some menueditvisitor

    DiscountMenuItem *dcMenuItem = dynamic_cast<DiscountMenuItem*>(mEditedMenuItem);
    if(dcMenuItem)
    {
        if(ui->discountCheckBox->isChecked() && ui->discountCheckBox->isEnabled())
            dcMenuItem->setDiscount(ui->discountSpinBox->value());
        else
            dcMenuItem->setDiscount(0.0);
    }
}
