#include "game.h"
#include "random.h"
#include "ui_game.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStandardPaths>
#include <QMainWindow>
#include <QSettings>

QTextStream out(stdout);
QSettings settings( "settings_demo.conf", QSettings::IniFormat );

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    connect(this, &GameWindow::signalFromButton, this, &GameWindow::slotLetter);
}

void GameWindow::setFileName(int l, int k)
{
    if (l == 1 && k == 1)
    {
        filename = ":/myfiles/level1_transport.txt";
    }
    if (l == 1 && k == 2)
    {
        filename = ":/myfiles/level1_cooking.txt";
    }
    if (l == 1 && k == 3)
    {
        filename = ":/myfiles/level1_music.txt";
    }
    if (l == 2 && k == 1)
    {
        filename = ":/myfiles/level2_transport.txt";
    }
    if (l == 2 && k == 2)
    {
        filename = ":/myfiles/level2_cooking.txt";
    }
    if (l == 2 && k == 3)
    {
        filename = ":/myfiles/level2_music.txt";
    }
    if (l == 3 && k == 1)
    {
        filename = ":/myfiles/level3_transport.txt";
    }
    if (l == 3 && k == 2)
    {
        filename = ":/myfiles/level3_cooking.txt";
    }
    if (l == 3 && k == 3)
    {
        filename = ":/myfiles/level3_music.txt";
    }
    out << l << endl;
    out << k << endl;
}

void GameWindow::showEvent(QShowEvent *)
{
    settings.beginGroup( "WidgetContent" );
    savedLabel = settings.value( "savedLabel", "" ).toString();
    savedWord = settings.value( "savedWord", "" ).toString();
    savedLives = settings.value( "savedLives", 9 ).toInt();
    savedCurrentSize = settings.value( "savedCurrentSize", 0 ).toInt();
    settings.endGroup();

    if (savedLives != 9 || savedCurrentSize != 0){
        lives = savedLives;
        current_size = savedCurrentSize;
        ui->labelWord->setText(savedLabel);
        ui->labelWord->show();
        word = savedWord;
    }
    else {
        enableKeyBoard();
        initGrafScene();
        QFile file(filename);
        file.open(QFile::ReadOnly);
        lives = 9;
        current_size = 0;
        QTextStream in(&file);      // Входящий поток
        int n = 0;
        for (int i = 0; i < 15; ++i)
        {
            n = Random::get(1, 41);
        }
        int i = 1;
        // Считываю файл строка за строкой
        while (!in.atEnd()) {           // метод atEnd() возвращает true, если в потоке больше нет данных для чтения
          QString line = in.readLine(); // метод readLine() считывает одну строку из потока
          if (i == n)
          {
              word = line;
          }
          i++;
        }
        QByteArray ba = word.toLocal8Bit();
        const char *c_str2 = ba.data();
        out << QString::fromUtf8(c_str2) << endl;
        // out << word.size()/2 << endl;
        unknown_word = "";
        for (i = 0; i < word.size(); i++){
            unknown_word.append("_ ");
        }
        ui->labelWord->setText(unknown_word);
        file.close();
    }
}

void GameWindow::slotLetter(QString letter)
{
    bool find = false; // флаг наличия буквы в слове
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
        paint(lives);
    }
    if (lives == 0)
    {
        QMessageBox::information(this, "Вы проиграли", "У вас не осталось жизней");
        cleanStored();
        this->close();
        this->show();
    }
    if (current_size == word.size()){
        QMessageBox::information(this, "Вы выиграли", "Поздравляем!");
        cleanStored();
        this->close();
        this->show();
    }
    saveStored();
}

void GameWindow::paint(int Lives)
{
    switch(Lives){
    case 8:
        scene->addLine(-125,-250,-125,450,QPen(Qt::black)); // рисую вертикальную линию
        break;
    case 7:
        scene->addLine(-125,-250,125,-250,QPen(Qt::black)); // рисую горизонтальную линию
        break;
    case 6:
        scene->addLine(125,-250,125,-125,QPen(Qt::black));  // рисую вертикальную линию
        break;
    case 5:
        scene->addItem(circle);         // Добавляю на сцену круг
        circle->setPos(62,-125);        // Устанавливаем круг
        break;
    case 4:
        scene->addLine(125,-1,125,250,QPen(Qt::black));      // рисую тело
        break;
    case 3:
        scene->addLine(125,-1,62,125,QPen(Qt::black));      // рисую левую руку
        break;
    case 2:
        scene->addLine(125,-1,188,125,QPen(Qt::black));      // рисую правую руку
        break;
    case 1:
        scene->addLine(125,250,62,374,QPen(Qt::black));      // левая нога
        break;
    case 0:
        scene->addLine(125,250,188,374,QPen(Qt::black));      // правая нога
        break;
    }
}

void GameWindow::initGrafScene()
{
    scene = new QGraphicsScene();   // Инициализирую графическую сцену
    circle = new Circle();          // Инициализирую круг

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключаю скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключаю скроллбар по горизонтали
    scene->setSceneRect(-450,-450,900,900);   // область графической сцены
}

void GameWindow::on_pushButton_back_clicked()
{
    this->close();      // закрываем окно
    emit toMainWindow();// вызываем сигнал на открытие главного окна
}

