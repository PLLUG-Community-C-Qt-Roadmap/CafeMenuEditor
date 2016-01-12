#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void slotDeleteButton();

private slots:
    void menuElementSelected();

    void slotUpdateMenu();
    void slotAddNewItem();

    void slotItemChanged();
    void slotSaveEditedItem();

    void slotEnableDeleteButton();
    void slotDisableDeleteButton();
private:
    void createMenu();

private:
    Ui::MainWindow *ui;
    Composite *mRoot;
};

#endif // MAINWINDOW_H
