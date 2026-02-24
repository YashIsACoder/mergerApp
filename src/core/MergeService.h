#pragma once

#include <QObject>
#include <QStringList>
#include <QProcess>

class QProcess;

class MergeService : public QObject
{
    Q_OBJECT

public:
    explicit MergeService(QObject *parent = nullptr);
    ~MergeService();

    void startMerge(const QStringList &inputFiles,
                    const QString &outputFile);

signals:
    void mergeFinished(bool ok, const QString &message);

private slots:
    void onFinished(int exitCode, QProcess::ExitStatus status);
    void onErrorOccurred(QProcess::ProcessError error);

private:
    QProcess *process = nullptr;
    QString pendingOutput;
};

