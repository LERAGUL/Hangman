#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <levels.h>
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
    void on_pushButtonContinue_clicked();
    void showUp(GameWindow *saved);

private:
    Ui::MainWindow *ui;
    LevelWindow *levelWindow;
    GameWindow *savedGame;
    QString savedLabel;
    QString savedWord;
    int savedLives;
    int savedCurrentSize;
    void updateFile();
    void setFile();
};

#endif // MAINWINDOW_H
