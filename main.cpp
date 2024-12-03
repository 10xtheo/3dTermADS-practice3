#include <iostream>
#include <fstream>

#include "BinaryTree.h"
#include "AVLTree.h"

using namespace std;

int getInt()
{
    int a;
    cin >> a;
    while (cin.fail())
    {
      cin.clear();
      cin.ignore();
      cin >> a;
    }
    return a;
}

int main()
{
    string filePath = "/home/theo/projects/allgorithms2024/3dTermADS-practice3/file.txt";
    ifstream inFile(filePath, ios::in);

    if (!inFile)
    {
        cerr << "Error opening file for reading!" << endl;
        return 1;
    }

    string seq;
    string line;

    while (getline(inFile, line))
    {
        seq += line;
    }
    inFile.close(); // Close the file



    BinaryTree<int> bt(seq);
    cout << "simple binary tree:" << endl;
    bt.printTree(bt.root);

    cout << "avl tree:" << endl;
    AVLTree<int> avl(bt);
    avl.printTree(avl.root);

    cout << "pre order: ";
    avl.preOrderTraverse();
    cout << "in order: ";
    avl.inOrderTraverse();
    cout << "post order: ";
    avl.postOrderTraverse();
    cout << endl;

    while (true)
    {
        cout << "---TREES MENU---" << endl;
        cout << "0. print avl tree" << endl;
        cout << "1. insert node to avl tree" << endl;
        cout << "2. delete node from avl tree" << endl;
        cout << "3. search for key in avl tree" << endl;
        cout << "> ";
        int choice = getInt();

        switch (choice)
        {
            case 0:
            {
                cout << "avl tree: " << endl;
                avl.printTree(avl.root);
                cout << endl;
                break;
            }

            case 1:
            {
                cout << "key: ";
                int key = getInt();
                avl.insertNode(avl.root, key);
                cout << "new avl tree: " << endl;
                avl.printTree(avl.root);
                cout << endl;
                break;
            }

            case 2:
            {
                cout << "key: ";
                int key = getInt();
                avl.deleteNode(avl.root, key);
                cout << "new avl tree: " << endl;
                avl.printTree(avl.root);
                cout << endl;
                break;
            }
            case 3:
            {
                cout << "key: ";
                int key = getInt();

                if (avl.searchAVLNode(key, avl.root))
                    cout << key << " in tree " << endl;
                else
                    cout << key << " not in tree" << endl;
                break;
            }

            default:
            {
                cout << "wrong input" << endl;
                break;
            }
        }

    }
    return 0;
}
