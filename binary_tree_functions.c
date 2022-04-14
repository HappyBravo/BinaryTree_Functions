// #include<stdio.h>
// #include<stdlib.h>
// #include <stdarg.h>
#include "python_function.c" // FROM "https://github.com/HappyBravo/python_functions_in_C"


struct btElement { // DEFINING ELEMENT FOR BINARY TREE
  int data;
  struct btElement *left;
  struct btElement *right;
};

typedef struct btElement btNode;
btNode *root = NULL;

int btheight(btNode *root){
  int left = 1;
  int right = 1;
  
  if(!(root)) return 0;

  if (root->left){
    left = 1 + btheight(root->left);
  }
  if (root->right){
    right = 1 + btheight(root->right);
  }
  if (right>left) return right;
  return left;

  // return ;
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

int isPresent(btNode *root, int dat){
  if (isInternal(root, dat)+isExternal(root, dat)) return 1;
  return 0;
}


int bt_findMax_main(btNode *root){
  int left;
  int Max = 0;
  int right;
  if (root) {
    Max = root->data;
    left = bt_findMax_main(root->left);
    right = bt_findMax_main(root->right);

    if(Max <= left) Max = left;
    else if (Max <= right) Max = right;
  }
  return Max;
}

int bt_findMax(btNode *root) {
    if (!(root)) return -1;
    return bt_findMax_main(root);
}


int bt_findMin_main(btNode *root){
  int left;
  int Min;
  int right;
  if (root) {
    Min = root->data;
    left = bt_findMin_main(root->left);
    right = bt_findMin_main(root->right);

    if(Min >= left) Min = left;
    else if (Min >= right) Min = right;
  }
  return Min;
}

int bt_findMin(btNode *root) {
    if (!(root)) return -1;
    return bt_findMin_main(root);
}




int btNode_level_main(btNode *root, int dat){
  int level = 0;
  // int d = 0;

  if (!(root)) return 0;

  if (root->data == dat){
    return 1;
  }

  if (root->left){
    level = btNode_level_main(root->left, dat);
    if(level) return level + 1;
  }
  if (root->right){
    level = btNode_level_main(root->right, dat);
    if(level) return level + 1;
  }
  return level;
}

int btNode_level(btNode *root, int dat){
  if (isPresent(root, dat)){
    return btNode_level_main(root, dat)-1;
  }
  return -1;
}

int bt_parent_main(btNode *root, int d){
  if (!(root)) return 0;
  int p = 0;
  
  if (root->left){
    if (root->left->data == d) return root->data;
    p = bt_parent_main(root->left, d);
    if (p) return p;
  }
  if (root->right){
    if(root->right->data == d) return root->data;
    p = bt_parent_main(root->right, d);
    if (p) return p;
  }
}

int bt_parent(btNode *root, int d){
  if (isPresent(root, d)) return bt_parent_main(root, d);
  return -1;
}

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

node *bt_children_main(btNode *root, int d){
  node *listHead = create_list(0);
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
    listHead = bt_children_main(root->left, d);
    if (listHead) return listHead;
    listHead = bt_children_main(root->right, d);
  }
  return listHead;
}

node *bt_children(btNode *root, int d){
  if (isPresent(root, d)) return bt_children_main(root, d);
  return create_list(0);
}

btNode *makeNode(int d) {
  btNode *new_node;
  new_node = malloc(sizeof(btNode));
  new_node->data = d;
  new_node->left = new_node->right = NULL;
  return new_node;
}

// %%%%%%%%%% NON-RECURSIVE TRANVERSAL FUNCTIONS %%%%%%%%%%%%%

void bt_inorder_nonrec(btNode *root){ 
  // Morris Inorder Traversal

  btNode *temp = root;
  btNode *p ;
  while(temp){
    if (!(temp->left)){
      printf("%d\t", temp->data);
      temp = temp->right;
    }
    else{
      p = temp->left;
      while( (p->right) && (p->right != temp)){
        p = p->right;
      }
      if (!(p->right)){
        p->right = temp;
        temp = temp->left;
      }
      else{
        p->right = NULL;
        printf("%d\t", temp->data);
        temp = temp->right;
      }
    }
  }
}

