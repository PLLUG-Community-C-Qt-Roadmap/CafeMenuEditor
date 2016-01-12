#ifndef MENUCOMBOBOX_H
#define MENUCOMBOBOX_H

#include <QComboBox>
#include <QHash>

class Composite;

class MenuComboBox : public QComboBox
{
    Q_OBJECT
public:
    MenuComboBox(QWidget *parent = 0);

    void setMenu(Composite *menu);

    Composite* currentMenuItem() const;

    void updateComboBox();
private:
    void populateComboBox();

private:
    Composite *mRoot; //Кореневий елемент у меню (той елемент який містить усі інші)

    QHash<int, Composite*> mItemByIndex; // Contains pairs: index - menu item.
    // Used to get menu item using index. When we choose item in combo box,
    // we will get index of that item (in combo box). Using its index we will
    // get poiner to certain menu element from QHash.
};

#endif // MENUCOMBOBOX_H
