//
// Created by Iron Tony on 19/12/2020.
//

#include "file_list/file.h"

File::File(QString name, bool isDirectory, bool isHidden, bool isReadable) :
        mName(std::move(name)), mIsDirectory(isDirectory), mIsHidden(isHidden), mIsReadable(isReadable) {}

const QString& File::getName() const {
    return mName;
}

bool File::isDirectory() const {
    return mIsDirectory;
}

bool File::isHidden() const {
    return mIsHidden;
}

bool File::isReadable() const {
    return mIsReadable;
}

File File::fromJson(const QJsonObject& json) {
    QString name = json.value("name").toString();
    int type = json.value("type").toInt();
    bool isHidden = json.value("isHidden").toBool();
    bool isReadable = json.value("isReadable").toBool();
    return File(name, type == 0, isHidden, isReadable);
}
