#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QJsonArray>
namespace Ui {
class MainWindow;
}

class Composite;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slotPrintMenu();

private slots:
    void menuElementSelected();

    void slotUpdateMenu();
    void slotAddNewItem();
   void saveMeBabe();

    void slotItemChanged();
    void slotSaveEditedItem();
   QJsonArray writeJson(Composite* component);
private:
    void createMenu();

private:
    Ui::MainWindow *ui;
    Composite *mRoot;
};

#endif // MAINWINDOW_H
