#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

void heapify(int arr[], int n, int i) {
    int largest = i;  // Initialize largest as root
    int l = 2 * i + 1;  // Left child index
    int r = 2 * i + 2;  // Right child index

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}

void heapsort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);

        
        heapify(arr, i, 0);
    }
}


struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
};

Node* newNode(int item) {
    Node* temp = new Node;
    temp->key = item;
    temp->height = 1;
    temp->left = temp->right = NULL;
    return temp;
}

int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

   
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    
    y->left = x;
    x->right = T2;

    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int key) {
   
if (node == NULL)
return newNode(key);

if (key < node->key)
    node->left = insert(node->left, key);
else if



else
    return node;


node->height = 1 + max(height(node->left), height(node->right));


int balance = getBalance(node);




if (balance > 1 && key < node->left->key)
    return rightRotate(node);


if (balance < -1 && key > node->right->key)
return leftRotate(node);


if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
}


if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
}


return node;
}

void inorder(Node* root, int arr[], int& index) {
    if (root != NULL) {
        inorder(root->left, arr, index);
        arr[index++] = root->key;
        inorder(root->right, arr, index);
    }
}

void treesort(int arr[], int n) {
    Node* root = NULL;

   
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    
    int index = 0;
    inorder(root, arr, index);

}

int main() {
   
    const int n = 100000;
    int arr[n];
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(1, n);
    for (int i = 0; i < n; i++)
        arr[i] = distr(eng);

   
    auto start_heap = chrono::steady_clock::now();
    heapsort(arr, n);
    auto end_heap = chrono::steady_clock::now();
    cout << "Heapsort time: " << chrono::duration_cast<chrono::microseconds>(end_heap - start_heap).count() << " microseconds\n";

   
    for (int i = 0; i < n; i++)
        arr[i] = distr(eng);

   
    auto start_tree = chrono::steady_clock::now();
    treesort(arr, n);
    auto end_tree = chrono::steady_clock::now();
    cout << "Treesort time: " << chrono::duration_cast<chrono::microseconds>(end_tree - start_tree).count() << " microseconds\n";

    return 0;


}
