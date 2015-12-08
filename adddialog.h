#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

namespace Ui {
class AddDialog;
}

class Composite;

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = 0);
    ~AddDialog();

    void setMenu(Composite *);

    Composite* newMenuItem() const;

protected:
    void showEvent(QShowEvent *);

private slots:
    void slotBackClicked();
    void slotCancelClicked();
    void slotNextClicked();
    void slotOkClicked();

    void slotChanged();

private:
    void showPage1();
    void showPage2();

    void clear();

private:
    Ui::AddDialog *ui;
    Composite *mRoot;
    Composite *mNewItem;
    Composite *mParent;
};

#endif // ADDDIALOG_H
