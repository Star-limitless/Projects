#ifndef TREEOUT_H
#define TREEOUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>

// 文件详细信息结构体
struct FileDetail {
    std::string name;          // 文件名称
    std::string type;          // 文件类型
    std::string creationDate;  // 创建日期
    std::string lastModDate;   // 最后修改日期
    std::string absPath;       // 绝对路径
    int id;                    // 文件位置标识符

    FileDetail(const std::string& name, const std::string& type, const std::string& creationDate,
               const std::string& lastModDate, const std::string& absPath, int id)
        : name(name), type(type), creationDate(creationDate), lastModDate(lastModDate), absPath(absPath), id(id) {}
};

// Trie 树节点类
class TrieNode {
public:
    std::string name;         // 节点名称，存储路径的一部分
    TrieNode* children[10];   // 子节点数组，最多有10个子节点
    int childrenCount;        // 当前节点的子节点数量

    // 构造函数，初始化节点名称和子节点数组
    TrieNode(const std::string& name) : name(name), childrenCount(0) {
        for (int i = 0; i < 10; ++i) {
            children[i] = nullptr;  // 将子节点数组初始化为空指针
        }
    }

    // 添加子节点到当前节点
    void addChild(TrieNode* child) {
        if (childrenCount < 10) {    // 确保子节点数量未超过上限
            children[childrenCount++] = child;  // 将子节点添加到数组中，并增加子节点计数
        }
    }

    // 根据名称查找子节点
    TrieNode* getChild(const std::string& name) {
        for (int i = 0; i < childrenCount; ++i) {
            if (children[i]->name == name) {   // 遍历子节点数组，找到与给定名称匹配的子节点
                return children[i];            // 返回找到的子节点指针
            }
        }
        return nullptr;   // 若未找到匹配的子节点，返回空指针
    }
};

// Trie 树类
class Trie {
private:
    TrieNode* root;   // 根节点指针
    int maxDepth;     // 最大深度

    // 递归打印 Trie 树的私有辅助函数
    void printTrie(TrieNode* node, const std::string& indent) {
        for (int i = 0; i < node->childrenCount; ++i) {
            std::cout << indent << node->children[i]->name << std::endl;  // 打印节点名称
            printTrie(node->children[i], indent + "  ");  // 递归打印子节点
        }
    }

    // 递归将 Trie 树写入文件的私有辅助函数
    void writeTrieToFile(std::ofstream& file, TrieNode* node, const std::string& path) {
        for (int i = 0; i < node->childrenCount; ++i) {
            std::string newPath = path + "/" + node->children[i]->name;
            file << newPath << std::endl;  // 写入路径到文件
            writeTrieToFile(file, node->children[i], newPath);  // 递归写入子节点
        }
    }

public:
    // 构造函数，初始化 Trie 树的根节点
    Trie(int maxDepth) : maxDepth(maxDepth) {
        root = new TrieNode("");   // 创建空的根节点
    }

    // 插入路径到 Trie 树中
    void insert(const std::string& path) {
        TrieNode* current = root;   // 从根节点开始插入路径
        size_t start = 0, end = 0;  // 起始和结束位置变量
        int depth = 0;              // 当前深度
        while ((end = path.find('/', start)) != std::string::npos) {
            if (depth >= maxDepth) break;  // 超过最大深度时停止插入
            std::string part = path.substr(start, end - start);  // 提取路径的一部分
            TrieNode* child = current->getChild(part);   // 查找当前节点是否有该子节点
            if (!child) {
                child = new TrieNode(part);   // 若不存在该子节点，则创建新节点
                current->addChild(child);     // 将新节点添加到当前节点的子节点数组中
            }
            current = child;   // 将当前节点移动到新创建的子节点
            start = end + 1;   // 更新起始位置到下一个路径部分的起始位置
            ++depth;           // 增加当前深度
        }
        // 插入路径的最后部分
        if (depth < maxDepth) {
            std::string lastPart = path.substr(start);
            TrieNode* child = current->getChild(lastPart);   // 查找最后部分的子节点
            if (!child) {
                child = new TrieNode(lastPart);   // 若不存在，则创建新节点
                current->addChild(child);         // 添加到当前节点的子节点数组中
            }
        }
    }

    // 打印 Trie 树
    void Trieprint() {
        printTrie(root, "");   // 调用私有打印函数从根节点开始打印 Trie 树
    }

    // 将 Trie 树写入文件
    void writeToFile(const std::string& filename) {
        std::ofstream file(filename);   // 打开文件流进行写入
        if (!file.is_open()) {          // 检查文件是否成功打开
            std::cerr << "Failed to open file: " << filename << std::endl;  // 输出错误消息并返回
            return;
        }

        writeTrieToFile(file, root, "");   // 递归写入 Trie 树
        file.close();   // 关闭文件流
    }

    // 从文件中读取路径并插入到 Trie 树中的函数
    void readFromFile(const std::string& filename) {
        std::ifstream file(filename);   // 打开文件流进行读取
        if (!file.is_open()) {          // 检查文件是否成功打开
            std::cerr << "Failed to open file: " << filename << std::endl;  // 输出错误消息并返回
            return;
        }

        std::string line;   // 存储从文件中读取的每一行路径信息
        while (std::getline(file, line)) {   // 逐行读取文件内容
            insert(line);   // 将每一行路径插入到 Trie 树中
        }

        file.close();   // 关闭文件流
    }
};

// 从文件中读取详细信息并插入到 vector 中的函数
void readDetails(const std::string& filename, std::vector<FileDetail>& details) {
    std::ifstream file(filename);   // 打开文件流进行读取
    if (!file.is_open()) {          // 检查文件是否成功打开
        std::cerr << "Failed to open file: " << filename << std::endl;  // 输出错误消息并返回
        return;
    }

    std::string line;   // 存储从文件中读取的每一行详细信息
    while (std::getline(file, line)) {   // 逐行读取文件内容
        std::istringstream iss(line);    // 创建字符串流
        std::string name, type, creationDate, lastModDate, absPath;
        int id;
        if (iss >> name >> type >> creationDate >> lastModDate >> absPath >> id) {
            details.emplace_back(name, type, creationDate, lastModDate, absPath, id);   // 插入详细信息到 vector 中
        }
    }

    file.close();   // 关闭文件流
}

// 将详细信息写入文件的函数
void writeDetails(const std::string& filename, const std::vector<FileDetail>& details) {
    std::ofstream file(filename);   // 打开文件流进行写入
    if (!file.is_open()) {          // 检查文件是否成功打开
        std::cerr << "Failed to open file: " << filename << std::endl;  // 输出错误消息并返回
        return;
    }

    for (const auto& detail : details) {
        file << detail.name << " " << detail.type << " " << detail.creationDate << " "
             << detail.lastModDate << " " << detail.absPath << " " << detail.id << std::endl;   // 写入详细信息到文件
    }

    file.close();   // 关闭文件流
}

#endif // TREEOUT_H
