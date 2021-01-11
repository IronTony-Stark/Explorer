#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDateTime>
#include <QFile>

#include "tcp_client.h"
#include "busy_indicator.h"
#include "file_list/file_list.h"
#include "file_tree/file_tree_model.h"

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

int main(int argc, char** argv) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QGuiApplication::setOrganizationName("IronTony");
    QGuiApplication::setOrganizationDomain("github.com/IronTony-Stark");

    mLogFile.reset(new QFile(kLogFilePath));
    mLogFile.data()->open(QFile::WriteOnly | QFile::Append | QFile::Text);
    qInstallMessageHandler(messageHandler);

    BusyIndicator busyIndicator;
    ErrorText errorText;

    TcpClient fileListTcpClient("localhost", 8090, busyIndicator, errorText);
    TcpClient fileTreeTcpClient("localhost", 8090, busyIndicator, errorText);

    FileList fileList(fileListTcpClient);
    FileTreeModel fileTreeModel(fileTreeTcpClient, fileList);

    QQmlApplicationEngine engine;
    engine.addImportPath(":/qml");

    engine.rootContext()->setContextProperty(QStringLiteral("busyIndicator"), &busyIndicator);
    engine.rootContext()->setContextProperty(QStringLiteral("errorText"), &errorText);
    engine.rootContext()->setContextProperty(QStringLiteral("fileList"), &fileList);
    engine.rootContext()->setContextProperty(QStringLiteral("fileListModel"), &fileList.getModel());
    engine.rootContext()->setContextProperty(QStringLiteral("fileTreeModel"), &fileTreeModel);

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject* obj, const QUrl& objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);

    return QGuiApplication::exec();
}