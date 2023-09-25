#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <deque>

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
    Node* left;
    Node* right;
};

Node* newNode(int item) {
    Node* temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(Node* root, int arr[], int& i) {
    if (root != NULL) {
        inorder(root->left, arr, i);
        arr[i++] = root->key;
        inorder(root->right, arr, i);
    }
}

void treesort(int arr[], int n) {
    Node* root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    int i = 0;
    inorder(root, arr, i);
}

int main() {
    int n = 100000;
    int* arr = new int[n];
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> uni(0, n);
    for (int i = 0; i < n; i++)
        arr[i] = uni(rng);

    auto start = chrono::steady_clock::now();
    heapsort(arr, n);
    auto end = chrono::steady_clock::now();
    cout << "Heapsort took "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << "ms.\n";

    start = chrono::steady_clock::now();
    treesort(arr, n);
    end = chrono::steady_clock::now();
    cout << "Treesort took "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << "ms.\n";

    delete[] arr;
    return 0;
}