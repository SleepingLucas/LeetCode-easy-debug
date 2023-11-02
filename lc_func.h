#pragma once
#include<bits/stdc++.h>
using namespace std;

/* 删除左侧多余空格 */
void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

/* 删除右侧多余空格 */
void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

/* 将字符串转换为vector */
vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    if (input.empty()) return output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

/* 将字符串转换为二维vector */
vector<vector<int>> stringTo2dIntegerVector(string input) {
	vector<vector<int>> output;
    if (input.empty()) return output;
	trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ']';
    while (getline(ss, item, delim)) {
		item = item.substr(item.find_first_of("[")) + "]";
        output.push_back(stringToIntegerVector(item));
    }
    return output;
}


/* 链表节点的定义 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/* 将字符串转换为链表 */
ListNode* stringToListNode(string input) {
    // Generate list from the input
    vector<int> list = stringToIntegerVector(input);

    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

/* 将字符串转换为链表vector */
vector<ListNode*> stringToListNodeVector(string input) {
	vector<ListNode*> output;
    if (input.empty()) return output;
	trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ']';
    while (getline(ss, item, delim)) {
		item = item.substr(item.find_first_of("[")) + "]";
        output.push_back(stringToListNode(item));
    }
    return output;
}

/* 将链表转换为字符串 */
string listNodeToString(ListNode* node) {
    if (node == nullptr) {
        return "[]";
    }

    string result;
    while (node) {
        result += to_string(node->val) + ", ";
        node = node->next;
    }
    return "[" + result.substr(0, result.length() - 2) + "]";
}

/* 美化链表输出 */
ostream& prettyPrintLinkedList(ostream& os, ListNode* node) {
    while (node && node->next) {
        os << node->val << "->";
        node = node->next;
    }

    if (node) {
        os << node->val;
    } else {
        os << "Empty LinkedList";
    }
    return os;
}

/* 重载链表输出 */
ostream& operator<<(ostream& os, ListNode* node) {
    return prettyPrintLinkedList(os, node);
}


/* 二叉树节点的定义 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 将二叉树转换成字符串 */
string treeNodeToString(TreeNode* root) {
    if (root == nullptr) {
      return "[]";
    }

    string output = "";
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (node == nullptr) {
          output += "null, ";
          continue;
        }

        output += to_string(node->val) + ", ";
        q.push(node->left);
        q.push(node->right);
    }
    return "[" + output.substr(0, output.length() - 2) + "]";
}

/* 将字符串转换成二叉树 */
TreeNode* stringToTreeNode(string input) {
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    if (!input.size()) {
        return nullptr;
    }

    string item;
    stringstream ss;
    ss.str(input);

    getline(ss, item, ',');
    TreeNode* root = new TreeNode(stoi(item));
    queue<TreeNode*> nodeQueue;
    nodeQueue.push(root);

    while (true) {
        TreeNode* node = nodeQueue.front();
        nodeQueue.pop();

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int leftNumber = stoi(item);
            node->left = new TreeNode(leftNumber);
            nodeQueue.push(node->left);
        }

        if (!getline(ss, item, ',')) {
            break;
        }

        trimLeftTrailingSpaces(item);
        if (item != "null") {
            int rightNumber = stoi(item);
            node->right = new TreeNode(rightNumber);
            nodeQueue.push(node->right);
        }
    }
    return root;
}

/* 将字符串转换为二叉树vector */
vector<TreeNode*> stringToTreeNodeVector(string input) {
	vector<TreeNode*> output;
    if (input.empty()) return output;
	trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ']';
    while (getline(ss, item, delim)) {
		item = item.substr(item.find_first_of("[")) + "]";
        output.push_back(stringToTreeNode(item));
    }
    return output;
}

/* 美化二叉树输出 */
ostream& prettyPrintTree(ostream& os, TreeNode* node, string prefix = "", bool isLeft = true) {
    if (node == nullptr) {
        os << "Empty tree";
        return os;
    }

    if(node->right) {
        prettyPrintTree(os, node->right, prefix + (isLeft ? "│   " : "    "), false);
    }

    os << prefix + (isLeft ? "└── " : "┌── ") + to_string(node->val) + "\n";

    if (node->left) {
        prettyPrintTree(os, node->left, prefix + (isLeft ? "    " : "│   "), true);
    }

    return os;
}

/* 重载二叉树输出 */
ostream& operator<<(ostream& os, TreeNode* root) {
    return prettyPrintTree(os, root);
}

/* 格式化字符串 */
string stringToString(string input) {
    if (input.length() < 2) return input;
    string result;
    for (int i = 1; i < input.length() -1; i++) {
        char currentChar = input[i];
        if (input[i] == '\\') {
            char nextChar = input[i+1];
            switch (nextChar) {
                case '\"': result.push_back('\"'); break;
                case '/' : result.push_back('/'); break;
                case '\\': result.push_back('\\'); break;
                case 'b' : result.push_back('\b'); break;
                case 'f' : result.push_back('\f'); break;
                case 'r' : result.push_back('\r'); break;
                case 'n' : result.push_back('\n'); break;
                case 't' : result.push_back('\t'); break;
                default: break;
            }
            i++;
        } else {
          result.push_back(currentChar);
        }
    }
    return result;
}

template<typename... Rest>
bool getInput(string&, Rest &...);
template<typename First, typename... Rest>
bool getInput(First&, Rest &...);

/* 字符串特化输入 */
template<typename... Rest>
bool getInput(string &first, Rest &... rest) {
    if (cin.peek() == EOF) return false;
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, first);
    if constexpr (sizeof...(rest) >= 1) {
        getInput(rest...);
    }
    return true;
}

/* 输入变量 */
template<typename First, typename... Rest>
bool getInput(First &first, Rest &... rest) {
    if (cin.peek() == EOF) return false;
    cin >> first;
    if constexpr (sizeof...(rest) >= 1) {
        getInput(rest...);
    }
    return true;
}