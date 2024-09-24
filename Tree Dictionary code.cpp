#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class nodes {
public:
    map<char, nodes*> chn;
    bool ending;

    nodes() {
        ending = false;
    }
};

class algorithm {
private:
    nodes* root;

    void collect(nodes* node, string s, vector<string>& res) {
        if (node->ending) {
            res.push_back(s);
        }
        for (auto tt : node->chn) {
            collect(tt.second, s + tt.first, res);
        }
    }

    bool deletemethod(nodes* node, const string& str, int d) {
        if (!node) return false;
        if (d == static_cast<int>(str.size())) {
            if (node->ending) {
                node->ending = false;
            }
            return node->chn.empty();
        }

        char c = str[d];
        if (node->chn.find(c) == node->chn.end()) {
            return false;
        }
        if (deletemethod(node->chn[c], str, d + 1)) {
            delete node->chn[c];
            node->chn.erase(c);
            return !node->ending && node->chn.empty();
        }
        return false;
    }

    void findLongest(nodes* node, string& str, string& longeststr) {
        if (!node) return;

        if (node->ending && str.length() > longeststr.length()) {
            longeststr = str;
        }

        for (auto& c : node->chn) {
            str.push_back(c.first);
            findLongest(c.second, str, longeststr);
            str.pop_back();
        }
    }

public:
    algorithm() {
        root = new nodes();
    }

    ~algorithm() {
        deleteNodes(root);
    }

    void insert(const string& str) {
        nodes* node = root;
        for (char c : str) {
            if (!node->chn[c]) {
                node->chn[c] = new nodes();
            }
            node = node->chn[c];
        }
        node->ending = true;
    }

    void remove(const string& str) {
        deletemethod(root, str, 0);
    }

    bool search(const string& str) {
        nodes* node = root;
        for (char c : str) {
            if (node->chn.find(c) == node->chn.end()) {
                return false;
            }
            node = node->chn[c];
        }
        return node->ending;
    }

    vector<string> startsWith(const string& str) {
        vector<string> res;
        nodes* node = root;
        for (char c : str) {
            if (node->chn.find(c) == node->chn.end()) {
                return res;
            }
            node = node->chn[c];
        }
        collect(node, str, res);
        sort(res.begin(), res.end());
        return res;
    }

    string longest() {
        string longeststr = "";
        string currentstr = "";
        findLongest(root, currentstr, longeststr);
        return longeststr;
    }

private:
    void deleteNodes(nodes* node) {
        if (!node) return;
        for (auto& kv : node->chn) {
            deleteNodes(kv.second);
        }
        delete node;
    }
};

int main() {
    algorithm algo;
    int counter;
    cin >> counter;
    while (counter--) {
        string command;
        cin >> command;
        if (command == "insert") {
            string str;
            cin >> str;
            algo.insert(str);
        }
        else if (command == "delete") {
            string str;
            cin >> str;
            algo.remove(str);
        }
        else if (command == "search") {
            string str;
            cin >> str;
            cout << (algo.search(str) ? "YES" : "NO") << endl;
        }
        else if (command == "startwith") {
            string str;
            cin >> str;
            vector<string> ress = algo.startsWith(str);
            for (const string& res : ress) {
                cout << res << endl;
            }
        }
        else if (command == "longest") {
            cout << algo.longest() << endl;
        }
    }
    return 0;
}
