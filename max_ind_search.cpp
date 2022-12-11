/*
  Поиск индекса максимума на отрезке 
*/

#include <iostream>

using namespace std;

int n;
int a[1000000];

struct node {
    int max_ind, l, r;
    node* left;
    node* right;

    node(int _l, int _r) {
        max_ind = _l;
        l = _l;
        r = _r;
        left = nullptr;
        right = nullptr;
    }
};

struct tree {
    node* root;

    tree() {
        root = new node(0, n);
        build(root);
        calc_max(root);
    }

    void build(node* cur) {
        if (cur->r > cur->l + 1) {
            int mid = (cur->l + cur->r) / 2;
            cur->left = new node(cur->l, mid);
            cur->right = new node(mid, cur->r);
            build(cur->left);
            build(cur->right);
        }
    }

    int calc_max(node* cur) {

        cur->max_ind = (
            cur->l == cur->r - 1 ?
            cur->l :
            (a[calc_max(cur->left)] > a[calc_max(cur->right)] ? cur->left->max_ind : cur->right->max_ind)
            );

        return cur->max_ind;
    }

    int get_max_ind(int l, int r) {
        return get_max_ind(root, l, r);
    }

    int get_max_ind(node* cur, int l, int r) {
        if (cur == nullptr) {
            return -1;
        }
        if (cur->l >= l && cur->r - 1 <= r) {
            return cur->max_ind;
        }
        else if (cur->l > r || cur->r <= l) {
            return -1;
        }
        else {
            int left_max_ind = get_max_ind(cur->left, l, r);
            int right_max_ind = get_max_ind(cur->right, l, r);
            if (left_max_ind == -1) return right_max_ind;
            if (right_max_ind == -1) return left_max_ind;
            return (a[left_max_ind] > a[right_max_ind] ? left_max_ind : right_max_ind);
        }
    }

    void print_node(node* cur_node, int cur_depth) {
        if (cur_node == nullptr) { return; }

        print_node(cur_node->right, cur_depth + 1);

        for (int i = 0; i < cur_depth; ++i) {
            cout << "|\t";
        }
        printf("|-------|%d[%d:%d)\n", cur_node->max_ind, cur_node->l, cur_node->r);

        print_node(cur_node->left, cur_depth + 1);
    }
};

int main() {
    srand(time(NULL));

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    tree t;
    //t.print_node(t.root, 0);

    int m, l, r;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> l >> r;
        cout << t.get_max_ind(--l, --r) + 1 << ' ';
    }
    return 0;
}
