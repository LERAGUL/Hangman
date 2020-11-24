#include "levels.h"
#include "ui_levels.h"
#include <QFile>
#include <QTextStream>
#include "game.h"

LevelWindow::LevelWindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::LevelWindow)
{
    ui->setupUi(this);
    kindWindow = new KindWindow(); // Инициализирую третье окно
    connect(kindWindow, &KindWindow::toMainWindow, this, &LevelWindow::back);
    connect(kindWindow, &KindWindow::previousWindow, this, &LevelWindow::show);
    connect(this, &LevelWindow::levelSignal, kindWindow, &KindWindow::setLevel);
}

void LevelWindow::on_pushButton_back_clicked()
{
    this->close();          // закрываем окно
    emit previousWindow();  // вызываем сигнал на открытие главного окна
}

void LevelWindow::back(GameWindow *saved)
{
    this->close();          // закрываем окно
    emit toMainWindow(saved);  // вызываем сигнал на открытие главного окна
}

void LevelWindow::on_pushButton_easy_clicked()
{
    kindWindow->show();
    this->close();
    emit levelSignal(1);
}

void LevelWindow::on_pushButton_middle_clicked()
{
    kindWindow->show();
    this->close();
    emit levelSignal(2);
}

void LevelWindow::on_pushButton_hard_clicked()
{
    kindWindow->show();
    this->close();
    emit levelSignal(3);
}

LevelWindow::~LevelWindow()
{
    delete ui;
}


