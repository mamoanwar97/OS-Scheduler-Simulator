#include "scheduler.h"

int process ::id_creator = 0;

Scheduler::Scheduler()
{
    this->error = new QMessageBox();
    deque<process> x;
    timeSlice=1;
    // id , time , start
    /*
    4
    0 2 0
    1 2 1
    2 1 2
    3 2 5
    */

//    process y(5,0.9,5);
//    process y2(2,2,4);
//    process y3(10,10,0);
//    process y4(3,15,3);
//    x.push_back(y);
//    x.push_back(y2);
//    x.push_back(y3);
//    x.push_back(y4);


//    y.id=0;
//    y.brust_time=5 ;
//    y.arrival_time=0.9;
//    y.priority=5;
//    x.push_back(y);
////    y.id=1;
//    y.brust_time=2 ;
//    y.arrival_time=2;
//    y.priority=4;
//    x.push_back(y);
////    y.id=2;
//    y.brust_time=10 ;
//    y.arrival_time=10;
//    y.priority=0;
//    x.push_back(y);
////    y.id=3;
//    y.brust_time=3 ;
//    y.arrival_time=15;
//    y.priority=3;
//    x.push_back(y);
////    y.id=4;
//    y.brust_time=2 ;
//    y.arrival_time=15;
//    y.priority=5;
//    x.push_back(y);
////    y.id=5;
//    y.brust_time=5 ;
//    y.arrival_time=10;
//    y.priority=0;
//    x.push_back(y);
////    y.id=6;
//    y.brust_time=3 ;
//    y.arrival_time=9;
//    y.priority=2;
//    x.push_back(y);
////    y.id=7;
//    y.brust_time=6 ;
//    y.arrival_time=12;
//    y.priority=0;
//    x.push_back(y);


    for(unsigned int i =0 ; i < this->output.size() ; i++)
        cout << "output " << x[i].id << "," << x[i].brust_time << endl;

    /*
        int n ; cin >> n ;
        for(int i =0 ; i< n ; i++)
        {
            process newProcess;
            cin >> newProcess.id >> newProcess.brust_time >> newProcess.arrival_time;
            x.push_back(newProcess);
        }
    */
//    this->STF(x,1);
//    this->RoundRobin(x);
    for(unsigned int i =0 ; i < this->output.size() ; i++)
        cout << "output " << this->output[i].id << "," << this->output[i].time << endl;


    process::id_creator =0;

}
int Scheduler::noOfProcess(void)
{
set<int> s;
for(int i=0;i<output.size();i++)
{
    s.insert(output[i].id);
}
    return s.size();
}
float Scheduler::maxTime(void)
{
    float t=0;
    float first=output[0].start;
    for(int i=0;i<output.size();i++)
    {
        t+=output[i].time;  

    }
    return (t+first);
}
int Scheduler::processID(int i)
{
    return output[i].id;
}

QVariant Scheduler::getProcessesQml()
{
// ########   m7dsh yms7 el coooooooooooooooooooooooooooooooooooooooooooode dh #######
//    QVariantList list ; list.append(4);     list.append("ray2222");
//    std::vector<int> list; list.push_back(3); list.push_back(55); // it can be any type
//    QVariantMap list ; list["ray2"]="7ray2" ; list["GPIO"]= 55; // QVariantMap typedef QMap<QString,QVariant> ... lazem QVariantMap to javascript Object (Lazem)
//    QVariant x = QVariant::fromValue(list) ;

    // convert the dequeue to vector (deque is not a sequence registered QML Type )
    vector<process_out> list;
    for (int i =0 ; i < this->output.size(); i++)
        list.push_back(this->output[i]);

    // convert the vector(or anything) to QVariant , to be converted again by Javascript
    QVariant x = QVariant::fromValue(list);
    return x;

//    also it can be done by signals and slots
    //    emit ray2Changed(x);
}

void Scheduler::addProcess(float brust , float arrival , unsigned int Priority)
{
    process x(brust,arrival,Priority);
    this->Input.push_back(x);

    for(int i =0 ; i < this->Input.size(); i++)
        cout << "("  << Input[i].brust_time<< "," << Input[i].arrival_time<< "," << Input[i].priority << ") ";
    cout << endl;
}

void Scheduler::startSTF(bool preemtive)
{
    this->STF(this->Input,preemtive);
    cout << "STF" << endl;
    this->sendQml();
}

