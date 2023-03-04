#ifndef MAINPROGRESSTABLEMODEL_H
#define MAINPROGRESSTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QList>
#include "common/enumTypeData.h"

class MainProgressTableModel : public QAbstractTableModel
{
public:
    MainProgressTableModel();

    // QAbstractItemModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role = Qt::EditRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

public slots:
    void addStage(StageData stData);//StageData stData
    void clearStage();

private:
    QStringList slHHeader;
    QList<StageData> stageData;

};

#endif // MAINPROGRESSTABLEMODEL_H
