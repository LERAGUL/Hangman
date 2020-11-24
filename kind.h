#ifndef KIND_H
#define KIND_H

#include <QWidget>
#include "game.h"

namespace Ui
{
    class KindWindow;
}

class KindWindow : public QWidget
{
    Q_OBJECT

public:
    KindWindow(QWidget *parent = 0);
    ~KindWindow();

signals:
    void previousWindow();
    void fileSignal(int l, int k);
    void toMainWindow(GameWindow *saved);

private slots:
    void on_pushButton_kind1_clicked();
    void on_pushButton_kind2_clicked();
    void on_pushButton_kind3_clicked();
    void on_pushButton_back_clicked();

public slots:
    void setLevel(int l);

private:
    Ui::KindWindow *ui;
    GameWindow *gameWindow;
    int level;
    void back();
};


#endif // KIND_H
