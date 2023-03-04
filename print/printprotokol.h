#ifndef PRINTPROTOKOL_H
#define PRINTPROTOKOL_H

#include <QObject>
#include <QDebug>
#include <QMap>
#include <QFile>
#include <QColor>
#include <QAxObject>
#include <QCoreApplication>
#include "windows.h"

class PrintProtokol : public QObject
{
    Q_OBJECT
public:
    explicit PrintProtokol(QObject *parent = nullptr);
    ~PrintProtokol();

    void setFileName(QString name);
    bool print(QMap<QString, QString> data);

signals:

private:
    QString fileName="";
    bool replaceString(QAxObject* wordApp, const QString& oldString, const QString& newString);

    QAxObject* wordApp;
    QAxObject* wordDoc;

};

#endif // PRINTPROTOKOL_H
