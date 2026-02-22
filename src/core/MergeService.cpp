#include "MergeService.h"
#include <QProcess>

MergeService::MergeService(QObject *parent) 
  : QObject(parent)
{}
 
MergeService::merge(const QStringList &inputs,
                    const QString &output)
{
  if (process) return;
  
  process = new QProcess(this);

  QStringList args;
  args << "--empty" << "--pages";

  for (const auto &f : inputs)
    args << f << "1-z";

  connect(process, &QProcess::finished,
          this, [this, output](int exitCode)
          {
            bool done = (exitCode == 0);
            emit finished(done,
                          done ? "Merged successfully:\n" + output 
                               : "QPDF merge failed."
                          );
            
            process->deleteLater();
            process = nullptr;
          });

  process->start("qpdf", args);
}
