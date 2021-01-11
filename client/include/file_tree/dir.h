//
// Created by Iron Tony on 24/12/2020.
//

#ifndef EXPLORERCLIENT_DIR_H
#define EXPLORERCLIENT_DIR_H

#include <QString>
#include <QJsonObject>
#include <QDebug>

class Dir {
public:
    Dir() = default;
    Dir(QString name, QString absolutePath, bool hasChildrenDirs);
    Dir(const Dir&) = default;
    Dir(Dir&&) = default;
    Dir& operator=(const Dir& file) = default;
    Dir& operator=(Dir&& file) = default;

    const QString& getName() const;
    const QString& getAbsolutePath() const;
    bool hasChildrenDirs() const;

    static Dir fromJson(const QJsonObject&);

private:
    QString mName;
    QString mAbsolutePath;
    bool mHasChildrenDirs;
};

#endif //EXPLORERCLIENT_DIR_H
