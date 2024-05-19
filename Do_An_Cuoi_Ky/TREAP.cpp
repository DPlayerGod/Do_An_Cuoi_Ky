#include <bits/stdc++.h>

using namespace std;

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

int Rand() {
    /*
        Ham de sinh cac so ngau nhien trong doan [l, r]

        Thong tin :
            l (int) : 1
            r (int) : 10^9

        Tra ve so duoc sinh ngau nhien trong doan [l, r].
    */
    int l = 1, r = 1000000000;

    return l + rd() * 1LL * rd() % (r - l + 1);
}


class Node {
    /*
        Cau truc cua cac nut tren cay tim kiem nhi phan ngau nhien Treap

        Thong tin :
            data (int)      : la gia tri cua nut
            priority (int)  : gia tri cua khoa Heap tren nut do, duoc sinh ngau nhien bang ham Rand()
            left (Node)     : mo ta nut con trai cua nut hien tai
            right (Node)    : mo ta nut con phai cua nut hien tai
    */

    public:
        int data, priority;
        Node *left, *right;

        Node(int d) {
            data = d;
            priority = Rand();
            left = NULL;
            right = NULL;
        }
};

class Solution {
    public:
        Node *rotate_right(Node *node) {
            /*
                Ham xoay cay sang phai voi nut dang xet

                Thong tin:
                    node (Node) : Nut can xoay phai
                    x (Node)    : Luu nut con trai cua node
                    t (Node)    : Luu nut con phai cua x

                Thao tac:
                    Gan nut con phai cua x thanh node
                    Gan nut con trai cua node thanh t.

                Tra ve x.
            */


            Node *x = node->left, *t = x->right;
            x->right = node;
            node->left = t;
            return x;
        }

        Node *rotate_left(Node *node) {
             /*
                Ham xoay cay sang trai voi nut dang xet

                Thong tin:
                    node (Node) : Nut can xoay trai
                    x (Node)    : Luu nut con phai cua node
                    t (Node)    : Luu nut con trai cua x

                Thao tac:
                    Gan nut con trai cua x thanh node
                    Gan nut con phai cua node thanh t

                Tra ve x
            */

            Node *x = node->right, *t = x->left;
            x->left = node;
            node->right = t;
            return x;
        }


        Node* insert(Node* root, int x) {
            /*
                Ham them mot nut mang gia tri x vao cay Treap

                Thong tin :
                    root (Node) : Nut dang xet
                    x (int)     : Gia tri x can them vao

                Thao tac :
                    Neu nut hien tai rong, tao nut moi mang gia tri x.

                    Neu x nho hon gia tri nut hien tai thi xet nut con trai:
                        Sau khi them nut moi o nut con trai ma nut root hien tai
                        bi vi pham tinh chat khoa Heap thi xoay phai cay.

                    Neu x lon hon gia tri nut hien tai thi xet nut con phai:
                        Sau khi them nut moi o nut con phai ma nut root hien tai
                        bi vi pham tinh chat khoa Heap thi xoay trai cay.

                Tra ve nut hien tai
            */


            if (root == NULL) return new Node(x);

            if (x < root->data) {
                root->left = insert(root->left, x);

                if (root->priority > root->left->priority)
                    root = rotate_right(root);

            } else {
                root->right = insert(root->right, x);

                if (root->priority > root->right->priority)
                    root = rotate_left(root);
            }
            return root;
        }

        Node* deleteNode(Node* root, int x) {
            /*
                Ham xoa mot nut mang gia tri x tren cay Treap

                Thong tin :
                    root (Node) : Nut dang xet
                    x (int)     : Gia tri cua nut can xoa

                Thao tac:
                    Neu root la rong thi ta bo qua.

                    Neu gia tri x khong o root:
                        Neu x nho hon gia tri nut root, xet nut con trai cua root
                        Neu x lon hon gia tri nut root, xet nut con phai cua root

                    Nguoc lai, neu x dang o root :

                        Truong hop 1 : root khong co nut con trai:
                            Xoa root ra khoi cay va xet nut con phai

                        Truong hop 2 : root khong co nut con phai:
                            Xoa root ra khoi cay va xet nut con trai

                        Truong hop 3 : root co ca nut con trai va phai:
                            Xet nut con trai, nut con phai cua root va thuc hien xoay cay

                 Tra ve nut hien tai.

            */


            if (root == NULL) return root;

            if (x < root->data)
                root->left = deleteNode(root->left, x);
            else if (x > root->data)
                root->right = deleteNode(root->right, x);

            else if (root->left == NULL) {
                Node *temp = root->right;
                delete(root);
                root = temp;
            }

            else if (root->right == NULL) {
                Node *temp = root->left;
                delete(root);
                root = temp;
            }
            else if (root->left->priority < root->right->priority) {
                root = rotate_right(root);
                root->right = deleteNode(root->right, x);
            }
            else {
                root = rotate_left(root);
                root->left = deleteNode(root->left, x);
            }

            return root;
        }


		Node *find(Node *root, int x) {
            /*
                Ham tra ve nut mang gia tri x.

                Thong tin:
                    root (Node) : Mo ta nut hien tai.
                    x (int)     : Gia tri tren nut can tim.

                Thuc hien:
                    Neu nut hien tai co gia tri nho hon x chuyen sang nut con trai.
                    Nguoc lai, nut hien tai co gia tri lon hon x chuyen sang nut con phai.

                Khi tim duoc tra ve nut root hien tai.
            */

            if (root == NULL) return nullptr;
            if (x > root->data) return find(root->right, x);
            if (x < root->data) return find(root->left, x);
            return root;
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
    cout << height;
    // do cao cua cay


    return 0;
}



