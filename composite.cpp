#include "composite.h"
#include "menuvisitor.h"

/*!
 * \brief Composite::Composite constructor
 * \param pTitle is item's title.
 */
Composite::Composite(const std::string &pTitle)
    : mTitle(pTitle),
      mParent(nullptr)
{
}

/*!
 * \brief Composite::~Composite destructor
 */
Composite::~Composite()
{
    for (const auto &subitem : mListSubitems)
    {
        delete subitem;
    }

    mListSubitems.clear();
}

/*!
 * \brief Composite::addSubitem
 * \param pItem is new child subitem for this item
 */
void Composite::addSubitem(Composite *pItem)
{
    if (this != pItem)
    {
        mListSubitems.push_back(pItem);
        pItem->mParent = this;
    }
}

/*!
 * \brief Composite::subitemsCount
 * \return number of item's childs
 */
int Composite::subitemsCount() const
{
    return mListSubitems.size();
}

/*!
 * \brief Composite::child
 * \param pIndex is index of child item
 * \return child by index
 */
Composite *Composite::child(int pIndex) const
{
    return mListSubitems.at(pIndex);
}

/*!
 * \brief Composite::parent
 * \return parent of this item
 */
Composite *Composite::parent() const
{
    return mParent;
}

/*!
 * \brief Composite::title
 * \return title of this item
 */
std::string Composite::title() const
{
    return mTitle;
}

void Composite::setTitle(const std::string &title)
{
    mTitle = title;
}

void Composite::removeSubitem(const std::string &title)
{
    std::vector<Composite*>::iterator it;
    for(it=mListSubitems.begin();it!=mListSubitems.end();++it)
    {
        if((*it)->title()==title)
        {
            (*it)->deleteChildren();
            delete (*it);
            mListSubitems.erase(it);
            return;
        }
    }
}



void Composite::deleteChildren()
{
    for(auto child: mListSubitems)
    {
        child->deleteChildren();
        delete child;
    }
    mListSubitems.clear();
}
