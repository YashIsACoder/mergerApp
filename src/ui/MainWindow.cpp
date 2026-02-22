#include "MainWindow.h"
#include "core/MergeService.h"

#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
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
  auto *rmvBtn = new QPushButton("Remove")
  mergeBtn = new QPushButton("Merge");

  // buttons 
  btnRow->addWidget(addBtn);
  btnRow->addWidget(rmvButton);
  btnRow->addStretch();
  btnRow->addWidget(mergeBtn);

  layout->addLayout(btnRow);

  // prog bar
  progress = new QProgressBar;
  progress->setVisible(false);
  layout->addWdiget(progress);

  // status 
  status = new QLabel;
  layout->addWidget(status);

  setCentralWidget(central);

  connect(addBtn, &QPushButton::clicked, this, &MainWindow::addFiles);
  connect(rmvButton, &QPushButton::clicked, this, &MainWindow::removeSelected);
  connect(mergeBtn, &QPushButton::clicked, this, &MainWindow::merge);
}

void MainWindow::addFiles()
{

}

void MainWindow::removeSelected()
{

}

void MainWindow::currentFiles() const
{

}

void MainWindow::chooseOutput()
{

}

void MainWindow::merge()
{

}

void MainWindow::mergeFinished(bool accepted, const QString &msg)
{
}


