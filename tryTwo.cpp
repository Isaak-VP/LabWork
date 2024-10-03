#include "matx.h"
#include "num.h"
#include <iostream>
#include <vector>

std::vector<matx> matrices; // Зберігання матриць

void createMatrix() {
    int rows, cols;
    std::cout << "Vvedit kilkist riadkiv: ";
    std::cin >> rows;
    std::cout << "Vvedit kilkist stovptsiv: ";
    std::cin >> cols;

    matx m(rows, cols);
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            std::string value;
            std::cout << "Vvedit element [" << i << "][" << j << "]: ";
            std::cin >> value;
            m.matrix[i][j] = num(value);
        }
    }
    matrices.push_back(m);
    std::cout << "Matrytsia stvorena pid nomerom " << matrices.size() - 1 << "\n";
}

void viewMatrix() {
    int index;
    std::cout << "Vvedit nomer matrytsi dlia perehliadu: ";
    std::cin >> index;

    if (index < 0 || index >= matrices.size()) {
        std::cout << "Nepravylnyi nomer matrytsi.\n";
        return;
    }

    std::cout << "Matrytsia nomer " << index << ":\n";
    std::cout << matrices[index] << std::endl;
}

void deleteMatrix() {
    int index;
    std::cout << "Vvedit nomer matrytsi dlia vydalennia: ";
    std::cin >> index;

    if (index < 0 || index >= matrices.size()) {
        std::cout << "Nepravylnyi nomer matrytsi.\n";
        return;
    }

    matrices.erase(matrices.begin() + index);
    std::cout << "Matrytsia vydalena.\n";
}

void addMatrices() {
    int index1, index2;
    std::cout << "Vvedit nomer pershoi matrytsi: ";
    std::cin >> index1;
    std::cout << "Vvedit nomer druhoi matrytsi: ";
    std::cin >> index2;

    if (index1 < 0 || index1 >= matrices.size() || index2 < 0 || index2 >= matrices.size()) {
        std::cout << "Nepravylnyi nomer matrytsi.\n";
        return;
    }

    matx result = matrices[index1] + matrices[index2];
    std::cout << "Rezultat dodavannia:\n" << result << std::endl;
}

void subtractMatrices() {
    int index1, index2;
    std::cout << "Vvedit nomer pershoi matrytsi: ";
    std::cin >> index1;
    std::cout << "Vvedit nomer druhoi matrytsi: ";
    std::cin >> index2;

    if (index1 < 0 || index1 >= matrices.size() || index2 < 0 || index2 >= matrices.size()) {
        std::cout << "Nepravylnyi nomer matrytsi.\n";
        return;
    }

    matx result = matrices[index1] - matrices[index2];
    std::cout << "Rezultat vidnimannia:\n" << result << std::endl;
}

void multiplyMatrices() {
    int index1, index2;
    std::cout << "Vvedit nomer pershoi matrytsi: ";
    std::cin >> index1;
    std::cout << "Vvedit nomer druhoi matrytsi: ";
    std::cin >> index2;

    if (index1 < 0 || index1 >= matrices.size() || index2 < 0 || index2 >= matrices.size()) {
        std::cout << "Nepravylnyi nomer matrytsi.\n";
        return;
    }

    try {
        matx result = matrices[index1] * matrices[index2];
        std::cout << "Rezultat mnozhennia:\n" << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}

void divideMatrices() {
    int index1, index2;
    std::cout << "Vvedit nomer pershoi matrytsi: ";
    std::cin >> index1;
    std::cout << "Vvedit nomer druhoi matrytsi: ";
    std::cin >> index2;

    if (index1 < 0 || index1 >= matrices.size() || index2 < 0 || index2 >= matrices.size()) {
        std::cout << "Nepravylnyi nomer matrytsi.\n";
        return;
    }

    try {
        matx result = matrices[index1] / matrices[index2];
        std::cout << "Rezultat dilennia:\n" << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }
}
void menu(){
 int choice;

    while (true) {
        std::cout << "\nVibirite operatsiu:\n";
        std::cout << "1. Stvoryty matrytsiu\n";
        std::cout << "2. Perehlianut matrytsiu\n";
        std::cout << "3. Vydalyty matrytsiu\n";
        std::cout << "4. Dodaty matrytsi\n";
        std::cout << "5. Vidnyaty matrytsi\n";
        std::cout << "6. Mnozhyty matrytsi\n";
        std::cout << "7. Dilyty matrytsi\n";
        std::cout << "8. Vyhid\n";
        std::cout << "Vvedit nomer operatsii: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                createMatrix();
                break;
            case 2:
                viewMatrix();
                break;
            case 3:
                deleteMatrix();
                break;
            case 4:
                addMatrices();
                break;
            case 5:
                subtractMatrices();
                break;
            case 6:
                multiplyMatrices();
                break;
            case 7:
                divideMatrices();
                break;
            case 8:
                std::cout << "Vyhid z prohramy.\n";
                
            default:
                std::cout << "Nepravylnyi vibir. Sprobuyte znovu.\n";
        }
    }
}

int main() {
    
    menu();

    return 0;
}
