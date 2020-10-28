#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <game.h>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void Update();

private slots:
    void on_pushButtonStart_clicked();

private:
    Ui::MainWindow *ui;
    AnotherWindow *gameWindow;
};

#endif // MAINWINDOW_H
