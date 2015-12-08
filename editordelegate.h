#ifndef EDITORDELEGATE_H
#define EDITORDELEGATE_H

#include <QWidget>
#include "menuvisitor.h"

namespace Ui {
class EditorDelegate;
}

class EditorDelegate : public QWidget, public MenuVisitor
{
    Q_OBJECT

public:
    explicit EditorDelegate(QWidget *parent = 0);
    ~EditorDelegate();

    virtual void visit(MenuItem *);
    virtual void visit(Menu *);

    void clear();

public slots:
    void slotSave();

signals:
    void itemChanged();

private:
    Ui::EditorDelegate *ui;

    Menu *mEditedMenu;
    MenuItem *mEditedMenuItem;
};

#endif // EDITORDELEGATE_H
