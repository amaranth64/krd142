#include "mysyntaxhighlighter.h"


MySyntaxHighlighter::MySyntaxHighlighter(QObject *parent):
    QSyntaxHighlighter(parent)
{

}

void MySyntaxHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat format;


    if (text.contains("ОШИБКА") | (text.contains("Ошибка"))){
        format.setBackground(Qt::yellow);
        setFormat(0,text.length(),format);
    }

    if (text.contains("РЕЗУЛЬТАТ: Соответствует ТУ")){
        format.setBackground(Qt::green);
        setFormat(0,text.length(),format);
    }

    if (text.contains("РЕЗУЛЬТАТ: Не соответствует ТУ")){
        format.setBackground(Qt::red);
        setFormat(0,text.length(),format);
    }
}
