/*
 * Name: Joe Francesconi
 * Date Submitted: 5/3/2022
 * Assignment Name: Word Ladder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

vector<string> V; //words from wordlist05.txt
//Global variables for bfs distance, bfs predecessor, and neighboring nodes
//Should be unordered_map type
//from lab 10
unordered_map<string, bool> visited;
unordered_map<string, string> pred;
unordered_map<string, int> dist;
unordered_map<string, vector<string>> nbrs;

//Implement breadth-first search, refer to Lab 10
int pathSearch(string s, string e, vector<string> &path)
{
  //end node must have a pred
  if (pred.find(e) == pred.end()) return 0;
  if (s.compare(e) != 0)
  {
    int step = 1 + pathSearch(s, pred[e], path);
    path.push_back(e);
    return step;
  }
  else
  {
    path.push_back(e);
    return 0;
  }
}
//fills V
void build_graph()
{
  ifstream fileIn("wordlist05.txt");
  string word;

  while (fileIn >> word) V.push_back(word);

  for (auto w : V)
  {
    for (int i = 0; i < w.length(); i++)
    {
      for (char alpha = 'a'; alpha <= 'z'; alpha++)
      {
        if (alpha == w.at(i)) continue;
        string current = w;
        current.at(i) = alpha;
        nbrs[w].push_back(current);
      }
    }
  }
}

// GENERIC (breadth-first search, outward from curnode)
//Pulled from lab 10
void search(string source)
{
  queue<string> to_visit;
  to_visit.push(source);
  visited[source] = true;
  dist[source] = 0;
  
  while (!to_visit.empty()) {
    string curnode = to_visit.front();
    to_visit.pop();
    for (string n : nbrs[curnode])
      if (!visited[n]) {
        pred[n] = curnode;
        dist[n] = 1 + dist[curnode];
        visited[n] = true;
        to_visit.push(n);
      }
  }
}

void wordLadder(string s, string t, int &steps, vector<string> &p)
{
  //Implement this function
  build_graph();
  search(s);
  steps = pathSearch(s, t, p);
}

int main(void)
{
  int steps = 0;
  string s, t;
  vector<string> path;
  
  cout << "Source: ";
  cin >> s;

  cout << "Target: ";
  cin >> t;

  wordLadder(s, t, steps, path);

  if (steps == 0)
  {
      cout << "No path!\n";
  }
  else
  {
      cout << "Steps: " << steps << "\n\n";
      for (int i=0; i<path.size(); i++)
      {
          cout << path[i] << endl;
      }
  }
  return 0;
}
