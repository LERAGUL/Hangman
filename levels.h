#ifndef LEVELS_H
#define LEVELS_H

#include <QWidget>
#include "kind.h"

namespace Ui
{
    class LevelWindow;
}

class LevelWindow : public QWidget
{
    Q_OBJECT

public:
    LevelWindow(QWidget *parent = 0);
    ~LevelWindow();

signals:
    void previousWindow();
    void levelSignal(int l);
    void toMainWindow(GameWindow *saved);

private slots:
    void on_pushButton_easy_clicked();
    void on_pushButton_middle_clicked();
    void on_pushButton_hard_clicked();
    void on_pushButton_back_clicked();

private:
    Ui::LevelWindow *ui;
    KindWindow *kindWindow;
    void back(GameWindow *saved);
};

#endif // LEVELS_H
