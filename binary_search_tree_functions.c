#include "binary_tree_functions.c"


int bst_isPresent(btNode *root, int d){
    if (!(root)) return 0;
    if (root->data == d) return 1;
    if (root->data > d) return bst_isPresent(root->left, d);
    if (root->data < d) return bst_isPresent(root->right, d);

}

btNode *bst_insert_main(btNode *root, int d){
    if (!(root)) return createNode(d);
    else{
        if (d < root->data) root->left = bst_insert_main(root->left, d);
        else{
            if (d > root->data) root->right = bst_insert_main(root->right, d);
        }
    }
    return root;
}

btNode *bst_insert(btNode *root, int d){
    if (isPresent(root, d)) {
        printf("\n\n>>> %d is already presesnt !\n\n");
        return 0;
    }
    return bst_insert_main(root, d);
}

int isBST(btNode *root){
    if(!(root)) return 1;
    if (root->left){
        if (root->left->data > root->data) return 0;
    }
    if (root->right){
        if (root->right->data < root->data) return 0;
    }
    if ( !(isBST(root->left)) + !(isBST(root->right)) ) return 0;
    return 1;
}

int bst_findMax(btNode *root){
    if (!(root)) return 0;
    if (!(root->right)) return root->data;
    else bst_findMax(root->right);
}

int bst_findMin(btNode *root){
    if (!(root)) return 100000;
    if (!(root->left)) return root->data;
    else bst_findMin(root->left);
}

int bst_inorderSuccessor(btNode *root, int d){
    if (!(root)) return 0;//NULL;
    if (root->data == d) {
        if(root->right) {
        return bst_findMin(root->right);
        }
        // else if(root->left){
        //     return bst_findMax(root->left);
        // }
        return root->data;
    }
    if (d < root->data) {
        return bst_inorderSuccessor(root->left, d);
    }
    else{
        if (d > root->data) {
            return bst_inorderSuccessor(root->right, d);
        }
    }
}

int bst_inorderPredecessor(btNode *root, int d){
    if (!(root)) return 0;//NULL;
    if (root->data == d) {
        if(root->left){
            return bst_findMax(root->left);
        }
        return root->data;
    }
    if (d < root->data) {
        return bst_inorderPredecessor(root->left, d);
    }
    else{
        if (d > root->data) {
            return bst_inorderPredecessor(root->right, d);
        }
    }
}

btNode *bst_minValAddress(btNode *root){
    btNode *temp = NULL;
    temp = root;
    while(temp->left){
        temp = temp->left;
    }
    return temp;
}

btNode *bst_delete_main(btNode *root, int d){
    if (d<root->data) root->left = bst_delete_main(root->left, d);
    else if (d>root->data) root->right = bst_delete_main(root->right, d);
    else{
        btNode *temp = NULL;
        if (!(root->left)){
            temp = root->right;
            root = NULL;
            return temp;
        }
        else if (!(root->right)){
            temp = root->left;
            root = NULL;
            return temp;
        }
        temp = bst_minValAddress(root->right);
        root->data = temp->data;
        root->right = bst_delete_main(root->right, temp->data);
    }
    return root;
}

btNode *bst_delete(btNode *root, int d){
    if(!(root)) return root;
    if (!(isPresent(root, d))) return root;
    return bst_delete_main(root, d); 
}
