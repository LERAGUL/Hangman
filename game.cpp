#include "game.h"
#include "ui_game.h"
#include <QFile>
#include <QTextStream>
#include <QDir>

QString word, unknown_word = "";
QTextStream out(stdout);
int lives;
int current_size;

void AnotherWindow::slotLetter(QString letter)
{
    bool find = false;
    QByteArray ba = word.toLocal8Bit();
    const char *w = ba.data();
    QString word = QString::fromUtf8(w);
    for (int i = 0; i < word.size(); ++i) {
        if (letter == word.at(i))
        {
           unknown_word.replace(i*2, 2, letter + " ");
           current_size++;
           find = true;
        }
    }
    if (find) {
        ui->labelWord->setText(unknown_word);
    }
    else
    {
        lives--;
        ui->labelMes->setText("Буквы " + letter + " нет в этом слове");
        ui->labelLives-> setText("У вас осталось " + QString::number(lives) + " жизней.");
    }
    if (lives == 0)
    {
        QMessageBox::information(this, "Вы проиграли", "У вас не осталось жизней");
        this->close();
        this->show();
    }
    if (current_size == word.size()){
        QMessageBox::information(this, "Вы выиграли", "Поздравляем!");
        this->close();
        this->show();
    }

}

void AnotherWindow::showEvent(QShowEvent *)
{
    enableKeyBoard();
    // Создаём объекn
    ui->label->setText(QDir::currentPath());
    out << "Current path:" << QDir::currentPath() << endl;
    QFile file(QDir::currentPath() + "/dictionary.txt");
    lives = 9;
    current_size = 0;
    // С помощью метода open() открываем файл в режиме чтения
    if (!file.open(QIODevice::ReadOnly)) {
      qWarning("Cannot open file for reading"); // если файл не найден, то выводим предупреждение и завершаем выполнение программы
    }
    // Создаём входящий поток, из которого будут считываться данные, и связываем его с нашим файлом
    QTextStream in(&file);
    int n = rand() % 19 +1;
    out << n << endl;
    int i = 1;
    // Считываем файл строка за строкой
    while (!in.atEnd()) { // метод atEnd() возвращает true, если в потоке больше нет данных для чтения
      QString line = in.readLine();// метод readLine() считывает одну строку из потока
      if (i == n)
      {
          word = line;
      }
      i++;
    }
    QByteArray ba = word.toLocal8Bit();
    const char *c_str2 = ba.data();
    out << QString::fromUtf8(c_str2) << endl;
    out << word.size()/2 << endl;
    unknown_word = "";
    for (i = 0; i < word.size()/2; i++){
        unknown_word.append("_ ");
    }
    ui->labelLives->setText("У вас " + QString::number(lives) + " жизней");
    ui->labelWord->setText(unknown_word);
    // Закрываем файл
    file.close();
}

void AnotherWindow::on_pushButtonMenu_clicked()
{
    this->close();      // Закрываем окно
    emit firstWindow(); // И вызываем сигнал на открытие главного окна
}

void AnotherWindow::on_pushButtonRestart_clicked(){
    this->close();
    this->show();
}

void AnotherWindow::enableKeyBoard(){
    ui->pushButton_1->setEnabled(1);
    ui->pushButton_2->setEnabled(1);
    ui->pushButton_3->setEnabled(1);
    ui->pushButton_4->setEnabled(1);
    ui->pushButton_5->setEnabled(1);
    ui->pushButton_6->setEnabled(1);
    ui->pushButton_7->setEnabled(1);
    ui->pushButton_8->setEnabled(1);
    ui->pushButton_9->setEnabled(1);
    ui->pushButton_10->setEnabled(1);
    ui->pushButton_11->setEnabled(1);
    ui->pushButton_12->setEnabled(1);
    ui->pushButton_13->setEnabled(1);
    ui->pushButton_14->setEnabled(1);
    ui->pushButton_15->setEnabled(1);
    ui->pushButton_16->setEnabled(1);
    ui->pushButton_17->setEnabled(1);
    ui->pushButton_18->setEnabled(1);
    ui->pushButton_19->setEnabled(1);
    ui->pushButton_20->setEnabled(1);
    ui->pushButton_21->setEnabled(1);
    ui->pushButton_22->setEnabled(1);
    ui->pushButton_23->setEnabled(1);
    ui->pushButton_24->setEnabled(1);
    ui->pushButton_25->setEnabled(1);
    ui->pushButton_26->setEnabled(1);
    ui->pushButton_27->setEnabled(1);
    ui->pushButton_28->setEnabled(1);
    ui->pushButton_29->setEnabled(1);
    ui->pushButton_30->setEnabled(1);
    ui->pushButton_31->setEnabled(1);
    ui->pushButton_32->setEnabled(1);
}

AnotherWindow::AnotherWindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::AnotherWindow)
{
    ui->setupUi(this);
    connect(this, &AnotherWindow::signalFromButton, this, &AnotherWindow::slotLetter);
}

