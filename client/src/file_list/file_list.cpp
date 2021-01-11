//
// Created by Iron Tony on 22/12/2020.
//

#include "include/file_list/file_list.h"

FileList::FileList(TcpClient& tcpClient, QObject* parent)
        : QObject(parent), mTcpClient(tcpClient) {
    mFileListModelProxy.setSourceModel(&mFileListModel);

    connect(&mTcpClient, &TcpClient::filesReceived, this, &FileList::onFilesReceived);

    mTcpClient.getRootFiles();
}

void FileList::addDestination(const QString& destination) {
    mDestinations.push(destination);
}

void FileList::btnHomeClicked() {
    mTcpClient.getRootFiles();
}

void FileList::btnBackClicked() {
    if (mDestinations.empty())
        return;

    QString previous = mDestinations.top();
    mDestinations.pop();
    if (previous.isEmpty())
        mTcpClient.getRootFiles();
    else
        mTcpClient.getFilesByPath(previous);
}

void FileList::changeDirectoryClicked(const QString& directory) {
    QString path = mCurrentPath;
    if (!path.isEmpty() && path[path.size() - 1] != '/')
        path += '/';
    path += directory;

    mTcpClient.getFilesByPath(path);
}

void FileList::setShowHidden(bool value) {
    mFileListModelProxy.setShowHidden(value);
}

void FileList::onFilesReceived(const QString& path, const QVector<File>& files) {
    mCurrentPath = path;
    emit currentPathChanged();

    mFileListModel.setData(files);
    mFileListModelProxy.invalidate();
}
