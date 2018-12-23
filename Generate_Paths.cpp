#include <vector>
#include <iostream>
#include <queue>

using namespace std;
using MAXCANDIDATES = vector<int>;
using NEXTCANDIDATES = int;
using CANDIDATES = vector<int>;
using graph = vector<vector<int>>;
int solution_count = 0;

bool is_a_solution(CANDIDATES A, int k, int t)
{
	return (A[k] == t);
}
void process_solution(CANDIDATES A, int k)
{
	solution_count++;
}
void construct_candidates(CANDIDATES A, int k, int n, MAXCANDIDATES &S, int &next, graph const &G, int t)
{
	vector<bool> in_sol(A.size()); 
	int last; 
	int v = 0;
	for (size_t i = 0; i < A.size(); i++) in_sol[i] = false;
	for (int i = 0; i < k; i++) in_sol[ A[i] ] = true;
	if(k == 0) 
	{ 
		S[0] = 0;
		next = 1;
	}
	else 
	{
		next = 0;
		last = A[k - 1];
		for (auto v : G[last])
		{
			if (!in_sol[v])
			{
				S[next] = v;
				next = next + 1;
			}
		}
	}
}
void backtrack(CANDIDATES A, int k, graph const &G, int t)
{
	MAXCANDIDATES S(G.size());
	NEXTCANDIDATES next = 0;
	int n = G.size();
	if (k != -1 && is_a_solution(A, k, t))
		process_solution(A, k);
	else
	{
		k = k + 1;
		construct_candidates(A, k, n, S, next, G, t);
		
		for (int i = 0; i < next; i++)
		{
			A[k] = S[i];
			backtrack(A, k, G, t);
		}
	}
}

void generate_subsets(vector<vector<int>> const &G, int t)
{
	vector<int> A(G.size());
	backtrack(A, -1, G, t);
}

int main()
{
	graph G
	{
		{1, 2, 3, 4},
		{0, 5},
		{0, 3, 5},
		{0, 2, 5},
		{0, 5},
		{1, 2, 3, 4}
	};
	generate_subsets(G, 3);
	cout << solution_count;
}
