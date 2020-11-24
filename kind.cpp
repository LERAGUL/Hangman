#include "kind.h"
#include "ui_kind.h"
#include <QFile>
#include <QTextStream>
#include "game.h"

KindWindow::KindWindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::KindWindow)
{
    ui->setupUi(this);
    gameWindow = new GameWindow(); // Инициализирую четвёртое окно
    connect(gameWindow, &GameWindow::toMainWindow, this, &KindWindow::back);
    connect(this, &KindWindow::fileSignal, gameWindow, &GameWindow::setFileName);
}

void KindWindow::on_pushButton_back_clicked()
{
    this->close();      // закрываем окно
    emit previousWindow(); // вызываем сигнал на открытие предыдущего окна
}

void KindWindow::back()
{
    this->close();
    emit toMainWindow(gameWindow);
}

void KindWindow::on_pushButton_kind1_clicked()
{
    emit fileSignal(level, 1);
    gameWindow->show();
    this->close();
}

void KindWindow::on_pushButton_kind2_clicked()
{
    emit fileSignal(level, 2);
    gameWindow->show();
    this->close();
}

void KindWindow::on_pushButton_kind3_clicked()
{
    emit fileSignal(level, 3);
    gameWindow->show();
    this->close();
}

void KindWindow::setLevel(int l)
{
    switch(l){
    case 1:
        ui->label->setText("Уровень сложности: лёгкий");
        break;
    case 2:
        ui->label->setText("Уровень сложности: средний");
        break;
    case 3:
        ui->label->setText("Уровень сложности: сложный");
        break;
    }
    level = l;
}

KindWindow::~KindWindow()
{
    delete ui;
}
