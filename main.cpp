#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

//функция переводит строку в число
int toInt(string str) {
    int ans = 0;
    for (char c : str) {
        ans *= 10;
        ans += c - '0';
    }
    return ans;
}

//структура узла дерева
struct node {
    int value;                  //значение узла
    int max_depth;              //расстояние до дальнейшего листа
    int min_depth;              //расстояние до ближайшего листа

    //укзаатели на соседние узлы
    node* parent;
    node* left;
    node* right;

    //конструктор с двумя параметрами
    node(int _value) {
        value = _value;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        max_depth = 0;
        min_depth = 0;
    }
};

//структура бинарного дерева построенного на массиве
struct binTree {
    node* root;         //корень дерева
    node* leaf_parent; //родитель для следующих листьев
    int odd;


    binTree() {
        root = nullptr;
        leaf_parent = nullptr;
        odd = 0;
    }

    //функция обновления глубин в дереве, вызывается от нового листа
    //функция рекурсивная идет от листа к корню
    //максимальная высота узла = макс(максимальная высота левого поддерева, правого поддерева)
    //минимальная     ...      =  мин(минимальная       ...               ,       ...        )
    void update_depth(node* cur_node) {
        if (cur_node == root) { return; }
        node* par = cur_node->parent;
        if (par->left != nullptr && par->right != nullptr) {
            par->min_depth = min(par->left->min_depth, par->right->min_depth) + 1;
            par->max_depth = max(par->left->max_depth, par->right->max_depth) + 1;
        }
        else {
            if (par->right == nullptr) {
                par->min_depth = par->left->min_depth + 1;
                par->max_depth = par->left->max_depth + 1;
            }
            else {
                par->min_depth = par->right->min_depth + 1;
                par->max_depth = par->right->max_depth + 1;
            }
        }
        update_depth(par);
    }

    //функция определяет предка для следующего листа
    void next_leaf_parent() {

        //у предка могут быть два потомка, поэтому переход осуществляем через раз
        ++odd;
        if (odd == 2) {
            odd = 0;
            return;
        }


        node* cur_node = leaf_parent;
        //взбираемся на верх до ближайшего перехода
        while (cur_node != root && (cur_node->parent->right == cur_node || cur_node->parent->right == nullptr)) {
            cur_node = cur_node->parent;
        }

        //переходим на правую сторону если нужно
        if (cur_node != root) {
            cur_node = cur_node->parent->right;
        }

        //спускаемся влево
        while (cur_node->left != nullptr) {
            cur_node = cur_node->left;
        }

        leaf_parent = cur_node;
    }

    //функция добавления узла в дерево
    void add_node(node* new_node) {
        
        new_node->parent = leaf_parent;

        if (leaf_parent->left == nullptr) {
            leaf_parent->left = new_node;
        }
        else {
            leaf_parent->right = new_node;
        }
        update_depth(new_node);
    }

    //функция пытается добавить в дерево элемент, возвращает соответствующее значение (true- элемент успешно добавлен)
    bool try_push_back(string str) {
        if (str == ";") { return false; }

        if (str != "-") {
            node* new_node = new node(toInt(str));
            if (root == nullptr) { 
                root = new_node; 
                leaf_parent = root;
            } else {
                add_node(new_node); 
            }
        }

        next_leaf_parent();
        return true;
    }

    //функция ввода дерева из файла
    void scanFromFile(string fname) {
        ifstream fin(fname);
        if (!fin.is_open()) {
            printf("Не удалось открыть файл \"%s\"\n", fname.c_str());
            return;
        }

        string temp;
        while (!fin.eof()) {
            fin >> temp;
            if (!try_push_back(temp)) { break; }
        }
    }


    //функция ввода дерева с клавиатуры
    void scan() {
        cout << "Введите значения вершин дерева через пробел: \n";
        cout << "Чтобы завершить ввод, вместо значения введите ';'\n";
        cout << "\nВвод: ";
        string temp;
        while (true) {
            cin >> temp;
            if (!try_push_back(temp)) { break; }
        }
    }

    //функция вывода полного дерева
    void print() {
        cout << "\nПолное дерево:\n";
        print_node(root, 0); //выводим дерево от корня
        cout << '\n';
    }

    //функция вывода поддерева
    void print_und_tree(node* cur_node) {
        printf("Поддерево с корнем в вершине %d:\n", cur_node->value);
        print_node(cur_node, 0);
        cout << '\n';
    }

    //рекурсивная функция вывода поддерева с корнем cur_node 
    void print_node(node* cur_node, int cur_depth) {
        if (cur_node == nullptr) { return; }

        print_node(cur_node->right, cur_depth+1);
        
        for (int i = 0; i < cur_depth; ++i) {
            cout << "|\t";
        }
        printf("|-------|%d\n", cur_node->value);

        print_node(cur_node->left, cur_depth + 1);
    }

    //функция выводит все поддеревья, в которых высота всех листьев лежит в диапазоне [l; r]
    void print_in_range(int l, int r) {
        printf("Поиск всех поддеревьев, в которых высота листьев лежит в диапазоне [%d; %d]...\n", l, r);
        print_node_in_range(root, l, r);
    }

    //рекурсивная функция выводит все поддеревья, в которых 
    //высота всех листьев лежит в диапазоне [l; r] начиная от уозла cur_node
    void print_node_in_range(node* cur_node, int l, int r) {
        if (cur_node == nullptr) {return;}
        if (cur_node->min_depth >= l && cur_node->max_depth <= r) {
            cout << "\nНайдено поддерево:\n";
            print_node(cur_node, 0);
        }
        print_node_in_range(cur_node->left, l, r);
        print_node_in_range(cur_node->right, l, r);
    }

};

int main()
{
    setlocale(LC_ALL, "Russian");
    binTree tree;

    tree.scanFromFile("tree.txt");
    if (tree.root == nullptr) {
        cout << "Дерево пустое!";
        return 0;
    }
    tree.print();
 
    int l, r;
    cout << "Введите диапазон (два числа через пробел): ";
    cin >> l >> r;

    tree.print_in_range(l, r);

    return 0;
}
