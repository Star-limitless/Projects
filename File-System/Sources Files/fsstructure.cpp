#include "fsstructure.h" // 包含头文件 fsstructure.h
#include <iostream> // 包含输入输出流库
#include <fstream> // 包含文件流库
#include <sstream> // 包含字符串流库

// TrieNode 构造函数，初始化节点名称和子节点计数
TrieNode::TrieNode(const std::string& name) : name(name), childrenCount(0) {
    for (int i = 0; i < 10; ++i) {
        children[i] = nullptr; // 初始化所有子节点指针为空
    }
}

// 向节点添加子节点
void TrieNode::addChild(TrieNode* child) {
    if (childrenCount < 10) { // 检查子节点数是否小于 10
        children[childrenCount++] = child; // 添加子节点并增加计数
    }
}

// 获取名称为 name 的子节点
TrieNode* TrieNode::getChild(const std::string& name) {
    for (int i = 0; i < childrenCount; ++i) {
        if (children[i]->name == name) { // 如果找到匹配的子节点
            return children[i]; // 返回子节点
        }
    }
    return nullptr; // 如果未找到匹配的子节点，返回空指针
}

// Trie 构造函数，初始化根节点
Trie::Trie() {
    root = new TrieNode(""); // 根节点名称为空字符串
}

// 插入路径到 Trie
void Trie::insert(const std::string& path) {
    TrieNode* current = root; // 从根节点开始
    size_t start = 0, end = 0;
    while ((end = path.find('/', start)) != std::string::npos) {
        std::string part = path.substr(start, end - start); // 提取路径中的一部分
        TrieNode* child = current->getChild(part); // 获取子节点
        if (!child) { // 如果子节点不存在
            child = new TrieNode(part); // 创建新的子节点
            current->addChild(child); // 添加子节点到当前节点
        }
        current = child; // 更新当前节点
        start = end + 1; // 更新起始位置
    }
    // 插入路径的最后一部分
    std::string lastPart = path.substr(start);
    TrieNode* child = current->getChild(lastPart);
    if (!child) {
        child = new TrieNode(lastPart);
        current->addChild(child);
    }
}

// 打印 Trie 结构
void Trie::printTrie(std::ostream& os, TrieNode* node, const std::string& prefix, bool isLast) const {
    if (node != root) { // 如果当前节点不是根节点
        os << prefix; // 输出前缀
        os << (isLast ? "└── " : "├── "); // 根据是否是最后一个子节点选择符号
        os << node->name << std::endl; // 输出节点名称
    }

    for (int i = 0; i < node->childrenCount; ++i) {
        printTrie(os, node->children[i], prefix + (isLast ? "    " : "│   "), i == node->childrenCount - 1); // 递归打印子节点
    }
}

// 打印 Trie 到输出流
void Trie::printToStream(std::ostream& os) const {
    if (root->childrenCount > 0) { // 如果根节点有子节点
        printTrie(os, root->children[0], "", true); // 打印 Trie 结构
    }
}

// 从文件读取路径并插入到 Trie 中
void readAndInsertPaths(const std::string& filename, Trie& trie) {
    std::ifstream file(filename); // 打开文件
    if (!file.is_open()) { // 检查文件是否成功打开
        std::cerr << "Failed to open file: " << filename << std::endl; // 输出错误信息
        return;
    }

    std::string line;
    while (std::getline(file, line)) { // 逐行读取文件内容
        trie.insert(line); // 插入路径到 Trie
    }

    file.close(); // 关闭文件
}
