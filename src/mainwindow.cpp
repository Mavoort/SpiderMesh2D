#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_Application_triggered()
{
	QMessageBox::about(
	    this, "About SpiderMesh2D",
	    "This is a 2D Delaunay mesh generator written in C++. "
	    "<br/>"
	    "For more information, see the <a href=\"https://github.com/Mavoort/SpiderMesh2D\">GitHub repo</a> of this "
	    "project.");
}

void MainWindow::on_actionAbout_Qt6_triggered()
{
	qDebug() << "aboutQt Action triggered.";
	QApplication::aboutQt();
}
