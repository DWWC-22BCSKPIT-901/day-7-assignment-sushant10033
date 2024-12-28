Accounts Merge
Given a list of accounts where each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some common email to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

class UnionFind {
public:
    UnionFind(int size) {
        parent.resize(size);
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootY] = rootX;  // Union operation
        }
    }

private:
    vector<int> parent;
};

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    unordered_map<string, int> emailToId;  // Email to index
    UnionFind uf(accounts.size());
    unordered_map<int, string> idToName;  // Account index to name

    int emailId = 0;
    
    // Step 1: Create mappings for email to id and account index to name
    for (int i = 0; i < accounts.size(); ++i) {
        const string& name = accounts[i][0];
        idToName[i] = name;
        
        // For every email in the account, associate it with an index
        for (int j = 1; j < accounts[i].size(); ++j) {
            const string& email = accounts[i][j];
            if (emailToId.find(email) == emailToId.end()) {
                emailToId[email] = emailId++;
            }
            // Union the first email with the rest of the emails
            uf.unite(emailToId[accounts[i][1]], emailToId[email]);
        }
    }

    // Step 2: Group emails by root email
    unordered_map<int, unordered_set<string>> groups;
    for (const auto& pair : emailToId) {
        const string& email = pair.first;
        int id = uf.find(pair.second);
        groups[id].insert(email);
    }

    // Step 3: Prepare the result
    vector<vector<string>> result;
    for (auto& group : groups) {
        vector<string> account;
        account.push_back(idToName[group.first]);  // Name of the account
        account.insert(account.end(), group.second.begin(), group.second.end());  // Emails
        sort(account.begin() + 1, account.end());  // Sort emails
        result.push_back(account);
    }

    return result;
}

int main() {
    // Example usage:
    vector<vector<string>> accounts = {
        {"John", "johnsmith@mail.com", "john00@mail.com"},
        {"John", "johnnybravo@mail.com"},
        {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
        {"Mary", "mary@mail.com"}
    };

    vector<vector<string>> mergedAccounts = accountsMerge(accounts);
    
    // Print the merged accounts
    for (const auto& account : mergedAccounts) {
        for (const auto& str : account) {
            cout << str << " ";
        }
        cout << endl;
    }

    return 0;
}
