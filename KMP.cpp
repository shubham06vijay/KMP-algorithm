#include <iostream>
#include <bits/stdc++.h>

using namespace std;
/**
  Computes the LPS array for the KMP algorithm
  Complexity: if pat.length() == m
              then O(m)
**/
void computeLPSArray(string pat, int* lps)
{
    int len = 0;
    int M= pat.length();
    lps[0] = 0;
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0) {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
/**
  Returns the vector of integers giving the positions of the indices of matches in the larger array
  that is StringA
  THIS IS THE KMP SEARCH algorithm.
  Complexity: if txt.length()== n and pat.length() == m
              then O(m+n)
**/
vector<int> KMPSearch(string pat, string txt)
{
    vector<int> answer;

    int M = pat.length();
    int N = txt.length();

    int lps[M];

    computeLPSArray(pat, lps);

    bool found = true;

    int i = 0;

    while(found) {
        found = false;
        int j = 0;
        while (i < N) {
            if (pat[j] == txt[i]) {
                j++;
                i++;
            }

            if (j == M) {
                found = true;
                answer.push_back(i - j);
                j = lps[j - 1];
            }

            else if (i < N && pat[j] != txt[i]) {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i = i + 1;
            }
        }
    }

    return answer;
}
int main()
{
    string txt,pat1,pat2;
    cout << "Enter string A = ";
    cin >> txt;
    cout << "Enter SearchStringB  = ";
    cin >> pat1;
    cout << "Enter SearchStringC = ";
    cin >> pat2;

    /**
      Complexity: if n= A.length() and m1= B.length() and m2= C.length()
                  then Complexity = O(n+m1) + O(n+m2)
                  IT IS LINEAR
    **/
    vector<int> pat1ind = KMPSearch(pat1, txt);
    vector<int> pat2ind = KMPSearch(pat2, txt);

    if(pat1ind.size()!=0 and pat2ind.size()!=0)
    {
      cout << "*******************************************************************\n";
      cout << "positions of SearchStringB in String A: ";
      for(auto i: pat1ind)
          cout << i << " ";
      cout << endl;

      cout << "\n";
      cout << "positions of SearchStringC in String A: ";
      for(auto i: pat2ind)
          cout << i << " ";
      cout << endl;


      bool isOverlapping = false;
      int j = 0;
      /**
        The following code will process both the vectors pat1ind and pat2ind for their overlap
        so Complexity: if n1=pat1ind.size() {No. of times the pat1 appears in String A}
                      and n2= pat2ind.size() {No. of times the pat2 appears in String A}
                      then the following for loop will run for O(n1 + n2)
                      n1 + n2 can have a max value of n.
                      so this loop is also O(n)
      **/
      for(int i = 0; i < pat1ind.size() && !isOverlapping; i++){
          // Processing all pat2ind elements which are smaller than i
          while(pat2ind[j] < pat1ind[i] and pat2ind[j] + pat2.length() < pat1ind[i] and j < pat2ind.size()){
              j++;
          }
          //Then Checking for a overlap in the strings.
          if(j < pat2ind.size() and (pat2ind[j] + pat2.length() > pat1ind[i] and pat2ind[j] < pat1ind[i])
                      || (pat2ind[j] < pat1ind[i] + pat1.length() and pat2ind[j] > pat1ind[i])) {
                            isOverlapping = true;
                          }
      }

      cout << "*******************************************************************\n";
      if(isOverlapping){
          cout << "Yes SearchStringB and SearchStringC overlap in StringA." << endl;
      }
      else{
          cout << "No SearchStringB and SearchStringC does not overlap in StringA." << endl;
      }
      cout << "*******************************************************************\n";
    }
    else{
      if(pat1ind.size()==0)
      {
        cout << "SearchStringB not found in String A" << endl;
      }
      else{
        cout << "SearchStringC not found in String A" << endl;
      }
    }
    return 0;
    /**
      SO OVERALL Complexity will be
      O(n+m1)+O(n+m2)+O(n)
      which is linear.
    **/
}
