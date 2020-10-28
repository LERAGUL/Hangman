#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
    class AnotherWindow;
}

class AnotherWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AnotherWindow(QWidget *parent = 0);
    ~AnotherWindow();

signals:
    void firstWindow();
    void signalFromButton(QString letter);// Сигнал для первого окна на открытие

private slots:
    // Слот-обработчик нажатия кнопки
    void on_pushButtonMenu_clicked();
    void on_pushButtonRestart_clicked();
    void showEvent(QShowEvent *);
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
    Ui::AnotherWindow *ui;
    void enableKeyBoard();

};

#endif // GAME_H
