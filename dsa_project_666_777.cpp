
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// NAIVE STRING MATCHING ALGORITHM
vector<int> searchNaive(const string& text, const string& pattern,
                        long long& comparisons) {
    vector<int> positions;
    int n = text.size();
    int m = pattern.size();
    for (int i = 0; i <= n - m; i++) {
        int j = 0;
        while (j < m) {
            comparisons++;
            if (text[i + j] == pattern[j]) {
                j++;
            }
            else {
                break;
            }
        }
        if (j == m) {
            positions.push_back(i);
        }
    }
    return positions;
}
// KMP (Knuth-Morris-Pratt) STRING MATCHING ALGORITHM
vector<int> buildLPS(const string& pattern, long long& comparisons) {
    vector<int> lps(pattern.size(), 0);
    int len = 0;
    int i = 1;
    while (i < (int)pattern.size()) {
        comparisons++;
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}
// SEARCH ALL PATTERN OCCURRENCES USING KMP
vector<int> searchKMP(const string& text, const string& pattern,
                      long long& comparisons) {
    vector<int> positions;
    vector<int> lps = buildLPS(pattern, comparisons);
    int i = 0;
    int j = 0;
    while (i < (int)text.size()) {
        comparisons++;
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
        else {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
        if (j == (int)pattern.size()) {
            positions.push_back(i - j);
            j = lps[j - 1];
        }
    }
    return positions;
}
// HIGHLIGHT MATCHING PARTS IN THE MESSAGE
string highlightMatches(const string& message,
                        const vector<int>& positions,
                        int patternLength) {
    vector<bool> highlight(message.size(), false);
    for (int start : positions) {
        for (int i = start; i < start + patternLength; i++) {
            highlight[i] = true;
        }
    }
    string result;
    bool insideMatch = false;
    for (int i = 0; i < (int)message.size(); i++) {
        if (highlight[i] && !insideMatch) {
            result += "[[";
            insideMatch = true;
        }
        else if (!highlight[i] && insideMatch) {
            result += "]]";
            insideMatch = false;
        }
        result += message[i];
    }
    if (insideMatch) {
        result += "]]";
    }
    return result;
}
int main() {
    string message;
    int numberOfPatterns;
    cout << "===== CHAT MESSAGE SEARCH =====\n";
    cout << "\nEnter your chat message.\n";
    cout << "Type END on a new line to finish:\n\n";
    string line;
    while (true) {
        getline(cin, line);
        if (line == "END") {
            break;
        }
        if (!message.empty()) {
            message += "\n";
        }
        message += line;
    }
    if (message.empty()) {
        cout << "Chat message cannot be empty.\n";
        return 0;
    }
    cout << "\nEnter the number of patterns to search: ";
    cin >> numberOfPatterns;
    cin.ignore();
    if (numberOfPatterns <= 0) {
        cout << "Please enter at least one pattern.\n";
        return 0;
    }
    // SEARCH MULTIPLE PATTERNS
    for (int p = 1; p <= numberOfPatterns; p++) {
        string pattern;
        cout << "\nEnter pattern " << p << ": ";
        getline(cin, pattern);
        if (pattern.empty()) {
            cout << "Empty pattern is not allowed. Skipping this pattern.\n";
            continue;
        }
        long long naiveComparisons = 0;
        long long kmpComparisons = 0;
        // NAIVE SEARCH
        vector<int> naivePositions =
            searchNaive(message, pattern, naiveComparisons);
        // KMP SEARCH
        vector<int> kmpPositions =
            searchKMP(message, pattern, kmpComparisons);
        cout << "\n========== SEARCH RESULT ==========\n";
        cout << "Pattern: " << pattern << "\n";
        cout << "\n--- NAIVE STRING MATCHING ---\n";
        cout << "Number of matches: "
             << naivePositions.size() << "\n";
        cout << "Starting indices: ";
        if (naivePositions.empty()) {
            cout << "No matches found.";
        }
        else {
            for (int index : naivePositions) {
                cout << index << " ";
            }
        }
        cout << "\nCharacter comparisons: "
             << naiveComparisons << "\n";
        cout << "\n--- KMP STRING MATCHING ---\n";
        cout << "Number of matches: "
             << kmpPositions.size() << "\n";
        cout << "Starting indices: ";
        if (kmpPositions.empty()) {
            cout << "No matches found.";
        }
        else {
            for (int index : kmpPositions) {
                cout << index << " ";
            }
        }
        cout << "\nCharacter comparisons: "
             << kmpComparisons << "\n";
        // HIGHLIGHT MATCHING MESSAGE
        if (!kmpPositions.empty()) {
            cout << "\nHighlighted message:\n";
            cout << highlightMatches(
                message, kmpPositions, pattern.size()
            ) << "\n";
        }
        else {
            cout << "\nNo matching text to highlight.\n";
        }
        // COMPARE BOTH ALGORITHMS
        cout << "\n--- ALGORITHM COMPARISON ---\n";
        if (naivePositions == kmpPositions) {
            cout << "Both algorithms found the same matches.\n";
        }
        else {
            cout << "Warning: Matching positions are different!\n";
        }
        cout << "Comparison is based on character comparisons for this input.\n";
        if (naiveComparisons > kmpComparisons) {
            cout << "Winner: KMP Algorithm\n";
            cout << "KMP performed fewer character comparisons for this input.\n";
        }
        else if (naiveComparisons < kmpComparisons) {
            cout << "Winner: Naive Algorithm\n";
            cout << "Naive performed fewer character comparisons for this input.\n";
        }
        else {
            cout << "Result: DRAW\n";
            cout << "Both algorithms performed equal comparisons.\n";
        }
    }
    cout << "\nSearch completed!\n";
    return 0;
}
