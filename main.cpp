#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


struct Node {

	char value[50] = "";
	int key = 0;

	Node* left = nullptr;
	Node* right = nullptr;
};

struct Pair {

	Node* first;
	Node* second;
};

Pair		_interFindNode(Node**, int);
void		_insertNode(Node**, int, const char*);
const char* find(Node**, int);
void		insert(Node** head, int, const char*);
bool		remove(Node** head, int);
void		drop(Node**);
void		printTree(Node*, int = 1);

int main()
{
	srand(time(NULL));

	Node* head = nullptr;
	const int n = 10;
	char str[50];
	for (int i = 0; i < n; i++)
	{
		snprintf(str, sizeof(str), "%i", rand() % 100);
		insert(&head, rand() % 100, str);
	}
	printTree(head);
	drop(&head);
	return 0;
}

Pair _interFindNode(Node** head, int key)
{
	Node* child = *head;
	Node* parent = nullptr;

	while (child && child->key != key)
	{
		parent = child;
		if (child->key > key)
			child = child->left;
		else
			child = child->right;
	}

	return Pair{ parent, child };
}

void _insertNode(Node** head, int key, const char* value)
{
	*head = new Node;
	strcpy((*head)->value, value);
	(*head)->key = key;
}

const char* find(Node** head, int key)
{
	Pair point = _interFindNode(head, key);
	Node* child = point.second;

	if (!child)
		return "";

	return child->value;
}

void insert(Node** head, int key, const char* value)
{
	if (!*head)
	{
		*head = new Node;
		strcpy((*head)->value, value);
		(*head)->key = key;

		return;
	}

	Pair point = _interFindNode(head, key);
	Node* parent = point.first;
	Node* child = point.second;

	if (child)
	{
		strcpy(child->value, value);
		return;
	}

	if (parent->key > key)
		_insertNode(&parent->left, key, value);
	else
		_insertNode(&parent->right, key, value);
}

bool remove(Node** head, int key)
{
	Pair point = _interFindNode(head, key);
	Node* rm_node = point.second;

	if (!rm_node)
		return false;

	Node* left_ptr = rm_node->left;
	Node* right_ptr = rm_node->right;
	while (left_ptr)
	{
		Node* temp = left_ptr->right;
		left_ptr->right = right_ptr;
		right_ptr = temp;
		left_ptr = left_ptr->left;
	}
	return true;
}

void drop(Node** head)
{
	if (!(*head))
		return;

	drop(&(*head)->left);
	drop(&(*head)->right);
	delete* head;
}

void printTree(Node* head, int cur_depth)
{
	if (!head)
		return;

	printTree(head->left, cur_depth++);
	printf("%i\t: %s\n", head->key, head->value);
	printTree(head->right, cur_depth++);
}