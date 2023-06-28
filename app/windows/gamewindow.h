
/*!
 * \file gamewindow.h
 * \brief Header contains describing of the \a Area, \a AboutWindow and \a GameWindow classes
*/

#include <QWidget>
#include <QPushButton>
#include <QFont>
#include <QComboBox>
#include <QPainter>
#include <QLabel>
#include <QStyle>
#include <QLineEdit>
#include <QBoxLayout>
#include <QCloseEvent>
#include <QDialog>
#include "app/grid/grid.h"

#pragma once

enum Size
{
    kSmall,
    kMed,
    kBig
};

/*!
 * \class Area gamewindow.h "app/windows/gamewindow.h"
 * \brief This is Area class
 * Describes auxiliary class that is inherited from QLabel.
 */
class Area : public QLabel
{
    Q_OBJECT
public:
    Area(QWidget *parent);

    /*!
     * \brief Overrides paint event
     * This method uses to paint separating lines
     */
    void paintEvent(QPaintEvent *) override;
};

/*!
 * \class AboutWindow gamewindow.h "app/windows/gamewindow.h"
 * \brief This is AboutWindow class
 * Describes pop-up window. This class is inherited from QDialog.
 */
class AboutWindow : public QDialog
{
    Q_OBJECT

    const QString kLabelStyle = "background-color: #0F195A";

    QBoxLayout* layout;
    QLabel* description;

public:
    AboutWindow(QString text, QWidget *parent = nullptr);
    ~AboutWindow();
};

/*!
 * \class GameWindow gamewindow.h "app/windows/gamewindow.h"
 * \brief This is GameWindow class
 * Describes Game window. This class is inherited from QWidget.
 */
class GameWindow : public QWidget
{
    Q_OBJECT

    const QString kButtonStyle = "background-color: #0F195A;"
                                 "color: #E4B2CB;"
                                 "border-style: outset;"
                                 "font: bold 14px;"
                                 "border-radius: 5px;";

    const QString kBoxStyle = "border: none;"
                              "background: #0F195A;"
                              "color: #E4B2CB;"
                              "font: bold 14px;"
                              "border-radius: 5px;"
                              "selection-background-color: #384A92;"
                              "selection-color: #E4B2CB;";

    const Size kCurrentSize = kSmall;

    const int sector_size[3] = {3, 4, 5};

    const int kSizeGrid = sector_size[kCurrentSize] * sector_size[kCurrentSize];

    Difficulty diff;

    QVector< QVector<QLineEdit*> > grid;
    Grid* matrix;

    QPushButton *return_button;
    QPushButton *generate_button;
    QPushButton *check_button;
    QPushButton *solve_button;
    QComboBox *diff_box;

    Area *paint_area;

    AboutWindow *about_window;
public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    /*!
     * \brief Overrides paint event
     * \param event Close event
     * This method uses to paint separating lines
     */
    void closeEvent(QCloseEvent *event) override;
signals:

    /*!
     * Signal that is used to return to Main menu
     * \brief returnToMain
     */
    void returnToMain();
private slots:

    /*!
     * Slot that emits \a returnToMain signal
     * \brief Returns to Main menu
     */
    void returnButtonClicked();
    void generateGrid();

    /*!
     * Slot that is used to check if user has been solved sudoku correct
     * \brief Checks solution
     */
    void checkSol();

    /*!
     * Slot that is used to show to user correct sudoku solution
     * \brief Shows sudoku solution
     */
    void solveGenerated();
private:

    /*!
     * Sets the style of the read-only \a line
     * \param line Pointer to \a QLineEdit object that needed to be edited
     */
    void setQLEStyle(QLineEdit *line);

    /*!
     * Sets the style of the editable \a line
     * \param line Pointer to \a QLineEdit object that needed to be edited
     */
    void setQLEStyleEditable(QLineEdit *line);

    /*!
     * Sets the style of the editable \a line. Uses when user makes a mistake
     * \param line Pointer to \a QLineEdit object that needed to be edited
     */
    void setQLEStyleMistake(QLineEdit *line);

    /*!
     * Sets syle, geometry and text of the \a button
     * \param button Pointer to \a QPushButton object that needed to be edited
     * \param x Left upper corner x-coordinate
     * \param y Left upper corner y-coordinate
     * \param w Width
     * \param h Height
     * \param style
     */
    void setButtonStyle(QPushButton *button, int x, int y, int w, int h, QString style);

    /*!
     * Edits the \a cell
     * \param cell Pointer to \a QLineEdit object that needed to be edited
     * \param text The text that needed to be shown on the \a cell
     * \param read_only The flag that makes \a cell read-only
     */
    void cellEdit(QLineEdit *cell, QString text, bool read_only);
};


