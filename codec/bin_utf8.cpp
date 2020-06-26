// 二进制流和utf8之间的转换。阿里云oss最大允许1kb的文件名长度，因此数据最大压缩1/8
#include <cstdlib>
#include "bin_utf8.h"
#include <cmath>

#define input_length 875
#define output_length 1000

string *binary_to_utf8(string *input_binary_data) {
    int new_length = ceil((float) input_binary_data->length() * 8.0 / 7.0);
    auto output_utf8_data = new string(new_length, '\0');
    auto output_position = output_utf8_data->begin();
    char last_byte = 0; // 0x11110000 左端开始数5位是有效的信息，右边都是0
    short valid_bit_count = 0;// last_byte中有几位是需要利用的
    for (char current_byte:*input_binary_data) {
        if (valid_bit_count == 8) {
            *output_position = current_byte >> 1;
            output_position++;
            last_byte = current_byte << 7;
            valid_bit_count = 1;
            continue;
        }
        char construction_byte = (last_byte >> 1) + (current_byte >> (1 + valid_bit_count));
        last_byte = current_byte << (7 - valid_bit_count);
        valid_bit_count = 1 + valid_bit_count;
        *output_position = construction_byte;
        output_position++;
    }
    if (last_byte > 0) {
        *output_position = last_byte >> 1;
    }
    return output_utf8_data;
}

string *utf8_to_binary(string *input_utf8_data) {
//    short last_bit_count = 8 - input_utf8_data->capacity * 7 % 8;
    auto output_binary_data = new string(input_utf8_data->length() * 7 / 8, '\0');
    auto output_position = output_binary_data->begin();
    char unfilled_byte = 0; //0x11110000 左端开始数5位是有效的信息，右边都是0
    short valid_bit_count = 0;
    for (char current_utf8_byte:*input_utf8_data) {
        char current_utf8_data_content = current_utf8_byte << 1;// 只取其中有用的7位
        if (valid_bit_count == 0) {
            valid_bit_count = 7;
            unfilled_byte = current_utf8_data_content;
            continue;
        }
        char construction_byte = unfilled_byte + (current_utf8_data_content >> valid_bit_count);
        unfilled_byte = current_utf8_data_content << (8 - valid_bit_count);
        valid_bit_count = valid_bit_count - 1;
        *output_position = construction_byte;
        output_position++;
    }
    return output_binary_data;
}


