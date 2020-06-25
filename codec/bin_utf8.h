#pragma once

struct data_piece {
    char *content;
    int index;
    int capacity;

    void push(char t);

    explicit data_piece(int initial_size);

    ~data_piece();
};
