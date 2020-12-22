#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QSettings>

QSettings set( "settings_demo.conf", QSettings::IniFormat );
QTextStream cout(stdout);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    updateFile();

    ui->setupUi(this);
    levelWindow = new LevelWindow(); // Инициализирую второе окно
    connect(levelWindow, &LevelWindow::previousWindow, this, &MainWindow::show);
    connect(levelWindow, &LevelWindow::toMainWindow, this, &MainWindow::showUp);

    setFile();

    cout << savedLives << endl;

}

void MainWindow::showUp(GameWindow *saved)
{
    this->show();

    setFile();

    cout << savedLives << endl;

    if (savedLives != 9 || savedCurrentSize != 0)
    {
        ui->pushButtonContinue->setEnabled(1);
    }
    else
    {
        ui->pushButtonContinue->setEnabled(0);
    }
    savedGame = saved;
}

void MainWindow::on_pushButtonContinue_clicked()
{
    savedGame->show();   // Показать окно игры
    this->close();       // Закрываем основное
}

void MainWindow::on_pushButtonStart_clicked()
{
    updateFile();

    levelWindow->show();  // Показать второе окно
    this->close();        // Закрываем основное
}

void MainWindow::updateFile()
{
    set.beginGroup( "WidgetContent" );
    set.setValue( "savedLabel", "");
    set.setValue( "savedWord", "");
    set.setValue( "savedLives", 9);
    set.setValue( "savedCurrentSize", 0);
    set.endGroup();
}

void MainWindow::setFile()
{
    set.beginGroup( "WidgetContent" );
    savedLabel = set.value( "savedLabel", "" ).toString();
    savedWord = set.value( "savedWord", "" ).toString();
    savedLives = set.value( "savedLives", 9 ).toInt();
    savedCurrentSize = set.value( "savedCurrentSize", 0 ).toInt();
    set.endGroup();
}

MainWindow::~MainWindow()
{
    delete ui;
}