void GameWindow::on_pushButtonRestart_clicked()
{
    cleanStored();
    this->close();
    this->show();
}
void GameWindow::saveStored()
{
    settings.beginGroup( "WidgetContent" );
    settings.setValue( "savedLabel", ui->labelWord->text());
    settings.setValue( "savedWord", word);
    settings.setValue( "savedLives", lives );
    settings.setValue( "savedCurrentSize", current_size );
    settings.endGroup();
}
void GameWindow::cleanStored()
{
    settings.beginGroup( "WidgetContent" );
    settings.setValue( "savedLabel", "");
    settings.setValue( "savedWord", "");
    settings.setValue( "savedLives", 9);
    settings.setValue( "savedCurrentSize", 0);
    settings.endGroup();
}
void GameWindow::enableKeyBoard()
{
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

void GameWindow::on_pushButton_1_clicked()
{
    ui->pushButton_1->setEnabled(0);
    emit signalFromButton("й");
}

void GameWindow::on_pushButton_2_clicked()
{
    ui->pushButton_2->setEnabled(0);
    emit signalFromButton("ц");
}

void GameWindow::on_pushButton_3_clicked()
{
    ui->pushButton_3->setEnabled(0);
    emit signalFromButton("у");
}

void GameWindow::on_pushButton_4_clicked()
{
    ui->pushButton_4->setEnabled(0);
    emit signalFromButton("к");
}

void GameWindow::on_pushButton_5_clicked()
{
    ui->pushButton_5->setEnabled(0);
    emit signalFromButton("е");
}

void GameWindow::on_pushButton_6_clicked()
{
    ui->pushButton_6->setEnabled(0);
    emit signalFromButton("н");
}

void GameWindow::on_pushButton_7_clicked()
{
    ui->pushButton_7->setEnabled(0);
    emit signalFromButton("г");
}

void GameWindow::on_pushButton_8_clicked()
{
    ui->pushButton_8->setEnabled(0);
    emit signalFromButton("ш");
}

void GameWindow::on_pushButton_9_clicked()
{
    ui->pushButton_9->setEnabled(0);
    emit signalFromButton("щ");
}

void GameWindow::on_pushButton_10_clicked()
{
    ui->pushButton_10->setEnabled(0);
    emit signalFromButton("з");
}

void GameWindow::on_pushButton_11_clicked()
{
    ui->pushButton_11->setEnabled(0);
    emit signalFromButton("х");
}

void GameWindow::on_pushButton_12_clicked()
{
    ui->pushButton_12->setEnabled(0);
    emit signalFromButton("ъ");
}

void GameWindow::on_pushButton_13_clicked()
{
    ui->pushButton_13->setEnabled(0);
    emit signalFromButton("ф");
}

void GameWindow::on_pushButton_14_clicked()
{
    ui->pushButton_14->setEnabled(0);
    emit signalFromButton("ы");
}

void GameWindow::on_pushButton_15_clicked()
{
    ui->pushButton_15->setEnabled(0);
    emit signalFromButton("в");
}

void GameWindow::on_pushButton_16_clicked()
{
    ui->pushButton_16->setEnabled(0);
    emit signalFromButton("а");
}

void GameWindow::on_pushButton_17_clicked()
{
    ui->pushButton_17->setEnabled(0);
    emit signalFromButton("п");
}

void GameWindow::on_pushButton_18_clicked()
{
    ui->pushButton_18->setEnabled(0);
    emit signalFromButton("р");
}

void GameWindow::on_pushButton_19_clicked()
{
    ui->pushButton_19->setEnabled(0);
    emit signalFromButton("о");
}

void GameWindow::on_pushButton_20_clicked()
{
    ui->pushButton_20->setEnabled(0);
    emit signalFromButton("л");
}

void GameWindow::on_pushButton_21_clicked()
{
    ui->pushButton_21->setEnabled(0);
    emit signalFromButton("д");
}

void GameWindow::on_pushButton_22_clicked()
{
    ui->pushButton_22->setEnabled(0);
    emit signalFromButton("ж");
}

void GameWindow::on_pushButton_23_clicked()
{
    ui->pushButton_23->setEnabled(0);
    emit signalFromButton("э");
}

void GameWindow::on_pushButton_24_clicked()
{
    ui->pushButton_24->setEnabled(0);
    emit signalFromButton("я");
}

void GameWindow::on_pushButton_25_clicked()
{
    ui->pushButton_25->setEnabled(0);
    emit signalFromButton("ч");
}

void GameWindow::on_pushButton_26_clicked()
{
    ui->pushButton_26->setEnabled(0);
    emit signalFromButton("с");
}

void GameWindow::on_pushButton_27_clicked()
{
    ui->pushButton_27->setEnabled(0);
    emit signalFromButton("м");
}

void GameWindow::on_pushButton_28_clicked()
{
    ui->pushButton_28->setEnabled(0);
    emit signalFromButton("и");
}

void GameWindow::on_pushButton_29_clicked()
{
    ui->pushButton_29->setEnabled(0);
    emit signalFromButton("т");
}

void GameWindow::on_pushButton_30_clicked()
{
    ui->pushButton_30->setEnabled(0);
    emit signalFromButton("ь");
}

void GameWindow::on_pushButton_31_clicked()
{
    ui->pushButton_31->setEnabled(0);
    emit signalFromButton("б");
}

void GameWindow::on_pushButton_32_clicked()
{
    ui->pushButton_32->setEnabled(0);
    emit signalFromButton("ю");
}

GameWindow::~GameWindow()
{
    delete ui;
}
