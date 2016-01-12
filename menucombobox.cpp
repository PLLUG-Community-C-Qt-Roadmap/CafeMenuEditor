#include "menucombobox.h"

#include "composite.h"
#include "menuiterator.h"

/*!
 * \brief Публічний конструктор.
 * \param parent Батьківський віджет.
 */
MenuComboBox::MenuComboBox(QWidget *parent)
    : QComboBox(parent),
      mRoot{nullptr}
{
}

/*!
 * \brief Встановлює кореневий елемент у меню (той елемент який містить усі інші),
 *  та оновлює QComboBox.
 * \param menu Вказівник на Compositor - кореневий елемент у єрархії нашого меню.
 */
void MenuComboBox::setMenu(Composite *menu)
{
    mRoot = menu;
    clear();  // Очищаємо QComboBox
    mItemByIndex.clear(); // Видаляємо усі елементи з QHash
    populateComboBox(); // Наповнюємо QComboBox заново
}

Composite *MenuComboBox::currentMenuItem() const
{
    int itemId = currentData().toInt();
    return mItemByIndex.value(itemId);
}

void MenuComboBox::updateComboBox()
{
    clear();
    populateComboBox();
}

void MenuComboBox::populateComboBox()
{
    if (mRoot) // Перевіряємо чи кореневий елемент встановлено
    {
        MenuIterator iterator(mRoot); // Створюємо ітератор для меню.
        while (iterator.hasNext())  // Якщо елемент є
        {
            Composite * item = iterator.next(); //  Беремо елемент, і пересуваємо ітератор на наступний

            // Додаємо елементи у QHash
            // To be able to access certain menu item by item id taken from QComboBox item data.
            int itemId = mItemByIndex.size();   // When QHash is empty id will be 0, when one element
                                                // element added - id will be 1, ...
                                                //So every new element will get unique number as an id.

            mItemByIndex.insert(itemId, item); // Add id - item pair.

            // Add item to combo box.
            addItem(item->title().c_str(), itemId);
        }
    }
}

