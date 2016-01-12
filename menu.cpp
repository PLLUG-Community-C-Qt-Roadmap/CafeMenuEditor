#include "menu.h"
#include "menuvisitor.h"

/*!
 * \brief Menu::Menu constructor
 * \param pTitle is menu title
 */
Menu::Menu(const std::string &pTitle)
    : Composite(pTitle)
{
    setTreeType("Menu");
}

/*!
 * \brief Menu::accept
 * \param visitor
 */
void Menu::accept(MenuVisitor *visitor)
{
    visitor->visit(this);
}

