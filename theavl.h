#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

struct point{
    int data;
    int height;
    point *left;
    point *right;
    point(int val){
        data = val;
        left = right = nullptr;
        //height = 1;
    }
};

class AVL{
    private:
        point *root;

        int getHeight(point *cur){
            if(cur == nullptr){
                return 0;
            }
            int leftHeight = getHeight(cur->left);
            int rightHeight = getHeight(cur->right);
            return 1 + max(leftHeight, rightHeight);
        }

        int getBF(point *cur){
            if(cur == nullptr){
                return 0;
            }
            return getHeight(cur->left) - getHeight(cur->right);
        }

        point *LeftRotate(point *cur){
            point *newcur = cur->right;
            point *newright = newcur->left;
            newcur->left = cur;
            cur->right = newright;
            return newcur;
        }

        point *RightRotate(point *cur){
            point *newcur = cur->left;
            point *newleft = newcur->right;
            newcur->right = cur;
            cur->left = newleft;
            return newcur;
        }

        point *successor(point *cur){
            point *now = cur;
            while(now->left != nullptr){
                now = now->left;
            }
            return now;
        }

        point *insert(point *cur, int val){
            if(cur == nullptr){
                return new point(val);
            }
            else if(val < cur->data){
                cur->left = insert(cur->left, val);
            }
            else if(val > cur->data){
                cur->right = insert(cur->right, val);
            }
            else{
                return cur;
            }

            int balanceFactor = getBF(cur);

            if(balanceFactor > 1 && val < cur->left->data){
                return RightRotate(cur);
            }
            else if(balanceFactor < -1 && val > cur->right->data){
                return LeftRotate(cur);
            }
            else if(balanceFactor > 1 && val > cur->left->data){
                cur->left = LeftRotate(cur->left);
                return RightRotate(cur);
            }
            else if(balanceFactor < -1 && val < cur->right->data){
                cur->right = RightRotate(cur->right);
                return LeftRotate(cur);
            }
            return cur;
        }

        point *remove(point *cur, int val){
            if(cur == nullptr){
                return cur;
            }
            if(val < cur->data){
                cur->left = remove(cur->left, val);
            }
            else if(val > cur->data){
                cur->right = remove(cur->right, val);
            }
            else{
                if ((cur->left == nullptr) || (cur->right == nullptr)) {
                    point *temp = cur->left ? cur->left : cur->right;
                    if (temp == nullptr) {
                        temp = cur;
                        cur = nullptr;
                    } 
                    else{
                        *cur = *temp;
                        free(temp);
                    }
                }
                else{
                    point *temp = successor(cur->right);
                    cur->data = temp->data;
                    cur->right = remove(cur->right, temp->data);
                }
            }
            if(cur == nullptr){
                return cur;
            }
            //int height = getHeight(cur);
            int balance = getBF(cur);

            if(balance > 1 && getBF(cur->left) >= 0){
                return RightRotate(cur);
            }
            if(balance > 1 && getBF(cur->left) < 0){
                cur->left = LeftRotate(cur->left);
                return RightRotate(cur);
            }
            if(balance < -1 && getBF(cur->right) <= 0){
                return LeftRotate(cur);
            }
            if(balance < -1 && getBF(cur->right) > 0){
                cur->right = RightRotate(cur->right);
                return LeftRotate(cur);
            }
            return cur;
        }

        void eachLevel(point *cur, int level, ofstream &out){
            if(cur == nullptr){
                return;
            }
            if(level == 1){
                out << cur->data << " ";
            }
            else if(level > 1){
                eachLevel(cur->left, level-1, out);
                eachLevel(cur->right, level-1, out);
            }
        }

        void eachOrder(point *cur, ofstream &out){
            int height = getHeight(cur);
            for(int i = 1; i <= height; i++){
                eachLevel(cur, i, out);
                out << endl;
            }
        }
    public:
        AVL(){root = nullptr;}

        point *getRoot(){return root;}

        void Destroy(point *cur){
            if(cur){
                Destroy(cur->left);
                Destroy(cur->right);
                delete cur;
            }
        }

        ~AVL(){Destroy(root);}

        bool isEmpty(){return getRoot() == nullptr;}

        void insert(int val) {root = insert(root, val);}
        void remove(int val) {root = remove(root, val);}

        void print(ofstream &out){
            eachOrder(root, out);
        }
};