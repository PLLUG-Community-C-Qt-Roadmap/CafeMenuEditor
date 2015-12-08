#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <vector>
#include "composite.h"

class MenuVisitor;

/*!
 * \brief The MenuItem class is main component, from which derive composites and leaves
 * and also class for menu item - leave of our hierarchy.
 */
class MenuItem : public Composite
{
public:

    MenuItem(const std::string &pTitle, double pPrice = 0.0, std::string pDescription = std::string());

    std::string description() const;
    void setDescription(const std::string &description);

    double price() const;
    void setPrice(double price);

    void accept(MenuVisitor *visitor);

private:
    double mPrice;
    std::string mDescription;
};

#endif // MENUITEM_H
