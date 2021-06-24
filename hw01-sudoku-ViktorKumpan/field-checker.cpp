#include "field-checker.h"
#include <iostream>
#include <numeric>
#include "sudoku-solver.h"


bool check_field(const std::vector<std::vector<int>> &init_field, const std::vector<std::vector<int>> &solution) {

    if ((solution.size() != init_field.size()) || (solution[0].size() != solution.size())) return false;
    int size  = init_field.size();
    int height = size/3;
    int full = 0; for (int i = 1; i <= size; i++) full += i;

    for (int col = 0; col < size; col++){
        std::vector<int> numbers_c; for (int i = 0; i < size; i++) numbers_c.push_back(0);
        std::vector<int> numbers_r; for (int i = 0; i < size; i++) numbers_r.push_back(0);
        int points_col = 0;
        for (int row = 0; row < size; row++){
            //проверка повторяющихся элементов в столбце
            if (numbers_c[solution[row][col] - 1] != 0) return false;
            numbers_c[solution[row][col] - 1] = 1;
            //проверка на изменение изначальной таблицы.
            if (init_field[row][col] != 0 && solution[row][col] != init_field[row][col]) return false;
            //проверка на сумму чисел в столбцах
            points_col += solution[row][col];
            //проверка на сумму чисел в строке только для первого прохода
            if (col == 0 && std::accumulate(solution[row].begin(), solution[row].end(), 0) != full) return false;
            //проверка повторяющихся элементов в строке
            if (numbers_r[solution[col][row] - 1] != 0) return false;
            numbers_r[solution[col][row] - 1] = 1;
        }
        //проверка на сумму чисел в столбце
        if (points_col != full) return false;
    }

    for (int col = 0; col < size; col += 3){
        for(int row = 0; row < size; row += height){
            std::vector<int> numbers_qua; for (int i = 0; i < size; i++) numbers_qua.push_back(0);
            int points_qua = 0;
            for (int block_r = 0; block_r < height; block_r++)
                for (int block_c = 0; block_c < 3; block_c++){
                    points_qua += solution[row + block_r][col + block_c];
                    //проверка на повторяющиеся элементы в блоке
                    if (numbers_qua[solution[row + block_r][col + block_c] - 1] !=0 ) return false;
                    numbers_qua[solution[row + block_r][col + block_c] - 1 ] = 1;

                }
            //  проверка на сумму элементов
            if (points_qua!=full) return false;
        }
    }

    return true;
}
