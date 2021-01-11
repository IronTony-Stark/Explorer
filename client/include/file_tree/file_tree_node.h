//
// Created by Iron Tony on 20/12/2020.
//

#ifndef EXPLORERSERVER_TREENODE_H
#define EXPLORERSERVER_TREENODE_H

#include <QList>
#include <QString>

class FileTreeNode {
public:
    explicit FileTreeNode(QString name, QString absolutePath, FileTreeNode* parentItem = nullptr);
    ~FileTreeNode();

    int childCount() const;
    QString data() const;
    QString getAbsolutePath() const;
    int row() const;
    bool hasBeenExpanded() const;
    const QList<FileTreeNode*>& children() const;

    void appendChild(FileTreeNode* child);
    void removeAllChildren();
    FileTreeNode* child(int row);
    FileTreeNode* parentItem();
    void setHasBeenExpanded(bool);

private:
    FileTreeNode* mParent;
    QList<FileTreeNode*> mChildren;
    QString mName;
    QString mAbsolutePath;
    bool mHasBeenExpanded;
};

#endif //EXPLORERSERVER_TREENODE_H
