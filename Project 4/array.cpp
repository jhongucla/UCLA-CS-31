#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);

int main()
{
    string a[7] = {"bernie", "marco", "hillary", "jeb", "carly", "ben", "donald"};
    
    assert(appendToAll(a, -2, "!!!") == -1 && a[0] == "bernie" && a[6] == "donald");
    assert(appendToAll(a, 7, "!!!") == 7 && a[0] == "bernie!!!" && a[6] == "donald!!!");
    
    string b[5] = {"bernie", "marco", "hillary", "marco", "carly"};
    
    assert(appendToAll(b, 1, "!!!") == 1 && b[0] == "bernie!!!" && b[4] == "carly");
    assert(lookup(b, 5, "hillary") == 2);
    assert(lookup(b, 4, "marco") == 1);
    assert(lookup(b, 0, "marco") == -1);
    assert(lookup(b, -1, "marco") == -1);
    assert(lookup(b, 5, "obama") == -1);
    
    assert(positionOfMax(b, 5) == 1);
    assert(positionOfMax(b, 1) == 0);
    assert(positionOfMax(b, 0) == -1);
    assert(positionOfMax(a, 7) == 1);
    assert(positionOfMax(a, -1) == -1);
    
    string c[5] = {"bernie", "marco", "hillary", "marco", "carly"};
    
    assert(rotateLeft(c, 5, 1) == 1 && c[0] == "bernie" && c[1] == "hillary" && c[4] == "marco");
    
    string d[4] = {"bernie", "marco", "hillary", "carly"};
    
    assert(rotateLeft(d, 3, 0) == 0 && d[0] == "marco" && d[1] == "hillary" && d[2] == "bernie");
    assert(rotateLeft(d, -1, -1) == -1);
    
    assert(countRuns(a, 7) == 7);
    assert(countRuns(a, 3) == 3);
    assert(countRuns(a, 0) == 0);
    
    string e[8] = {"bernie", "bernie", "marco", "hillary", "hillary", "hillary", "ben", "donald"};
    
    assert(countRuns(e, 8) == 5);
    assert(countRuns(e, -1) == -1);
    
    assert(flip(e, 8) == 8 && e[0] == "donald" && e[1] == "ben" && e[7] == "bernie");
    assert(flip(e, 8) == 8 && e[0] == "bernie" && e[1] == "bernie" && e[7] == "donald");
    assert(flip(e, 3) == 3 && e[0] == "marco" && e[2] == "bernie" && e[7] == "donald");
    assert(flip(e, 0) == 0);
    assert(flip(e, -1) == -1);
    
    string f[5] = {"bernie", "marco", "chris", "hillary", "donald"};
    string g[4] = {"bernie", "marco", "donald", "chris"};
    
    assert(differ(f, 5, g, 4) == 2);
    assert(differ(f, 4, g, 2) == 2);
    assert(differ(f, 2, g, 4) == 2);
    assert(differ(f, 0, g, 2) == 0);
    assert(differ(f, -1, g, 2) == -1);
    
    string h[6] = {"marco", "jeb", "mike", "carly", "ted", "donald"};
    string i[3] = {"mike", "carly", "ted"};
    string j[3] = {"mike", "jeb", "ted"};
    string k[0];
    
    assert(subsequence(h, 6, i, 3) == 2);
    assert(subsequence(h, 5, i, 3) == 2);
    assert(subsequence(h, 6, i, 2) == 2);
    assert(subsequence(h, 6, j, 3) == -1);
    assert(subsequence(h, -1, i, 3) == -1);
    assert(subsequence(i, 3, k, 0) == 0);
    assert(subsequence(h, 0, i, 2) == -1);
    
    string l[5] = {"donald", "marco", "hillary", "carly", "bernie"};
    string m[5] = {"carly", "jeb", "mike", "marco", "ted"};
    
    assert(lookupAny(l, 5, m, 5) == 1);
    assert(lookupAny(l, 4, m, 2) == 3);
    assert(lookupAny(l, 0, m, 2) == -1);
    assert(lookupAny(l, 3, m, 3) == -1);
    assert(lookupAny(l, -1, m, 2) == -1);
    
    string o[7] = {"marco", "jeb", "mike", "ted", "hillary", "carly", "bernie"};
    string p[7] = {"marco", "jeb", "mike", "ted", "hillary", "carly", "bernie"};
    string q[7] = {"marco", "jeb", "mike", "ted", "hillary", "carly", "bernie"};
    
    assert(split(o, 7, "hillary") == 2);
    assert(split(p, 7, "rand") == 6);
    assert(split(q, 4, "mark") == 2);
    assert(split(q, -1, "hillary") == -1);
    assert(split(q, 0, "jeb") == 0);
    
    cout << "ALL TESTS SUCCEEDED!" << endl;
}

