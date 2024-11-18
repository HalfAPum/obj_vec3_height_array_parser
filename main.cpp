//
// Created by o.narvatov on 8/18/2024.
//

#include <iostream>

#include "height_array.h"

using namespace std;

int main() {
    std::string file_name;

    std::cin >> file_name;

    Height_Array::get_height_array(file_name);
}
