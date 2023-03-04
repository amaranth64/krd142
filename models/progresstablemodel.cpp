#include "progresstablemodel.h"

MainProgressTableModel::MainProgressTableModel()
{
    slHHeader << "Время начала" << "Пункт методики" << "Наименование";
    stageData.clear();
}

int MainProgressTableModel::rowCount(const QModelIndex &parent) const
{
    return stageData.size();
}

int MainProgressTableModel::columnCount(const QModelIndex &parent) const
{
    return slHHeader.count();
}

QVariant MainProgressTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

//    if (orientation == Qt::Vertical){
//        return QString::number(section + 1) ;
//    }

    if (orientation == Qt::Horizontal){
        return slHHeader.at(section);
    }
    return QVariant();
}

QVariant MainProgressTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
        case Qt::DisplayRole:
        if (stageData.count() < index.row() + 1) return QVariant();

        switch (index.column()) {
        case 0:
            return stageData.at(index.row()).time;
        case 1:
            return stageData.at(index.row()).punkt;
        case 2:
            return stageData.at(index.row()).text;
        }
            return QVariant(); // пока так

        case Qt::TextAlignmentRole:
            if (index.column() == 2) return Qt::AlignLeft ^ Qt::AlignVCenter;
            return Qt::AlignCenter;

        case Qt::BackgroundRole:
//            if ()
//                return QBrush(Qt::green);
            return QVariant();

        default:
            return QVariant();
    }
}

Qt::ItemFlags MainProgressTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return  Qt::ItemIsEnabled;
}

void MainProgressTableModel::addStage(StageData stData)//
{
    int row = 0;
    if (stageData.count() > 0) row = stageData.count() - 1;

    beginInsertRows(QModelIndex(), row, row);
    stageData.append(stData);
    endInsertRows();
}

void MainProgressTableModel::clearStage()
{
    beginResetModel();
    stageData.clear();
    endResetModel();
}

