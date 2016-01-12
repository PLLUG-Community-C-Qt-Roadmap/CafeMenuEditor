#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include "texteditprintmenuvisitor.h"
#include "menuiterator.h"
#include "menu.h"
#include "menuitem.h"
#include "adddialog.h"
#include<QString>
#include <QJsonObject>
#include<QJsonValue>
#include<QFile>
#include<QJsonDocument>
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
    connect(ui->action_Save,SIGNAL(triggered()),SLOT(saveMeBabe()),Qt::UniqueConnection);
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

QJsonArray MainWindow::writeJson(Composite* component)
{
    QJsonObject JsonObj;
    QJsonArray JsonArray;
    for( int i =0; i < component->subitemsCount(); ++i)
    {
        if( component->child(i)->TreeType()=="Menu")
        {
            Menu* temp = dynamic_cast<Menu*>(component->child(i));
            JsonObj["type"] = "Menu";
            JsonObj["title"]= temp->title().c_str();
           JsonObj["children"] = writeJson(component->child(i));
        }
        else
        {
            MenuItem* temp = dynamic_cast<MenuItem*>(component->child(i));
            JsonObj["type"] = "MenuItem";
            JsonObj["title"]= temp->title().c_str();
            JsonObj["price"]  = temp->price();
            JsonObj["description"] = temp->description().c_str();
        }

        JsonArray.append(JsonObj);
    }
    return JsonArray;
}

void MainWindow::saveMeBabe()
{
    QString lFileName = QFileDialog::getSaveFileName(this, tr("Save file"),"Menu",
                                                  tr("JSON files (*.json)"));
       QJsonObject ObjectToSave;
       ObjectToSave["type"] = "Menu";
     ObjectToSave["title"] = "MAIN MENU";
     ObjectToSave["children"] = writeJson(mRoot);
      QJsonDocument mainDoc(ObjectToSave);
         QFile jsonFile(lFileName); //provides an interface for reading from and writing to files.
            jsonFile.open(QFile::WriteOnly);
             jsonFile.write(mainDoc.toJson());
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