int appendToAll(string a[], int n, string value)
{
    if (n < 0) // check for bad input
        return -1;
    for (int k = 0; k < n; k++)
        a[k] += value; // appends value to each element
    return n;
}

int lookup(const string a[], int n, string target)
{
    if (n < 0) // check for bad input
        return -1;
    for (int k = 0; k < n; k++)
    {
        if (a[k] == target) // searches for target string and returns index of match
            return k;
    }
    return -1;
}

int positionOfMax(const string a[], int n)
{
    if (n <= 0) // check for bad input
        return -1;
    string max = a[0]; // sets initial max to first element
    int maxPos = 0;
    for (int k = 0; k < n; k++)
    {
        if (a[k] > max)
        {
            max = a[k]; // if there is a new max string, max is updated and the index position is saved
            maxPos = k;
        }
    }
    return maxPos;
}

int rotateLeft(string a[], int n, int pos)
{
    if (n <= 0 || pos < 0 || pos > n-1) // check for bad input
        return -1;
    string rotated = a[pos]; // saves a temporary copy of the element to move
    for (int k = pos; k < n - 1; k++)
        a[k] = a[k+1]; // rotates all elements left
    a[n-1] = rotated; // puts copy of element at the end of the string
    return pos;
}

int countRuns(const string a[], int n)
{
    if (n < 0) // check for bad input
        return -1;
    else if (n == 0) // an empty array has 0 runs
        return 0;
    int count = 1;
    for (int k = 0; k < n-1; k++)
    {
        if (a[k] != a[k+1]) // every time the elements change, a counter is incremented
            count++;
    }
    return count;
}

int flip(string a[], int n)
{
    if (n < 0) // check for bad input
        return -1;
    int j = 0, middle = 0;
    if (n % 2 == 0) // sets the middle of the array where elements should stop being swapped, depending on odd/even # of elements
        middle = n/2;
    else
        middle = n/2 + 1;
    for (int k = n-1; k >= middle; k--)
    {
        string temp = a[k]; // swaps elements from the left and right of the array until the middle is reached
        a[k] = a[j];
        a[j] = temp;
        j++;
    }
    return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0) // check for bad input
        return -1;
    else if (n1 == 0 || n2 == 0)
        return 0;
    int i = 0, j = 0, pos = 0;
    bool differs = false; // boolean for whether a differing element is found or not
    while (!differs) // loops until a differing element is found
    {
        if (a1[i] != a2[j]) // if a differing element is found, the position is saved and differs becomes true
        {
            differs = true;
            pos = i;
        }
        else if (i + 1 == n1 || j + 1 == n2) // if no differing element is found before the end of either array is reached
        {
            if (n1 < n2)
                return n1; // returns the smaller of n1 and n2
            return n2;
        }
        else
        {
            i++; // increments indexes for both arrays
            j++;
        }
    }
    return pos;
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0) // check for bad input
        return -1;
    else if (n2 == 0) // a sequence of 0 elements is a subsequence of any sequence
        return 0;
    int j = -1, pos = -1;
    bool found = false; // variable to store whether a subsequence is found or not
    while (!found)
    {
        for (int k = 0; k < n1; k++)
        {
            if (a1[k] == a2[0]) // if a matching element is found, the location is saved in both j and pos
            {
                j = pos = k;
                break;
            }
        }
        if (j == -1) // j = -1 when no matching element is found
            return -1;
        for (int i = 0; i < n2; i++) // checks to see if the rest of the second array is a subsequence of the first
        {
            if (a1[j] != a2[i]) // if the subsequence is not complete
                return -1;
            else if (j == n1) // if the first array ends before a subsequence is complete
                return -1;
            else
                j++;
        }
        found = true; // a subsequence is found when execution of the function reaches here
    }
    return pos;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0) // check for bad input
        return -1;
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++) // check each element in the second array to see if it matches an element in the first array
        {
            if (a1[i] == a2[j])
                return i;
        }
    }
    return -1;
}

int split(string a[], int n, string splitter)
{
    if (n < 0) // check for bad input
        return -1;
    bool sorted = false; // variable to store whether the array is sorted alphabetically
    while (!sorted)
    {
        for (int k = 0; k < n-1; k++) // the array is sorted progressively each time the for loop runs
        {
            if (a[k] > a[k+1])
            {
                string temp = a[k];
                a[k] = a[k+1];
                a[k+1] = temp;
            }
        }
        sorted = true;
        for (int k = 0; k < n-1; k++) // this for loop checks to see whether the array is sorted alphabetically
        {
            if (a[k] > a[k+1])
                sorted = false;
        }
    }
    for (int k = 0; k < n; k++)
    {
        if (a[k] >= splitter) // finds the position of the first element that is not less than splitter
            return k;
    }
    return n; // if there are no elements not less than splitter
}
