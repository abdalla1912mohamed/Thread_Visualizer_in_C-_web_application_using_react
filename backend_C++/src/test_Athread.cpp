#include <gtest/gtest.h>
#include "ATthread.hpp"
#include <thread>
#include <chrono>

// Test default constructor
TEST(AThreadTest, DefaultConstructor) {
    AThread a;
    EXPECT_EQ(a.getId(), 1); // Assuming default_id starts at 0
    EXPECT_EQ(a.getName(), "A1");
    EXPECT_EQ(a.getStatus(), "IDLE");
    EXPECT_FALSE(a.isHidden());
}

// Test constructor with id
TEST(AThreadTest, ConstructorWithId) {
    AThread a(5);
    EXPECT_EQ(a.getId(), 5);
    EXPECT_EQ(a.getName(), "A5");
    EXPECT_EQ(a.getStatus(), "IDLE");
    EXPECT_FALSE(a.isHidden());
}

// Test constructor with id and name
TEST(AThreadTest, ConstructorWithIdAndName) {
    AThread a(5, "CustomName");
    EXPECT_EQ(a.getId(), 5);
    EXPECT_EQ(a.getName(), "CustomName");
    EXPECT_EQ(a.getStatus(), "IDLE");
    EXPECT_FALSE(a.isHidden());
}

// Test move constructor
TEST(AThreadTest, MoveConstructor) {
    AThread a(5, "MoveTest");
    AThread b(std::move(a));

    EXPECT_EQ(b.getId(), 5);
    EXPECT_EQ(b.getName(), "MoveTest");
    EXPECT_EQ(b.getStatus(), "IDLE");
    EXPECT_FALSE(b.isHidden());
}

// Test move assignment operator
TEST(AThreadTest, MoveAssignmentOperator) {
    AThread a(5, "MoveAssign");
    AThread b;
    b = std::move(a);

    EXPECT_EQ(b.getId(), 5);
    EXPECT_EQ(b.getName(), "MoveAssign");
    EXPECT_EQ(b.getStatus(), "IDLE");
    EXPECT_FALSE(b.isHidden());
}

// Test setStatus and getStatus
TEST(AThreadTest, SetStatus) {
    AThread a;
    a.setStatus(AThread::Status::RUNNING);
    EXPECT_EQ(a.getStatus(), "RUNNING");
}

// Test sleep method
TEST(AThreadTest, SleepMethod) {
    AThread a;
    a.setStatus(AThread::Status::RUNNING);
    auto start = std::chrono::high_resolution_clock::now();
    a.sleep(100); // Sleep for 100 milliseconds
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    EXPECT_NEAR(elapsed.count(), 0.1, 0.02); // Allowing a tolerance
    EXPECT_EQ(a.getStatus(), "RUNNING");
}

// Test getExecutionTime
TEST(AThreadTest, GetExecutionTime) {
    AThread a; // a thread a
    a.setStatus(AThread::Status::RUNNING); // running status mimicking function call
    std::this_thread::sleep_for(std::chrono::seconds(1));
    a.setStatus(AThread::Status::TERMINATED);
    EXPECT_GT(a.getExecutionTIme(), 0.9);
}

// Test endAThread method
TEST(AThreadTest, EndAThreadMethod) {
    AThread a;
    a.setStatus(AThread::Status::RUNNING);
    a.endAThread();
    EXPECT_EQ(a.getStatus(), "TERMINATED");
    EXPECT_GT(a.getExecutionTIme(), 0.9);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
