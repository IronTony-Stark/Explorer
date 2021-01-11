#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>

class FileSystem {
public:
    FileSystem() = default;

    QJsonDocument getRootFiles();
    QJsonDocument getFilesByPath(const QString& path);

    QJsonDocument getRootDirs();
    QJsonDocument getDirsByPath(const QString& path);

private:
    static QJsonDocument filesToJsonDoc(const QString& path, const QJsonArray& files);
    static QJsonArray getFileInfoJsonArray(const QList<QFileInfo>& files);

    static QJsonDocument dirsToJsonDoc(const QJsonArray& dirs);
    static QJsonArray getDirInfoJsonArray(const QList<QFileInfo>& files);

    static QDir getDir(const QString& path);
};

#endif // FILESYSTEM_H
