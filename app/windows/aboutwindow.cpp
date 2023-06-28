#include "gamewindow.h"

AboutWindow::AboutWindow(QString text, QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(200, 100);
    layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    description = new QLabel(text);
    layout->addWidget(description, Qt::AlignCenter);
    this->setStyleSheet(kLabelStyle);
}

AboutWindow::~AboutWindow()
{
    delete description;
    delete layout;
}

