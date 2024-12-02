#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

template<typename T>
struct Node
{
    T key;
    Node* left = nullptr;
    Node* right = nullptr;

    Node(T key)
    {
        this->key = key;
    }
};

template<typename T>
class BinaryTree
{
    Node<T>* root = nullptr;
public:
    BinaryTree();
    BinaryTree(string str); // (x (y z))
    ~BinaryTree();

    void insertNode(T key);
    void traverse(); // level order traverse
    void deleteTree(Node<T>* node);

};

template<typename T>
BinaryTree<T>::BinaryTree()
{

}

template<typename T>
BinaryTree<T>::BinaryTree(string str)
{
    vector<string> tokens;
    string current;

    for (char ch : str)
    {
        if (isdigit(ch))
        {
            current += ch;
        }
        else
        {
            if (!current.empty())
            {
                tokens.push_back(current);
                current.clear();
            }
            if (ch == '(' || ch == ')')
            {
                tokens.push_back(std::string(1, ch)); // Добавляем скобку в результат
            }
        }
    }

    if (!current.empty())
    {
        tokens.push_back(current);
    }

    stack<Node<T>*> stack;

    for (string token : tokens)
    {
        if (token == ")")
        {
            if (!stack.empty())
            {
                stack.pop();
            }
        }
        else if (token != "(")
        {
            int value = stoi(token);
            Node<int>* node = new Node<int>(value);

            if (!this->root)
            {
                this->root = node;
            }
            else if (!stack.empty())
            {
                Node<int>* parent = stack.top();
                if (!parent->left)
                {
                    parent->left = node;
                }
                else
                {
                    parent->right = node;
                }
            }
            stack.push(node);
        }
    }
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
    deleteTree(this->root);
}

template<typename T>
void BinaryTree<T>::insertNode(T key)
{
    Node<T>* newNode = new Node<T>(key);

    if (this->root == nullptr)
    {
        this->root = newNode;
        return;
    }

    queue<Node<T>*> q;
    q.push(this->root);

    while (!q.empty())
    {
        Node<T>* curr = q.front();
        q.pop();
        if (curr->left)
            q.push(curr->left);
        else
        {
            curr->left = newNode;
            return;
        }

        if (curr->right)
            q.push(curr->right);
        else
        {
            curr->right = newNode;
            return;
        }
    }
}

template<typename T>
void BinaryTree<T>::traverse()
{
    if (!this->root)
        return;
    queue<Node<T>*> q;
    q.push(this->root);
    while (!q.empty())
    {
        Node<T>* curr = q.front();
        q.pop();
        cout << curr->key << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

template<typename T>
void BinaryTree<T>::deleteTree(Node<T>* node)
{
    if (node == nullptr)
    {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    cout << "Deleting node with value: " << node->key << std::endl;
    delete node;
}

#endif // BINARYTREE_H
