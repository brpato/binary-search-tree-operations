#include <iostream>
#include <vector>
using namespace std;

/*Create a node type and a BinarySearchTree class.
Implement insertion, search, removal, inorder traversal, preorder traversal, postorder traversal, and height.
Insert at least 10 distinct integers.
Demonstrate searching for one present key and one absent key.
Demonstrate all three removal cases: leaf, one child, and two children.
Show that inorder traversal remains sorted after each removal.*/

//still need to test everything

struct Node{
    int value;
    Node *left = nullptr;
    Node *right = nullptr;
};

class BST{
private:
    Node *root = nullptr;

public:
    bool insert(const int val){
        if(root == nullptr){
            root = new Node{val};
            return true;
        }
        Node *current = root;
        while(current != nullptr){
            if(val < current->value){
                if(current->left == nullptr){
                    current->left = new Node{val};
                    return true;
                }
                current = current->left;
            } else if(val > current->value){
                if(current->right == nullptr){
                    current->right = new Node{val};
                    return true;
                }
                current = current->right;
            } else{
                break;
            }
        }
        return false;
    }

    Node *search(const int val) const{
        Node *current = root;
        while(current != nullptr){
            if(current->value > val) current = current->left;
            else if(current->value < val) current = current->right;
            else return current;
        }
        return nullptr;
    }

    bool removal(const int val){
        Node *current = root;
        //root no children
        if(current && current->value == val && !current->left && !current->right){
            root = nullptr;
            delete current;
            return true;
        }
        //traverse
        Node *parent = nullptr;
        while(current != nullptr){
            if(current->value > val){
                parent = current;
                current = current->left;
            } else if(current->value < val){
                parent = current;
                current = current->right;
            } else break;
        }
        //node should be here but doesnt exist
        if(current == nullptr){
            return false;
        }
        //non-parent node
        if(!current->left && !current->right){
            if(parent->value > val) parent->left = nullptr;
            else parent->right = nullptr;
            delete current;
            return true;
        }
        //parent with one child (including root)
        if(!current->left || !current->right){
            Node *child = current->left ? current->left : current->right;
            //root
            if(!parent) root = child;
                //current value is less than parent value
            else if(parent->value > val) parent->left = child;
                //current value is greater than parent value
            else parent->right = child;
            delete current;
            return true;
        }
        //parent with two children (including root)
        if(current->left && current->right){
            Node *successorParent = current;
            Node *successor = current->right;

            while(successor->left){
                successorParent = successor;
                successor = successor->left;
            }
            current->value = successor->value;
            if(successorParent == current) successorParent->right = successor->right;
            else successorParent->left = successor->right;
            delete successor;
            return true;
        }
        return false;
    }

    static vector<int> inOrderT(){
        return {};
    }

    static vector<int> preOrderT(){
        return {};
    }

    static vector<int> postOrderT(){
        return {};
    }

    static int height(){
        return -1;
    }
};

int main(){
    return 0;
}
