#ifndef SUFFIX_TREE_HPP
#define SUFFIX_TREE_HPP

#include <memory>
#include <string>
#include <vector>

class TSuffixTree {
private:
    struct TEdge {
        int Left;
        std::shared_ptr<int> Right;
        int IdTo;

        TEdge(int l, std::shared_ptr<int> r, int id) : Left(l), Right(r), IdTo(id) {}
    };

    std::string DataString;
    std::vector< std::vector< TSuffixTree::TEdge > > Data;
    std::vector<int> SuffixPtr;
    std::vector<int> PathSize;
public:
    TSuffixTree(const std::string & s);
    std::string LexMinString(const size_t & n);
    std::string LexMinString(const int id, const size_t & n);
};

#endif /* SUFFIX_TREE_HPP */
