#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

/* takeaways 
     - two pointers i and j, which are row indexes
       of encoded1 and encoded2 respectively
       - they might advance to next row at a 
         different pace

     - however they need to be in-sync in terms 
       of the number of elements being paired to 
       produce the same product

     - let use test fixture 2 as an example to
       explain:
       encoded1: [[1,3],[2,1],[3,2]]
       encoded2: [[2,3],[3,3]]
       - at first both i and j point at first row
         i -> [1,3] (first row)
         j -> [2,3] (first row)
       - the number of pairs that compute to 1x2=2
         is at most 3 (three 1's from i and three 2's from j)
         so the result is now [[2,3]] 
       - both i and j are advanced to the second row as all the
         elements have been accounted for on the first row
         for both i and j 
         i -> [2,1] (second row)
         j -> [3,3] (second row)
       - we can only produce 1 pair to compute to the same product 
         ,which is 2x3=6 : one 2's from i and one 3's from j
         - the result is now [[2,3],[6,1]]
       - i is running out of element so it needs to advance
         to the third row. j remains on the second row with
         2 elements left to form pairs with i 
         i -> [3,2] (third row)
         j -> [3,2] (second row) 
       - now we can produce two 3x3=9's
         - so the result becomes [[2,3],[6,1],[9,2]]       
       - you also need to make sure the result
         have the minimum number of rows possible             
  
  */

/* 
  - pass in parameter by refernce: 
    - vector<vector<int>> &  
*/
void print2DVec(vector<vector<int>> &vec)
{
  cout << "[";

  for (int i = 0; i < vec.size(); i++)
  {
    cout << "[";
    for (int j = 0; j < vec[i].size(); j++)
    {
      cout << vec[i][j];
      if (j < vec[i].size() - 1)
        cout << ",";
    }
    cout << "]";
    if (i < vec.size() - 1)
      cout << ",";
  }

  cout << "]";
}

tuple<vector<vector<int>>, vector<vector<int>>> testFixture1()
{
  vector<vector<int>> vec1{{1, 3},
                           {2, 3}};
  vector<vector<int>> vec2{{6, 3},
                           {3, 3}};

  return make_tuple(vec1, vec2);
}

tuple<vector<vector<int>>, vector<vector<int>>> testFixture2()
{

  vector<vector<int>> vec1{{1, 3},
                           {2, 1},
                           {3, 2}};
  vector<vector<int>> vec2{{2, 3},
                           {3, 3}};

  return make_tuple(vec1, vec2);
}

tuple<vector<vector<int>>, vector<vector<int>>> testFixture3()
{
  vector<vector<int>> vec1{{1, 3},
                           {2, 3}};
  vector<vector<int>> vec2{{6, 2},
                           {3, 4}};

  return make_tuple(vec1, vec2);
}

class Solution
{
public:
  vector<vector<int>> product(vector<vector<int>> encoded1,
                              vector<vector<int>> encoded2)

  {
    vector<vector<int>> result;

    int i = 0;
    int j = 0;

    while (i < encoded1.size() && j < encoded2.size())
    {
      /* compute the product */
      const int prod = encoded1[i][0] * encoded2[j][0];

      /* the most number of pairs that can produce the same product */
      const int numOfSameProd = min(encoded1[i][1], encoded2[j][1]);

      /* 
        - you also need to make sure the result
          have the minimum number of rows possible             
     */
      if (!findAdd(result, prod, numOfSameProd))
      {
        result.push_back({prod, numOfSameProd});
      }

      /* calculate the leftover that have not been used to form pairs */
      encoded1[i][1] -= numOfSameProd;
      encoded2[j][1] -= numOfSameProd;

      /* 
        - advance to the next row if the elements have been used
          up to form pairs  
      */
      if (encoded1[i][1] == 0)
        ++i;
      if (encoded2[j][1] == 0)
        ++j;
    }

    return result;
  }

  /* naive implementation  */
  bool findAdd(vector<vector<int>> &vec, int findProd, int count)
  {
    bool added = false;
    for (int i = 0; i < vec.size(); i++)
    {
      if (vec[i][0] == findProd)
      {
        vec[i][1] += count;
        added = true;
        break;
      }
    }
    return added;
  }
};

void test1()
{
  tuple<vector<vector<int>>, vector<vector<int>>> fixture = testFixture1();

  vector<vector<int>> encode1 = std::get<0>(fixture);
  vector<vector<int>> encode2 = std::get<1>(fixture);

  Solution sol;
  vector<vector<int>> result = sol.product(encode1, encode2);
  cout << "Test 1 - expected to see:" << endl
       << "[[6,6]]" << endl;
  cout << "Result:" << endl;
  print2DVec(result);
  cout << endl;
}

void test2()
{
  tuple<vector<vector<int>>, vector<vector<int>>> fixture = testFixture2();

  vector<vector<int>> encode1 = std::get<0>(fixture);
  vector<vector<int>> encode2 = std::get<1>(fixture);

  Solution sol;
  vector<vector<int>> result = sol.product(encode1, encode2);
  cout << "Test 2 - expected to see:" << endl
       << "[[2,3],[6,1],[9,2]]" << endl;
  cout << "Result:" << endl;
  print2DVec(result);
  cout << endl;
}

void test3()
{
  tuple<vector<vector<int>>, vector<vector<int>>> fixture = testFixture3();

  vector<vector<int>> encode1 = std::get<0>(fixture);
  vector<vector<int>> encode2 = std::get<1>(fixture);

  Solution sol;
  vector<vector<int>> result = sol.product(encode1, encode2);
  cout << "Test 3 - expected to see:" << endl
       << "[[6,5],[3,1]]" << endl;
  cout << "Result:" << endl;
  print2DVec(result);
  cout << endl;
}

main()
{
  test1();
  test2();
  test3();
  return 0;
}