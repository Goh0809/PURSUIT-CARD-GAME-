#pragma once
#include <iostream> 
#include <string>

using namespace std;

struct StudentNode {
	int ranking;
	string studentName;
	StudentNode* left;
	StudentNode* right;
};

class WinnerBinarySearchTree {
	StudentNode* root;
	int size;

public:
	WinnerBinarySearchTree() {
		size = 0;
		root = nullptr;
	}

	~WinnerBinarySearchTree() {

	}

	void insert(string studentName, int ranking) {
		root = insert(root, studentName, ranking);
	}

	bool find(string studentName) {
		StudentNode* result = find(root, studentName);
		if (result != nullptr) {
			cout << "Congratulations! " << result->studentName << " Your Ranking is Number " << result->ranking + 1 << endl << endl;
			return true;
		}
		cout << "You are not Top 30 winners" << endl << endl;
		return false;
	}

	int height() {
		return height(root);
	}


private:
	// insert
	StudentNode* insert(StudentNode* root, string studentName, int ranking) {
		// create a new student node
		StudentNode* newStudent = new StudentNode;
		newStudent->studentName = studentName;
		newStudent->ranking = ranking;
		newStudent->left = nullptr;
		newStudent->right = nullptr;

		if (root == nullptr) {
			root = newStudent;
		}
		else {
			StudentNode* parent = nullptr;
			StudentNode* current = root;
			while (current != nullptr)
			{
				if (current->studentName == studentName) {
					return root;
				}
				parent = current;
				if (current->studentName < studentName) {
					current = current->right;
				}
				else
					current = current->left;
			}

			if (parent->studentName > studentName) {
				parent->left = newStudent;
			}
			else {
				parent->right = newStudent;
			}
		}
		size++;
		return root;
	}

	// find
	StudentNode* find(StudentNode* root, string studentName) {
		if (root == nullptr) {
			return nullptr;
		}
		else if (root->studentName == studentName) {
			return root;
		}
		else if (root->studentName > studentName) {
			return find(root->left, studentName);
		}
		else {
			return find(root->right, studentName);
		}
	}

	// calculate the height
	int height(StudentNode* root) {
		if (root == nullptr) {
			return 0;
		}
		else {
			return 1 + max(height(root->left), height(root->right));
		}
	}

};

//https://www.digitalocean.com/community/tutorials/level-order-traversal-in-a-binary-tree