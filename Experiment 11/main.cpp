
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct Node
{
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f)
    {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

struct Compare
{
    bool operator()(Node* a, Node* b)
    {
        return a->freq > b->freq;
    }
};

void printCodes(Node* root, string code)
{
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr)
    {
        cout << root->ch << " : "
             << (code.empty() ? "0" : code) << endl;
        return;
    }

    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

void huffmanCoding(vector<char>& chars,
                   vector<int>& freq, int n)
{
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (int i = 0; i < n; i++)
    {
        pq.push(new Node(chars[i], freq[i]));
    }

    while (pq.size() > 1)
    {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        pq.push(top);
    }

    cout << "\nHuffman Codes:\n";
    printCodes(pq.top(), "");
}

int main()
{
    int n;

    cout << "Enter number of characters: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Invalid number of characters." << endl;
        return 0;
    }

    vector<char> chars(n);
    vector<int> freq(n);

    cout << "Enter characters:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> chars[i];
    }

    cout << "Enter frequencies:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> freq[i];

        if (freq[i] < 0)
        {
            cout << "Frequency cannot be negative." << endl;
            return 0;
        }
    }

    huffmanCoding(chars, freq, n);

    return 0;
}
