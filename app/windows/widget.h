
/*!
 * \file widget.h
 * \brief Header contains describing of the \a MainWindow class
*/

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QGroupBox>
#include <QPushButton>
#include <QGridLayout>

#include "gamewindow.h"

#include <QFileInfo>
#include <QDebug>

#pragma once

/*!
 * \class MainMenu widget.h "app/windows/widget.h"
 * \brief The MainMenu class
 * Describes Main menu of the game. \a MainWindow is inherited from \a QWidget
 */
class MainMenu : public QWidget
{
    Q_OBJECT

    friend class AboutWindow;

    const QString kButtonStyle = "background-color: #0F195A;"
                                 "color: #E4B2CB;"
                                 "border-style: outset;"
                                 "font: bold 14px;"
                                 "border-radius: 5px;"; /*!< Style for buttons */

    const QString kBoxStyle = "border-radius: 5px;"
                              "border-style: outset;"; /*!< Style for box */

    QGroupBox *main_box;

    QLabel *background_label;

    QPushButton *start_button;
    QPushButton *about_button;
    QPushButton *quit_button;

    AboutWindow *about_window;
    GameWindow *game_window;
public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
private slots:
    /*!
     * Slot that creates \a AboutWindow object and show it over main menu window
     * \brief Opens about window
     */
    void aboutWindowOpen();

    /*!
     * Slot that creates \a GameWindow object and show it instead of main menu window
     * \brief Opens game window
     */
    void gameWindowOpen();
};



