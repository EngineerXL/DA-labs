#include "suffix_tree.hpp"

TSuffixTree::TSuffixTree(const std::string & s) : DataString(s), Data(s.size() * 2), SuffixPtr(s.size() * 2), PathSize(s.size() * 2) {
    bool newVertex = false;
    std::shared_ptr<int> end(new int);
    *end = 0;
    int curVertex = 0;
    int l = 0;
    int vertexId = 0;
    int curEq = 0;
    int passEq = 0;
    int curEdgeId = -1;
    for (size_t i = 0; i < s.size(); ++i) {
        ++*end;
        int lastCreatedVertexId = 0;
        int nextCreatedVertexId = -1;
        while (l < *end) {
            if (curEdgeId == -1) {
                int nextEdgeId = -1;
                for (size_t j = 0; j < Data[curVertex].size(); ++j) {
                    if (DataString[Data[curVertex][j].Left] == DataString[l + passEq + curEq]) {
                        nextEdgeId = j;
                        curEq = 1;
                        break;
                    }
                }
                if (nextEdgeId == -1) {
                    newVertex = true;
                }
                curEdgeId = nextEdgeId;
            } else {
                if (DataString[Data[curVertex][curEdgeId].Left + curEq] == DataString[l + curEq + passEq]) {
                    ++curEq;
                } else {
                    newVertex = true;
                }
            }
            if (curEq > 0 and Data[curVertex][curEdgeId].Left + curEq == *Data[curVertex][curEdgeId].Right) {
                curVertex = Data[curVertex][curEdgeId].IdTo;
                curEdgeId = -1;
                passEq = passEq + curEq;
                curEq = 0;
            }
            if (newVertex) {
                ++vertexId;
                if (curEq == 0 and curEdgeId == -1) {
                    Data[curVertex].push_back(TSuffixTree::TEdge(l + passEq, end, vertexId));
                } else {
                    nextCreatedVertexId = vertexId;
                    TEdge curEdge = Data[curVertex][curEdgeId];
                    std::shared_ptr<int> newRightBorder(new int);
                    *newRightBorder = Data[curVertex][curEdgeId].Left + curEq;
                    Data[curVertex][curEdgeId].Right = newRightBorder;
                    Data[curVertex][curEdgeId].IdTo = vertexId;
                    curEdge.Left = *newRightBorder;

                    Data[vertexId].push_back(curEdge);
                    ++vertexId;
                    Data[vertexId - 1].push_back(TSuffixTree::TEdge(l + curEq + passEq, end, vertexId));
                    PathSize[vertexId - 1] = PathSize[curVertex] + *Data[curVertex][curEdgeId].Right - Data[curVertex][curEdgeId].Left;

                    if (lastCreatedVertexId > 0) {
                        SuffixPtr[lastCreatedVertexId] = nextCreatedVertexId;
                    }
                    lastCreatedVertexId = nextCreatedVertexId;
                }
                int nextCurVertex = SuffixPtr[curVertex];
                int nextPassEq = PathSize[nextCurVertex];
                int nextCurEq = curEq + passEq - nextPassEq - 1;
                int nextEdgeId = -1;
                while (nextCurEq > 0) {
                    for (size_t j = 0; j < Data[nextCurVertex].size(); ++j) {
                        if (DataString[Data[nextCurVertex][j].Left] == DataString[l + 1 + nextPassEq]) {
                            nextEdgeId = j;
                            break;
                        }
                    }
                    int curRight = *Data[nextCurVertex][nextEdgeId].Right;
                    int curLeft = Data[nextCurVertex][nextEdgeId].Left;
                    if (nextEdgeId != -1 and curRight - curLeft <= nextCurEq) {
                        nextPassEq = nextPassEq + curRight - curLeft;
                        nextCurEq = nextCurEq - curRight + curLeft;
                        nextCurVertex = Data[nextCurVertex][nextEdgeId].IdTo;
                        nextEdgeId = -1;
                    } else {
                        break;
                    }
                }
                if (nextEdgeId != -1) {
                    curEq = nextCurEq;
                } else {
                    curEq = 0;
                }
                curEdgeId = nextEdgeId;
                curVertex = nextCurVertex;
                passEq = nextPassEq;
                ++l;
                newVertex = false;
            } else {
                if (i < s.size() - 1) {
                    break;
                }
            }
        }
    }
}

std::string TSuffixTree::LexMinString(const size_t & n) {
    return LexMinString(0, n);
}

std::string TSuffixTree::LexMinString(const int id, const size_t & n) {
    char lexMinId = 0;
    for (size_t i = 0; i < Data[id].size(); ++i) {
        if (DataString[Data[id][i].Left] < DataString[Data[id][lexMinId].Left]) {
            lexMinId = i;
        }
    }
    size_t curEdgeLen = *Data[id][lexMinId].Right - Data[id][lexMinId].Left;
    if (n <= curEdgeLen) {
        return DataString.substr(Data[id][lexMinId].Left, n);
    } else {
        std::string res = DataString.substr(Data[id][lexMinId].Left, curEdgeLen);
        return res + LexMinString(Data[id][lexMinId].IdTo, n - curEdgeLen);
    }
}
