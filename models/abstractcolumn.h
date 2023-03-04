#ifndef ABSTRACTCOLUMN_H
#define ABSTRACTCOLUMN_H

#include <QString>
#include <QVariantMap>


class AbstractColumn
{
public:
    AbstractColumn(QString name, QString header = "");
    ~AbstractColumn();

    QString name() {return nameCol;}
    QString header() {return headerCol;}

    virtual QVariant colData(const QVariantMap &rowData, int role = Qt::DisplayRole) = 0;
private:
    QString nameCol;
    QString headerCol;

};

#endif // ABSTRACTCOLUMN_H
