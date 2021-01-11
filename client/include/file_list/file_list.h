//
// Created by Iron Tony on 22/12/2020.
//

#ifndef EXPLORERCLIENT_FILE_LIST_H
#define EXPLORERCLIENT_FILE_LIST_H

#include <QObject>
#include <QVector>
#include <QStack>

#include "tcp_client.h"
#include "file_list_model.h"
#include "file_list_model_proxy.h"
#include "busy_indicator.h"

class FileList : public QObject {
Q_OBJECT

    Q_PROPERTY(QString currentPath READ getCurrentPath NOTIFY currentPathChanged)

public:
    explicit FileList(TcpClient&, QObject* parent = nullptr);

    Q_INVOKABLE void addDestination(const QString&);

    Q_INVOKABLE void btnHomeClicked();
    Q_INVOKABLE void btnBackClicked();
    Q_INVOKABLE void changeDirectoryClicked(const QString& directory);

    Q_INVOKABLE void setShowHidden(bool);

    const QString& getCurrentPath() {
        return mCurrentPath;
    }

    QAbstractItemModel& getModel() {
        return mFileListModelProxy;
    }

signals:
    void currentPathChanged();

public slots:
    void onFilesReceived(const QString&, const QVector<File>&);

private:
    FileListModel mFileListModel;
    FileListModelProxy mFileListModelProxy;

    QString mCurrentPath;
    TcpClient& mTcpClient;
    QStack<QString> mDestinations;
};

#endif //EXPLORERCLIENT_FILE_LIST_H
