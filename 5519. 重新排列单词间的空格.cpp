#include <iostream>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;


class Solution {
public:
    string reorderSpaces(string text) {
        vector<string> v;
        int  number=0;
        string temp="";
        for(int i=0;i<text.length();i++)
        {
            if(text[i]==' ') {
                if(temp!="") v.push_back(temp);
                temp="";
                number++;
            }
            else
            {
                temp.push_back(text[i]);
            }
        }
        if(temp!="") v.push_back(temp);
        if(v.size()==1)
        {
            for(int i=0;i<number;i++)
                v[0].push_back(' ');
            return v[0];
        }
        int num1=number/(v.size()-1);
        int num2=number%(v.size()-1);
        string result;
        for(int i=0;i<v.size();i++)
        {
            result+=v[i];
            if(i==v.size()-1) break;
            for(int j=0;j<num1;j++)
            {
                result.push_back(' ');
            }
        }
        for(int i=0;i<num2;i++)
        {
            result.push_back(' ');
        }
        return result;
    }
};