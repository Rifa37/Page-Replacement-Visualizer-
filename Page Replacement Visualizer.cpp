#include <bits/stdc++.h>
using namespace std;

// Display function
void display(vector<vector<int>> frames, vector<bool> fault, vector<int> pages) {
    int n = pages.size();
    int f = frames.size();

    cout << "Page: ";
    for (int i = 0; i < n; i++) cout << pages[i] << " ";
    cout << endl;

    for (int i = 0; i < f; i++) {
        cout << "[" << i << "]: ";
        for (int j = 0; j < n; j++) {
            if (frames[i][j] == -1) cout << "- ";
            else cout << frames[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Fault: ";
    for (int i = 0; i < n; i++) {
        if (fault[i]) cout << "F ";
        else cout << ". ";
    }
    cout << endl;
}

// FIFO Algorithm
void FIFO(vector<int> pages, int capacity) {
    cout << "\n=== FIFO ===\n";

    int n = pages.size();
    vector<vector<int>> frames(capacity, vector<int>(n, -1));
    vector<bool> fault(n, false);

    queue<int> q;
    set<int> s;
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        if (s.find(pages[i]) == s.end()) {
            page_faults++;
            fault[i] = true;

            if (s.size() == capacity) {
                int val = q.front();
                q.pop();
                s.erase(val);
            }

            s.insert(pages[i]);
            q.push(pages[i]);
        }

        int j = 0;
        for (auto x : s) {
            frames[j][i] = x;
            j++;
        }
    }

    display(frames, fault, pages);
    cout << "Total Page Faults: " << page_faults << endl;
}

// LRU Algorithm
void LRU(vector<int> pages, int capacity) {
    cout << "\n=== LRU ===\n";

    int n = pages.size();
    vector<vector<int>> frames(capacity, vector<int>(n, -1));
    vector<bool> fault(n, false);

    vector<int> s;
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        auto it = find(s.begin(), s.end(), pages[i]);

        if (it == s.end()) {
            page_faults++;
            fault[i] = true;

            if (s.size() == capacity) {
                s.erase(s.begin());
            }
        } else {
            s.erase(it);
        }

        s.push_back(pages[i]);

        for (int j = 0; j < s.size(); j++) {
            frames[j][i] = s[j];
        }
    }

    display(frames, fault, pages);
    cout << "Total Page Faults: " << page_faults << endl;
}

// Optimal Algorithm
void Optimal(vector<int> pages, int capacity) {
    cout << "\n=== Optimal ===\n";

    int n = pages.size();
    vector<vector<int>> frames(capacity, vector<int>(n, -1));
    vector<bool> fault(n, false);

    vector<int> s;
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        if (find(s.begin(), s.end(), pages[i]) == s.end()) {
            page_faults++;
            fault[i] = true;

            if (s.size() < capacity) {
                s.push_back(pages[i]);
            } else {
                int farthest = i, idx = -1;

                for (int j = 0; j < s.size(); j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (s[j] == pages[k]) break;
                    }

                    if (k == n) {
                        idx = j;
                        break;
                    }

                    if (k > farthest) {
                        farthest = k;
                        idx = j;
                    }
                }

                s[idx] = pages[i];
            }
        }

        for (int j = 0; j < s.size(); j++) {
            frames[j][i] = s[j];
        }
    }

    display(frames, fault, pages);
    cout << "Total Page Faults: " << page_faults << endl;
}

// Main Function
int main() {
    int n, frames;

    cout << "Enter number of pages: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter reference string: ";
    for (int i = 0; i < n; i++) cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> frames;

    FIFO(pages, frames);
    LRU(pages, frames);
    Optimal(pages, frames);

    return 0;
}
