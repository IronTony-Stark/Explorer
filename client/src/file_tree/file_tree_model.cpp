//
// Created by Iron Tony on 20/12/2020.
//

#include <file_tree/dir.h>

#include "file_list/file_list_model.h"
#include "file_tree/file_tree_model.h"
#include "file_tree/file_tree_node.h"

FileTreeModel::FileTreeModel(TcpClient& tcpClient, const FileList& fileList, QObject* parent)
        : QAbstractItemModel(parent), mTcpClient(tcpClient) {
    mRoot = new FileTreeNode("", "");

    connect(&mTcpClient, &TcpClient::filesReceived, &fileList, &FileList::onFilesReceived);
    connect(&mTcpClient, &TcpClient::dirsReceived, this, &FileTreeModel::onDirsReceived);
    connect(&mTcpClient, &TcpClient::rootDirsReceived, this, &FileTreeModel::onRootDirsReceived);

    mTcpClient.getRootDirs();
}

FileTreeModel::~FileTreeModel() {
    delete mRoot;
}

QVariant FileTreeModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    auto* item = static_cast<FileTreeNode*>(index.internalPointer());

    return item->data();
}

QModelIndex FileTreeModel::index(int row, int column, const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent))
        return {};

    FileTreeNode* parentItem;
    if (!parent.isValid())
        parentItem = mRoot;
    else
        parentItem = static_cast<FileTreeNode*>(parent.internalPointer());

    FileTreeNode* childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return {};
}

QModelIndex FileTreeModel::parent(const QModelIndex& index) const {
    if (!index.isValid())
        return {};

    auto* childItem = static_cast<FileTreeNode*>(index.internalPointer());
    FileTreeNode* parentItem = childItem->parentItem();

    if (parentItem == mRoot)
        return {};

    return createIndex(parentItem->row(), 0, parentItem);
}

int FileTreeModel::rowCount(const QModelIndex& parent) const {
    FileTreeNode* parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = mRoot;
    else
        parentItem = static_cast<FileTreeNode*>(parent.internalPointer());

    return parentItem->childCount();
}

int FileTreeModel::columnCount(const QModelIndex& parent) const {
    return 1;
}

void FileTreeModel::changeDirectoryClicked(const QModelIndex& index) {
    if (!index.isValid())
        return;

    auto* parent = static_cast<FileTreeNode*>(index.internalPointer());
    mTcpClient.getFilesByPath(parent->getAbsolutePath());
}

void FileTreeModel::expand(const QModelIndex& index) {
    if (!index.isValid())
        return;

    auto* parent = static_cast<FileTreeNode*>(index.internalPointer());
    expand(parent);
}

void FileTreeModel::onRootDirsReceived(const QVector<Dir>& dirs) {
    beginInsertRows(QModelIndex(), 0, dirs.size() - 1);
    appendChildren(*mRoot, dirs);
    endInsertRows();
}

void FileTreeModel::onDirsReceived(const QVector<Dir>& dirs) {
    FileTreeNode* parent = mExpandQueue.dequeue();

    QModelIndex parentIndex = createIndex(parent->row(), 0, parent);

    beginRemoveRows(parentIndex, 0, 0);
    parent->removeAllChildren();
    endRemoveRows();

    beginInsertRows(parentIndex, 0, dirs.size() - 1);
    appendChildren(*parent, dirs);
    endInsertRows();
}

void FileTreeModel::expand(FileTreeNode* parent) {
    if (!parent->hasBeenExpanded()) {
        parent->setHasBeenExpanded(true);
        mExpandQueue.enqueue(parent);
        mTcpClient.getDirsByPath(parent->getAbsolutePath());
    }
}

void FileTreeModel::appendChildren(FileTreeNode& parent, const QVector<Dir>& dirs) {
    for (auto& dir : dirs) {
        auto* child = new FileTreeNode(dir.getName(), dir.getAbsolutePath(), &parent);

        if (dir.hasChildrenDirs()) {
            auto* dummyChild = new FileTreeNode("Loading...", "", child);
            child->appendChild(dummyChild);
        }

        parent.appendChild(child);
    }
}
