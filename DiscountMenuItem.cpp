#include "DiscountMenuItem.h"

DiscountMenuItem::DiscountMenuItem(const std::string &pTitle, double pPrice, double pDiscount, std::string pDescription) :
    MenuItem(pTitle, pPrice, pDescription),
    mDiscount(pDiscount)
{

}

double DiscountMenuItem::discount() const
{
    return mDiscount;
}

void DiscountMenuItem::setDiscount(double discount)
{
    mDiscount = discount;
}

void DiscountMenuItem::accept(MenuVisitor *visitor)
{
    visitor->visit(this);
}

