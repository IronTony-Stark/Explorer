#include <QJsonArray>
#include <http_exception.h>

#include "filesystem.h"
#include "file_info.h"
#include "dir_info.h"

QJsonDocument FileSystem::getRootFiles() {
    QList<QFileInfo> drives = QDir::drives();
    bool isWindows = drives[0].path() != "/";

    if (isWindows) {
        QJsonArray files = getFileInfoJsonArray(drives);
        return filesToJsonDoc("", files);
    } else {
        return getFilesByPath("/");
    }
}

QJsonDocument FileSystem::getFilesByPath(const QString& path) {
    QDir dir = getDir(path);
    QList<QFileInfo> files = dir.entryInfoList(QDir::AllDirs | QDir::Files | QDir::Hidden);
    QJsonArray arr = getFileInfoJsonArray(files);
    return filesToJsonDoc(path, arr);
}

QJsonDocument FileSystem::getRootDirs() {
    QList<QFileInfo> drives = QDir::drives();
    bool isWindows = drives[0].path() != "/";

    if (isWindows) {
        QJsonArray dirs = getDirInfoJsonArray(drives);
        return dirsToJsonDoc(dirs);
    } else {
        return getDirsByPath("/");
    }
}

QJsonDocument FileSystem::getDirsByPath(const QString& path) {
    QDir dir = getDir(path);
    QList<QFileInfo> dirs = dir.entryInfoList(QDir::AllDirs | QDir::NoDot | QDir::NoDotDot);
    QJsonArray arr = getDirInfoJsonArray(dirs);
    return dirsToJsonDoc(arr);
}

QJsonDocument FileSystem::filesToJsonDoc(const QString& path, const QJsonArray& files) {
    QJsonDocument result;
    QJsonObject json;

    json.insert("directory", path);
    json.insert("files", files);

    result.setObject(json);
    return result;
}

QJsonDocument FileSystem::dirsToJsonDoc(const QJsonArray& dirs) {
    QJsonDocument result;
    QJsonObject json;

    json.insert("dirs", dirs);

    result.setObject(json);
    return result;
}

QJsonArray FileSystem::getFileInfoJsonArray(const QList<QFileInfo>& files) {
    QJsonArray json;

    for (const auto& file : files) {
        FileInfo info(file);
        json.append(info.toJson());
    }

    return json;
}

QJsonArray FileSystem::getDirInfoJsonArray(const QList<QFileInfo>& files) {
    QJsonArray json;

    for (const auto& file : files) {
        DirInfo info(file);
        json.append(info.toJson());
    }

    return json;
}

QDir FileSystem::getDir(const QString& path) {
    QDir dir(path);
    if (!dir.exists())
        throw HttpException(404, "Not Found", "Directory Does Not Exist");

    return dir;
}
