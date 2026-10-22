#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

/*Create a node type and a BinarySearchTree class.
Implement insertion, search, removal, inorder traversal, preorder traversal, postorder traversal, and height.
Insert at least 10 distinct integers.
Demonstrate searching for one present key and one absent key.
Demonstrate all three removal cases: leaf, one child, and two children.
Show that inorder traversal remains sorted after each removal.*/

struct Node{
    int value;
    Node* left = nullptr;
    Node* right = nullptr;
};

class BST{
private:
    Node *root = nullptr;
    
    void clear(Node* current){
        if(!current) return;
        clear(current->left);
        clear(current->right);
        delete current;
    }
    
    //recursively traverse tree in order
    void inOrderT(Node* current, vector<int>& result){
        if(!current) return;
        inOrderT(current->left, result);
        result.push_back(current->value);
        inOrderT(current->right, result);
    }
    
    //recursively traverse 
    void preOrderT(Node* current, vector<int>& result){
        if(!current) return;
        result.push_back(current->value);
        preOrderT(current->left, result);
        preOrderT(current->right, result);
    }
    
    //recursively traverse
    void postOrderT(Node* current, vector<int>& result){
        if(!current) return;
        postOrderT(current->left, result);
        postOrderT(current->right, result);
        result.push_back(current->value);
    }
    
    //recursively traverse 
    int height(Node* current){
        if(!current) return -1;
        int leftHeight = height(current->left);
        int rightHeight = height(current->right);
        return 1 + max(leftHeight, rightHeight);
    }
public:
    ~BST(){ clear(root); }
    //insert a node using a key
    bool insert(const int val){
        //no root exists, insert at root
        if(root == nullptr){
            root = new Node{val};
            return true;
        }
        Node* current = root;
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
            } else break;
        }
        return false;
    }
    //search for a node using a key
    Node *search(const int val) const{
        Node* current = root;
        while(current != nullptr){
            if(current->value > val) current = current->left;
            else if(current->value < val) current = current->right;
            else return current;
        }
        return nullptr;
    }
    
    //remove a node using a key
    bool remove(const int val){
        Node* current = root;
        //root no children
        if(current && current->value == val && !current->left && !current->right){
            root = nullptr;
            delete current;
            return true;
        }
        //traverse
        Node* parent = nullptr;
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
            Node* child = current->left ? current->left : current->right;
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
            Node* successorParent = current;
            Node* successor = current->right;
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

    vector<int> inOrderT(){
        vector<int> result;
        inOrderT(root, result);
        return result;
    }

    vector<int> preOrderT(){
        vector<int> result;
        preOrderT(root, result);
        return result;
    }

    vector<int> postOrderT(){
        vector<int> result;
        postOrderT(root, result);
        return result;
    }

    int height(){ return height(root); }
    
    void populate(){
        int demoNums[] = {5, 3, 8, 2, 4, 7, 9, 1, 6, 0};
        for(int n : demoNums){
            insert(n);
        }
    }
    
    string vToS(const vector<int>& nums){
        string result;
        bool first = true;
        for(int n : nums){
           if(!first) result += ", ";
           result += to_string(n);
           first = false;
        }
        return result;
    }
    
    void printAll(){
        string result = "height: " + to_string(height());
        result += "\nin order: " + vToS(inOrderT());
        result += "\npre order: " + vToS(preOrderT());
        result += "\npost order: " + vToS(postOrderT());
        cout << result;
    }
    
    void demo(){
        string result = "\n";
        for(int demoNums : {3, 9123}){
            result += "\nsearch for node with key " + to_string(demoNums) + ": ";
            result += search(demoNums) ? "found!" : "not found";
        }
        result += "\n";
        for(int demoNums : {0, 2, 8, 8912371}){
            result += "\nremove a node with key " + to_string(demoNums) + ": ";
            result += remove(demoNums) ? "done!\nnew in order: " + vToS(inOrderT()) : "not found";
        }
        cout << result << "\n\n";
    }
};

int main(){
    BST tree;
    tree.populate();
    tree.printAll();    
    tree.demo();
    //tree.printAll();
}