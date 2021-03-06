#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QMessageBox>
#include <QTextStream>
#include <QShowEvent>
#include <QWidget>
#include <QGraphicsScene>
#include <QFile>

#include <circle.h>


namespace Ui {
    class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

signals:
    void previousWindow();
    void signalFromButton(QString letter);
    void toMainWindow();

public slots:
    void setFileName(int l, int k);

private slots:
    void showEvent(QShowEvent *);
    void on_pushButton_back_clicked();       // Слот-обработчик нажатия кнопки
    void on_pushButtonRestart_clicked();    // Слот-обработчик нажатия кнопки
    void slotLetter(QString letter);

    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_22_clicked();
    void on_pushButton_23_clicked();
    void on_pushButton_24_clicked();
    void on_pushButton_25_clicked();
    void on_pushButton_26_clicked();
    void on_pushButton_27_clicked();
    void on_pushButton_28_clicked();
    void on_pushButton_29_clicked();
    void on_pushButton_30_clicked();
    void on_pushButton_31_clicked();
    void on_pushButton_32_clicked();

private:
    Ui::GameWindow *ui;
    QString word, unknown_word = "";
    QFile file;
    QString filename;
    int lives;
    int current_size;
    QString savedLabel;
    QString savedWord;
    int savedLives;
    int savedCurrentSize;
    QGraphicsScene  *scene;     // Объявляю графическую сцену
    Circle        *circle;      // и круг

    void enableKeyBoard();
    void initGrafScene();       // инициализация графической сцены
    void paint(int Lives);      // отрисовка виселицы
    void cleanStored();
    void saveStored();
};

#endif // GAME_H
