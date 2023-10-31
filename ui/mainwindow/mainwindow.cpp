#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

using std::cout, std::endl;

void MainWindow::CanTX() {
	cout << "Hello World!" << endl;
}

void MainWindow::CanRX() {
	cout << "Hello World!" << endl;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	connect(canTXTimer, &QTimer::timeout, this, &MainWindow::CanTX);
	connect(canRXTimer, &QTimer::timeout, this, &MainWindow::CanRX);
	canTXTimer->start(10);
	canRXTimer->start(10);

	ui->setupUi(this);
}

MainWindow::~MainWindow() {
	delete ui;
}

