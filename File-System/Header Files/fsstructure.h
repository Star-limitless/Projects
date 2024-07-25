#ifndef FSSTRUCTURE_H
#define FSSTRUCTURE_H

#include <iostream>
#include <fstream>
#include <string>

class TrieNode {
public:
    std::string name;
    TrieNode* children[10];  // 假设最多有10个子节点
    int childrenCount;

    TrieNode(const std::string& name);
    void addChild(TrieNode* child);
    TrieNode* getChild(const std::string& name);
};

class Trie {
private:
    TrieNode* root;

    void printTrie(std::ostream& os, TrieNode* node, const std::string& prefix, bool isLast) const;

public:
    Trie();
    void insert(const std::string& path);
    void printToStream(std::ostream& os) const;
};

void readAndInsertPaths(const std::string& filename, Trie& trie);

#endif // FSSTRUCTURE_H
