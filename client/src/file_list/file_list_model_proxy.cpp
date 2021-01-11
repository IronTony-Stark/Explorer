//
// Created by Iron Tony on 20/12/2020.
//

#include "file_list/file_list_model_proxy.h"
#include "file_list/file_list_model.h"

FileListModelProxy::FileListModelProxy(QObject* parent)
        : QSortFilterProxyModel(parent), mShowHidden(false) {}

void FileListModelProxy::setShowHidden(bool showHidden) {
    mShowHidden = showHidden;
    invalidateFilter();
}

bool FileListModelProxy::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const {
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    bool isHidden = sourceModel()->data(index, FileListModel::IsHiddenRole).toBool();
    return !isHidden || mShowHidden;
}
void FileListModelProxy::invalidate() {
    invalidateFilter();
}
