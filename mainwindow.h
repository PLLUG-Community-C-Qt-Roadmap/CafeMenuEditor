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
private slots:
    void menuElementSelected();
    void slotUpdateMenu();
    void slotAddNewItem();
    void slotItemChanged();
    void slotSaveEditedItem();
    void slotDeleteMenuItem();

private:
    void createMenu();

private:
    Ui::MainWindow *ui;
    Composite *mRoot;
};

#endif // MAINWINDOW_H
