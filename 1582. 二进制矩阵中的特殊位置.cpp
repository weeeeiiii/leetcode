class Solution {
    vector<vector<int>> matrix;
public:
    bool judge(int x,int y)
    {
        for(int i=0;i<matrix.size();i++)
        {
            if(i==x) continue;
            if(matrix[i][y]!=0) return false;
        }

        for(int j=0;j<matrix[0].size();j++)
        {
            if(j==y) continue;
            if(matrix[x][j]!=0) return false;
        }
        return true;
    }

    int numSpecial(vector<vector<int>>& mat) {
        matrix=mat;
        int number=0;
        int n=mat.size(),m=mat[0].size();
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(mat[i][j]==1&&judge(i,j)) number++;
            }
        }
        return number;
    }
};