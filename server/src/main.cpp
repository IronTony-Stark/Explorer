#include <QCoreApplication>
#include <QtDebug>
#include <QFile>
#include <QDateTime>

#include "http_server.h"

static const char* const kLogFilePath = "log.txt";

QScopedPointer<QFile> mLogFile;

void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QTextStream out(mLogFile.data());
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    switch (type) {
        case QtInfoMsg:     out << " INF "; break;
        case QtDebugMsg:    out << " DBG "; break;
        case QtWarningMsg:  out << " WRN "; break;
        case QtCriticalMsg: out << " CRT "; break;
        case QtFatalMsg:    out << " FTL "; break;
    }
    out << context.category << " - " << msg << "\n";
    out.flush();
}

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    mLogFile.reset(new QFile(kLogFilePath));
    mLogFile.data()->open(QFile::WriteOnly | QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);

    HttpServer server(8090); // do not change port number
    qInfo() << "Server is running";

    return QCoreApplication::exec();
}
