#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);

	~MainWindow() override;

	static void CanRX();

	static void CanTX();

private:
	Ui::MainWindow *ui;
	QTimer *canRXTimer = new QTimer(this), *canTXTimer = new QTimer(this);
};

#endif // MAINWINDOW_H
