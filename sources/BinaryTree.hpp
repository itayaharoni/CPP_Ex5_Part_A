#include <iostream>
#include <vector>
using namespace std;

namespace ariel{
template<typename T>
class BinaryTree{

    // Inner class for Binary Tree - Node.
    class BTNode{
    public:
    T data;
    BTNode* left;
    BTNode* right;
    BTNode(T& data): data{data},left{nullptr},right{nullptr}{};
    void set_val(T& new_data){this->data=new_data;}
    friend ostream& operator<<(ostream& output, BTNode& other){
        output << other.data;
        return output;
    }
    };

    // Binary Tree Class root.
    BTNode* root;

    public:

    BinaryTree():root{nullptr}{}
    BinaryTree& add_root(T new_root){
        if(root==nullptr){ root = new BTNode(new_root);}
        else{root->set_val(new_root);}
        return *this;
    }

    private:
    // Private methods of Binary-Tree Class.
    BinaryTree(const BinaryTree& other);
    BinaryTree& operator=(const BinaryTree& other);
    
    struct Node{
        BTNode& val;
        Node* next;
        Node(BTNode& val, Node* next): val{val}, next{next} {}
    };
    Node* point_iterator;
    public:

    // Class  iterator.
    class iterator{
        private:
        Node* p;
        Node* del;
        public:
        iterator(Node* ptr=nullptr):p{ptr},del{ptr}{}
        ~iterator(){
            Node* temp=del;
            while(temp){
                temp=del->next;
                delete del;
                del=temp;
            }
        }
        T& operator*() const {
            return p->val.data;
		}
        T* operator->() const {
            return &(p->val.data);
		}
        iterator& operator++() {
			p=p->next;
            return *this;
		}
        const iterator operator++(int) {
			iterator tmp= *this;
            p=p->next;
            return tmp;
		}
        bool operator==(const iterator& other) const {
			return p == other.p;
		}

		bool operator!=(const iterator& other) const {
			return !(p==other.p);
		}
    };
    private:
    void init_preorder(BTNode*& root,vector<BTNode*>& vec){
        if(root==nullptr) return;
        vec.push_back(root);
        init_preorder(root->left,vec);
        init_preorder(root->right,vec);
    }
    void init_inorder(BTNode*& root,vector<BTNode*>& vec){
        if(root==nullptr) return;
        init_inorder(root->left,vec);
        vec.push_back(root);
        init_inorder(root->right,vec);
    }
    void init_postorder(BTNode*& root,vector<BTNode*>& vec){
        if(root==nullptr) return;
        init_postorder(root->left,vec);
        init_postorder(root->right,vec);
        vec.push_back(root);
    }
    void copy_vec(vector<BTNode*>& vec){
        point_iterator=new Node(*vec.at(0),nullptr);
        Node* itr=point_iterator;
        Node* next;
        for (unsigned int i = 0; i < vec.size()-1; i++)
        {
            next=new Node(*vec[i+1],nullptr);
            itr->next=next;
            itr=itr->next;
        }
    }
    public:
    iterator begin() {
        vector<BTNode*> vec;
        init_inorder(root,vec);
        copy_vec(vec);
		return iterator{point_iterator};
	}
    iterator end() {
		return iterator{nullptr};
	}
    iterator begin_preorder() {
        vector<BTNode*> vec;
        init_preorder(root,vec);
        copy_vec(vec);
		return iterator{point_iterator};
	}
    iterator end_preorder() {
		return iterator{nullptr};
	}
	iterator begin_inorder() {
        vector<BTNode*> vec;
        init_inorder(root,vec);
        copy_vec(vec);
		return iterator{point_iterator};
	}
    iterator end_inorder() {
		return iterator{nullptr};
	}
	iterator begin_postorder() {
        vector<BTNode*> vec;
        init_postorder(root,vec);
        copy_vec(vec);
		return iterator{point_iterator};
	}
    iterator end_postorder() {
		return iterator{nullptr};
	}
    friend ostream& operator<<(ostream& output,BinaryTree& bt){
        for (auto i : bt) {
            output << i << endl;
        }
        return output;
    }
        BinaryTree& add_left(T father,T child){
        BTNode* temp=root;
        vector<BTNode*> vec;
        init_preorder(root,vec);
        copy_vec(vec);
        iterator itr{point_iterator};
        for(auto n: vec){
            if(n->data==father){
                temp=n;
                break;
            }
        }
        if(temp==root&&root->data!=father) throw out_of_range{"Error in add_left() function."};
        if(temp->left==nullptr){ temp->left=new BTNode(child);}
        else temp->left->set_val(child);
        return *this;
    }

    BinaryTree& add_right(T father,T child){
        BTNode* temp=root;
        vector<BTNode*> vec;
        init_preorder(root,vec);
        copy_vec(vec);
        iterator itr{point_iterator};
        for(auto n: vec){
            if(n->data==father){
                temp=n;
                break;
            }
        }
        if(temp==root&&root->data!=father) throw out_of_range{"Error in add_right() function."};
        if(temp->right==nullptr){  temp->right=new BTNode(child);}
        else temp->right->set_val(child);
        return *this;
    }
    ~BinaryTree(){
        vector<BTNode*> vec;
        init_postorder(root,vec);
        copy_vec(vec);
        iterator itr{point_iterator};
        for (unsigned int i = 0; i < vec.size(); i++) {
            delete vec[i];    
        }
    }
};
};