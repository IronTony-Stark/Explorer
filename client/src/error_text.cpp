//
// Created by Iron Tony on 22/12/2020.
//

#include <QDebug>
#include "error_text.h"

void ErrorText::setError(const QString& error) {
    qWarning() << "Error:" << error;
    mError = error;
    emit errorChanged();
}
