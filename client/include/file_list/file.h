//
// Created by Iron Tony on 19/12/2020.
//

#ifndef EXPLORERSERVER_FILE_H
#define EXPLORERSERVER_FILE_H

#include <QString>
#include <QJsonObject>

class File {
public:
    File() = default;
    File(QString name, bool isDirectory, bool isHidden, bool isReadable);
    File(const File&) = default;
    File(File&&) = default;
    File& operator=(const File& file) = default;
    File& operator=(File&& file) = default;

    const QString& getName() const;
    bool isDirectory() const;
    bool isHidden() const;
    bool isReadable() const;

    static File fromJson(const QJsonObject&);

private:
    QString mName;
    bool mIsDirectory{};
    bool mIsHidden{};
    bool mIsReadable{};
};

#endif //EXPLORERSERVER_FILE_H
