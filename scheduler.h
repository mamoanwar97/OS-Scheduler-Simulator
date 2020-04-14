#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <bits/stdc++.h>
#include<QObject>
#include <QVariant>
using namespace std;

class process
{
public:
    static int id_creator;
    int id;
    float brust_time ;
    float arrival_time ;
    float start_time ;
    unsigned int priority ;

    process(float brust , float arrival ,  unsigned int Priority=0) {
//        this->id = process::id_creator;
//        process::id_creator ++;

        this->brust_time =brust ;
        this->arrival_time= arrival;
        this->start_time = 0;
        this->priority =Priority ;

        this->id = id_creator;
        id_creator ++ ;
    }
};

// ===============================================================
class process_out
{
    // to activate communication through signals and slots by passing that object (directly or inside a list , map ..etc )s
    Q_GADGET
public:
    int id;
    float time ;
    float start ;
    //    QML & Javascript can access only Q_INVOCKABLE Functions or using Q_PROPERTY
    // of course it can be send via signals and slots too
public:
    Q_INVOKABLE int getID() {return this->id;}
    Q_INVOKABLE float getTime() {return this->time;}
    Q_INVOKABLE float getStart() {return this->start;}

};
Q_DECLARE_METATYPE(process_out);
// ===============================================================

class Scheduler : public QObject
{
    Q_OBJECT
private:
    deque<process> Input;
    deque<process_out> output;
    unsigned int timeSlice;

signals :
    void sendProcesses(QVariant processes);
public:
    Scheduler();

    Q_INVOKABLE  void RoundRobin(deque<process> input);
    Q_INVOKABLE  void Priority(deque<process> input, bool preemptive);
    Q_INVOKABLE  void FCFS(deque<process> input);
    Q_INVOKABLE  void STF(deque<process> input,bool preemptive);
    Q_INVOKABLE   int noOfProcess(void);
    Q_INVOKABLE   float maxTime(void);
    Q_INVOKABLE   int processID(int i);
    Q_INVOKABLE QVariant getProcessesQml();

    //
    Q_INVOKABLE void addProcess(float brust , float arrival , unsigned int Priority=0);
    Q_INVOKABLE void startSTF(bool);
    Q_INVOKABLE void startPriority(bool);
    Q_INVOKABLE void startRoundRobin();
    Q_INVOKABLE void startFCFS();

    Q_INVOKABLE void clear();

private:
    void sendQml();
};

#endif // SCHEDULER_H
