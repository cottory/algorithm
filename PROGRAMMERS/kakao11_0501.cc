#define MAX_X 100001
#define X first
#define NODE_NUMBER second
#define pii pair<int,int>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct Node{
    pii info;
    Node *left;
    Node *right;
    Node(pii val) : info(val), left(nullptr), right(nullptr) {}
}Node;

//preOrder 결과담는 vector
//postOrder 결과담는 vector
vector<int> pre_ret, post_ret;  

//Y(높이)를 기준으로 한 높이당 하나의 PQ를 가지고 있는 vector
vector< priority_queue<pii> > nodeList_based_on_y;

//1정렬기준: Y축 값(내림차순)
//2정렬기준: X축 값(오름차순)
bool comp(vector<int> v1, vector<int> v2)
{
    return v1[1] == v2[1] ? v1[0] < v2[0] : v1[1] > v2[1];
}

void preOrder(Node* tree)
{
    pre_ret.push_back(tree->info.NODE_NUMBER);
    if (tree->left) preOrder(tree->left);
    if (tree->right) preOrder(tree->right);
}

void postOrder(Node* tree)
{
    if (tree->left) postOrder(tree->left);
    if (tree->right) postOrder(tree->right);
    post_ret.push_back(tree->info.NODE_NUMBER);
}

Node* makeBinaryTree(int maxX, int level, int maxHeight, vector< priority_queue<pii> >& vpq)
{
    //★★현재 도달한 깊이에서 하나의 Node 생성★★
    int x = -vpq[level].top().X;
    int node_number = vpq[level].top().NODE_NUMBER;
    vpq[level].pop();
    Node* root = new Node({x,node_number});

    //1. 기저사례: 마지막 레벨이거나 자식 노드가 없다면 바로 return
    if (level == maxHeight || vpq[level+1].empty())
        return root;
    
    //2. make Next Node
    int next_x = -vpq[level+1].top().X;
    
    //2-1. make left Child
    if (next_x < x)
        root->left = makeBinaryTree(x, level +1, maxHeight, vpq);
    
    //2-2. make right child

    //2-2-1. left Child를 만든 후, Right Child를 만들 수 있는 노드가 없다면 바로 root 리턴
    if (vpq[level+1].empty())
        return root;

    //2-2-2. left Child를 만든 후, 그 다음 Right Child 후보의 x좌표 get
    next_x = -vpq[level+1].top().X;
    
    if (x < next_x && next_x < maxX)
        root->right = makeBinaryTree(maxX, level + 1, maxHeight, vpq);

    return root;
}

//nodeinfo:: [0]: X좌표, [1]: Y좌표
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {

    vector<vector<int>> answer;

    for (int nodeNumber, i = 0; i < nodeinfo.size(); ++i)
    {   
        //순회 계산을 위해 노드 정보에 몇 번째로 들어온 노드였는지 value 추가
        nodeNumber = i +1;
        nodeinfo[i].push_back(nodeNumber);
    }
    
    sort(nodeinfo.begin(), nodeinfo.end(), comp);

    int beforeHeight = -1;  //Y value
    int treeHeight = -1;    //전체 트리 높이값 저장

    for (int i = 0; i < nodeinfo.size(); ++i)
    {
        int nowHeight = nodeinfo[i][1];
        
        if (beforeHeight != nowHeight)
        {
            nodeList_based_on_y.push_back(priority_queue<pii>());
            beforeHeight = nowHeight;
            treeHeight++;
        }
        
        nodeList_based_on_y[treeHeight].push({-nodeinfo[i][0],nodeinfo[i][2]});
    }

    Node* root = makeBinaryTree(MAX_X, 0, treeHeight, nodeList_based_on_y);

    preOrder(root);
    postOrder(root);
    answer.push_back(pre_ret);
    answer.push_back(post_ret);

    return answer;
}