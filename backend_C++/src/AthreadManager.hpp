#ifndef Athread_Manager_HPP
#define Athread_Manager_HPP
#include"ATthread.hpp" 
#include <cstddef>
#include <mutex>
#include <vector>
#include <iostream>
#include <algorithm>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct ThreadInfo {
std::string name ; 
int threadId ;
std::string  threadStatus ; 
int threadPriority ; 
double threadActiveTime ; 

bool isLocked ; 

    void printDetails() const {
        std::cout << "Name: " << name << "\n"
                  << "Thread ID: " << threadId << "\n"
                  << "Status: " << threadStatus << "\n"
                  << "Priority: " << threadPriority << "\n"
                  << "Active Time: " << threadActiveTime << "\n"
                  << "Locked: " << (isLocked ? "Yes" : "No") << "\n";
    }
}; 


class AThreadManager{
public : 
static int VisualThreadCount ; 
static int TotalThreadCount ;
static AThreadManager& getInstance(int maxThreadsNumber) {
        static AThreadManager instance(maxThreadsNumber);
        return instance;
    }


    AThreadManager(const AThreadManager&) = delete;
    AThreadManager& operator=(const AThreadManager&) = delete;
    AThreadManager(const AThreadManager&&) = delete;
    AThreadManager& operator=(const AThreadManager&&) = delete;
 ~AThreadManager() ; 
void AddThread(); 
void RemoveThreadInfo(int id ) ; 
void SleepThread(int id , int milliseconds) ; 
void UpdateThreadInfo();
int SleepCount() ;
int RunCount() ;
int IdleCount() ;
int BlockedCount() ;
int LockedCount();
int UnlockedCount() ; 
std::recursive_mutex & GetMutex(){
return mtx ; 
}
std::vector<ThreadInfo> getNeededInfo(char k);
json toJson(char k ='F')  ; 
// remember to stop termnated from starting a task  
int TerminatedCount() ;


 void SortThreadsByName();
 void SortThreadsByPriority() ;

    // Sort ThreadsInfos by threadId
    void SortThreadsById() ;


json  infotoJson(ThreadInfo A) ; 




ThreadInfo findThread(int id ); 

std::vector<AThread>& getThreadsArray();
std::vector<ThreadInfo> & getThreadsInfo();

private : 
    AThreadManager(int maxThreadsNumber)
    : maxThreadsNumber(maxThreadsNumber) {
        Threads.reserve(maxThreadsNumber);
    }
const int maxThreadsNumber = 512 ;
std::vector<AThread> Threads ; 
std::vector<ThreadInfo> ThreadsInfos ; 
std::vector<ThreadInfo> SleepingThreadsInfo ; //contain only sleeping threads
std::vector<ThreadInfo> RunningThreadsInfo ; 
std::vector<ThreadInfo> BlockedThreadsInfo ;
std::vector<ThreadInfo> TerminatedThreadsInfo ;
std::vector<ThreadInfo> IdleThreadsInfo ;
std::vector<ThreadInfo> LockedThreadInfo ;
std::vector<ThreadInfo> UnLockedThreadInfo ;
std::vector<ThreadInfo> NeededThreadsInfo ; // to edit in json file and before it assign the needed info to required based on search and filter 
mutable std::recursive_mutex mtx; // Recursive mutex for thread safety




}; 


















#endif // !