#include "simplecolumn.h"

SimpleColumn::SimpleColumn(QString name,QString header):AbstractColumn (name, header)
{

}

SimpleColumn::~SimpleColumn()
{

}

QVariant SimpleColumn::colData(const QVariantMap &rowData, int role)
{
    if ((role == Qt::DisplayRole) || (role == Qt::EditRole) ||  (role == Qt::BackgroundRole)) return rowData.value(name()); // вернули данные для нужной колонки
    return QVariant();
}



