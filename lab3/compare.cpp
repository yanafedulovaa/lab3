
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <queue> 
#include "avl_tree.h"
#include "binary_search_tree.h"
#include "rb_tree.h"
#include "compare.h"

using namespace std;

void fill_unique(int arr[], int size) {
    srand(static_cast<unsigned int>(time(0))); 

    for (int i = 0; i < size; i++) {
        int randomNumber;
        bool isUnique;
        do {
            isUnique = true;
            randomNumber = rand() % 3000; 

            
            for (int j = 0; j < i; j++) {
                if (arr[j] == randomNumber || randomNumber == 1500) {
                    isUnique = false;
                    break;
                }
            }
        } while (!isUnique);

        arr[i] = randomNumber;
    }
}


void menu()
{
    ofstream fout;
    while (1)
    {
        short int cmd;
        cout << "Выберите действие:\n\n0.Выход из программы\n1.Сравнение высот деревьев\n2.Сравнение времени балансировки\n\n";
        cin >> cmd;

        switch (cmd)
        {
        case(0):
            return;
        case(1):
        {
            fout.open("out.txt", ios::app);
            for (int size = 200; size <= 2000; size += 200)
            {
                BST bst; RBT rbt;
                AVLTree avl;
                int* data = new int[size];
                fill_unique(data, size);
                for (int i = 0; i < size; i++)
                {
                    bst.insert_num(data[i]);
                    avl.insert_num(data[i]);
                    rbt.insert_num(data[i]);
                }

                cout << "\nКоличество элементов в списке: " << size;
                fout << "\nКоличество элементов в списке: " << size;
                cout << "\nВысота бинарного дерева:" << bst.tree_height();
                fout << "\nHeight BST:" << bst.tree_height();
                cout << "\nВысота красно-черного дерева:" << rbt.tree_height();
                fout << "\nHeight RBT:" << rbt.tree_height();
                cout << "\nВысота АВЛ дерева:" << avl.tree_height();
                fout << "\nHeight AVLT:" << avl.tree_height();
                cout << "\n_________________________________________________";
                fout << "\n_________________________________________________";
            }
            fout.close();
            break;
        }
        case(2):
        {
            fout.open("out.txt", ios::app);
            for (int size = 200; size <= 2000; size += 200)
            {
                BST bst; RBT rbt;
                AVLTree avl;
                int* data = new int[size];
                fill_unique(data, size);
                for (int i = 0; i < size; i++)
                {
                    rbt.insert_num(data[i]);
                    avl.insert_num(data[i]);
                }
                cout << "\nКоличество элементов в списке: " << size;
                fout << "\nКоличество элементов в списке: " << size;
                auto start1 = chrono::high_resolution_clock::now();
                avl.insert_num(1500);
                auto end1 = chrono::high_resolution_clock::now();

                cout << "\nВременные затраты на балансировку для АВЛ дерева при вставке:" << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() << " ns\n";
                fout << "\nInsertion Time AVL:" << chrono::duration_cast<chrono::nanoseconds>(end1 - start1).count() << " ns\n";
                auto start2 = chrono::high_resolution_clock::now();
                rbt.insert_num(1500);
                auto end2 = chrono::high_resolution_clock::now();

                cout << "\nВременные затраты на балансировку для красно-черного дерева при вставке:" << chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count() << " ns\n";
                fout << "\nInsertion Time RB:" << chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count() << " ns\n";
                auto start3 = chrono::high_resolution_clock::now();
                avl.delete_num(1500);
                auto end3 = chrono::high_resolution_clock::now();

                cout << "\nВременные затраты на балансировку для АВЛ дерева при удалении:" << chrono::duration_cast<chrono::nanoseconds>(end3 - start3).count() << " ns\n";
                fout << "\nDeletion Time AVL:" << chrono::duration_cast<chrono::nanoseconds>(end3 - start3).count() << " ns\n";
                auto start4 = chrono::high_resolution_clock::now();
                rbt.delete_num(1500);
                auto end4 = chrono::high_resolution_clock::now();

                cout << "\nВременные затраты на балансировку для красно-черного дерева при удалении:" << chrono::duration_cast<chrono::nanoseconds>(end4 - start4).count() << " ns\n";
                fout << "\nDeletion Time RB:" << chrono::duration_cast<chrono::nanoseconds>(end4 - start4).count() << " ns\n";
                cout << "\n_________________________________________________";
                fout << "\n_________________________________________________";
            }
            fout.close();
            break;
        }
        case(3):
            break;
        }

    }
}
