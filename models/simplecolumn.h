#ifndef SIMPLECOLUMN_H
#define SIMPLECOLUMN_H

#include "abstractcolumn.h"

class SimpleColumn : public AbstractColumn
{
public:
    SimpleColumn(QString name,QString header);
    ~SimpleColumn();

public:
    virtual QVariant colData(const QVariantMap &rowData, int role) override;
};

#endif // SIMPLECOLUMN_H
