#ifndef TEXTEDITPRINTMENUVISITOR_H
#define TEXTEDITPRINTMENUVISITOR_H

#include "menuvisitor.h"

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

private:
    QPlainTextEdit *mTextEdit;
    QString indent(Composite *item) const;
};


#endif // TEXTEDITPRINTMENUVISITOR_H
