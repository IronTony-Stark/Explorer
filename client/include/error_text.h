//
// Created by Iron Tony on 22/12/2020.
//

#ifndef EXPLORERCLIENT_ERROR_TEXT_H
#define EXPLORERCLIENT_ERROR_TEXT_H

#include <QObject>

class ErrorText : public QObject {
Q_OBJECT

    Q_PROPERTY(QString error READ getError NOTIFY errorChanged)

public:
    QString getError() const {
        return mError;
    }

    void setError(const QString& error);

signals:
    void errorChanged();

private:
    QString mError;
};

#endif //EXPLORERCLIENT_ERROR_TEXT_H
