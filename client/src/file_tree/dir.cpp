//
// Created by Iron Tony on 24/12/2020.
//

#include "file_tree/dir.h"

Dir::Dir(QString name, QString absolutePath, bool hasChildrenDirs)
    : mName(std::move(name)), mAbsolutePath(std::move(absolutePath)), mHasChildrenDirs(hasChildrenDirs) {}

const QString& Dir::getName() const {
    return mName;
}

const QString& Dir::getAbsolutePath() const {
    return mAbsolutePath;
}

bool Dir::hasChildrenDirs() const {
    return mHasChildrenDirs;
}

Dir Dir::fromJson(const QJsonObject& json) {
    QString name = json.value("name").toString();
    QString absolutePath = json.value("absolutePath").toString();
    bool hasChildren = json.value("hasChildrenDirs").toBool();
    return Dir(name, absolutePath, hasChildren);
}
