//
// Created by Iron Tony on 24/12/2020.
//

#include <QDir>

#include "dir_info.h"

DirInfo::DirInfo(const QFileInfo& fileInfo)
        : mName(fileInfo.fileName().isEmpty() ? fileInfo.path() : fileInfo.fileName()),
          mAbsolutePath(fileInfo.absolutePath()) {
    if (!mAbsolutePath.isEmpty() && mAbsolutePath[mAbsolutePath.size() - 1] != '/')
        mAbsolutePath += '/';
    mAbsolutePath += fileInfo.fileName();

    QDir dir = QDir(mAbsolutePath);
    QList<QFileInfo> dirs = dir.entryInfoList(QDir::AllDirs | QDir::NoDot | QDir::NoDotDot);
    mHasChildrenDirs = !dirs.isEmpty();
}

QJsonObject DirInfo::toJson() {
    QJsonObject result;

    result.insert("name", mName);
    result.insert("absolutePath", mAbsolutePath);
    result.insert("hasChildrenDirs", mHasChildrenDirs);

    return result;
}