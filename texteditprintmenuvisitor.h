#ifndef TEXTEDITPRINTMENUVISITOR_H
#define TEXTEDITPRINTMENUVISITOR_H

#include "menuvisitor.h"
#include "DiscountMenuItem.h"
#include<QString>

class Composite;
class QPlainTextEdit;
/*!
 * \brief The ConsolePrintMenuVisitor class
 */
class TextEditPrintMenuVisitor : public MenuVisitor
{
public:
    TextEditPrintMenuVisitor(QPlainTextEdit *textEdit);
    void visit(MenuItem *item);
    void visit(Menu *menu);
    void visit(DiscountMenuItem *item);

private:
    QPlainTextEdit *mTextEdit;
    QString indent(Composite *item) const;
    QString indent(DiscountMenuItem *item) const;
    const QString DISCOUNT_TEXT = QStringLiteral("!!!Discount!!!");
};


#endif // TEXTEDITPRINTMENUVISITOR_H