void Scheduler::startPriority(bool preemtive)
{
    this->Priority(this->Input ,preemtive);
    cout << "Priority Mode" << endl;
    this->sendQml();
}

void Scheduler::startRoundRobin()
{
    this->RoundRobin(this->Input);
    cout << "RoundRobin Mode" << endl;
    this->sendQml();

}

void Scheduler::startFCFS()
{
    this->FCFS(this->Input);
    cout << "FCFS Mode" << endl;
    this->sendQml();
}

void Scheduler::clear()
{
    this->Input.clear();
    this->output.clear();
}

void Scheduler::errorMsg(QString e)
{
    this->error->setText(e);
    this->error->show();
}

void Scheduler::sendQml()
{

    vector<process_out> list;
    for (uint i =0 ; i < this->output.size(); i++)
        list.push_back(this->output[i]);

    cout << "sending Processes " << endl;
    for(unsigned int i =0 ; i < this->output.size() ; i++)
        cout << "output " << this->output[i].id << "," << this->output[i].time << endl;
    cout << "#####################" << endl;

    QVariant x = QVariant::fromValue(list);
    emit sendProcesses(x);

    // clear all
    process::id_creator = 0;
    this->clear();

}

//process_out Scheduler::getProcess(int i)
//{
//    return this->output[i];
//}
bool sortByArrivalTime(process p1, process p2)
{
    return p1.arrival_time < p2.arrival_time;
}

void Scheduler::RoundRobin(deque<process> input)
{

    sort(input.begin(),input.end(),sortByArrivalTime);

    int index = 0;
    float currentTime = 0;

    deque<process> activeProcesses;

    while (input.size() || activeProcesses.size())
    {
        process_out newProcess;

        while(input[0].arrival_time <= currentTime && input.size() != 0)
        {
            activeProcesses.push_back( input[0] );
            input.pop_front();
        }

        // if there is no process so don't do anything just increment the time
        if(activeProcesses.size() == 0)
        {
            currentTime ++;
            continue;
        }
        // same thing, if there is no current processes or the current time didn't reach it yet
        //        if(activeProcesses[index].arrival_time > currentTime)
        //            continue;

        // index = the same of its val        currentTime += newProcess.time;        currentTime += newProcess.time;ue until in reach the input size: it return to the zero position
        index = index % activeProcesses.size();
        // if process takes small time , so we don't need the
        if(this->timeSlice >= activeProcesses[index].brust_time)
        {
            newProcess.time = activeProcesses[index].brust_time;
            newProcess.id = activeProcesses[index].id;
            newProcess.start = currentTime;
            // delete the finished process not iterate over it again
            activeProcesses.erase(activeProcesses.begin()+index);
            // don't increment the index, because when we delete element from the vector, the current index will be the next element
            // XXXXXXXX    index ++  XXXXXXXXX
            //           if(index >= activeProcesses.size())
            //                index = 0;
        }
        else
        {
            // if the process time is still exists , decrement it by time slice
            newProcess.time = this->timeSlice;
            newProcess.id = activeProcesses[index].id;
            newProcess.start = currentTime;
            // decrement the time of the process with the consumed time (time slice) to know when it ends
            activeProcesses[index].brust_time -= this->timeSlice;
            //            activeProcesses[index].arrival_time = currentTime;

            index ++;
        }

        // add new process with calculated time to the output vector
        this->output.push_back(newProcess);
        currentTime += newProcess.time;

        cout << "new " << index << " : "<< newProcess.id << "," << newProcess.time <<  "," << newProcess.start <<  endl;
        for(unsigned int i =0 ; i < activeProcesses.size(); i++)
            cout << "active(" << activeProcesses[i].id << "," << activeProcesses[i].brust_time << ","<< activeProcesses[i].arrival_time << ") ";
        cout << endl;
        for(unsigned int i =0 ; i < input.size(); i++)
            cout << "input(" << input[i].id << "," << input[i].brust_time << ","<< input[i].arrival_time << ") ";
        cout << endl;
        cout << "currentTime" << currentTime << endl;
        cout << endl;

    }
}

bool sortByPriority(process p1, process p2)
{
    if(p1.arrival_time == p2.arrival_time)
        return p1.priority < p2.priority;
    else
        return p1.arrival_time < p2.arrival_time;
}

