#include <stdio.h>
#include <stdlib.h>

struct node_t {
	int data_t;
	struct node_t *left_child;
	struct node_t *right_child;
};

typedef struct node_t Node;
typedef Node *Node_P;
typedef Node_P *BinarySearchTree;

BinarySearchTree createBST() {
	BinarySearchTree bst = (Node_P *)malloc(sizeof(Node_P));
	*bst = NULL;

	return bst;
}

void destroy_tree(Node_P node_p) {
	if (node_p == NULL) {
		return;
	}

	destroy_tree(node_p->left_child);
	destroy_tree(node_p->right_child);

	node_p->left_child = NULL;
	node_p->right_child = NULL;
	free(node_p);
}

int destroyBST(BinarySearchTree bst) {
	if (*bst == NULL) {
		return -1;
	}

	destroy_tree(*bst);
	*bst = NULL;

	return 0;
}

void insertN(Node_P root, Node_P node_n) {
	if (node_n->data_t < root->data_t) {
		if (root->left_child == NULL)
			root->left_child = node_n;
		else
			insertN(root->left_child, node_n);
	}

	if (node_n->data_t >= root->data_t) {
		if (root->right_child == NULL)
			root->right_child = node_n;
		else
			insertN(root->right_child, node_n);
	}
}

int addBST(BinarySearchTree bst, int data) {
	Node_P node_p = (Node *)malloc(sizeof(Node));

	if (node_p) {
		node_p->data_t = data;
		node_p->left_child = NULL;
		node_p->right_child = NULL;
	}

	if (*bst == NULL) {
		*bst = node_p;

		return 0;
	}

	if (node_p) {
		insertN(*bst, node_p);

		return 0;
	}

	return -1;
}

Node_P preorderCOPY(Node_P root) {
	if (root == NULL) {
		return root;
	}

	Node_P temp = (Node *)malloc(sizeof(Node));

	temp->data_t = root->data_t;
	temp->left_child = preorderCOPY(root->left_child);
	temp->right_child = preorderCOPY(root->right_child);

	return temp;
}

BinarySearchTree copyBST(BinarySearchTree bst) {
	if (*bst == NULL) {
		printf("Binary search tree is empty\n");

		return NULL;
	}

	BinarySearchTree copy = createBST();
	*copy = preorderCOPY(*bst);

	return copy;
}

Node_P findBST(BinarySearchTree root, int key, Node_P *parent) {
	Node_P temp = *root;

	while (temp != NULL) {
		if (temp->data_t == key) {
			printf("Found element: %d\n", key);
			return temp;
		}

		*parent = temp;

		if (temp->data_t > key) {
			temp = temp->left_child;
		}
		else {
			temp = temp->right_child;
		}
	}

	printf("Element is not in the tree\n");
	return NULL;
}

int deleteBST(BinarySearchTree bst) {
	if (*bst) {
		printf("Binary search tree is empty\n");

		return -1;
	}

	return 0;

}

int find_min(Node_P node_p) {
	if (node_p->left_child == NULL) {
		return node_p->data_t;
	}

	return find_min(node_p->left_child);
}

int findMin(BinarySearchTree bst) {
	if (*bst == NULL) {
		printf("Binary search tree is empty\n");
		return NULL;
	}
	return find_min(*bst);
}

int find_max(Node_P node_p) {
	if (node_p->right_child == NULL) {
		return node_p->data_t;
	}

	return find_max(node_p->right_child);
}

int findMax(BinarySearchTree bst) {
	if (*bst == NULL) {
		printf("Binary search tree is empty\n");
		return NULL;
	}
	return find_max(*bst);
}

void printPre(Node_P node_P) {
	if (node_P) {
		printf("%d ", node_P->data_t);
		printPre(node_P->left_child);
		printPre(node_P->right_child);
	}
}

void printIn(Node_P node_P) {
	if (node_P) {
		printIn(node_P->left_child);
		printf("%d ", node_P->data_t);
		printIn(node_P->right_child);
	}
}

void printBST(BinarySearchTree bst) {
	if (*bst == NULL) {
		printf("Binary search tree is empty\n");

		return;
	}

	printPre(*bst);
	printf("\n");
}

void printOrderedList(BinarySearchTree bst) {
	if (*bst == NULL) {
		printf("Binary search tree is empty\n");

		return;
	}

	printIn(*bst);
	printf("\n");
}

int main() {
	BinarySearchTree bst = createBST();

	addBST(bst, 17);
	addBST(bst, 6);
	addBST(bst, 19);
	addBST(bst, 4);
	addBST(bst, 14);
	addBST(bst, 25);
	addBST(bst, 2);
	addBST(bst, 5);
	addBST(bst, 16);
	addBST(bst, 11);

	printf("Original binary search tree (preorder printing): ");
	printBST(bst);

	BinarySearchTree copy = copyBST(bst);

	printf("Copy of binary search tree (preorder printing): ");
	printBST(copy);

	printf("Original binary search tree (inorder printing): ");
	printOrderedList(bst);

	printf("\nFind element: 6\n");
	Node_P parent;
	findBST(bst, 6, &parent);
	printf("Parent of the element: %d\n", parent->data_t);

	printf("\nFinding minimum value\n");
	printf("Minimum: %d\n", findMin(bst));

	printf("\nFinding maximum value\n");
	printf("Maximum: %d\n", findMax(bst));

	printf("\nDeleting the binary search tree\n");
	destroyBST(bst);
	printf("Original binary search tree (preorder printing): ");
	printBST(bst);

	return 0;
}

