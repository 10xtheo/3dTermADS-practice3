#include <iostream>
#include "BinaryTree.h"
using namespace std;

int main()
{
    string seq = "(8(9(5))(1))";
    BinaryTree<int> tree(seq);

    tree.traverse();
    return 0;
}
