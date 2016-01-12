#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <string>
#include <vector>

class MenuVisitor;

/*!
 * \brief The Composite basic class that realise compositor patern for cafe menu.
 */
class Composite
{
public:
    Composite(const std::string &pTitle);
    virtual ~Composite();

    void addSubitem(Composite *pItem);
    int subitemsCount() const;

    Composite *child(int pIndex) const;
    Composite *parent() const;

    std::string title() const;
    void setTitle(const std::string &title);


    virtual void accept(MenuVisitor *visitor) = 0;

    void removeSubitem(const std::string &title);

private:
    void deleteChildren();

private:
    std::string mTitle;
    Composite *mParent;
    std::vector<Composite *> mListSubitems;
};

#endif // COMPOSITE_H
