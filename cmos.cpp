#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

// Function to tokenize the content of a submission into shingles
vector<string> tokenize(string content, int k) {
    vector<string> shingles;
    for (size_t i = 0; i <= content.size() - k; ++i) {
        shingles.push_back(content.substr(i, k));
    }
    return shingles;
}

// Function to calculate the hash value of a shingle
size_t hashShingle(const string& shingle) {
    // Use a simple hash function for demonstration
    size_t hash = 0;
    for (char c : shingle) {
        hash = (hash * 31) + c; // Arbitrary prime number
    }
    return hash;
}

// Function to apply the Winnowing Algorithm and select fingerprints
vector<size_t> winnowing(const vector<size_t>& hashes, int windowSize) {
    vector<size_t> fingerprints;
    for (size_t i = 0; i <= hashes.size() - windowSize; ++i) {
        size_t minHash = *min_element(hashes.begin() + i, hashes.begin() + i + windowSize);
        fingerprints.push_back(minHash);
    }
    return fingerprints;
}

int main() {
    // Parameters
    const int k = 5; // Shingle size
    const int windowSize = 5; // Window size for Winnowing Algorithm

    // Read the content of the tokens.txt file
    ifstream inFile("tokens.txt");
    if (!inFile) {
        cerr << "Error: Unable to open tokens.txt" << endl;
        return 1;
    }

    // Vector to store fingerprints for each submission
    vector<vector<size_t>> fingerprints;

    string line;
    while (getline(inFile, line)) {
        // Tokenize the content into shingles
        vector<string> shingles = tokenize(line, k);

        // Calculate the hash value of each shingle
        vector<size_t> hashes;
        for (const auto& shingle : shingles) {
            hashes.push_back(hashShingle(shingle));
        }

        // Apply the Winnowing Algorithm to select fingerprints
        vector<size_t> submissionFingerprints = winnowing(hashes, windowSize);

        // Store fingerprints for this submission
        fingerprints.push_back(submissionFingerprints);
    }

    // Output fingerprints for each submission
    for (size_t i = 0; i < fingerprints.size(); ++i) {
        cout << "Submission " << i+1 << " fingerprints: ";
        for (size_t fingerprint : fingerprints[i]) {
            cout << fingerprint << " ";
        }
        cout << endl;
    }

    return 0;
}
