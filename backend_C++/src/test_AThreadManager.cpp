#include <gtest/gtest.h>
#include "AthreadManager.hpp"
// Test fixture class
class AThreadManagerTest : public ::testing::Test {
protected:
    // Setup method for setting up common objects
    void SetUp() override {
        // Initialize the singleton instance with a limit of 5 threads
        manager = &AThreadManager::getInstance(5);
    }

    // Teardown method
    void TearDown() override {
        manager->getThreadsInfo().clear() ; 
        manager->UpdateThreadInfo() ; 

    }

    // Reference to the AThreadManager instance
    AThreadManager* manager;
};

// Test the initialization of AThreadManager
TEST_F(AThreadManagerTest, Initialization) {
    EXPECT_EQ(manager->getThreadsInfo().size(), 0);
}

// Test adding threads to the manager
TEST_F(AThreadManagerTest, AddThread) {
    manager->AddThread();
    manager->AddThread();
    EXPECT_EQ(manager->getThreadsInfo().size(), 2);

    auto threads = manager->getThreadsInfo();
    EXPECT_EQ(threads[0].threadId, 1);  // First thread should have ID 0
    EXPECT_EQ(threads[1].threadId, 2);  // Second thread should have ID 1
}

// Test removing thread information
TEST_F(AThreadManagerTest, RemoveThreadInfo) {
  
    manager->AddThread();
    manager->AddThread();
    EXPECT_EQ(manager->getThreadsInfo().size(), 2);
      // get threadsize 
    // Remove the thread with ID 1
   
    manager->RemoveThreadInfo(3);

    EXPECT_EQ(manager->getThreadsInfo().size(), 1);

    auto threads = manager->getThreadsInfo();
    EXPECT_EQ(threads[0].threadId, 4);  
}

// Test sleeping a thread
TEST_F(AThreadManagerTest, SleepThread) {
    manager->AddThread();
    manager->SleepThread(5, 1000);  // Sleep thread 0 for 1 second
    auto threads = manager->getThreadsInfo();
    EXPECT_EQ(threads[0].threadStatus, "SLEEPING");
}

// Test counting threads by status
TEST_F(AThreadManagerTest, CountThreadsByStatus) {
    manager->AddThread();  // Thread 6 - IDLE
    manager->AddThread();  // Thread 7 - IDLE
    manager->SleepThread(7, 1000);  // Sleep thread 0
    EXPECT_EQ(manager->SleepCount(), 1);  // 1 thread should be sleeping
    EXPECT_EQ(manager->IdleCount(), 1);  // 1 thread should be idle
}

// Test converting to JSON
TEST_F(AThreadManagerTest, ToJson) {
    manager->AddThread(); // Thread 8
    manager->AddThread(); // Thread 9
    auto jsonOutput = manager->toJson();
    EXPECT_EQ(jsonOutput["thread_count"], 8);
}

// Test sorting threads by ID
TEST_F(AThreadManagerTest, SortThreadsById) {
    manager->AddThread(); // Thread 10
    manager->AddThread(); // Thread 11

    // Sorting should work even if threads are already sorted
    manager->SortThreadsById();
    auto threads = manager->getThreadsInfo();
    EXPECT_EQ(threads[0].threadId, 10);
    EXPECT_EQ(threads[1].threadId, 11);
}


