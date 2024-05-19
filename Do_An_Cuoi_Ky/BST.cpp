#include <bits/stdc++.h>

using namespace std;

class Node {
    /*
        Cau truc cua cac nut tren cay tim kiem nhi phan BST

        Thong tin :
            data (int)      : la gia tri cua nut
            left (Node)     : mo ta nut con trai cua nut hien tai
            right (Node)    : mo ta nut con phai cua nut hien tai
    */

    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

class Solution {
    public:

  		Node* insert(Node* root, int data) {
  		    /*
                Ham them mot nut mang gia tri data vao cay BST

                Thong tin :
                    root (Node) : Nut dang xet
                    data (int)     : Gia tri data can them vao

                Thao tac :
                    Neu nut hien tai rong, tao nut moi mang gia tri data.

                    Neu data nho hon gia tri nut hien tai thi xet nut con trai.

                    Neu data lon hon gia tri nut hien tai thi xet nut con phai.

                Tra ve nut hien tai
            */

            if(root == NULL) {
                return new Node(data);
            } else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->left, data);
                    root->left = cur;
                } else {
                    cur = insert(root->right, data);
                    root->right = cur;
               }

               return root;
           }
        }

        int height(Node* root) {
            /*
                Ham tinh do cao cua cay

                Thong tin :
                    root (Node) : Mo ta nut hien tai

                Thuc hien xet nut trai, nut phai

                Tra ve do cao cua cay con cua root
            */
            if (root == NULL) return 0;
            int res = 0;
            res = max(res, height(root->left) + 1);
            res = max(res, height(root->right) + 1);
            return res;
        }

};

int main() {

    Solution myTree;
    Node* root = NULL;

    int t;
    int data;

    std::cin >> t;
    // so nut t

    while(t-- > 0) {
        cin >> data;
        root = myTree.insert(root, data);
    }

    int height = myTree.height(root);
    // do cao cua cay

  	cout << height;

    return 0;
}



