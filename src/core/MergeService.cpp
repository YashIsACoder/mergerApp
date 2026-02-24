#include "MergeService.h"

#include <QProcess>
#include <QDebug>
#include <QFileInfo>

MergeService::MergeService(QObject *parent)
    : QObject(parent)
{
}

MergeService::~MergeService()
{
    if (process) {
        process->kill();
        process->waitForFinished(200);
        delete process;
        process = nullptr;
    }
}

void MergeService::startMerge(const QStringList &inputFiles,
                              const QString &outputFile)
{
    if (process) {
        emit mergeFinished(false, "Merge already in progress.");
        return;
    }

    if (inputFiles.isEmpty()) {
        emit mergeFinished(false, "No input files provided.");
        return;
    }

    if (outputFile.trimmed().isEmpty()) {
        emit mergeFinished(false, "No output file provided.");
        return;
    }

    QStringList args;
    args << "--empty" << "--pages";

    for (const QString &file : inputFiles) {
        args << file << "1-z";
    }

    args << "--" << outputFile;

    process = new QProcess(this);
    pendingOutput = outputFile;

    connect(process,
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this,
            &MergeService::onFinished);

    connect(process,
            &QProcess::errorOccurred,
            this,
            &MergeService::onErrorOccurred);

    process->start("qpdf", args);

    if (!process->waitForStarted(2000)) {
        process->deleteLater();
        process = nullptr;
        emit mergeFinished(false,
            "Failed to start qpdf. Is it installed and in PATH?");
    }
}

void MergeService::onFinished(int exitCode,
                              QProcess::ExitStatus status)
{
    Q_UNUSED(status);

    QString errorOutput;

    if (process) {
        errorOutput =
            QString::fromLocal8Bit(process->readAllStandardError());
        process->deleteLater();
        process = nullptr;
    }

    if (exitCode == 0) {
        emit mergeFinished(true,
            QString("Merged successfully to: %1")
                .arg(pendingOutput));
    } else {
        if (errorOutput.isEmpty())
            errorOutput =
                QString("qpdf failed (exit code %1)")
                    .arg(exitCode);

        emit mergeFinished(false, errorOutput);
    }
}

void MergeService::onErrorOccurred(QProcess::ProcessError error)
{
    QString message;

    switch (error) {
    case QProcess::FailedToStart:
        message = "Failed to start qpdf (not installed or not in PATH).";
        break;
    case QProcess::Crashed:
        message = "qpdf crashed during merge.";
        break;
    default:
        message = "Unknown error occurred while running qpdf.";
        break;
    }

    if (process) {
        process->kill();
        process->deleteLater();
        process = nullptr;
    }

    emit mergeFinished(false, message);
}
