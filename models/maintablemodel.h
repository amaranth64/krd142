#ifndef MAINTABLEMODEL_H
#define MAINTABLEMODEL_H

#include <QAbstractTableModel>
#include <QColor>
#include <QBrush>
#include <QFile>
#include <QFont>
#include <QFlags>
#include <QXmlStreamReader>

#include "abstractcolumn.h"
#include "simplecolumn.h"

class MainTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MainTableModel(QObject *parent = nullptr);

    void registerColumn(AbstractColumn *column);
    void addRow(QVariantMap rowData);
    QString getIdByRow(int row) const;
    int getRowById(QString id) const;
    int getColumnByName(QString name) const;
    QString getNameByColumn(int col) const;
    void insertData(QString rowId, QVariant data);
    void insertResult(QString rowId, QVariant data);
    void resetModel();


    bool loadFromXMLFile(QFile *file);


public:
    QString dataErrorString = "";




    // Header:    // Basic functionality:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

signals:
    void errorHappend(QString err);

private:

    QList<QString> rowIndex; // здесь храним идентификатор ряда
    QHash<QString, QVariantMap> dataHash; // здесь хроним данные для ряда с идентификатором int
    QList<AbstractColumn*> columns;


    // QAbstractItemModel interface
public:

};

#endif // MAINTABLEMODEL_H
