// 二进制流和utf8之间的转换。阿里云oss最大允许1kb的文件名长度，因此数据最大压缩1/8
#include <cstdlib>
#include "bin_utf8.h"

#define input_length 875
#define output_length 1000

void data_piece::push(char t) {
    content[index] = t;
    index++;
}

data_piece::data_piece(int initial_size) {
    content = static_cast<char *>(malloc(initial_size));
    index = 0;
    capacity = initial_size;
}

data_piece::~data_piece() {
    free(content);
};


//using namespace std;

data_piece *binary_to_utf8(data_piece *input_binary_data) {
    int new_length = input_binary_data->capacity * 8 / 7 + 1;
    auto output_utf8_data = new data_piece(new_length);
    char last_byte = 0; // 0x11110000 左端开始数5位是有效的信息，右边都是0
    short valid_bit_count = 0;// last_byte中有几位是需要利用的
    for (int i = 0; i < input_binary_data->capacity; i++) {
        char current_byte = input_binary_data->content[i];
        if (output_utf8_data->index < new_length) {
            char construction_byte = (last_byte >> 1) + (current_byte >> (1 + valid_bit_count));
            last_byte = current_byte << 7 - valid_bit_count;
            valid_bit_count = 1 + valid_bit_count;
            output_utf8_data->push(construction_byte);
        }
        output_utf8_data->push(last_byte >> 1);
    }
    return output_utf8_data;
}

data_piece *utf8_to_binary(data_piece *input_utf8_data) {
//    short last_bit_count = 8 - input_utf8_data->capacity * 7 % 8;
    auto output_binary_data = new data_piece(input_utf8_data->capacity * 7 / 8);
    char unfilled_byte = 0; //0x11110000 左端开始数5位是有效的信息，右边都是0
    short valid_bit_count = 0;
    for (int i = 0; i < input_utf8_data->capacity; i++) {
        char current_utf8_data_content = input_utf8_data->content[i] << 1;// 只取其中有用的7位
        if (valid_bit_count == 0) {
            valid_bit_count = 7;
            unfilled_byte = current_utf8_data_content;
        } else {
            char construction_byte = unfilled_byte + (current_utf8_data_content >> valid_bit_count);
            unfilled_byte = current_utf8_data_content << (8 - valid_bit_count);
            valid_bit_count = valid_bit_count - 1;
            output_binary_data->push(construction_byte);
        }
    }
    return output_binary_data;
}


