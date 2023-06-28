#include "grid.h"

Grid::Grid(int n)
{
    sector_size = n;
    size = n * n;

    vectorResize(matrix, size, size);
    vectorResize(solving, size, size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = (i * n + i / n + j) % (n * n)  + 1;
        }
}

int Grid::getSize() const
{
    return size;
}

int Grid::getItem(int i, int j) const
{
    return solving[i][j];
}

int Grid::getItemAnswer(int i, int j) const
{
    return matrix[i][j];
}

void Grid::swapRows(int first, int second)
{
    if (first < 0 || second < 0 || first >= size || second >= size)
        return;
    QVector<int> temp = matrix[first];
    matrix[first] = matrix[second];
    matrix[second] = temp;
}

void Grid::swapColumns(int first, int second)
{
    if (first < 0 || second < 0 || first >= size || second >= size)
        return;
    QVector<int> temp(size);
    for (int i = 0; i < size; i++)
        temp[i] = matrix[i][first];
    for (int i = 0; i < size; i++)
        matrix[i][first] = matrix[i][second];
    for (int i = 0; i < size; i++)
        matrix[i][second] = temp[i];
}

void Grid::transpose()
{
    int tmp;
    for(int i = 0; i < size; ++i)
    {
        for(int j = i; j < size; ++j)
        {
            tmp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = tmp;
        }
    }
}

int randomBetween(int low, int high)
{
    return (rand() % ((high + 1) - low) + low);
}

void vectorResize(QVector<QVector<int>> &v, int n, int m)
{
    v.resize(n);
    for (int i = 0; i < n; i++)
        v[i].resize(m);
}

void vectorResize(QVector<QVector<QLineEdit*>> &v, int n, int m)
{
    v.resize(n);
    for (int i = 0; i < n; i++)
        v[i].resize(m);
}

void Grid::mix()
{
    srand(time(0));
    for (int i = 0; i < 2 * size; i++)
    {
        auto sector = randomBetween(0, sector_size - 1);
        auto func_num = randomBetween(0, 2);
        if (func_num == 0)
            this->swapRows(sector * sector_size + randomBetween(0, sector_size - 1), sector * sector_size + randomBetween(0, sector_size - 1));
        else if (func_num == 1)
            this->swapColumns(sector * sector_size + randomBetween(0, sector_size - 1), sector * sector_size + randomBetween(0, sector_size - 1));
        else
            this->transpose();
    }
}

void Grid::resetToZero(Difficulty d)
{
    solving = matrix;
    srand(time(0));
    for (int k = 0; k < 30 + (int)d * 15; k++)
    {
        solving[randomBetween(0, size - 1)][randomBetween(0, size - 1)] = 0;
    }
}

