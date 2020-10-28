#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Инициализируем второе окно
    gameWindow = new AnotherWindow();
    // подключаем к слоту запуска главного окна по кнопке во втором окне
    connect(gameWindow, &AnotherWindow::firstWindow, this, &MainWindow::show);
}

void MainWindow::on_pushButtonStart_clicked()
{
    gameWindow->show();  // Показываем второе окно
    this->close();    // Закрываем основное окно
}

MainWindow::~MainWindow()
{
    delete ui;
}


