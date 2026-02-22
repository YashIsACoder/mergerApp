#include "MainWindow.h"
#include "core/MergeService.h"

#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QProgressBar>
#include <QLabel>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), 
      service(new MergeService(this))
{
  setupUI();
  connect(service, &MergeService::finished, 
          this, &MainWindow::mergeFinished);
}

void MainWindow::setupUI()
{
  auto *central = new QWidget(this);
  auto *layout = new QVBoxLayout(central);

  fileList = new QListWidget;
  fileList->setSelectionMode(QAbstractItemView::ExtendedSelection);
  layout->addWidget(fileList);

  auto *btnRow = new QHBoxLayout;

  auto *addBtn = new QPushButton("Add");
  auto *rmvBtn = new QPushButton("Remove");
  mergeBtn = new QPushButton("Merge");

  // buttons 
  btnRow->addWidget(addBtn);
  btnRow->addWidget(rmvBtn);
  btnRow->addStretch();
  btnRow->addWidget(mergeBtn);

  layout->addLayout(btnRow);

  // prog bar
  progress = new QProgressBar;
  progress->setVisible(false);
  layout->addWidget(progress);

  // status 
  status = new QLabel;
  layout->addWidget(status);

  setCentralWidget(central);

  connect(addBtn, &QPushButton::clicked, this, &MainWindow::addFiles);
  connect(rmvBtn, &QPushButton::clicked, this, &MainWindow::removeSelected);
  connect(mergeBtn, &QPushButton::clicked, this, &MainWindow::merge);
}

void MainWindow::addFiles()
{
  auto files = QFileDialog::getOpenFileNames(this, "Select PDFs", 
                                             {}, "PDF Files (*.pdf)");
  for (const auto &f : files) fileList->addItem(f);
}

void MainWindow::removeSelected()
{
  auto items = fileList->selectedItems();
  for (auto *item : items) {
    delete fileList->takeItem(fileList->row(item));
  }
}

QStringList MainWindow::currentFiles() const
{
  QStringList files;
  for (int i{}; i < fileList->count(); ++i)
    files << fileList->item(i)->text();
  return files;
}

void MainWindow::chooseOutput()
{
  outputPath = QFileDialog::getSaveFileName(this, "Output File", 
                                            {}, "PDF Files (*.pdf)");
}

void MainWindow::merge()
{
  if (fileList->count() == 0)
  {
    QMessageBox::warning(this, "Error", "Add PDFs first.");
    return;
  }

  chooseOutput();
  if (outputPath.isEmpty()) return;

  progress->setRange(0,0);
  progress->setFormat("Merging..");
  progress->setTextVisible(true);

  service->merge(currentFiles(), outputPath);
}

void MainWindow::mergeFinished(bool done, const QString &msg)
{
  progress->setVisible(false);
  status->setText(done ? "Done" : "Failed");

  QMessageBox::information(
    this,
    done ? "Success" : "Error", 
    msg
  );
}


