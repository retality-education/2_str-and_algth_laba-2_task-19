
#include "Binary_Tree.h"
#include <stack>
using btree::ptrNODE;

void calculate_sum_and_count(ptrNODE node, int& sum, int& count) {
    if (node) {
        sum += node->info;
        count++;
        calculate_sum_and_count(node->left, sum, count);
        calculate_sum_and_count(node->right, sum, count);
    }
}

void remove_less_than_iterative(btree::BTREE& btree, ptrNODE root, double avg) {
    
    if (!btree.empty()) {
        std::stack<ptrNODE> stack1;
        stack1.push(root);
        ptrNODE temp1 = root;
        while (!stack1.empty()) {
            ptrNODE node = stack1.top();
            stack1.pop();
            if (node == root && node->info < avg)
            {
                ptrNODE temp = node->right;
                node->right = nullptr;
                btree.clear(node);
                btree.set_root(temp);
                root = btree.get_root();
                if (temp)
                    stack1.push(temp);
            }
            else if (node->info < avg) {
                ptrNODE temp = node->right;
                node->right = nullptr;
                btree.clear(temp1->left);
                temp1->left = temp;
                if (temp)
                    stack1.push(temp);
            }
            else
                if (node->left)
                {
                    if (node != temp1)
                        temp1 = node;
                    stack1.push(node->left);
                }
        }
    }
}

void remove_less_than_recursive(btree::BTREE& btree, ptrNODE& node, double avg) {
    if (!node) return;

    if (node->info < avg)
    {
        ptrNODE temp = node;
        node = node->right;
        temp->right = nullptr;
        btree.clear(temp);
        remove_less_than_recursive(btree, node, avg);
    }
    else
        remove_less_than_recursive(btree, node->left, avg);
}

int main() {
    btree::BTREE tree("test.txt"); // Предполагается, что данные находятся в файле data.txt

    std::cout << "Дерево до удаления:" << std::endl;
    tree.print();

    ptrNODE root = tree.get_root();

    int sum = 0;
    int count = 0;

    calculate_sum_and_count(root, sum, count);

    if (count != 0) {
        double avg_sum = static_cast<double>(sum) / count; // Вычисляем среднее арифметическое

        // remove_less_than_recursive(tree, root, avg_sum); // Рекурсивный вариант
        // tree.set_root(root);
        
        remove_less_than_iterative(tree, root, avg_sum); // Нерекурсивный вариант
    }
    

    std::cout << "Дерево после удаления:" << std::endl;
    tree.print();

    return 0;
}
