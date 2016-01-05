#include "texteditprintmenuvisitor.h"

#include <QPlainTextEdit>

#include "menuitem.h"
#include "menu.h"

TextEditPrintMenuVisitor::TextEditPrintMenuVisitor(QPlainTextEdit *textEdit)
        : mTextEdit{textEdit}
{

}

/*!
 * \brief TextEditPrintMenuVisitor::indent
 * \param item
 * \return
 */
QString TextEditPrintMenuVisitor::indent(Composite *item) const
{
    QString rIndentString;

    QString lIndentStep("    ");
    Composite *lMenuItem = item->parent();
    while (lMenuItem)
    {
        lMenuItem = lMenuItem->parent();
        rIndentString.append(lIndentStep);
    }

    return rIndentString;
}


QString TextEditPrintMenuVisitor::indent(DiscountMenuItem *item) const
{
    QString rIndentString;

    QString lIndentStep("    ");
    Composite *lMenuItem = item->parent();
    while (lMenuItem)
    {
        lMenuItem = lMenuItem->parent();
        rIndentString.append(lIndentStep);
    }
    rIndentString.chop(lIndentStep.size()+1); // miss one indent level
    return rIndentString;
}

/*!
 * \brief TextEditPrintMenuVisitor::visit
 * \param item
 */
void TextEditPrintMenuVisitor::visit(MenuItem *item)
{
    QString outString;

    QString lIndentString = indent(item);

    outString = QString("%1 > %2    %3$").arg(lIndentString).arg(item->title().c_str()).arg(item->price());
    mTextEdit->appendPlainText(outString);

    if (!item->description().empty())
    {
        QString description;
        description = QString("%1   ::::%2::::").arg(lIndentString).arg(item->description().c_str());
        mTextEdit->appendPlainText(description);
    }
}

/*!
 * \brief TextEditPrintMenuVisitor::visit
 * \param menu
 */
void TextEditPrintMenuVisitor::visit(Menu *menu)
{
//    std::cout << indent(menu) << "[" << menu->title() << "]" << std::endl;
    QString outString;
    QString lIndentString = indent(menu);
    outString = QString("%2[%1]").arg(menu->title().c_str()).arg(lIndentString);
    mTextEdit->appendPlainText(outString);
}

void TextEditPrintMenuVisitor::visit(DiscountMenuItem *item)
{
    if(item->discount() != 0.0)
    {
        QString outString;
        QString lIndentString = indent(item);

        outString = QString("%1 %2 > %3    %4$ %5").arg(lIndentString)
                .arg(DISCOUNT_TEXT)
                .arg(item->title().c_str())
                .arg(item->price()-item->discount())
                .arg(DISCOUNT_TEXT);
        mTextEdit->appendPlainText(outString);

        if (!item->description().empty())
        {
            QString description;
            QString spaces(lIndentString.size() + DISCOUNT_TEXT.size() + 4, QChar(' '));
            description = QString("%1::::%2::::").arg(spaces).arg(item->description().c_str());
            mTextEdit->appendPlainText(description);
        }
    }
    else
        visit(static_cast<MenuItem*>(item));
}