void bt_preorder_nonrec(btNode *root){
  // Morris Preorder Traversal

  btNode *temp = root;
  btNode *p;
  while(temp){
    if (!(temp->left)){
      printf("%d\t", temp->data);
      temp = temp->right;
    }
    else {
      p = temp->left;
      while( (p->right) && (p->right != temp) ){
        p = p->right;
      }
      if(p->right == temp){
        p->right = NULL;
        temp = temp->right;
      }
      else{
        printf("%d\t", temp->data);
        p->right = temp;
        temp = temp->left;
      }
    }
  }
}

node *bt_postorder_nonrec_main(btNode *root){
  // similar to Morris preorder Traversal, but swapped left and right

  btNode *temp = root;
  node *post = create_list(0);
  btNode *p;
  while(temp){
    if(!(temp->right)){
      // printf("%d\t", temp->data);
      post = python_append(post, temp->data);
      temp = temp->left;
    }
    else{
      p = temp->right;
      while ((p->left) && (p->left != temp)){
        p = p->left;
      }
      if(!(p->left)){
        // printf("%d\t", temp->data);
        post = python_append(post, temp->data);
        p->left = temp;
        temp = temp->right;
      }
      else{
        p->left = NULL;
        temp = temp->left;
      }
    }
  }
  return post;
  // printf("");
}

void bt_postorder_nonrec(btNode *root){
  node *temp = NULL;
  temp = bt_postorder_nonrec_main(root);
  temp = python_reverse(temp);
  while(temp){
    printf("%d\t", temp->data);
    temp = temp->next;
  }
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


// %%%%%%%%%% RECURSIVE TRANVERSAL FUNCTIONS %%%%%%%%%%%%%

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

void bt_levelorder_main(btNode *root, int l){
  if(!(root)) return;
  if (l == 1) printf("%d\t", root->data);
  else if (l>1){
    bt_levelorder_main(root->left, l-1);
    bt_levelorder_main(root->right, l-1);
  }
}

void bt_levelorder(btNode *root){
  int h = btheight(root);
  for (int i = 1; i<=h; i++){
    bt_levelorder_main(root, i);
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

btNode *bt_deepestNodeAddress(btNode *root, int tree_height){
  int h = tree_height;
  btNode *res = NULL;
  if(!(root)) return root;
  if(h == 1) {
    printf("%d", root->data);
    return root;
  }
  else if (h>1){
    res = bt_deepestNodeAddress(root->left, h-1);
    if(res) return res;
    res = bt_deepestNodeAddress(root->right, h-1);
    if(res) return res;
  }
  // return root;

}

btNode *bt_deleteNode_main(btNode *root, int d){
  btNode *temp = root;
  // if (!(root->left) + !(root->right)){
  //   if (root->data == d) return NULL;
  //   else return root;
  // }
  // btNode *p = NULL;
  // btNode *addr = NULL;
  // while(!p){
  //   temp = root;
  //   if (temp->data == d) addr = temp;
  //   if (temp->left) p = temp->left;
  //   if ()

  // }
  
  if (temp->data == d){
    if (!(temp->left)){
      temp = root->right;
      root = NULL;
      return temp;
    }
    else if (!(temp->left)){
      temp = root->right;
      root = NULL;
      return temp;
    }
    else{
      temp = bt_deepestNodeAddress(root->right, btheight(root->right));
      root->data = temp->data;
      root->right = bt_deleteNode_main(root->right, temp->data);
      // temp = root->left;
    }

  }
  if (root->right) root->right = bt_deleteNode_main(root->right, d);
  if (root->left) root->left = bt_deleteNode_main(root->left, d);

  return root;
}

btNode *bt_deleteNode(btNode *root, int d){
  if (!(root)) return root;
  if (!(isPresent(root, d))) return root;
  return bt_deleteNode_main(root, d);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*
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
*/

// %%%%%%%%%% TREE DISPLAY FUNCTION %%%%%%%%%%%%%%

int _print_t(btNode *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    // char s[20][255];
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

    } 
    else if (depth && !is_left) {

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
    int h = btheight(tree)+6;
    char s[h][255];

    for (int i = 0; i < h; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < h; i++)
        printf("%s\n", s[i]);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
