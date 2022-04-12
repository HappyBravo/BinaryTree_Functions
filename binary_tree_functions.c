// #include<stdio.h>
// #include<stdlib.h>
#include "python_function.c" // FROM "https://github.com/HappyBravo/python_functions_in_C"

struct btElement { // DEFINING ELEMENT FOR BINARY TREE
  int data;
  struct btElement *left;
  struct btElement *right;
};

typedef struct btElement btNode;
btNode *root = NULL;

/*
int height(btNode *root){
  if(!(isExternal(root))) return 0;
  
  return height(root);
}
*/

int isEmpty(btNode *root)
{
  if(!(root))
    return 1;
  return 0;
}

int isRoot(btNode *root){
  if (root){
    if ((root->right == NULL) && (root->left == NULL))
      return 1;
    return 0;
  }
}

node *children(btNode *root, int d){
  node *listHead = NULL;
  if (root){
    if (d == root->data){
      if (root->left != NULL){
        listHead = python_append(listHead, root->left->data);
      }
      if (root->right != NULL){
        listHead = python_append(listHead, root->right->data);
      }
      return listHead;
    }
    listHead = children(root->left, d);
    listHead = children(root->right, d);
    // return (isInternal(root->left, d)+isInternal(root->right, d));
  }
  return listHead;
}

int isInternal(btNode *root, int d){
  if (root){
    if (d == root->data){
      if ((root->right != NULL) || (root->left != NULL)){
        return 1;
      }
    }
    return (isInternal(root->left, d)+isInternal(root->right, d));
  }
  return 0;
}

int isExternal(btNode *root, int d){
  if (root){
    if (d == root->data){
      if ((root->right == NULL) || (root->left == NULL)){
        return 1;
      }
    }
    return (isExternal(root->left, d)+isExternal(root->right, d));
  }
  return 0;
}

btNode *makeNode(int d) {
  btNode *new_node;
  new_node = malloc(sizeof(btNode));
  new_node->data = d;
  new_node->left = new_node->right = NULL;
  return new_node;
}

// %%%%%%%%%% RECURSIVE FUNCTIONS %%%%%%%%%%%%%

void bt_inorder(btNode *root) {
  // LEFT - DATA - RIGHT
  if (root) {
    bt_inorder(root->left);
    printf("%d\t", root->data);
    bt_inorder(root->right);
  }
}

void bt_preorder(btNode *root) {
  // DATA - LEFT - RIGHT
  if (root) {
    printf("%d\t", root->data);
    bt_preorder(root->left);
    bt_preorder(root->right);
  }
}

void bt_postorder(btNode *root){
  // LEFT - RIGHT - DATA
  if (root) {
    bt_postorder(root->left);
    bt_postorder(root->right);
    printf("%d\t", root->data);
  }  
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


// MAKING NODE AND INSERING ELEMENTS IN LEFT OR RIGHT
btNode *createNode(int value)
{
    btNode *newNode = malloc(sizeof(btNode));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
};

btNode *insertLeft(btNode *root, int d){
  root->left = createNode(d);
  return root->left;
}

btNode *insertRight(btNode *root, int d){
  root->right = createNode(d);
  return root->right;
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void display(btNode *ptr, int level)
{
    int i;
    if(ptr != NULL)
    {
      display(ptr->right, level+1);
      for(i = 0; i<level; i++)
        printf("\t");
      printf("%d\n", ptr->data);
      display(ptr->left, level+1);
    }
}

// %%%%%%%%%% MY TREE DISPLAY FUNCTION %%%%%%%%%%%%%%

int _print_t(btNode *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->data);

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

void print_t(btNode *tree)
{
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
