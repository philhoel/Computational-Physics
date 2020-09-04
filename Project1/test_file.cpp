#include <iostream>
#include <cmath>


int main() {

    int **array = new int*[10];
    for (int count = 0; count < 10; ++count) {
        array[count] = new int[count+1];
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            array[i][j] = i*j;
        }
    }


    std::cout << array[5][5] << std::endl;




    return 0;
}