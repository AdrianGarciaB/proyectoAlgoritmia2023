//Este programa solo pone el valor donde el x0 es el mediano de toda la lista de valores x0 del arbol como primer valor de la lista

#include <iostream>
#include <bits/stdc++.h>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<double> Coord;

// Standard partition process of QuickSort().
// It considers the last element as pivot
// and moves all smaller element to left of
// it and greater elements to right
int partition(vector<Coord>& arr, int l, int r)
{
    double x = arr[r][0], i = l;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j][0] <= x) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[r]);
    return i;
}
  
// This function returns k'th smallest 
// element in arr[l..r] using QuickSort 
// based method.  ASSUMPTION: ALL ELEMENTS
// IN ARR[] ARE DISTINCT
int kthSmallest(vector<Coord>& arr, int l, int r, int k)
{
    // If k is smaller than number of 
    // elements in array
    if (k > 0 && k <= r - l + 1) {
  
        // Partition the array around last 
        // element and get position of pivot 
        // element in sorted array
        int index = partition(arr, l, r);
  
        // If position is same as k
        if (index - l == k - 1)
            return index;
  
        // If position is more, recur 
        // for left subarray
        if (index - l > k - 1) 
            return kthSmallest(arr, l, index - 1, k);
  
        // Else recur for right subarray
        return kthSmallest(arr, index + 1, r, 
                            k - index + l - 1);
    }
  
    // If k is more than number of 
    // elements in array
    return INT_MAX;
}

bool cmp(Coord a, Coord b) {
    return a[0] < b[0];
}

int main() {

    int T;      //num de arboles a generar
    int k;      //dimension de cada arbol
    int n;      //num de nodos de cada arbol

    cout << "Numero de arboles:" << endl; 
    cin >> T;

    srand(time(NULL));

    for (int i = 1; i <= T; ++i) {
        cout << "Dimension:" << endl;
        cin >> k;
        cout << "Numero de nodos:" << endl;
        cin >> n;

        cout << "Arbol #" << i << ": " << k << " dimensiones y " << n << " nodos" << endl;
        vector<Coord> Coords(n, Coord(k));

        for(int j = 0; j < n; ++j) {
            for(int l = 0; l < k; ++l) {
                double val = double(rand()/double(RAND_MAX));
                Coords[j][l] = val;
            }
        }
        
        int e = kthSmallest(Coords, 0, Coords.size()-1, Coords.size()/2);
        cout << Coords[e][0] << endl;
        swap(Coords[0], Coords[e]);

        for (int j = 0; j < n; ++j) {
            for (int l = 0; l < k; ++l) {
                cout << Coords[j][l] << " ";
            }
            cout << endl;
        }

        cout << endl << endl << "----------------------------------" << endl << endl;
    }

}