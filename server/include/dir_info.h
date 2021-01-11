//
// Created by Iron Tony on 24/12/2020.
//

#ifndef EXPLORERSERVER_DIR_INFO_H
#define EXPLORERSERVER_DIR_INFO_H

#include <QString>
#include <QFileInfo>
#include <QJsonObject>

class DirInfo {
public:
    explicit DirInfo(const QFileInfo& fileInfo);

    QJsonObject toJson();

private:
    QString mName;
    QString mAbsolutePath;
    bool mHasChildrenDirs;
};


#endif //EXPLORERSERVER_DIR_INFO_H
