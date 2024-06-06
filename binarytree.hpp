#pragma once
#include <iostream>

using namespace std;

struct node {
	string studentName;
	node* left;
	node* right;
};

class BinaryTree {
	node* root;
	int size;

public:
	BinaryTree() {
		root = nullptr;
		size = 0;
	}

	~BinaryTree() {

	}

	void buildTree(string* student) {
		root = insert(student, 0);
	}

	node* insert(string* a, int currentindex) {
		node* temp = nullptr;
		if (a[currentindex] != "") {
			temp = new node;
			temp->studentName = a[currentindex];
			temp->left = insert(a, 2 * currentindex + 1);
			temp->left = insert(a, 2 * currentindex + 2);
			size++;
		}
		return temp;
	}

    int height(node* root) {
        if (root == NULL)
            return 0;
        return max(height(root->left), height(root->right)) + 1;
    }

    int getcol(int h) {
        if (h == 1)
            return 1;
        return getcol(h - 1) + getcol(h - 1) + 1;
    }

    void printTree(string** M, node* root, int col, int row, int height) {
        if (root == NULL)
            return;
        M[row][col] = root->studentName;
        printTree(M, root->left, col - pow(2, height - 2), row + 1, height - 1);
        printTree(M, root->right, col + pow(2, height - 2), row + 1, height - 1);
    }

    void TreePrinter() {
        int h = height(root);
        int col = getcol(h);
        string** M = new string* [h];
        for (int i = 0; i < h; i++) {
            M[i] = new string[col];
        }
        printTree(M, root, col / 2, 0, h);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < col; j++) {
                if (M[i][j] == "")
                    cout << " " << " ";
                else
                    cout << M[i][j] << " ";
            }
            cout << endl;
        }
    }

};