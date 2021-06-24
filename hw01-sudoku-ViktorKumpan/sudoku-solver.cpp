#include "sudoku-solver.h"

#include <iostream>
#include <numeric>
#include <vector>
#include <set>
#include <tuple>

bool cheker( std::vector<std::vector<int>> &field1) {

    int size = field1.size();
    int size_quadrant = size/3;
    int full = 0; for (int i = 1; i <= size;i++) full += i;

    for (int row = 0; row < size; row++){
        if (std::accumulate(field1[row].begin(), field1[row].end(), 0) != full) return false;

        int summ_col = 0;
        for(int col = 0; col < size; col ++)
            summ_col += field1[col][row];

        if (summ_col != full) return false;
    }

    for (int column= 0; column < size; column += 3){
        for (int row = 0; row < size; row += size_quadrant){

            int sum_quad = 0;
            for (int col = 0; col < 3; col++) {
                for (int line = 0; line < size_quadrant; line++)
                    sum_quad += field1[row + line][col + column];
            }
            if (sum_quad != full) return false;
        }
    }
    return true;
}

std::pair<int ,int> get_empty( std::vector<std::vector<int>> &field1) {
    int size = field1.size();
    for (int row = 0; row < size; row++)
        for (int col = 0; col < size; col++)
            if (field1[row][col] == 0) return std::pair(row, col);
}

std::set<int> check_row( std::vector<std::vector<int>> &field1, int row){
    int size = field1.size();
    std::set<int> set_numb; for (int i = 1; i <= size; i ++) set_numb.insert(i);
    for (int i = 0; i < size; i ++)
        if (field1[row][i] != 0) set_numb.erase(field1[row][i]);
    return set_numb;
}

std::set<int> check_col( std::vector<std::vector<int>> &field1, std::set<int> &select_set, int col){
    int size = field1.size();
    for (int i = 0; i < size; i ++)
        if (field1[i][col] != 0) select_set.erase(field1[i][col]);
    return select_set;
}

std::set<int> check_qua( std::vector<std::vector<int>> &field1, std::set<int>&select_set, int row, int col){
    int size = field1.size();
    int size_quadrant = size/3;

    int start_row = (row/size_quadrant)*size_quadrant;
    int start_col = (col/3)*3;

    for (int block_r = 0; block_r < size_quadrant; block_r++)
        for (int block_c = 0; block_c < 3; block_c++)
            if (field1[start_row + block_r][start_col + block_c] != 0){
                select_set.erase(field1[start_row + block_r][start_col + block_c]);
            }
    return select_set;
}

std::set<int> execution( std::vector<std::vector<int>> &field1, int row, int col){
    std::set<int> select_set;
    select_set = check_row(field1, row);
    select_set = check_col(field1, select_set, col);
    select_set = check_qua(field1, select_set, row, col);
    return select_set;
}

std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>, int, bool> BDFS( std::vector<std::vector<int>> &field ,std::vector<std::vector<int>> &answer, int count){

    if (cheker(field)){
        count+=1;
        if (count == 1)
            answer = field;
        return std::tuple(field, answer, count, true);
    }
    std::pair<int, int> coord = get_empty(field);
    std::set<int> cor_numbers = execution(field, coord.first, coord.second);

    for (int num: cor_numbers){
        field[coord.first][coord.second] = num;
        std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>, int, bool> check = BDFS(field,answer, count);
        count = std::get<2>(check);
        if (std::get<3>(check)){
            if (cor_numbers.size() > 1){
                field[coord.first][coord.second] = 0;
                continue;
            }else{
                field[coord.first][coord.second] = 0;
                return std::tuple(std::get<0>(check), std::get<1>(check), std::get<2>(check), true);
            }
        }else{
            field[coord.first][coord.second] = 0;
        }

    }
    return std::tuple(field, answer, count, false);
}

std::pair<size_t, std::vector<std::vector<int>>> sudoku_solve(const std::vector<std::vector<int>> &field) {
    int count = 0;
    std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>, int, bool> answer;
    std::vector<std::vector<int>> load;
    int k;
    std::vector<std::vector<int>> cop_field;
    cop_field.reserve(field.size());
    std::copy(field.begin(),field.end(),back_inserter(cop_field));
    answer = BDFS(cop_field,load, count);

    return std::pair(std::get<2>(answer), std::get<1>(answer));
};
