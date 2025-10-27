#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

void create_substrings(string &s) {
    int n = s.length();
    int max_len = 0;
    string longest_substring;

    // Two-pointer technique
    for (int i = 0; i < n; ++i) {
        string current = "";
        unordered_set<char> seen; // to check for repeated characters

        for (int j = i; j < n; ++j) {
            char c = s[j];
            // if repeated, break and start new substring
            if (seen.find(c) != seen.end())
                break;

            current += c;
            seen.insert(c);

            // update longest substring
            if (current.length() > max_len) {
                max_len = current.length();
                longest_substring = current;
            }
        }
    }

    cout << "Longest substring without repeating chars: " << longest_substring << endl;
    cout << "Length: " << max_len << endl;
}

int main() {
    string main_str;  // variable name 'main' conflicts with function main()
    cout << "Enter main string: ";
    cin >> main_str;

    create_substrings(main_str);
}

