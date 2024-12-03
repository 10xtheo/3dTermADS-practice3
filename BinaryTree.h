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
public:
    Node<T>* root = nullptr;
public:
    BinaryTree();
    BinaryTree(string str); // (x (y z))
    ~BinaryTree();

    Node<T>* getRoot();
    void insertNode(T key);
    void traverse(); // level order traverse
    void preOrderTraverse();
    void deleteTree(Node<T>* node);
    void printTree(Node<T>* node, int level = 0, bool isRight = false);

};

template<typename T>
BinaryTree<T>::BinaryTree()
{

}

template<typename T>
BinaryTree<T>::BinaryTree(string str)
{
    // Check for empty input
    if (str.empty()) {
        throw std::invalid_argument("Input string is empty");
    }

    vector<string> tokens;
    string current;
    int openParentheses = 0;

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
            if (ch == '(')
            {
                tokens.push_back("(");
                openParentheses++;
            }
            else if (ch == ')')
            {
                tokens.push_back(")");
                if (openParentheses == 0) {
                    throw std::invalid_argument("Unmatched closing parenthesis found");
                }
                openParentheses--;
            }
            else if (!isspace(ch)) // ignore whitespace
            {
                throw std::invalid_argument("Invalid character found in input");
            }
        }
    }
    // add the last number if exists
    if (!current.empty())
    {
        tokens.push_back(current);
    }
    // final check for unmatched parentheses
    if (openParentheses != 0) {
        throw std::invalid_argument("Unmatched opening parenthesis found");
    }


    stack<Node<T>*> stack;

    for (const string& token : tokens)
    {
        if (token == ")")
        {
            if (!stack.empty())
            {
                stack.pop();
            }
            else
            {
                throw std::invalid_argument("Unmatched closing parenthesis found");
            }
        }
        else if (token == "(")
        {
            // do nothing - just a marker for the start of a subtree
        }
        else
        {
            int value = stoi(token);
            Node<T>* node = new Node<T>(value);

            if (!this->root)
            {
                this->root = node;
            }
            else if (!stack.empty())
            {
                Node<T>* parent = stack.top();
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

    // final check to ensure the stack is empty
    if (!stack.empty())
    {
         throw std::invalid_argument("Stack isn't empty at the end, indicating an incomplete tree structure");
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

    // cout << "deleting node with value: " << node->key << endl;
    delete node;
}

template<typename T>
void BinaryTree<T>::printTree(Node<T>* tree, int level, bool isRight)
{
  if (tree == NULL) return;
  printTree(tree->right, level + 1, true);

  if (!level) cout << "-->";
  else cout << "   ";

  for (int i = 0; i < level; i++)
  {
    if (i + 1 == level) isRight ? cout << ".-->" : cout << "`-->";
    else cout << "    ";
  }

  cout << tree->key << "\n";

  printTree(tree->left, level + 1);
}

template<typename T>
Node<T>* BinaryTree<T>::getRoot()
{
    return this->root;
}

template<typename T>
void BinaryTree<T>::preOrderTraverse()
{
    if (root == nullptr) return;

    cout << root->data << " ";
    preOrder(root->left);
    preOrder(root->right);
}

#endif // BINARYTREE_H
