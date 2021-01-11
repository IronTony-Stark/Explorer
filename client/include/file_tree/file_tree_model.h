//
// Created by Iron Tony on 20/12/2020.
//

#ifndef EXPLORERCLIENT_FILE_TREE_MODEL_H
#define EXPLORERCLIENT_FILE_TREE_MODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QVector>
#include <QQueue>
#include <file_list/file_list.h>

#include "tcp_client.h"
#include "dir.h"

class FileTreeNode;

class FileTreeModel : public QAbstractItemModel {
Q_OBJECT

public:
    FileTreeModel(TcpClient&, const FileList&, QObject* parent = nullptr);
    ~FileTreeModel() override;

    QVariant data(const QModelIndex& index, int role) const override;

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE void changeDirectoryClicked(const QModelIndex& index);
    Q_INVOKABLE void expand(const QModelIndex& index);

private slots:
    void onRootDirsReceived(const QVector<Dir>&);
    void onDirsReceived(const QVector<Dir>&);

private:
    void expand(FileTreeNode*);
    void appendChildren(FileTreeNode&, const QVector<Dir>&);

    FileTreeNode* mRoot;
    TcpClient& mTcpClient;
    QQueue<FileTreeNode*> mExpandQueue;
};

#endif //EXPLORERCLIENT_FILE_TREE_MODEL_H
