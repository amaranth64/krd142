#include "maintablemodel.h"

MainTableModel::MainTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

//================================================================================================
//================== ДОПОЛНИТЕЛЬНЫЕ МЕТОДЫ МОДЕЛИ ================================================
//================================================================================================

void MainTableModel::registerColumn(AbstractColumn *column)
{
    columns.append(column); // добавили новую колонку в список (зарегистрировали)
}

void MainTableModel::addRow(QVariantMap rowData)
{
    QString id = rowData.value("id").toString(); // считаем, что идентификатор ряда храниться в поле id

    beginInsertRows(QModelIndex(), rowIndex.count(), rowIndex.count());
    rowIndex.append(id); // добавляем идентификатор ряда в список рядов
    dataHash.insert(id,rowData); // добавляем идентификатор и данные в список данных
    endInsertRows();
}

QString MainTableModel::getIdByRow(int row) const
{
    return rowIndex.at(row);
}

int MainTableModel::getRowById(QString id) const
{
    return rowIndex.indexOf(id);
}

int MainTableModel::getColumnByName(QString name) const
{
    for (int col = 0; col < columns.count(); col++){
        if (getNameByColumn(col) == name) return col;
    }
    return -1;
}

QString MainTableModel::getNameByColumn(int col) const
{
    return columns.at(col)->name();
}

void MainTableModel::insertData(QString rowId, QVariant data)
{
    int row = getRowById(rowId);
    if (row >= 0) {
        QModelIndex startIndex=createIndex(getRowById(rowId), getColumnByName("dataHave"));
        setData(startIndex, data, Qt::EditRole);
    }
}

void MainTableModel::insertResult(QString rowId, QVariant data)
{
    int row = getRowById(rowId);
    if (row >= 0) {
        QModelIndex startIndex=createIndex(getRowById(rowId), getColumnByName("result"));
        setData(startIndex, data, Qt::EditRole);
    }
}

void MainTableModel::resetModel()
{
    beginResetModel();
    rowIndex.clear(); // здесь храним идентификатор ряда
    dataHash.clear(); // здесь храним данные для ряда с идентификатором int
    columns.clear();
    endResetModel();
}

bool MainTableModel::loadFromXMLFile(QFile *file)
{
    QVariantMap line;
    QString id;

    dataErrorString.clear();
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        dataErrorString = "Ошибка открытия файла";
        emit errorHappend(dataErrorString);
        return false;
    }

    columns.clear();
    QXmlStreamReader xml(file);

    while (!xml.atEnd() && !xml.hasError()){

            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartDocument)
                continue;
            if (token == QXmlStreamReader::StartElement)
            {
                if (xml.name() == "data")
                    continue;

                if (xml.name() == "columns")
                    continue;

                if (xml.name() == "column"){
                    QXmlStreamAttributes attributes = xml.attributes();

                    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "column"))
                    {
                        if (attributes.hasAttribute("name")){
                            QString elementName = attributes.value("name").toString();
                            xml.readNext();
                            registerColumn(new SimpleColumn(elementName, xml.text().toString()));
                        }

                       xml.readNext();
                    }
                } //column

                if (xml.name() == "rows")
                    continue;

                if (xml.name() == "row") {
                    // читаем аттрибуты ряда
                    QXmlStreamAttributes attributes = xml.attributes();
                    // читаем аттрибут id ряда
                    if (attributes.hasAttribute("id")) id = attributes.value("id").toString();
                    // начинаем заполнять ряд данными
                    line.insert("id", attributes.value("id").toString());

                    xml.readNext();

                    // цикл для чтения нанных внутри тега row
                    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "row"))
                    {
                        if (xml.tokenType() == QXmlStreamReader::StartElement)
                        {
                            if (xml.name() == "name"){
                                QString elementName = xml.name().toString();
                                xml.readNext();
                                line.insert("name", xml.text().toString());
                            }

                            if (xml.name() == "punkt"){
                                QString elementName = xml.name().toString();
                                xml.readNext();
                                line.insert("punkt", xml.text().toString());
                            }

                            if (xml.name() == "dataNeed"){
                                QString elementName = xml.name().toString();
                                xml.readNext();
                                line.insert("dataNeed", xml.text().toString());
                            }

                            if (xml.name() == "dataHave"){
                                QString elementName = xml.name().toString();
                                xml.readNext();
                                line.insert("dataHave", xml.text().toString());
                            }

                            if (xml.name() == "result"){
                                QString elementName = xml.name().toString();
                                xml.readNext();
                                line.insert("result", xml.text().toString());
                            }


                            if (xml.name() == "color"){
                                QXmlStreamAttributes attributes = xml.attributes();
                                if (attributes.hasAttribute("value")){
                                    QColor c = attributes.value("value").toString();
                                    QString elementName = attributes.value("value").toString();
                                    xml.readNext();
                                    line.insert(xml.name().toString(), c);
                                } else {
                                    line.insert("color", "#FFFFFF");
                                }
                            }
                        }
                        xml.readNext();
                    }

                    // добавляем ряд в модель
                    addRow(line);
                 } //row
            }
    }

    file->close();

    if (xml.hasError()) {
        dataErrorString.append(xml.errorString());
        return false;
    }
    return true;
}


//================================================================================================
//================== ОСНОВНЫЕ МЕТОДЫ МОДЕЛИ ======================================================
//================================================================================================

QVariant MainTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::FontRole){
        QFont f;
        f.setPointSize(12);
        f.setWeight(QFont::Bold);
        return f;
    }
    if (role != Qt::DisplayRole)
        return QVariant();

     if (orientation == Qt::Horizontal){
        if (section > (columns.count()-1)) return QVariant();
        return columns.at(section)->header();
    }

//    if (orientation == Qt::Vertical){
//        if (section > (rowIndex.count()-1)) return QVariant();
//        return rowIndex.at(section);
//    }

    return QVariant();
}


int MainTableModel::rowCount(const QModelIndex &parent) const
{
    return rowIndex.count();
}

int MainTableModel::columnCount(const QModelIndex &parent) const
{
    return columns.count();
}

QVariant MainTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole){
        QString id = getIdByRow(index.row()); // получили идентификатор ряда
        QVariantMap data = dataHash.value(id); // получили данные
        return columns.at(index.column())->colData(data, role); //вернули данные
    }

    if (role == Qt::TextAlignmentRole) {
        QString id = getIdByRow(index.row()); // получили идентификатор ряда

        if (id.contains("C")) return Qt::AlignCenter;

        if ((id.contains("D"))&(index.column()==1)) {
            return static_cast<QVariant>(Qt::AlignRight | Qt::AlignVCenter);
        }

        return Qt::AlignCenter;
    }

    if (role == Qt::FontRole){
        QString id = getIdByRow(index.row()); // получили идентификатор ряда
        QFont f;
        if (id.contains("C")){
            f.setPointSize(10);
            f.setWeight(QFont::Bold);
        } else {
            f.setPointSize(10);
            f.setWeight(QFont::Normal);
        }

         return f;
 //       return QVariant();
    }

    if (role == Qt::BackgroundRole) {
        QString id = getIdByRow(index.row()); // получили идентификатор ряда
        QVariantMap data = dataHash.value(id); // получили данные
        QString color = data.value("color").toString();
        return QColor(color);
    }

    // FIXME: Implement me!
    return QVariant();
}

bool MainTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (role == Qt::EditRole){
        QString id = getIdByRow(index.row());
        dataHash[id].insert(getNameByColumn(index.column()),value);
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags MainTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

