#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "tree.h"

// Memory alloted to a node
node* getnode()
{
	node* new_node;
	new_node = (node*)malloc(sizeof(node));
	return new_node;
}

// Calculates the heigth of node
int height(node* p)
{
	if(p == NULL) {
		return 0;
	} else {
		return p->height;
	}
}

// Returns the max value from of two integers
int max(int a, int b)
{
	return (a > b) ? a : b;
}

// Compute the balance factor of any node
int getBalance(node* p)
{
	if(p == NULL) {
		return 0;
	} else {
		return height(p->left) - height(p->right);
	}
}

// Rotates the node in left direction
node* rotateleft(node* x)
{
	node *y = x->right;
	node *T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(height(x->left), height(x->right))+1;
	y->height = max(height(y->left), height(y->right))+1;

	return y;
}

// Rotates the node in right direction
node* rotateright(node* y)
{
	node *x = y->left;
	node *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = max(height(y->left), height(y->right))+1;
	x->height = max(height(x->left), height(x->right))+1;

	return x;
}

// Insert a node in the tree and balance the whole tree to maintain the height of tree in order of O(log n).
node* insert(node* root, node* p)
{
	if (root == NULL)
		return p;

	if (p->matchpercentage < root->matchpercentage) {
		root->left = insert(root->left, p);
	} else if (p->matchpercentage > root->matchpercentage) {
		root->right = insert(root->right, p);
	} else if(p->matchpercentage == root->matchpercentage) {
		if(p->age < root->age) {
			root->left = insert(root->left, p);
		} else if(p->age > root->age) {
			root->right = insert(root->right, p);
		} else {
			return root;
		}
	} else {
		return root;
	}

	root->height = 1 + max(height(root->left),height(root->right));

	int balance = getBalance(root);

	if (balance > 1 && p->matchpercentage < root->left->matchpercentage)
		return rotateright(root);

	if (balance < -1 && p->matchpercentage > root->right->matchpercentage)
		return rotateleft(root);

	if (balance > 1 && p->matchpercentage > root->left->matchpercentage)
	{
		root->left = rotateleft(root->left);
		return rotateright(root);
	}

	if (balance < -1 && p->matchpercentage < root->right->matchpercentage)
	{
		root->right = rotateright(root->right);
		return rotateleft(root);
	}

	return root;
}

// Preorder representation of the tree
void preorder(node* root)
{
	if(root == NULL) {
		return;
	}
	printf("%s\n",root->name);
	preorder(root->left);
	preorder(root->right);
}

// Print the details of the person whose match percentage lies in the range left_bound & right_bound in increasing order
void printincreasing(node* root, int left_bound, int right_bound)
{
	if(root == NULL){
		return;
	}
	printincreasing(root->left,left_bound,right_bound);
	if(root->matchpercentage >= left_bound && root->matchpercentage <= right_bound) {
		print_node(root);
	}
	printincreasing(root->right,left_bound,right_bound);
}

// Print the details of the person whose match percentage lies in the range left_bound & right_bound in decreasing order
void printdecreasing(node* root, int left_bound, int right_bound)
{
	if(root == NULL) {
		return;
	}
	printdecreasing(root->right,left_bound,right_bound);
	if(root->matchpercentage >= left_bound && root->matchpercentage <= right_bound) {
		print_node(root);
	}
	printdecreasing(root->left,left_bound,right_bound);
}

// Print the node in indented format to make user - understandable
void print_node(node* person)
{
	int len = strlen(person->name);
	printf("%s",person->name);
	int i = 0;
	for(i = 0;i < 15 - len; i++){
		printf(" ");
	}
	for(i = 0;i < 8; i++){
		printf(" ");
	}
	printf("%d",person->matchpercentage);
	if(person->matchpercentage < 10){
		printf("               ");
	} else {
		printf("              ");
	}
	printf("%d\n",person->age);
}