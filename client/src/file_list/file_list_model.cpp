//
// Created by Iron Tony on 19/12/2020.
//

#include "file_list/file_list_model.h"

FileListModel::FileListModel(QObject* parent)
        : QAbstractListModel(parent) {}

int FileListModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent)
    return static_cast<int>(mFiles.size());
}

QHash<int, QByteArray> FileListModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[FileRoles::NameRole] = "name";
    roles[FileRoles::IsDirectoryRole] = "isDirectory";
    roles[FileRoles::IsHiddenRole] = "isHidden";
    roles[FileRoles::IsReadableRole] = "isReadable";

    return roles;
}

QVariant FileListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || index.row() > rowCount(index)) return QVariant();

    const File& file = mFiles.at(index.row());

    switch (role) {
        case NameRole:
            return QVariant::fromValue(file.getName());
        case IsDirectoryRole:
            return QVariant::fromValue(file.isDirectory());
        case IsHiddenRole:
            return QVariant::fromValue(file.isHidden());
        case IsReadableRole:
            return QVariant::fromValue(file.isReadable());
        default:
            return QVariant();
    }
}

void FileListModel::setData(const QVector<File>& files) {
    beginResetModel();
    mFiles = files;
    endResetModel();
}
