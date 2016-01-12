#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "texteditprintmenuvisitor.h"
#include "menuiterator.h"
#include "menu.h"
#include "menuitem.h"
#include "adddialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mRoot{nullptr}
{
    ui->setupUi(this);
    resize(800, 600);

    createMenu();
    slotUpdateMenu();

    connect(ui->menuComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(menuElementSelected()), Qt::UniqueConnection);
    connect(ui->action_Add, SIGNAL(triggered(bool)),
            this, SLOT(slotAddNewItem()), Qt::UniqueConnection);
    connect(ui->savePushButton, SIGNAL(clicked(bool)),
            this, SLOT(slotSaveEditedItem()), Qt::UniqueConnection);
    connect(ui->menuEditorDelegate, SIGNAL(itemChanged()),
            this, SLOT(slotItemChanged()), Qt::UniqueConnection);
    connect(ui->menuComboBox, SIGNAL(activated(int)),
            this, SLOT(slotEnableDeleteButton()), Qt::UniqueConnection);
    connect(ui->deletePushButton,SIGNAL(clicked(bool)),
            this,SLOT(slotDisableDeleteButton()), Qt::UniqueConnection);
    connect(ui->deletePushButton,SIGNAL(clicked(bool)),
            this,SLOT(slotDeleteButton()), Qt::UniqueConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mRoot;
}

void MainWindow::slotPrintMenu()
{
    ui->menuTextEdit->clear();
    TextEditPrintMenuVisitor visitor (ui->menuTextEdit);
    MenuIterator iterator(mRoot);
    while(iterator.hasNext())
    {
        auto item =  iterator.next();
        item->accept(&visitor);
    }
}

void MainWindow::slotDeleteButton()
{
    int elemIndex=ui->menuComboBox->currentIndex();
    MenuIterator it(mRoot);
    for(int i=0;i<elemIndex;++i)
    {
        if(it.hasNext())
        it.next();
    }
    Composite *child=it.next();
    Composite *parent=child->parent();
    parent->removeSubitem(child->title());

    //крешиться, якшо видаляємо beverages
    slotPrintMenu();
    ui->menuComboBox->updateComboBox();
}

void MainWindow::menuElementSelected()
{
    ui->savePushButton->setEnabled(false);
    Composite * item = ui->menuComboBox->currentMenuItem();
    MenuVisitor *visitor = ui->menuEditorDelegate;
    item->accept(visitor);
}

void MainWindow::slotUpdateMenu()
{
    int index = ui->menuComboBox->currentIndex();
    ui->menuComboBox->setMenu(mRoot);
    slotPrintMenu();
    ui->menuComboBox->setCurrentIndex(index);
}

void MainWindow::slotAddNewItem()
{
    AddDialog addDialog;
    addDialog.setMenu(mRoot);

    if (addDialog.exec())
    {
        Composite *newItem = addDialog.newMenuItem();

        if (newItem)
        {
            slotUpdateMenu();
        }
    }
}

void MainWindow::slotItemChanged()
{
    ui->savePushButton->setEnabled(true);
}

void MainWindow::slotSaveEditedItem()
{
    ui->savePushButton->setEnabled(false);
    ui->menuEditorDelegate->slotSave();
    slotUpdateMenu();
}

void MainWindow::slotEnableDeleteButton()
{
    ui->deletePushButton->setEnabled(true);
}

void MainWindow::slotDisableDeleteButton()
{
   ui->deletePushButton->setEnabled(false);
}

void MainWindow::createMenu()
{
    mRoot = new Menu("MAIN MENU");

    Menu *lPizzaMenu = new Menu("Pizza Menu");
    lPizzaMenu->addSubitem(new MenuItem("hawaiian pizza", 2.4, "cheese and tomato base with toppings of ham and pineapple"));
    lPizzaMenu->addSubitem(new MenuItem("vegetarian pizza", 4.2, "cheese and tomato ... "));
    mRoot->addSubitem(lPizzaMenu);

    Menu *lBeveragesMenu = new Menu("Beverages");
    lBeveragesMenu->addSubitem(new MenuItem("Coca-Cola", 2));

    Menu *lCoffeMenu = new Menu("Coffe");
    lCoffeMenu->addSubitem(new MenuItem("Late", 1, "             "));
    lCoffeMenu->addSubitem(new MenuItem("Capucino", 2, "             "));
    lBeveragesMenu->addSubitem(lCoffeMenu);

    lBeveragesMenu->addSubitem(new MenuItem("Pepsi-Cola", 3));

    Menu *lMineralWatersMenu = new Menu("Mineral waters");
    lMineralWatersMenu->addSubitem(new MenuItem("Borjomi", 2.43, "   nice thing  "));
    lMineralWatersMenu->addSubitem(new MenuItem("Morshynska", 1.4, "         "));
    lBeveragesMenu->addSubitem(lMineralWatersMenu);

    Menu *lAlcoDrinksMenu = new Menu("Alco drinks");
    Menu *lWinesMenu = new Menu("Wines");
    Menu *lDryWines = new Menu("Dry Wines");
    lDryWines->addSubitem(new MenuItem("Bordeaux", 20));
    lWinesMenu->addSubitem(lDryWines);
    lWinesMenu->addSubitem(new MenuItem("Champagne", 16.5));
    lAlcoDrinksMenu->addSubitem(lWinesMenu);
    lAlcoDrinksMenu->addSubitem(new MenuItem("Beer", 5));
    lBeveragesMenu->addSubitem(lAlcoDrinksMenu);

    mRoot->addSubitem(lBeveragesMenu);
}
