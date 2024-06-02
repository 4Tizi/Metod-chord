#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    label(new QLabel("Auth+", this))
{
    setCentralWidget(label);
    setWindowTitle("Main Application");
}

MainWindow::~MainWindow()
{
    delete label;
}
