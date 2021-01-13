//
// Created by kirilloid on 15.12.2020.
//

#include <bits/stdc++.h>

using namespace std;

const int k = 27;
vector<int> ans(1000001, 0);

struct Node {
    Node *son[k]{};
    Node *go[k]{};
    Node *parent{};
    Node *suffLink{};
    Node *up{};
    int charToParent{};
    bool isTerminal{};
    int count = 0;
    vector<int> leafPatternNumber;
    vector<Node *> nodeTree;
};

Node *root;

void addString(string &s, int leafPatternNumber) {
    Node *cur = root;
    for (auto now : s) {
        int c = now - 97;
        if (cur->son[c] == nullptr) {
            cur->son[c] = new Node;
            cur->son[c]->parent = cur;
            cur->son[c]->suffLink = nullptr;
            cur->son[c]->up = nullptr;
            cur->son[c]->charToParent = now - 97;
            cur->son[c]->isTerminal = false;
        }
        cur = cur->son[c];
    }
    cur->isTerminal = true;
    cur->leafPatternNumber.push_back(leafPatternNumber);
}

Node *getSuffLink(Node *v);

Node *getLink(Node *v, int c) {
    if (v->go[c] == nullptr) {
        if (v->son[c] != nullptr)
            v->go[c] = v->son[c];
        else if (v == root)
            v->go[c] = root;
        else
            v->go[c] = getLink(getSuffLink(v), c);
    }
    return v->go[c];
}

Node *getSuffLink(Node *v) {
    if (v->suffLink == nullptr) {
        if (v == root || v->parent == root)
            v->suffLink = root;
        else
            v->suffLink = getLink(getSuffLink(v->parent), v->charToParent);
        v->suffLink->nodeTree.push_back(v);
    }
    return v->suffLink;
}

Node *getUp(Node *v) {
    if (v->up == nullptr) {
        if (getSuffLink(v)->isTerminal)
            v->up = getSuffLink(v);
        else if (getSuffLink(v) == root)
            v->up = root;
        else
            v->up = getUp(getSuffLink(v));
    }
    return v->up;
}

int dfs(Node *v) {
    int count = v->count;
    for (auto now : v->nodeTree) {
        count += dfs(now);
    }
    if (v->isTerminal) {
        for (int now : v->leafPatternNumber) {
            ans[now] = count;
        }
    }
    return count;
}

void bfs(Node *s) {
    queue<Node *> q;
    q.push(s);
    while(!q.empty()) {
        Node * cur = q.front();
        q.pop();
        for (auto now : cur->son) {
            if (now != nullptr) {
                getSuffLink(now);
                q.push(now);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    root = new Node;
    root->parent = root;
    root->suffLink = root;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        addString(s, i);
    }
    string t;
    cin >> t;
    Node *cur = root;
    bfs(root);
    for (auto c : t) {
        cur = getLink(cur, c - 'a');
        cur->count++;
    }
    dfs(root);
    for (int i = 0; i < n; i++)
        cout << ans[i] << '\n';
}
