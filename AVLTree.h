#ifndef AVLTREE_H
#define AVLTREE_H

#include "BinaryTree.h"

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

template<typename T>
struct AVLNode
{
    T key;
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;

    int height = 1;
    int balance = 0;

    AVLNode(T value)
    {
        this->key = value;
    }

};

template<typename T>
class AVLTree
{
public:
    AVLNode<T>* root = nullptr;
public:
    AVLTree();
    AVLTree(const BinaryTree<T>& binaryTree);
    void inOrderInsert(Node<T>* node);
    ~AVLTree(); // done



    AVLNode<T>* getRoot(); // done
    void traverse(); // done
    void deleteTree(AVLNode<T>* node); // done
    void printTree(AVLNode<T>* node, int level = 0, bool isRight = false); // done

    AVLNode<T>* searchAVLNode(T key, AVLNode<T>* node); // done
    void inOrderTraverse(); // done
    void preOrderTraverse(); // done
    void postOrderTraverse(); // done

    int getHeight(AVLNode<T>* node); // done
    int getBalanceValue(AVLNode<T>* node); // done

    AVLNode<T>* rightRotate(AVLNode<T>* y); // done
    AVLNode<T>* leftRotate(AVLNode<T>* x); // done

    void insertNode(AVLNode<T>*& node, int key); // done

    AVLNode<T>* minValueNode(AVLNode<T>* node); // done
    void deleteNode(AVLNode<T>*& root, T key); // done

};

template<typename T>
AVLTree<T>::AVLTree(const BinaryTree<T>& binaryTree)
{
    inOrderInsert(binaryTree.root);
}

template<typename T>
void AVLTree<T>::inOrderInsert(Node<T>* node)
{
    if (node == nullptr) return;

    // Recursively insert left subtree
    inOrderInsert(node->left);

    // Insert current node into AVL tree
    insertNode(root, node->key);

    // Recursively insert right subtree
    inOrderInsert(node->right);
}



template<typename T>
AVLTree<T>::AVLTree()
{

}

template<typename T>
AVLTree<T>::~AVLTree()
{
    deleteTree(this->root);
}

template<typename T>
AVLNode<T>* AVLTree<T>::searchAVLNode(T key, AVLNode<T>* node)
{
    if (node == NULL) return NULL;

    if (key == node->key) return node;
    if (key < node->key) return searchAVLNode(key, node->left);
    else return searchAVLNode(key, node->right);

    return NULL;
}

template<typename T>
void AVLTree<T>::inOrderTraverse()
{
    stack<AVLNode<T>*> stack;
    AVLNode<T>* current = root;

    while (current != nullptr || !stack.empty())
    {
        // Перемещаемся до самого левого узла
        while (current != nullptr)
        {
            stack.push(current);
            current = current->left;
        }

        // Обрабатываем узел
        current = stack.top();
        stack.pop();
        cout << current->key << " ";

        // Переходим к правому поддереву
        current = current->right;
    }
    cout << endl;
}

template<typename T>
void AVLTree<T>::preOrderTraverse()
{

    if (this->root == nullptr) return;

    stack<AVLNode<T>*> stack;
    stack.push(this->root);

    while (!stack.empty())
    {
        AVLNode<T>* node = stack.top();
        stack.pop();
        cout << node->key << " ";

        // Сначала добавляем правого потомка, чтобы левый потомок был обработан первым
        if (node->right) stack.push(node->right);
        if (node->left) stack.push(node->left);
    }
    cout << endl;
}

template<typename T>
void AVLTree<T>::postOrderTraverse()
{
    if (this->root == nullptr) return;

    stack<AVLNode<T>*> stack;
    std::stack<int> output; // Для хранения результата
    stack.push(this->root);

    while (!stack.empty())
    {
        AVLNode<T>* node = stack.top();
        stack.pop();
        output.push(node->key); // Сохраняем узел в выходной стек

        // Сначала добавляем левого потомка, затем правого, чтобы правый обрабатывался первым
        if (node->left) stack.push(node->left);
        if (node->right) stack.push(node->right);
    }

    // Выводим результат в обратном порядке
    while (!output.empty())
    {
        cout << output.top() << " ";
        output.pop();
    }
    cout << endl;
}


