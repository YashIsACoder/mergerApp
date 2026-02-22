#include <QApplication>
#include "ui/MainWindow.h"

int main(int argc, char*argv[])
{
  QApplication app(argc, argv);
  MainWindow w;
  w.resize(500, 400);
  w.show();
  return app.exec();
}
