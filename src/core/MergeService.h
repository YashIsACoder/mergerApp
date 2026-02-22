#pragma once

#include <QObject>
#include <QStringList>

class QProcess;

class MergeService : public QObject
{
  Q_OBJECT

public:
  explicit MergeService(QObject *parent = nullptr);
  void merge(const QStringList &inputs, const QString &output);

signals:
  void finished(bool done, const QString &msg);

private:
  QProcess *process = nullptr;
};
