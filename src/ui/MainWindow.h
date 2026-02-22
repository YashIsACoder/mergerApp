#pragma once

class QListWidget;
class QPushButton;
class QProgressBar;
class QLabel;
class MergeService;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

private slots:
  void addFiles();
  void removeSelected();
  void chooseOutput();
  void merge();
  void mergeFinished(bool accepted, const QString &msg);

private:
  QStringList currentFiles() const;
  void setupUI();

  QListWidget *fileList;
  QPushButton *mergeBtn;
  QProgressBar *progress;
  QLabel *status;

  QString outputPath;
  MergeService *service;
};


