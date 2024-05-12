#include <bits/stdc++.h>

using namespace std;

mt19937 rd(chrono::steady_clock::now().time_since_epoch().count());
#define rand rd

// Ham sinh random trong doan [l, r] 
int Rand() {
    int l = 1, r = 1000000000;
    return l + rd() * 1LL * rd() % (r - l + 1);
}


// Cau truc cac nut cua cay Treap 
class Node {
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
    	// Thao tac xoay phai 
        Node *rotate_right(Node *node) {
            Node *x = node->left, *t = x->right;
            x->right = node;
            node->left = t;
            return x;
        }

		// Thao tac xoay trai
        Node *rotate_left(Node *node) {
            Node *x = node->right, *t = x->left;
            x->left = node;
            node->right = t;
            return x;
        }

		//  Thao tac them phan tu x
  		Node* insert(Node* root, int x) {
            // root la dinh goc cua cay Treap
            // x la gia tri duoc them vao
            if(root == NULL) return new Node(x);

            if(x < root->data) {
                root->left = insert(root->left, x);

                if (root->priority > root->left->priority)
                    root = rotate_right(root);

                // neu cay bi vi pham, xoay phai
            } else {
                root->right = insert(root->right, x);

                if (root->priority > root->right->priority)
                    root = rotate_left(root);

                // neu cay bi vi pham, xoay trai
            }
            return root;
        }
		
		
		// Thao tac tim mot phan tu 
        Node *find(Node *root, int key) {
            if (root == NULL) return nullptr;
            if (key > root->data) return find(root->right, key);
            // neu key lon hon gia tri dinh hien tai thi di theo nhanh phai
            if (key < root->data) return find(root->left, key);
            // neu key nho hon gia tri dinh hien tai thi di theo nhanh trai
            return root;
        }
		
		
		// ham tinh do cao cua cay
        int height(Node* root) {
            if (root == NULL) return 0;
            int res = 0;
            cout << root->data << ' ' << root->priority << '\n';
            res = max(res, height(root->left) + 1);
            res = max(res, height(root->right) + 1);
            return res;
        }
		
		
		// Thao tac xoa mot phan tu 
        Node* deleteNode(Node* root, int x) {
            // root la dinh goc cua cay Treap
            // x la gia tri can xoa

            if (root == NULL) return root;

            // Neu x khong phai o root
            if (x < root->data)
                root->left = deleteNode(root->left, x);
            else if (x > root->data)
                root->right = deleteNode(root->right, x);

            // Neu x o root
            // Truong hop 1 : root khong co nut con trai
            else if (root->left == NULL) {
                Node *temp = root->right;
                delete(root);
                root = temp; // Xet nut con phai lam root
            }

            // Truong hop 2 : root khong co nut phai
            else if (root->right == NULL) {
                Node *temp = root->left;
                delete(root);
                root = temp; // Xet nut con trai lam root
            }

            // Truong hop 3 : Neu x o root va root co ca hai nut con
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


}; //End of Solution

int main() {
  
    Solution myTree;
    Node* root = NULL;
    
    int t;
    int data;

    std::cin >> t;
    // so nut t

    while(t-- > 0) {
        std::cin >> data;
        root = myTree.insert(root, data);
    }
  
    int height = myTree.height(root);
    cout << height;
    
  	//std::cout << height;

    return 0;
}