template<typename T>
void AVLTree<T>::traverse()
{
    if (!this->root)
        return;
    queue<AVLNode<T>*> q;
    q.push(this->root);
    while (!q.empty())
    {
        AVLNode<T>* curr = q.front();
        q.pop();
        cout << curr->key << " ";
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    cout << endl;
}

template<typename T>
void AVLTree<T>::deleteTree(AVLNode<T>* node)
{
    if (node == nullptr)
    {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    // cout << "Deleting node with value: " << node->key << endl;
    delete node;
}

template<typename T>
void AVLTree<T>::printTree(AVLNode<T>* tree, int level, bool isRight)
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
AVLNode<T>* AVLTree<T>::getRoot()
{
    return this->root;
}

template <typename T>
int AVLTree<T>::getHeight(AVLNode<T>* node)
{
    return node ? node->height : 0;
}

template <typename T>
int AVLTree<T>::getBalanceValue(AVLNode<T>* node)
{
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

template <typename T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* y)
{
    AVLNode<T>* x = y->left;
    AVLNode<T>* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x; // Return new root
}

template <typename T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* x)
{
    AVLNode<T>* y = x->right;
    AVLNode<T>* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y; // Return new root
}

template <typename T>
void AVLTree<T>::insertNode(AVLNode<T>*& node, int key)
{
    // Perform the normal BST insertion
    if (!node)
    {
        node = new AVLNode<T>(key);
        return;
    }

    if (key < node->key)
        insertNode(node->left, key);
    else if (key > node->key)
        insertNode(node->right, key);
    else // Duplicate keys are not allowed in the AVL tree
        return;

    // Update height of this ancestor node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalanceValue(node);

    // If this node becomes unbalanced, then there are 4 cases

    // left subtree of left child
    if (balance > 1 && key < node->left->key)
        node = rightRotate(node);

    // Right subtree of right child
    else if (balance < -1 && key > node->right->key)
        node = leftRotate(node);

    // Right subtree of Left child
    else if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        node = rightRotate(node);
    }

    // Left subtree of right child
    else if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        node = leftRotate(node);
    }
}

template <typename T>
AVLNode<T>* AVLTree<T>::minValueNode(AVLNode<T>* node)
{
    AVLNode<T>* curr = node;

       while (curr && curr->left != nullptr)
           curr = curr->left;

       return curr;
}

template <typename T>
void AVLTree<T>::deleteNode(AVLNode<T>*& root, T key)
{
    // STEP 1: PERFORM STANDARD BST DELETE
    if (root == nullptr) return;

    if (key < root->key)
        deleteNode(root->left, key);

    else if (key > root->key)
        deleteNode(root->right, key);

    else
    {
        // Node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr))
        {
            AVLNode<T> *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            delete temp; // Use delete instead of free for C++
        }
        else
        {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            AVLNode<T>* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr) return;

    // STEP 2: UPDATE HEIGHT OF THIS ANCESTOR NODE
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;


    // STEP 3: GET THE BALANCE FACTOR OF THIS ANCESTOR NODE TO CHECK WHETHER
    // THIS NODE BECAME UNBALANCED
    int balance = getBalanceValue(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalanceValue(root->left) >= 0)
        root = rightRotate(root);

    // Left Right Case
    else if (balance > 1 && getBalanceValue(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    }

    // Right Right Case
    else if (balance < -1 && getBalanceValue(root->right) <= 0)
        root = leftRotate(root);

    // Right Left Case
    else if (balance < -1 && getBalanceValue(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }
}
#endif // AVLTREE_H
