//
// Created by Iron Tony on 19/12/2020.
//

#ifndef EXPLORERSERVER_FILE_MODEL_H
#define EXPLORERSERVER_FILE_MODEL_H

#include <QAbstractListModel>
#include <QVector>

#include "file.h"

class FileListModel : public QAbstractListModel {
Q_OBJECT

public:
    enum FileRoles {
        NameRole = Qt::UserRole + 1,
        IsDirectoryRole,
        IsHiddenRole,
        IsReadableRole,
    };

    explicit FileListModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex& index, int role) const override;

    void setData(const QVector<File>& files);

private:
    QVector<File> mFiles;
};

#endif //EXPLORERSERVER_FILE_MODEL_H
