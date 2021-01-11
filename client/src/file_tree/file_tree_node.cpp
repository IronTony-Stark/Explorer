//
// Created by Iron Tony on 20/12/2020.
//

#include "file_tree/file_tree_node.h"

FileTreeNode::FileTreeNode(QString data, QString absolutePath, FileTreeNode* parentItem)
        : mParent(parentItem), mName(std::move(data)),
          mAbsolutePath(std::move(absolutePath)), mHasBeenExpanded(false) {}

FileTreeNode::~FileTreeNode() {
    qDeleteAll(mChildren);
}

int FileTreeNode::childCount() const {
    return mChildren.count();
}

QString FileTreeNode::data() const {
    return mName;
}

int FileTreeNode::row() const {
    if (mParent)
        return mParent->mChildren.indexOf(const_cast<FileTreeNode*>(this));

    return 0;
}

void FileTreeNode::appendChild(FileTreeNode* child) {
    mChildren.append(child);
}

FileTreeNode* FileTreeNode::child(int row) {
    return mChildren.value(row);
}

FileTreeNode* FileTreeNode::parentItem() {
    return mParent;
}

bool FileTreeNode::hasBeenExpanded() const {
    return mHasBeenExpanded;
}

void FileTreeNode::setHasBeenExpanded(bool value) {
    mHasBeenExpanded = value;
}

const QList<FileTreeNode*>& FileTreeNode::children() const {
    return mChildren;
}

QString FileTreeNode::getAbsolutePath() const {
    return mAbsolutePath;
}

void FileTreeNode::removeAllChildren() {
    mChildren.clear();
}
