#include <armadillo>

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

	// Armadillo Example
	auto armaMatrix = arma::mat{{3.14159, 3.7}, {-0.5, 2.71828}};
    auto armaVector = arma::vec{1.0, 2.0};

    return app.exec();
}
