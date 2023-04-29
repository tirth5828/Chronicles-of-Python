#include <bits/stdc++.h>
using namespace std;

int travellingSalesmanProblem(vector<vector<int>>graph,int source,int temp)
{
    int V=graph.size(),mincost;
    cout << "Path\t\t\tCost\tTemperature\tProbability\n";
    vector<int>ans;
    while(temp)
    {
    	vector<int>vertex;
    	for(int i=0;i<V;i++)
    	{
    		if(i!=source)
    			vertex.push_back(i);
        }
        
    	int min_path = INT_MAX,previous_pathweight = 0;
    	do {
    
    		// store current Path weight(cost)
    		int current_pathweight = 0;
    
    		// compute current path weight
    		int k=source;
    		for (int i=0;i<vertex.size();i++) 
    		{
    			current_pathweight+=graph[k][vertex[i]];
    			k=vertex[i];
    		}
    		current_pathweight+=graph[k][source];
            double probability=1/(1+exp((previous_pathweight-current_pathweight)/temp));
            cout << "[" << source+1 << ", ";
            for(int i=0;i<vertex.size();i++)
                cout << vertex[i]+1 << ", ";
            cout << source+1 << "]\t\t";
            if(current_pathweight<previous_pathweight)
                cout << current_pathweight << "\t" << temp << "\t\t" << 1 << '\n';
            else
                cout << current_pathweight << "\t" << temp << "\t\t" << probability << '\n';
            
            if(current_pathweight<min_path)
            {
                min_path=current_pathweight;
                ans=vertex;
    	    }
    	    mincost=min(mincost,current_pathweight);
    		previous_pathweight=current_pathweight;
    
    	} while(next_permutation(vertex.begin(), vertex.end()));
    	temp/=2;
    }
    cout << "Final minimum cost path possible is \n[" << source+1 << ", ";
    for(int i=0;i<V-1;i++)
        cout << ans[i]+1 << ", ";
    cout << ans[V-1]+1 << "]\n";
    cout << "Cost: " << mincost << '\n';
}

void inputGraph()
{
    cout << "In this implementation the points i.e. cities are numered from 1 to N\n";
    int V=1;
    cout << "Enter the number of cities - Make sure they are atleast 20\n";
    // while(V<20)
    // {
    //     cin >> V;
    //     if(V<20)
    //         cout << "Number of cities should be greater than 20\nEnter again\n";
    //     else
    //         break;
    // }
    cin >> V;
    vector<vector<int>>graph;
	for(int i=0;i<V;i++)
	{
	    vector<int>temp;
	    for(int j=0;j<V;j++)
	        temp.push_back(0);
	    graph.push_back(temp);
	}
	for(int i=0;i<V;i++)
	{
	    for(int j=i+1;j<V;j++)
	    {
	        if(i+1!=j+1)
	        {
    	        cout << "Enter the distance between city " << i+1 << " and " << "city " << j+1 << '\n';
    	        int val;
    	        cin >> val;
    	        graph[i][j]=val;
    	        graph[j][i]=val;
	        }
	    }
	}
	cout << "Enter a source point - [1," << V << "]\n";
	int source=0;
	while(source<1 || source>V)
    {
        cin >> source;
        if(source>=1 && source<=V)
            break;
        else
            cout << "Source point should be in [1," << V << "] range\nEnter again\n";
    }
    int temp;
    cout << "Enter a value of temperature\n";
    cin >> temp;
    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
            cout << graph[i][j] << " ";
        cout << '\n';
    }
    travellingSalesmanProblem(graph,source-1,temp);
}

void instructions()
{
    cout << "This is the implementation of Travelling Salesman Problem\nProblem states that a salesman has to travel all cities with the minimum cost\nCost is considered to be the total distance here\n";
    cout << "The algorithm uses simulated annealing to find the minimum cost path\n";
    cout << "Perturbation method for TSP used is 2-Edge exchange\nReason being 2-Edge exchange gives a solution which is much closer to the optimal one than 2-vertex exchange\n";
    cout << "Algorithm\n";
    cout << "1) A graph is taken as input from user\n2) At first a simple cycle which goes from 1 to last city to 1 is considered\n3) Using 2-Edge exchange edges are exchanged and a new cycle thus formed is compared to the previous one and hence the probability calculated\n";
    cout << "4) To apply Simulated Annealing a high(theoretically infinite) value is taken input\n5) Using the temperature value an epoch is run and the algorithm goes from Random Walk to Hill Climbing thus giving us a minimum cost path\n6) Here temperature reduces by 2 and for each probability calculated\n";
    cout << "7) Probability is calculated using Sigmoid function - 1/1+e^(ΔE/T)\n8) ΔE is difference of the cost of current path and previous path\n";
    cout << "Take care of following\n";
    cout << "1) In this implementation the points i.e. cities are numered from 1 to N\n2) Number of cities should be greater than 20\n3) Value of source point should be in [1,last city] range\n4) For better results choose temperature value as high as possible say,10^9\n";
    cout << "Things to notice\n";
    cout << "Observe the acceptance probability of different hamiltonian cycles as temperature decreases\n\n\n";
}

int main()
{
    instructions();
    inputGraph();
	return 0;
}