void AnotherWindow::on_pushButton_1_clicked()
{
    ui->pushButton_1->setEnabled(0);
    emit signalFromButton("й");
}

void AnotherWindow::on_pushButton_2_clicked()
{
    ui->pushButton_2->setEnabled(0);
    emit signalFromButton("ц");
}

void AnotherWindow::on_pushButton_3_clicked()
{
    ui->pushButton_3->setEnabled(0);
    emit signalFromButton("у");
}

void AnotherWindow::on_pushButton_4_clicked()
{
    ui->pushButton_4->setEnabled(0);
    emit signalFromButton("к");
}

void AnotherWindow::on_pushButton_5_clicked()
{
    ui->pushButton_5->setEnabled(0);
    emit signalFromButton("е");
}

void AnotherWindow::on_pushButton_6_clicked()
{
    ui->pushButton_6->setEnabled(0);
    emit signalFromButton("н");
}

void AnotherWindow::on_pushButton_7_clicked()
{
    ui->pushButton_7->setEnabled(0);
    emit signalFromButton("г");
}

void AnotherWindow::on_pushButton_8_clicked()
{
    ui->pushButton_8->setEnabled(0);
    emit signalFromButton("ш");
}

void AnotherWindow::on_pushButton_9_clicked()
{
    ui->pushButton_9->setEnabled(0);
    emit signalFromButton("щ");
}

void AnotherWindow::on_pushButton_10_clicked()
{
    ui->pushButton_10->setEnabled(0);
    emit signalFromButton("з");
}

void AnotherWindow::on_pushButton_11_clicked()
{
    ui->pushButton_11->setEnabled(0);
    emit signalFromButton("х");
}

void AnotherWindow::on_pushButton_12_clicked()
{
    ui->pushButton_12->setEnabled(0);
    emit signalFromButton("ъ");
}

void AnotherWindow::on_pushButton_13_clicked()
{
    ui->pushButton_13->setEnabled(0);
    emit signalFromButton("ф");
}

void AnotherWindow::on_pushButton_14_clicked()
{
    ui->pushButton_14->setEnabled(0);
    emit signalFromButton("ы");
}

void AnotherWindow::on_pushButton_15_clicked()
{
    ui->pushButton_15->setEnabled(0);
    emit signalFromButton("в");
}

void AnotherWindow::on_pushButton_16_clicked()
{
    ui->pushButton_16->setEnabled(0);
    emit signalFromButton("а");
}

void AnotherWindow::on_pushButton_17_clicked()
{
    ui->pushButton_17->setEnabled(0);
    emit signalFromButton("п");
}

void AnotherWindow::on_pushButton_18_clicked()
{
    ui->pushButton_18->setEnabled(0);
    emit signalFromButton("р");
}

void AnotherWindow::on_pushButton_19_clicked()
{
    ui->pushButton_19->setEnabled(0);
    emit signalFromButton("о");
}

void AnotherWindow::on_pushButton_20_clicked()
{
    ui->pushButton_20->setEnabled(0);
    emit signalFromButton("л");
}

void AnotherWindow::on_pushButton_21_clicked()
{
    ui->pushButton_21->setEnabled(0);
    emit signalFromButton("д");
}

void AnotherWindow::on_pushButton_22_clicked()
{
    ui->pushButton_22->setEnabled(0);
    emit signalFromButton("ж");
}

void AnotherWindow::on_pushButton_23_clicked()
{
    ui->pushButton_23->setEnabled(0);
    emit signalFromButton("э");
}

void AnotherWindow::on_pushButton_24_clicked()
{
    ui->pushButton_24->setEnabled(0);
    emit signalFromButton("я");
}

void AnotherWindow::on_pushButton_25_clicked()
{
    ui->pushButton_25->setEnabled(0);
    emit signalFromButton("ч");
}

void AnotherWindow::on_pushButton_26_clicked()
{
    ui->pushButton_26->setEnabled(0);
    emit signalFromButton("с");
}

void AnotherWindow::on_pushButton_27_clicked()
{
    ui->pushButton_27->setEnabled(0);
    emit signalFromButton("м");
}

void AnotherWindow::on_pushButton_28_clicked()
{
    ui->pushButton_28->setEnabled(0);
    emit signalFromButton("и");
}

void AnotherWindow::on_pushButton_29_clicked()
{
    ui->pushButton_29->setEnabled(0);
    emit signalFromButton("т");
}

void AnotherWindow::on_pushButton_30_clicked()
{
    ui->pushButton_30->setEnabled(0);
    emit signalFromButton("ь");
}

void AnotherWindow::on_pushButton_31_clicked()
{
    ui->pushButton_31->setEnabled(0);
    emit signalFromButton("б");
}

void AnotherWindow::on_pushButton_32_clicked()
{
    ui->pushButton_32->setEnabled(0);
    emit signalFromButton("ю");
}

AnotherWindow::~AnotherWindow()
{
    delete ui;
}
