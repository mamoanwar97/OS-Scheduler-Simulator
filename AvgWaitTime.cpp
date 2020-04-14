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
float burst_find(int id, deque<process> input)
{
    for(unsigned int i = 0 ; i < input.size() ; i++)
        if(input[i].id == id)
            return input[i].brust_time;
    return -1;
}
float arr_find(int id, deque<process> input)
{
    for(unsigned int i = 0 ; i < input.size() ; i++)
        if(input[i].id == id)
            return input[i].arrival_time;
}
void set_start_time (unsigned int id, float st,deque<process> input)
{
    for(int i = 0 ; i < input.size() ; i++)
        if(input[i].id == id)
            input[i].start_time = st ;
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
void STF(deque<process> input, bool preemptive)
{
    /// sorting processes according to the arrival time in ascending order
    priority_queue< pair < float,int> > Sch_Arr_Time;
    /// sorting processes according to the burst time in ascending order
    priority_queue< pair <float,int> > Sch_Burst_Time;
    /// copying processes
    for(unsigned int i  = 0 ; i < input.size() ; i++)
        Sch_Arr_Time.push( pair<float,int> ( - input[i].arrival_time, input[i].id  ) );
    if(preemptive)
    {
        /// set to check the repeated processes
        set<int>rep;
        /// works until all the processes finished (ready queue is empty)
        while(!Sch_Arr_Time.empty())
        {
            ///The time of processing equals the time of the next arrived process
            double Current_Time = -Sch_Arr_Time.top().first ;
            ///The arrival time of the smallest arrival time process
            double Temp_Arr_Time = - Sch_Arr_Time.top().first ;
            ///The burst time of the smallest burst time process
            double first_burst =  burst_find(Sch_Arr_Time.top().second);
            ///add the process of the smallest arrival time
            Sch_Burst_Time.push( pair<double,int> ( - first_burst, Sch_Arr_Time.top().second )) ;
            ///remove this process from ready queue
            Sch_Arr_Time.pop();
            ///adding the processes of the same time to the queue to get the shortest time process among them
            while( Sch_Arr_Time.top().first == - Temp_Arr_Time && ! Sch_Arr_Time.empty() ) /// Put the Processes of same time on the CPU
            {
                double burst =  burst_find(Sch_Arr_Time.top().second);
                /// Here the shortest time process will be first
                Sch_Burst_Time.push( pair<double,int> ( - burst, Sch_Arr_Time.top().second )) ;
                ///remove this process from ready queue
                Sch_Arr_Time.pop();
            }
            /// there is no processes arrive after that
            if(Sch_Arr_Time.empty())
            {
                ///finishes all processes in the ready queue
                while(!Sch_Burst_Time.empty())
                {
                    int l = rep.size();
                    rep.insert(Sch_Burst_Time.top().second) ;
                    ///checks if that process processed before or not
                    if(l != rep.size())
                        set_start_time(Sch_Burst_Time.top().second,Current_Time);
                    process_out newprocess ;
                    if(!output.empty() && output.back().id == Sch_Burst_Time.top().second )
                    {
                        newprocess = output.back() ;
                        output.pop_back() ;
                        newprocess.time += -Sch_Burst_Time.top().first ;
                    }
                    else
                    {
                        newprocess.id =  Sch_Burst_Time.top().second ;
                        newprocess.time = -Sch_Burst_Time.top().first;
                        newprocess.start = Current_Time ;
                    }
                    output.push_back( newprocess );
                    cout<<"Process "<< Sch_Burst_Time.top().second ;
                    cout << " Takes " << -Sch_Burst_Time.top().first <<"\n" ;
                    ///increase the current time by the time of this process
                    Current_Time += -Sch_Burst_Time.top().first ;
                    ///remove from ready queue
                    Sch_Burst_Time.pop();
                }
            }
            /// there are processes will arrive
            else
            {
                ///checks if that process processed before or not
                int l = rep.size();
                rep.insert(Sch_Burst_Time.top().second);
                if(l != rep.size())
                    set_start_time(Sch_Burst_Time.top().second,Current_Time);
                ///the time at which the next process comes
                double Temp_Time_Next = - Sch_Arr_Time.top().first ;
                /// CPU runs until the next process comes
                while(1)
                {
                    /// Pick up the time of the shortest time process
                    double Temp_Time = -Sch_Burst_Time.top().first ;
                    /// Pick up the ID of the shortest time process
                    int Temp_ID = Sch_Burst_Time.top().second ;
                    //  Sch_Burst_Time.pop();
                    /// Calculating the Time of CPU burst
                    Temp_Time = Temp_Time - ( Temp_Time_Next  - Current_Time    )  ;
                    ///The time between the current process and the next process is small compared to the CPU burst of the current process
                    if(Temp_Time > 0 )
                    {
                        Sch_Burst_Time.pop();
                        process_out newprocess ;
                        if( !output.empty() && output.back().id == Temp_ID )
                        {
                            newprocess = output.back() ;
                            output.pop_back();
                            newprocess.time += Temp_Time_Next  - Current_Time ;
                        }
                        else
                        {
                            newprocess.id =  Temp_ID ;
                            newprocess.time = Temp_Time_Next  - Current_Time;
                            newprocess.start = Current_Time ;
                        }
                        output.push_back( newprocess );
                        cout<<"Process "<< Temp_ID ;
                        cout << " Takes " << Temp_Time_Next  - Current_Time <<"\n" ;
                        ///increase the current time by the time taken by the current process
                        Current_Time += ( Temp_Time_Next  - Current_Time );
                        ///push the rest of the current process to ready queue to be completed later if the come process is longer
                        Sch_Burst_Time.push(pair< int, int>( - Temp_Time, Temp_ID ) );
                        break;
                    }
                    ///The time between the current process and the next process is lager or equal compared to the CPU burst of the current process
                    else
                    {

                        process_out newprocess ;
                        if(!output.empty() && output.back().id == Temp_ID)
                        {
                            newprocess = output.back() ;
                            output.pop_back();
                            newprocess.time += -Sch_Burst_Time.top().first ;
                        }
                        else
                        {

                            newprocess.id =  Temp_ID ;
                            newprocess.time = -Sch_Burst_Time.top().first;
                            newprocess.start = Current_Time ;
                        }
                        output.push_back( newprocess );
                        cout<<"Process "<< Temp_ID;
                        cout << " Takes " << -Sch_Burst_Time.top().first <<"\n" ;
                        Current_Time += -Sch_Burst_Time.top().first;
                        Sch_Burst_Time.pop();
                        /// if the time between the next process and the finish time of current process = 0
                        /// or the ready queue is empty so waits the next process
                        if( Temp_Time == 0 || Sch_Burst_Time.empty() )
                            break;
                    }
                }
            }
        }
    }
    else
    {
        float current_time = 0 ;
        /// works until all the processes finished (ready queue is empty)
        while(!Sch_Arr_Time.empty())
        {
            if(current_time < -Sch_Arr_Time.top().first  )
                current_time = -Sch_Arr_Time.top().first;
            /// Put the Processes of same arrival time or less on the CPU
            while( -Sch_Arr_Time.top().first <= current_time &&  ! Sch_Arr_Time.empty() )
            {
                float burst =  burst_find(Sch_Arr_Time.top().second,input);
                /// Here the shortest time process will be on the top of the queue but (-ve)
                Sch_Burst_Time.push( pair<float,int> ( - burst, Sch_Arr_Time.top().second )) ;
                Sch_Arr_Time.pop();
            }
            ///Takes the shortest one and finish it
            process_out newprocess ;
            newprocess.id =  Sch_Burst_Time.top().second ;
            newprocess.time = -Sch_Burst_Time.top().first;
            newprocess.start = current_time;
            output.push_back( newprocess );
            cout<<"Process "<< Sch_Burst_Time.top().second ;
            cout<< " Takes " << -Sch_Burst_Time.top().first <<"\n" ;
            ///set the start of the current process
            set_start_time(Sch_Burst_Time.top().second,current_time,input);
            ///Increase the current time by the burst time of process
            current_time += -Sch_Burst_Time.top().first;
            Sch_Burst_Time.pop();
            ///Push the rest in the ready queue again :D
            while(!Sch_Burst_Time.empty())
            {
                Sch_Arr_Time.push( pair<float,int> ( arr_find(Sch_Burst_Time.top().second,input), Sch_Burst_Time.top().second) );
                Sch_Burst_Time.pop();
            }
        }
    }
}
deque<output_process>output;
deque<process> x;
int main()
{

    process y;
     y.id=0;
    y.brust_time=5 ;
    y.arrival_time=0.9;
    y.priority=5;
   x.push_back(y);
   y.id=1;
   y.brust_time=2 ;
    y.arrival_time=2;
    y.priority=4;
    x.push_back(y);
    y.id=2;
   y.brust_time=10 ;
    y.arrival_time=10;
    y.priority=0;
    x.push_back(y);
    y.id=3;
   y.brust_time=3 ;
    y.arrival_time=15;
    y.priority=3;
    x.push_back(y);
    y.id=4;
   y.brust_time=2 ;
   y.arrival_time=15;
    y.priority=5;
    x.push_back(y);
    y.id=5;
    y.brust_time=5 ;
    y.arrival_time=10;
    y.priority=0;
    x.push_back(y);
   y.id=6;
    y.brust_time=3 ;
    y.arrival_time=9;
    y.priority=2;
    x.push_back(y);
    y.id=7;
    y.brust_time=6 ;
    y.arrival_time=12;
    y.priority=0;
    x.push_back(y);
    return 0;
}
