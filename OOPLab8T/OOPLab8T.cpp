#include <iostream>
#include <vector>
#include <stdexcept>
#include <stack>
#include <cstring>

using namespace std;

template<typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template<>
void swapValues<char*>(char*& a, char*& b) {
    char* temp = a;
    a = b;
    b = temp;
}

template<typename T>
int partition(T arr[], int low, int high) {
    T pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swapValues(arr[i], arr[j]);
        }
    }
    swapValues(arr[i + 1], arr[high]);
    return (i + 1);
}

template<typename T>
void quickSort(T arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

template<>
int partition<char*>(char* arr[], int low, int high) {
    char* pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            swapValues(arr[i], arr[j]);
        }
    }
    swapValues(arr[i + 1], arr[high]);
    return (i + 1);
}

template<>
void quickSort<char*>(char* arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

template<typename T>
class Matrix {
private:
    vector<vector<T>> data;
    size_t rows;
    size_t cols;

public:
    Matrix() : rows(0), cols(0) {}

    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
        data.resize(rows, vector<T>(cols));
    }

    Matrix(const Matrix<T>& other) : rows(other.rows), cols(other.cols), data(other.data) {}

    Matrix<T>& operator=(const Matrix<T>& other) {
        if (this != &other) {
            rows = other.rows;
            cols = other.cols;
            data = other.data;
        }
        return *this;
    }

    vector<T>& operator[](size_t index) {
        if (index >= rows) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    const vector<T>& operator[](size_t index) const {
        if (index >= rows) {
            throw out_of_range("Index out of range");
        }
        return data[index];
    }

    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrices must have the same dimensions for addition");
        }

        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result[i][j] = data[i][j] + other[i][j];
            }
        }
        return result;
    }

    Matrix<T>& operator+=(const Matrix<T>& other) {
        if (rows != other.rows || cols != other.cols) {
            throw invalid_argument("Matrices must have the same dimensions for addition");
        }

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                data[i][j] += other[i][j];
            }
        }
        return *this;
    }

    size_t numRows() const {
        return rows;
    }

    size_t numCols() const {
        return cols;
    }

    ~Matrix() {}

};

template<typename T>
class BinaryTreeNode {
public:
    T data;
    BinaryTreeNode<T>* left;
    BinaryTreeNode<T>* right;

    BinaryTreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
};

template<typename T>
class BinaryTreeIterator {
private:
    stack<BinaryTreeNode<T>*> nodeStack;

public:
    BinaryTreeIterator(BinaryTreeNode<T>* root) {
        while (root != nullptr) {
            nodeStack.push(root);
            root = root->left;
        }
    }

    bool hasNext() const {
        return !nodeStack.empty();
    }

    T next() {
        if (!hasNext()) {
            throw runtime_error("No more elements in the tree");
        }

        BinaryTreeNode<T>* current = nodeStack.top();
        nodeStack.pop();

        if (current->right != nullptr) {
            BinaryTreeNode<T>* temp = current->right;
            while (temp != nullptr) {
                nodeStack.push(temp);
                temp = temp->left;
            }
        }

        return current->data;
    }
};

template<typename T>
class BinaryTree {
private:
    BinaryTreeNode<T>* root;

public:
    BinaryTree() : root(nullptr) {}

    void insert(const T& value) {
        root = insert(root, value);
    }

    void traverseInOrder() const {
        BinaryTreeIterator<T> it(root);
        while (it.hasNext()) {
            cout << it.next() << " ";
        }
        cout << endl;
    }

private:
    BinaryTreeNode<T>* insert(BinaryTreeNode<T>* node, const T& value) {
        if (node == nullptr) {
            return new BinaryTreeNode<T>(value);
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        }
        else {
            node->right = insert(node->right, value);
        }

        return node;
    }
};


int main() {
    int task;
    cout << "Enter task: ";
    cin >> task;
    switch (task)
    {
    case 1: {
        int x = 5, y = 10;
        cout << "Before swap: x = " << x << ", y = " << y << endl;
        swapValues(x, y);
        cout << "After swap: x = " << x << ", y = " << y << endl;

        char* str1 = (char*)"Hello";
        char* str2 = (char*)"World";
        cout << "Before swap: str1 = " << str1 << ", str2 = " << str2 << endl;
        swapValues(str1, str2);
        cout << "After swap: str1 = " << str1 << ", str2 = " << str2 << endl;

        break;
    }
    case 2: {
        Matrix<int> m1(2, 2);
        m1[0][0] = 1;
        m1[0][1] = 2;
        m1[1][0] = 3;
        m1[1][1] = 4;

        Matrix<int> m2(2, 2);
        m2[0][0] = 5;
        m2[0][1] = 6;
        m2[1][0] = 7;
        m2[1][1] = 8;

        Matrix<int> m3 = m1 + m2;

        cout << "Matrix m1:" << endl;
        for (size_t i = 0; i < m1.numRows(); ++i) {
            for (size_t j = 0; j < m1.numCols(); ++j) {
                cout << m1[i][j] << " ";
            }
            cout << endl;
        }

        cout << "Matrix m2:" << endl;
        for (size_t i = 0; i < m2.numRows(); ++i) {
            for (size_t j = 0; j < m2.numCols(); ++j) {
                cout << m2[i][j] << " ";
            }
            cout << endl;
        }

        cout << "Matrix m3 (m1 + m2):" << endl;
        for (size_t i = 0; i < m3.numRows(); ++i) {
            for (size_t j = 0; j < m3.numCols(); ++j) {
                cout << m3[i][j] << " ";
            }
            cout << endl;
        }
        break;
    }
    case 3: {
        BinaryTree<int> tree;
        tree.insert(5);
        tree.insert(3);
        tree.insert(8);
        tree.insert(2);
        tree.insert(4);
        tree.insert(7);
        tree.insert(9);

        cout << "In-order traversal of the binary tree:" << endl;
        tree.traverseInOrder();
        break;
    }
    default:
        cout << "Invalid task number." << endl;
        break;
    }
    return 0;
}
