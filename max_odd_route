#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

//структура бинарного дерева построенного на массиве
struct binTree {
    const int max_size = 1000;   //максимальный размер массива
    int* nodes; //массив узлов, каждый узел хранит числовое значение

    binTree() {
        nodes = new int[max_size];
        clear();
    }

    ~binTree() {
        delete[] nodes;
    }

    //функция очищения дерева
    void clear() {
        for (int i = 0; i < max_size; ++i) {
            nodes[i] = -1;
        }
    }

    void scan() {
        int n;
        cout << "Введите размер массива: ";
        cin >> n;
        cout << "Введите массив дерева: ";
        for (int i = 0; i < n; ++i) {
            cin >> nodes[i];
        }
    }

    //функция ввода дерева из файла
    void scan_from_file(string fname) {
        ifstream fin(fname);
        if (!fin.is_open()) {
            printf("Не удалось открыть файл \"%s\"\n", fname.c_str());
            return;
        }

        int n;
        fin >> n;
        for (int i = 0; i < n; ++i) {
            fin >> nodes[i];
            nodes[i]--;
        }
    }

    //функция вывода полного дерева
    void print() {
        cout << "\nПолное дерево:\n";
        print_node(0, 0); //выводим дерево от корня
        cout << '\n';
    }

    //функция вывода поддерева
    void print_und_tree(int ind) {
        printf("Поддерево с корнем в вершине %d:\n", nodes[ind]);
        print_node(ind, 0);
        cout << '\n';
    }

    //рекурсивная функция вывода поддерева с корнем cur_node 
    void print_node(int ind, int cur_depth) {
        if (nodes[ind] == -1) { return; }

        print_node(ind*2+2, cur_depth + 1);

        for (int i = 0; i < cur_depth; ++i) {
            cout << "|\t";
        }
        printf("|-------|%d\n", nodes[ind]);

        print_node(ind*2+1, cur_depth + 1);
    }

    //рекурсивная функция, возвращающая максимальное расстояние от вершины ind 
    void rec(int ind, vector<int>& temp_route, vector<int>& max_route) {

        if (nodes[ind] == -1 || nodes[ind] % 2 == 0) {
            //мы не рассматриваем вершины с четными номерами
            return;
        }
        
        temp_route.push_back(nodes[ind]);
        if (max_route.size() < temp_route.size()) {
            max_route.clear();
            for (size_t i = 0; i < temp_route.size(); ++i) {
                max_route.push_back(temp_route[i]);
            }
        }
        rec(ind * 2 + 1, temp_route, max_route);
        rec(ind * 2 + 2, temp_route, max_route);
        temp_route.pop_back();
    }

};

int main()
{
    setlocale(LC_ALL, "Russian");
    binTree tree;

    tree.scan();
    tree.print();

    vector<int> max_route;
    vector<int> temp_route;
    tree.rec(0, temp_route, max_route);
    
    printf("Размер самого длинного пути: %d\n", max_route.size());
    printf("Путь: ");
    for (size_t i = 0; i < max_route.size(); ++i) {
        printf("%d ", max_route[i]);
    }
    printf("\n");

    return 0;
}
 
