#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

#define sec 1e6

vector<vector<int>> goal;
map<vector<vector<int>>, bool> visited;

class node
{
public:
    vector<vector<int>> state;
    vector<node *> child;
    node *parent;
    string action;
    int path_cost;
    int h_n;
    int heuristics_value(vector<vector<int>> temp) //Heuristic function  (count number of misplaced tiles)
    {
        int ct = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (temp[i][j] != goal[i][j])
                    ct++;
            }
        }
        return ct;
    }
    node()
    {
        cout << "\n Enter Initial config" << endl;
        for (int i = 0; i < 3; i++)
        {
            vector<int> temp;
            for (int j = 0; j < 3; j++)
            {
                int val;
                cin >> val;
                temp.push_back(val);
            }
            state.push_back(temp);
        }
        parent = NULL;
        action = "";
        path_cost = 0;
        h_n = 9;
    }
    node(vector<vector<int>> ar, node *p, string ac, int path_cst, int h_val)
    {
        for (int i = 0; i < ar.size(); i++)
        {
            vector<int> temp;
            for (int j = 0; j < ar[0].size(); j++)
            {
                temp.push_back(ar[i][j]);
            }
            this->state.push_back(temp);
        }
        this->parent = p;
        this->action = ac;
        this->path_cost = path_cst + 1;
        this->h_n = h_val;
    }
    bool is_valid(int x, int y) // to check whether a child is valid or not
    {
        if (x >= 0 and x < 3 and y >= 0 and y < 3)
            return true;
        else
            return false;
    }
    void successor() // Function to find child of a given node
    {
        int xpos = 0, ypos = 0;
        int size = this->state.size();
        queue<pair<int, int>> dir; // dir is queue to store all the possible directions
        dir.push(make_pair(1, 0));
        dir.push(make_pair(-1, 0));
        dir.push(make_pair(0, -1));
        dir.push(make_pair(0, 1));
        for (int i = 0; i < size; i++)
        {
            vector<int> val;
            for (int j = 0; j < size; j++) //loop to find the position of 0
            {
                if (this->state[i][j] == 0)
                {
                    xpos = i;
                    ypos = j;
                }
            }
        }
        pair<int, int> p;
        string act;
        while (!dir.empty()) // while loop to check for all the four directions
        {
            p = dir.front();
            dir.pop();
            int curx = xpos + p.first;
            int cury = ypos + p.second;
            if (is_valid(curx, cury)) // check if the direction is valid or not

            {
                if (p.first == 1 and p.second == 0)
                    act = "D";
                if (p.first == -1 and p.second == 0)
                    act = "U";
                if (p.first == 0 and p.second == -1)
                    act = "L";
                if (p.first == 0 and p.second == 1)
                    act = "R";
                vector<vector<int>> temp;
                for (int i = 0; i < 3; i++) // store the valude of parent node in temp
                {
                    vector<int> temp2;
                    for (int j = 0; j < 3; j++)
                        temp2.push_back(this->state[i][j]);
                    temp.push_back(temp2);
                }
                int swap = temp[curx][cury]; // find child by swapping in the found direction
                temp[curx][cury] = temp[xpos][ypos];
                temp[xpos][ypos] = swap;
                int heuristic_val = heuristics_value(temp);
                node *c = new node(temp, this, act, this->path_cost + 1, heuristic_val);
                this->child.push_back(c);
            }
        }
    }
};
typedef pair<node *, int> pd;
struct myComp
{
    constexpr bool operator()(
        pair<node *, int> const &a,
        pair<node *, int> const &b)
        const noexcept
    {
        return a.second > b.second;
    }
};
bool visit(vector<vector<int>> a)
{
    if (visited[a] == true)
        return true;
    else
        return false;
}
bool isGoal(vector<vector<int>> a) // checks for the goal state
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (a[i][j] != goal[i][j])
                return false;
        }
    }
    return true;
}
void Solution(node *n)
{
    cout << "\nPath  followed is :" << endl;
    stack<node *> temp1;
    stack<node *> temp2;
    while (n != NULL)
    {
        temp2.push(n);
        temp1.push(n);
        n = n->parent;
    }
    while (!temp1.empty())
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << temp1.top()->state[i][j] << " ";
            }
            cout << endl;
        }
        temp1.pop();
        cout << endl;
    }
    int path_length = 0;
    cout << "\nAction taken  are::" << endl;
    while (!temp2.empty())
    {
        cout << temp2.top()->action << "->";
        temp2.pop();
        path_length++;
    }
    cout << "\nPath length is " << path_length - 1;
}

int main()
{
    auto strt = high_resolution_clock::now();
    node *start = new node();
    cout << "Enter Goal state" << endl;
    for (int i = 0; i < 3; i++)
    {
        vector<int> te;
        for (int j = 0; j < 3; j++)
        {
            int t;
            cin >> t;
            te.push_back(t);
        }
        goal.push_back(te);
    }
    cout << "Solution" << endl;
    start->successor();
    priority_queue<pd, vector<pd>, myComp> frontier;
    set<node *> explored;
    frontier.push(make_pair(start, start->h_n));
    int ct = 0;
    while (!frontier.empty())
    {
        node *n = frontier.top().first;
        if (isGoal(n->state))
        {
            cout << "NO of nodes explored are " << ct;
            Solution(n);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - strt);
            cout << "\nTime taken by function: "
                 << (double)duration.count() / sec << " seconds" << endl;
            return 0;
        }
        else
        {
            explored.insert(n);
            visited[n->state] = true;
            ct++;
            n->successor();
            vector<node *>::iterator itr;
            for (itr = n->child.begin(); itr != n->child.end(); itr++)
            {
                vector<vector<int>> temp = (*itr)->state;
                if (!visit(temp))
                {
                    frontier.push(make_pair(*itr, (*itr)->h_n + (*itr)->path_cost));
                }
            }
        }
        frontier.pop();
    }
    cout << "NOT SOLVABLE" << endl;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - strt);
    cout << "\nTime taken by function: "
         << (double)duration.count() / sec << " seconds" << endl;
}