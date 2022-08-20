#include<iostream>
#include<stack>
#include<vector>

//find if there is a path from start to destination

struct position
{
    int x{} , y{};
    int dist{};
};

bool isValid(std::vector<std::vector<int>>& mat , bool visited[][10] , position& pos)
{
    return (pos.x >= 0 && pos.x < mat.size() && pos.y >= 0 && pos.y < mat[0].size() && mat[pos.x][pos.y] && !visited[pos.x][pos.y]);

}

//search if path from start to destination exists
bool DFS(std::vector<std::vector<int>>& mat , position& start , position& dest)
{
    if(mat.size() == 0 || mat[0].size() == 0)
    {
        throw std::invalid_argument("empty maze");
    }

    std::stack<position> cells;

    cells.push({start.x , start.y , 0});

    bool visited[10][10]{0};

    //moves: right , down , left , up
    int row[]={ 0 , 1, 0 , -1};
    int col[]={1 ,  0 , -1 , 0};

    visited[start.x][start.y] = 1;

    position curr;

    int i = 0 , y = 0;

    while(!cells.empty())
    {
        curr = cells.top();

        cells.pop();

        if(curr.x == dest.x && curr.y == dest.y)
        {
            return true;
        }

        for(int i = 0 ; i < 4 ; ++i)
        {
            position pos;
            pos.x = curr.x + row[i];
            pos.y = curr.y + col[i];
            pos.dist = curr.dist+1;
            if(isValid(mat , visited , pos) == true)
            {
                cells.push(pos);
                visited[pos.x][pos.y] = 1;

            }
        }

    }

    //no path found
    return false;
}

int main()
{
    // 0 -> not valid cell
    //1 -> valid cell
    // matrix 10 x 10
    //start {0 , 0} -> destination {9 , 9}
    std::vector<std::vector<int>> mat =
    {
        { 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
        { 0, 1, 1, 1, 1, 1, 0, 1, 0, 1 },
        { 0, 0, 1, 0, 1, 1, 1, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
        { 0, 0, 0, 1, 0, 0, 0, 1, 0, 1 },
        { 1, 0, 1, 1, 1, 0, 0, 1, 1, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 1, 0, 1 },
        { 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 },
        { 0, 0, 1, 0, 0, 1, 1, 0, 0, 1 },
    };

    std::cout<<mat.size()<<std::endl;

    position start;
    start.x = 0;
    start.y = 0;

    position end;
    end.x = 9;
    end.y = 9;

    std::cout<<std::boolalpha<<DFS(mat , start , end)<<std::endl;

    return 0;
}