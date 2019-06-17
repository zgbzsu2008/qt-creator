#include "stringlistmodel.h"

#include <QDataStream>
#include <QMimeData>

StringListModel::StringListModel(const QStringList& strings, QObject* parent)
    : QAbstractListModel(parent), stringList(strings)
{}

int StringListModel::rowCount(const QModelIndex& /*parent*/) const
{
    return stringList.count();
}

QVariant StringListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }
    if (index.row() >= stringList.size()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        return stringList.at(index.row());
    } else {
        return QVariant();
    }
}

QVariant StringListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        return QString("Column %1").arg(section);
    } else {
        return QString("Row %1").arg(section);
    }
}

bool StringListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        if (!value.toString().isEmpty()) {  // 数据空不改
            stringList.replace(index.row(), value.toString());
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

Qt::ItemFlags StringListModel::flags(const QModelIndex& index) const
{
    if (!index.isValid()) {
        return Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

bool StringListModel::insertRows(int row, int count, const QModelIndex& parent)
{
    beginInsertRows(parent, row, row + count - 1);
    for (int r = 0; r < count; ++r) {
        stringList.insert(row, "value");
    }
    endInsertRows();
    return true;
}

bool StringListModel::removeRows(int row, int count, const QModelIndex& parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    for (int r = 0; r < count; ++r) {
        stringList.removeAt(row);
    }
    endRemoveRows();
    return true;
}

QStringList StringListModel::mimeTypes() const
{
    QStringList types;
    types << "application/vnd.txt.list";
    return types;
}

QMimeData* StringListModel::mimeData(const QModelIndexList& indexes) const
{
    QMimeData* mimeData = new QMimeData;
    QByteArray encodedData;
    QDataStream stream(&encodedData, QIODevice::WriteOnly);
    for (auto index : indexes) {
        if (index.isValid()) {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << text;
        }
    }
    mimeData->setData("application/vnd.txt.list", encodedData);
    return mimeData;
}

bool StringListModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int column,
                                   const QModelIndex& parent)
{
    if (action == Qt::IgnoreAction) {
        return false;
    }
    if (!data->hasFormat("application/vnd.txt.list")) {
        return false;
    }
    if (column > 0) {
        return false;
    }

    int beginRow;
    if (row != -1) {
        beginRow = row;
    } else if (parent.isValid()) {
        beginRow = parent.row();
    } else {
        beginRow = rowCount(QModelIndex());
    }

    QByteArray encodedData = data->data("application/vnd.txt.list");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QStringList items;
    int rows = 0;
    while (!stream.atEnd()) {
        QString text;
        stream >> text;
        items << text;
        ++rows;
    }
    insertRows(beginRow, rows);
    for (auto item : items) {
        QModelIndex idx = index(beginRow, 0);
        setData(idx, items);
        ++beginRow;
    }
    return true;
}

Qt::DropActions StringListModel::supportedDropActions() const
{
    return Qt::CopyAction | Qt::MoveAction;
}
