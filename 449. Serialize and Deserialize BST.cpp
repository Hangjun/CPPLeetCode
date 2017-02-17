/*
Serialization is the process of converting a data structure or object into a sequence of bits so that it can be stored in a file or memory buffer, or transmitted across a network connection link to be reconstructed later in the same or another computer environment.

Design an algorithm to serialize and deserialize a binary search tree. There is no restriction on how your serialization/deserialization algorithm should work. You just need to ensure that a binary search tree can be serialized to a string and this string can be deserialized to the original tree structure.

The encoded string should be as compact as possible.

Note: Do not use class member/global/static variables to store states. Your serialize and deserialize algorithms should be stateless.
*/

/* The solution of the problem 297. Serialize and Deserialize Binary Tree (https://leetcode.com/problems/serialize-and-deserialize-binary-tree/?tab=Description) can be directly appied here. We recursively DFS traverse the tree, and store the node values in an ostringstream. When deserialize the string, we use istringstream.
*/
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serializePrivate(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserializePrivate(in);
    }

void serializePrivate(TreeNode *root, ostringstream &out) {
         if (root) {
             out << root->val << " ";
             serializePrivate(root->left, out);
             serializePrivate(root->right, out);
         } else {
             out << "# ";
         }
     }
     
     TreeNode *deserializePrivate(istringstream &in) {
        string val;
        in >> val;
        if (val == "#") return NULL;
        TreeNode *root = new TreeNode(stoi(val));
        root->left = deserializePrivate(in);
        root->right = deserializePrivate(in);
        
        return root;
    }
};


// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));


/* The above solution works for any binary tree, and does not use the property that the tree is a BST. How can we come up with a more compact encoding utilizing the BST structure? 

Recall that we need either inorder + preorder or inorder postorder in order to reconstruct a binary tree. However, for a binary search tree, we can reconstruct it by using its preorder traversals along (see problem 255. Verify Preorder Sequence in Binary Search Tree, https://leetcode.com/problems/verify-preorder-sequence-in-binary-search-tree/).
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out; // out stores the preorder traversal of this BST
        preorder(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        vector<int> preorder;
        string val;
        while (in >> val && val != " ") {
            preorder.push_back(stoi(val));
        }
        return constructBST(preorder, 0, preorder.size()-1);
    }
    
private:
    void preorder(TreeNode *root, ostringstream &out) {
        if (!root) return;
        stack<TreeNode *> st;
        TreeNode *curNode = root;
        while (curNode || !st.empty()) {
            if (curNode) {
                out << curNode->val << " ";
                st.push(curNode);
                curNode = curNode->left;
            } else {
                TreeNode *readyNode = st.top();
                st.pop();
                curNode = readyNode->right;
            }
        }
    }
    
    TreeNode *constructBST(vector<int> &preorder, int start, int end) {
        if (start > end) return NULL;
        TreeNode *root = new TreeNode (preorder[start]);
        // find the right subtree
        int m = -1;
        for (int i = start+1; i <= end; i++) {
            if (m == -1 && preorder[i] > root->val) {
                m = i;
                break;
            }
        }
        if (m == -1) {
            root->left = constructBST(preorder, start+1, end);
        } else {
            root->left = constructBST(preorder, start+1, m-1);
            root->right = constructBST(preorder, m, end);
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));
