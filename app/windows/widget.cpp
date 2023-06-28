#include "widget.h"
#include "ui_widget.h"

MainMenu::MainMenu(QWidget *parent)
    : QWidget(parent)
{
    about_window = nullptr;
    this->setFixedSize(500, 500);

    game_window = new GameWindow();
    connect(game_window, &GameWindow::returnToMain, this, &MainMenu::show);

    background_label = new QLabel(this);
    background_label->setPixmap(QPixmap("./data/backgrounds/lscape2.png"));
    background_label->setGeometry(0, 0, 500, 500);
    background_label->update();

    main_box = new QGroupBox(this);
    main_box->setGeometry(300, 0, 300, 300);
    main_box->setStyleSheet(kBoxStyle);

    start_button = new QPushButton("Начать игру", main_box);
    start_button->setGeometry(20, 20, 160, 80);
    start_button->setStyleSheet(kButtonStyle);
    QObject::connect(start_button, SIGNAL(clicked()), this, SLOT(gameWindowOpen()));

    about_button = new QPushButton("Подробнее об игре", main_box);
    about_button->setGeometry(20, 110, 160, 80);
    about_button->setStyleSheet(kButtonStyle);
    QObject::connect(about_button, SIGNAL(clicked()), this, SLOT(aboutWindowOpen()));

    quit_button = new QPushButton("Выйти", main_box);
    quit_button->setGeometry(20, 200, 160, 80);
    quit_button->setStyleSheet(kButtonStyle);
    QObject::connect(quit_button, SIGNAL(clicked()), this, SLOT(close()));

}

MainMenu::~MainMenu()
{
    delete main_box;
    delete start_button;
    delete about_button;
    delete quit_button;
    delete about_window;
}

void MainMenu::aboutWindowOpen()
{
    if (about_window)
        delete about_window;
    about_window = new AboutWindow("<center><h3><font color=#E4B2CB>Игра судоку<br>©Астафьев Игорь</font></h3></center>", this);
    about_window->exec();
}

void MainMenu::gameWindowOpen()
{
    game_window->show();
    this->close();
}