void Scheduler::Priority(deque<process> input, bool preemptive)
{
     if(preemptive)
    {
        sort(input.begin(), input.end(), sortByPriority);

        //intialize our first process, and make our own timer
        int current_proccess = input[0].id;
        float cnt = input[0].arrival_time, start = input[0].arrival_time;
        // 3 1   0 5 1   2 2 0   3 2 3
        while(input.size())
        {
            //Print(input);
            //When then process finishes
            if(input[0].brust_time == 0.00000)
            {
                process_out newProcess;
                newProcess.id = input[0].id;
                newProcess.time = cnt - start;
                newProcess.start = start;
                output.push_back(newProcess);
                input.pop_front();
                current_proccess = input[0].id;
                start = max(cnt,input[0].arrival_time);
            }
            else if (input[0].id != current_proccess)
            {
                process_out newProcess;
                newProcess.id = current_proccess;
                newProcess.time = cnt - start;
                newProcess.start = start;
                output.push_back(newProcess);
                current_proccess = input[0].id;
                start = cnt;
            }

            input[0].brust_time -=0.5;
            cnt+= 0.5;
// 8 1  0 5 0   2 2 0   10 10 0   15 3 0   15 2 0   10 5 0   9 3 0   12 6 0
            for(unsigned int i = 0; i < input.size(); i++)
            {
                    input[i].arrival_time = max(input[i].arrival_time, cnt);
            }

            sort(input.begin(), input.end(), sortByPriority);
        }
    }
    else
    {
        while(input.size())
        {
            sort(input.begin(), input.end(), sortByPriority);
            process_out newProcess;
            newProcess.id = input[0].id;
            newProcess.time = input[0].brust_time;
            newProcess.start = input[0].arrival_time;
            output.push_back(newProcess);


            for(unsigned int j = 1; j < input.size(); j++)
            {
                input[j].arrival_time = max(input[j].arrival_time, input[0].arrival_time + input[0].brust_time);
            }
            input.pop_front();
        }
    }
}
bool First(process A,process B)
{
    return A.arrival_time<B.arrival_time;
}
void Scheduler::FCFS(deque<process> input)
{
    sort( input.begin(), input.end(),First);
    float time =0;
    for(unsigned int i =0; i<input.size(); i++)
    {
        process_out newProcess;
        newProcess.id = input[i].id;

        if(time<input[i].arrival_time){
            newProcess.start = input[i].arrival_time;
            newProcess.time = input[i].brust_time;
            time=newProcess.time+newProcess.start;
        }
        else{
            newProcess.start = time;
            newProcess.time = input[i].brust_time;
            time+=newProcess.time;
        }
        this->output.push_back(newProcess);

    }
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
void Scheduler::STF(deque<process> input, bool preemptive)
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
            float Current_Time = -Sch_Arr_Time.top().first ;
            ///The arrival time of the smallest arrival time process
            float Temp_Arr_Time = - Sch_Arr_Time.top().first ;
            ///The burst time of the smallest burst time process
            float first_burst =  burst_find(Sch_Arr_Time.top().second,input);
            ///add the process of the smallest arrival time
            Sch_Burst_Time.push( pair<float,int> ( - first_burst, Sch_Arr_Time.top().second )) ;
            ///remove this process from ready queue
            Sch_Arr_Time.pop();
            ///adding the processes of the same time to the queue to get the shortest time process among them
            while( Sch_Arr_Time.top().first == - Temp_Arr_Time && ! Sch_Arr_Time.empty() ) /// Put the Processes of same time on the CPU
            {
                float burst =  burst_find(Sch_Arr_Time.top().second,input);
                /// Here the shortest time process will be first
                Sch_Burst_Time.push( pair<float,int> ( - burst, Sch_Arr_Time.top().second )) ;
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
                        set_start_time(Sch_Burst_Time.top().second,Current_Time,input);
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
                    set_start_time(Sch_Burst_Time.top().second,Current_Time,input);
                ///the time at which the next process comes
                float Temp_Time_Next = - Sch_Arr_Time.top().first ;
                /// CPU runs until the next process comes
                while(1)
                {
                    /// Pick up the time of the shortest time process
                    float Temp_Time = -Sch_Burst_Time.top().first ;
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
            this -> output.push_back( newprocess );
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
