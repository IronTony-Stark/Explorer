#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <QString>
#include <QFileInfo>
#include <QJsonObject>

#include "file_type.h"

class FileInfo {
public:
    explicit FileInfo(const QFileInfo& fileInfo);

    QJsonObject toJson();

private:
    QString mName;
    FileType mType;
    bool mIsHidden;
    bool mIsReadable;
};

#endif // FILE_INFO_H
