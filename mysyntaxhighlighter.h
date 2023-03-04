#ifndef MYSYNTAXHIGHLIGHTER_H
#define MYSYNTAXHIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class MySyntaxHighlighter : public QSyntaxHighlighter
{
public:
    explicit MySyntaxHighlighter(QObject *parent = 0);

    // QSyntaxHighlighter interface
protected:
    void highlightBlock(const QString &text);
private:
    QString pattern;
};

#endif // MYSYNTAXHIGHLIGHTER_H
