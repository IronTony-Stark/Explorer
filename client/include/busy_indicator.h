//
// Created by Iron Tony on 22/12/2020.
//

#ifndef EXPLORERCLIENT_BUSY_INDICATOR_H
#define EXPLORERCLIENT_BUSY_INDICATOR_H

#include <QObject>

class BusyIndicator : public QObject {
Q_OBJECT

    Q_PROPERTY(bool running READ isRunning NOTIFY runningChanged)

public:
    bool isRunning() const {
        return mRunning;
    }

    void run() {
        ++mCount;
        if (!mRunning) {
            mRunning = true;
            emit runningChanged();
        }
    }

    void stop() {
        --mCount;
        if (mRunning && mCount <= 0) {
            mRunning = false;
            emit runningChanged();
        }
    }

signals:
    void runningChanged();

private:
    bool mRunning = false;
    int mCount;
};

#endif //EXPLORERCLIENT_BUSY_INDICATOR_H
