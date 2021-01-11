//
// Created by Iron Tony on 20/12/2020.
//

#ifndef EXPLORERSERVER_FILE_MODEL_PROXY_H
#define EXPLORERSERVER_FILE_MODEL_PROXY_H

#include <QSortFilterProxyModel>
#include "file.h"

class FileListModelProxy : public QSortFilterProxyModel {
Q_OBJECT

public:
    explicit FileListModelProxy(QObject* parent = nullptr);

    void setShowHidden(bool);

    void invalidate();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

private:
    bool mShowHidden;
};

#endif //EXPLORERSERVER_FILE_MODEL_PROXY_H
