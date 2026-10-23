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
    Node* root = nullptr;

    //destructor
    static void clear(const Node* current){
        if(!current) return;
        clear(current->left);
        clear(current->right);
        delete current;
    }

    //recursively traverse tree in order
    static void inOrderT(const Node* current, vector<int> &result){
        if(!current) return;
        inOrderT(current->left, result);
        result.push_back(current->value);
        inOrderT(current->right, result);
    }

    //recursively traverse smallest to greatest but start with root
    static void preOrderT(const Node* current, vector<int> &result){
        if(!current) return;
        result.push_back(current->value);
        preOrderT(current->left, result);
        preOrderT(current->right, result);
    }

    //recursively traverse uhhhh
    static void postOrderT(const Node* current, vector<int> &result){
        if(!current) return;
        postOrderT(current->left, result);
        postOrderT(current->right, result);
        result.push_back(current->value);
    }

    //recursively traverse each branch and compare the left to the right heights to figure out the biggest branch and add the root edge after
    static int height(const Node* current){
        if(!current) return -1;
        const int leftHeight = height(current->left);
        const int rightHeight = height(current->right);
        return 1 + max(leftHeight, rightHeight);
    }

public:
    ~BST(){ clear(root); }

    //insert a node using a key
    bool insert(const int val){
        //no root exists, insert at root
        if(!root){
            root = new Node{val};
            return true;
        }
        //while current exists
        Node* current = root;
        while(current){
            //if current does not have a left child and the val is less than current, insert, otherwise keep moving down the branch
            if(current->value > val){
                if(current->left == nullptr){
                    current->left = new Node{val};
                    return true;
                }
                current = current->left;
                //if current does not have a right child and the val is more than current, insert, otherwise keep moving down the branch
            } else if(current->value < val){
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
    Node* search(const int val) const{
        Node* current = root;
        while(current != nullptr){
            //move left
            if(current->value > val) current = current->left;
                //move right
            else if(current->value < val) current = current->right;
                //found the target node
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
        Node* parent = nullptr;
        while(current){
            //move parent to current and current left if val is less than current val
            if(current->value > val){
                parent = current;
                current = current->left;
                //move parent to current and current right if val is more than current val
            } else if(current->value < val){
                parent = current;
                current = current->right;
            } else break;
        }
        //node should be here but doesnt exist
        if(!current){
            return false;
        }
        //non-parent node
        if(!current->left && !current->right){
            //detatch either left or right child of parent, whichever current is, then delete current
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
                //link child to parent left or right, whatever is correct then delete current
            else if(parent->value > val) parent->left = child;
            else parent->right = child;
            delete current;
            return true;
        }
        //parent with two children (including root)
        if(current->left && current->right){
            Node* successorParent = current;
            //find the next largest node by going right once and then left until you cant and replace successor's value with current's
            Node* successor = current->right;
            while(successor->left){
                successorParent = successor;
                successor = successor->left;
            }
            current->value = successor->value;
            //link the child of successor to successor parent and then delete successor
            if(successorParent == current) successorParent->right = successor->right;
            else successorParent->left = successor->right;
            delete successor;
            return true;
        }
        return false;
    }

    vector<int> inOrderT() const{
        vector<int> result;
        inOrderT(root, result);
        return result;
    }

    vector<int> preOrderT() const{
        vector<int> result;
        preOrderT(root, result);
        return result;
    }

    vector<int> postOrderT() const{
        vector<int> result;
        postOrderT(root, result);
        return result;
    }

    int height() const{ return height(root); }

    void populate(){
        int demoNums[] = {5,3,8,2,4,7,9,1,6,0};
        for(int n: demoNums){
            insert(n);
        }
    }

    static string vToS(const vector<int> &nums){
        string result;
        bool first = true;
        for(const int n: nums){
            if(!first) result += ", ";
            result += to_string(n);
            first = false;
        }
        return result;
    }

    void printAll() const{
        string result = "insert {5, 3, 8, 2, 4, 7, 9, 1, 6, 0} in this order\nheight: " + to_string(height());
        result += "\nin order: " + vToS(inOrderT());
        result += "\npre order: " + vToS(preOrderT());
        result += "\npost order: " + vToS(postOrderT());
        cout << result;
    }

    void demo(){
        string result = "\n";
        for(const int demoNums: {3,9123}){
            result += "\nsearch for node with key " + to_string(demoNums) + ": ";
            result += search(demoNums) ? "found!" : "not found";
        }
        result += "\n";
        for(int demoNums: {0,2,8,8912371}){
            result += "\nremove a node with key " + to_string(demoNums) + ": ";
            result += remove(demoNums) ? "done!\nnew in order: " + vToS(inOrderT()) : "not found";
        }
        const int testNum = 4;
        result += "\n\ninsert a node with key " + to_string(testNum) + ": ";
        result += insert(testNum) ? "done!\nnew in order: " + vToS(inOrderT()) : "already exists";
        cout << result;
    }
};

int main(){
    BST tree;
    tree.populate();
    tree.printAll();
    tree.demo();
}
