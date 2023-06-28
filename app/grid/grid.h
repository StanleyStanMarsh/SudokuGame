
/*!
 * \file grid.h
 * \brief Header contains describing of the \a Grid class
*/

#include <QVector>
#include <QLineEdit>
#include <QDebug>
#include <iostream>

#pragma once

/*!
 * \brief "Difficulty" of sudoku matrix
 * Using to defining amount of clues
 */
enum Difficulty
{
    kEasy = 0,
    kMedium,
    kHard
};

/*!
 * \class Grid grid.h "app/grid/grid.h"
 * \brief This is Grid class
 * Describes sudoku matrix
 */
class Grid
{
    int size;
    int sector_size;

    QVector <QVector <int> > matrix; /*!< Original matrix */
    QVector <QVector <int> > solving; /*!< Matrix that is used to store unsolved sudoku matrix */

    /*!
     * Swaps rows in original \a matrix within the same section
     * \param first First row number
     * \param second Second row number
     */
    void swapRows(int first, int second);

    /*!
     * Swaps columns in original \a matrix within the same section
     * \param first First column number
     * \param second Second column number
     */
    void swapColumns(int first, int second);

    /*!
     * Transposes the original \a matrix
     * \brief transpose
     */
    void transpose();
public:
    Grid(int n);

    /*!
     * \return Size of the original \a matrix
     */
    int getSize() const;

    /*!
     * \brief Gets item from unsolved matrix \a solving
     * \param i Row number
     * \param j Column number
     * \return \a solving[i][j]
     */
    int getItem(int i, int j) const;

    /*!
     * \brief Gets item from original \a matrix
     * \param i Row number
     * \param j Column number
     * \return \a matrix[i][j]
     */
    int getItemAnswer(int i, int j) const;

    /*!
     * Method uses \a swapRows(), \a swapColumns and \a transpose() to randomly mix items.
     * \brief Mix items in the original \a matrix
     */
    void mix();

    /*!
     * Fills random items with zeros in unsolved matrix \a solving. Number of items depends on "difficulty" \a d
     * \brief Reset some items in unsolved matrix \a solving to zero
     * \param d "Difficulty" of sudoku
     */
    void resetToZero(Difficulty d);
};

/*!
 * \param low Lower limit
 * \param high Higher limit
 * \return Pseudorandom number between \a low and \a high
 */
int randomBetween(int low, int high);

/*!
 * Overloaded function that sets the size of the matrix \a v to \a n x \a m.
 * \brief Resize matrix \a v
 * \param[out] v Reference to \a QVector<Qvector<int>>
 * \param n Row number
 * \param m Column number
 */
void vectorResize(QVector<QVector<int>> &v, int n, int m);

/*!
 * Overloaded function that sets the size of the matrix \a v to \a n x \a m.
 * \brief Resize matrix \a v
 * \param[out] v Reference to \a QVector<Qvector<QLineEdit*>>
 * \param n Row number
 * \param m Column number
 */
void vectorResize(QVector<QVector<QLineEdit*>> &v, int n, int m);
