#include <bits/stdc++.h>
#define clo cout << "Time execute: " << clock() / (double)CLOCKS_PER_SEC << " sec" << endl;
#define FastIO ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#define nl << '\n';
#define yes cout << "YES" << '\n';
#define no cout << "NO" << '\n';

using namespace std;

void readFiles(); // to read files from input.txt, output to output.txt
int gcd2(int a, int b); // Gcd of 2 Numbers
int gcdV(vector<int> vec); // Gcd of a vector
int recursiveBinarySearch(vector<int> vec, int num, int start, int end);
int iterativeBinarySearch(const vector<int>& vec, int target);
void fillPrefixSum(vector <int> &vc, vector <int> &prefixSum, int starting_index = 0);




int main() {
    FastIO
    // readFiles();
    for(char c = 'A'; c <= 'Z'; c++){
        std::bitset<sizeof(char) * CHAR_BIT> binary(c);
        std::cout << "Letter: " << c << "\t";
        std::cout << "Hex: " << std::hex << (int)c << "\t";
        std::cout << "Binary: " << binary << std::endl;
    }

}











//vector sorting in descending order third parameter greater <int>() 

int iterativeBinarySearch(const vector<int>& vec, int target) {
    int low = 0, high = vec.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (vec[mid] == target) {
            return mid;
        } else if (vec[mid] > target) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}


// Default Parameters are Search Vector, Target, 0, vec.size() - 1
int recursiveBinarySearch(vector<int> vec, int num, int start, int end){
    if (start > end) {
        return -1; // Not found
    }
    int middle_index = (start + (end - start)  / 2);
    if(num == vec[middle_index]){
        return middle_index;
    }
    else if(num < vec[middle_index]){
        return recursiveBinarySearch(vec, num, start , middle_index - 1);
    }
    else{
        return recursiveBinarySearch(vec, num, middle_index + 1, end);
    }
}




// Note that Prefix problems are 1 based, thus I 1 based the array to start from index 1, not 0
// so you initialize prefix sum as size n + 1
// Parameters: 1. Array for Prefixing 2. Its size 3. The array to be filled with prefix sums, 4. Array index to start prefix summing from
void fillPrefixSum(vector <int> &vc, vector <int> &prefixSum, int starting_index) {
    prefixSum[0] = 0;
    int n = vc.size();
    for (int i = 1; i < n + 1; ++i) {
        prefixSum[i] = prefixSum[i - 1] + vc[starting_index + i - 1];
    }
}

// querying for a sum from array[x] to array[x + y], which equates to prefix[x + y] - prefix[x - 1]
// querying for a multiplication, Multiplication from array[x] to array[x + y] same algorithm but prefix[x + y] / prefix[x - 1]
// and you fill the array as a prefix multiplication not sum just edit the function, prefix[0] = 1, and instead of the + put *
// Frequency Range: you make an array for the letter, loop on the string, if is letter, modify array element to 1, else 0
// array will look something like this if string = abccabaac, and you're looking for A's
// [0, 1, 0, 0, 0, 1, 0, 1, 1, 0], now prefix sum this array, ex: 0 to 4
// which is 1 to 5 in our prefix array = prefix[5] - prefix[1-1] = 2 - 0 = 2
// for more than one letter you make a 2D array





void readFiles() {
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        // Check if files are open
        if (!cin) {
            cerr << "Error opening input file" << endl;
            exit(1);
        }
        if (!cout) {
            cerr << "Error opening output file" << endl;
            exit(1);
        }
    #endif
}

int gcd2(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int gcdV(vector<int> vec) {
    int tempVar = vec[0];
    for (int i = 1; i < vec.size(); ++i) {
        tempVar = gcd2(tempVar, vec[i]);
        if (tempVar == 1) return 1;
    }
    return tempVar;
}