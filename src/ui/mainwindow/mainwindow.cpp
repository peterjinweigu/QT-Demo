#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

using std::cout, std::endl;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
}

MainWindow::~MainWindow() = default;

