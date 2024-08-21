#ifndef BOARD_H
#define BOARD_H
class tetramino;

struct Coordinate{
    int x, y;
};

class Board {
    private:
        const int row_size = 10;
        const int col_size = 20;
    public:
        int score;
        Board(int score);
        int matrix[20][10];   

        void init_matrix();
        void print_matrix();
        bool is_full(int row);
        bool is_empty(int row);
        void move_row_down(int row, int n_rows);
        void clear_row(int row);
};

int max_y(tetramino* point);
void update_score(int l_cleared, Board &griglia);
void clear_full_rows(tetramino* point, Board &griglia);
bool is_game_over(tetramino* point, Board &griglia);
#endif