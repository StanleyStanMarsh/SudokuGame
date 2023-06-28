#include "gamewindow.h"

Area::Area(QWidget *parent) : QLabel(parent)
{

}

void Area::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.setPen(QPen(QColor(15, 25, 90), 8, Qt::SolidLine, Qt::RoundCap));
    // vertical
    paint.drawLine(235, 10, 235, 630);
    paint.drawLine(445, 10, 445, 630);
    // horizontal
    paint.drawLine(30, 215, 650, 215);
    paint.drawLine(30, 425, 650, 425);
}

GameWindow::GameWindow(QWidget *parent) : QWidget(parent)
{
    about_window = nullptr;
    matrix = nullptr;
    this->setFixedSize(680, 710);
    this->setStyleSheet("background-color: #384A92;");

    return_button = new QPushButton("Вернуться", this);
    setButtonStyle(return_button, 30, 10, 80, 50, kButtonStyle);
    QObject::connect(return_button, SIGNAL(clicked()), this, SLOT(returnButtonClicked()));

    generate_button = new QPushButton("Сгенерировать", this);
    setButtonStyle(generate_button, 120, 10, 120, 50, kButtonStyle);
    QObject::connect(generate_button, SIGNAL(clicked()), this, SLOT(generateGrid()));

    diff_box = new QComboBox(this);
    diff_box->setGeometry(250, 10, 100, 50);
    diff_box->addItem("Легкий");
    diff_box->addItem("Средний");
    diff_box->addItem("Сложный");
    diff_box->setStyleSheet(kBoxStyle);

    check_button = new QPushButton("Проверить", this);
    setButtonStyle(check_button, 360, 10, 100, 50, kButtonStyle);
    QObject::connect(check_button, SIGNAL(clicked()), this, SLOT(checkSol()));

    solve_button = new QPushButton("Решить", this);
    setButtonStyle(solve_button, 470, 10, 100, 50, kButtonStyle);
    QObject::connect(solve_button, SIGNAL(clicked()), this, SLOT(solveGenerated()));

    paint_area = new Area(this);
    paint_area->setGeometry(0, 60, 700, 640);

    vectorResize(grid, kSizeGrid, kSizeGrid);
    for (int i = 0; i < kSizeGrid; i++)
        for (int j = 0; j < kSizeGrid; j++)
        {
            grid[i][j] = new QLineEdit(this);
            setQLEStyle(grid[i][j]);
            grid[i][j]->setReadOnly(true);
            grid[i][j]->setGeometry(30 + (210 / sector_size[kCurrentSize]) * j, 70 + (210 / sector_size[kCurrentSize]) * i, 60, 60);
        }


}

GameWindow::~GameWindow()
{
    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[i].size(); j++)
            delete grid[i][j];

    delete matrix;

    delete return_button;
    delete generate_button;
    delete check_button;
    delete solve_button;
    delete diff_box;

    delete paint_area;

    delete about_window;

    for (int i = 0; i < grid.size(); i++)
        for (int j = 0; j < grid[i].size(); j++)
            delete grid[i][j];
}

void GameWindow::returnButtonClicked()
{
    this->close();
    emit returnToMain();
}

void GameWindow::generateGrid()
{
    if (matrix)
    {
        for (int i = 0; i < kSizeGrid; i++)
            for (int j = 0; j < kSizeGrid; j++)
                grid[i][j]->close();
        delete matrix;
    }

    diff = (Difficulty)diff_box->currentIndex();

    matrix = new Grid(sector_size[kCurrentSize]);
    matrix->mix();

    matrix->resetToZero(diff);

    vectorResize(grid, kSizeGrid, kSizeGrid);

    for (int i = 0; i < kSizeGrid; i++)
        for (int j = 0; j < kSizeGrid; j++)
        {
            if (matrix->getItem(i, j) == 0)
                cellEdit(grid[i][j], "", false);
            else
                cellEdit(grid[i][j], QString::number(matrix->getItem(i, j)), true);

            grid[i][j]->show();
        }
    paint_area->update();
}

void GameWindow::checkSol()
{
    if (!matrix)
    {
        return;
    }

    bool solved = true;

    for (int i = 0; i < kSizeGrid; i++)
    {
        for (int j = 0; j < kSizeGrid; j++)
            if (!grid[i][j]->isReadOnly())
            {
                if (grid[i][j]->text().toInt() != matrix->getItemAnswer(i, j))
                {
                    solved = false;
                    setQLEStyleMistake(grid[i][j]);
                }
                else
                    setQLEStyleEditable(grid[i][j]);
            }
    }

    if (solved)
    {
        if (about_window)
            delete about_window;
        about_window = new AboutWindow("<center><h2><font color=#E4B2CB>Вы решили<br>судоку</font></h2></center>", this);
        about_window->exec();
    }
    else
        qDebug() << "not solved";

}

void GameWindow::solveGenerated()
{
    if (!matrix)
    {
        return;
    }

    for (int i = 0; i < kSizeGrid; i++)
        for (int j = 0; j < kSizeGrid; j++)
        {
            grid[i][j]->close();
            grid[i][j]->setReadOnly(true);
            grid[i][j]->setText(QString::number(matrix->getItemAnswer(i, j)));
            grid[i][j]->show();
        }
}

void GameWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit returnToMain();
}

void GameWindow::setQLEStyle(QLineEdit *line)
{
    line->setAlignment(Qt::AlignCenter);
    line->setFont(QFont("Times", 15));
    QPalette pal;
    pal.setColor(QPalette::Text, QColor(218, 185, 198));
    line->setPalette(pal);
    line->setStyleSheet("border: 1px solid #E4B2CB;"
                        "border-radius: 3px;");
}

void GameWindow::setQLEStyleEditable(QLineEdit *line)
{
    line->setAlignment(Qt::AlignCenter);
    line->setFont(QFont("Times", 15));
    QPalette pal;
    pal.setColor(QPalette::Text, QColor(218, 185, 198));
    line->setPalette(pal);
    line->setStyleSheet("background-color: #0F195A;"
                        "border: 1px solid #E4B2CB;"
                        "border-radius: 3px;");
}

void GameWindow::setQLEStyleMistake(QLineEdit *line)
{
    line->setAlignment(Qt::AlignCenter);
    line->setFont(QFont("Times", 15));
    QPalette pal;
    pal.setColor(QPalette::Text, QColor(218, 185, 198));
    line->setPalette(pal);
    line->setStyleSheet("background-color: #0F195A;"
                        "border: 1px solid red;"
                        "border-radius: 3px;");
}

void GameWindow::setButtonStyle(QPushButton *button, int x, int y, int w, int h, QString style)
{
    button->setGeometry(x, y, w, h);
    button->setStyleSheet(style);
}

void GameWindow::cellEdit(QLineEdit *cell, QString text, bool read_only)
{
    cell->setText(text);
    cell->setReadOnly(read_only);
    cell->setMaxLength(1);
    if (read_only)
        setQLEStyle(cell);
    else
        setQLEStyleEditable(cell);
}
