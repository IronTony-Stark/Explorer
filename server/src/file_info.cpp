#include "file_info.h"

extern Q_CORE_EXPORT int qt_ntfs_permission_lookup;

FileInfo::FileInfo(const QFileInfo& fileInfo)
        : mName(fileInfo.fileName().isEmpty() ? fileInfo.path() : fileInfo.fileName()),
          mType(fileInfo.isDir() ? DIRECTORY : FS_FILE),
          mIsHidden(fileInfo.isHidden()) {
#if defined(WIN32) || defined(_WIN32)
    ++qt_ntfs_permission_lookup;
    mIsReadable = fileInfo.isReadable();
    --qt_ntfs_permission_lookup;
#else
    mIsReadable = fileInfo.isReadable();
#endif
}

QJsonObject FileInfo::toJson() {
    QJsonObject result;

    result.insert("name", mName);
    result.insert("type", mType);
    result.insert("isHidden", mIsHidden);
    result.insert("isReadable", mIsReadable);

    return result;
}
