#include <bits/stdc++.h>
using namespace std;
class output_process
{
public:
    int id;
    float time = 0;
    float start = 0;
};
class process
{
public:
    int id;
    float brust_time = 0;
    float arrival_time = 0;
    float start_time = 0;
    unsigned int priority = 0 ;
};
float arr_find(int id, deque<process> input)
{
    for(unsigned int i = 0 ; i < input.size() ; i++)
        if(input[i].id == id)
            return input[i].arrival_time;
    return -1 ;
}
float AWT(deque<output_process>out,deque<process> input,int n)
{
    set<int>IsRep;
    float WaitTime=0 ;
    while(!out.empty())
    {
        int id = out.front().id;
        unsigned int l = IsRep.size();
        IsRep.insert(id);
        if(l==IsRep.size())
        {
            out.pop_front();
        }
        else
        {
            float arrive = arr_find(id,input);
            float start = out.front().start;
            float endp = start + out.front().time;
            WaitTime += start - arrive ;
            out.pop_front();
            for(unsigned int j = 0 ; j<out.size() ; j++)
            {
                if(out[j].id == id)
                {
                    WaitTime += out[j].start - endp ;
                    endp = out[j].start + out[j].time ;
                }
            }
        }
    }
    return WaitTime/n;
}
deque<output_process>output;
deque<process> input;
int main()
{
    return 0;
}
