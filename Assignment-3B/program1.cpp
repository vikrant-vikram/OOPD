
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <queue>


#include <chrono>
// Task class to represent scheduled tasks
class Task {
private:
    string name;
    int priority;
    chrono::system_clock::time_point scheduledTime;
    string description;

public:
    // Constructor
    Task(const string& n, int p, const chrono::system_clock::time_point& t, const string& d)
        : name(n), priority(p), scheduledTime(t), description(d) {}

    // Operator overload for heap comparison
    bool operator<(const Task& other) const {
        if (priority != other.priority)
            return priority < other.priority;
        return scheduledTime > other.scheduledTime;
    }

    // Getter methods
    string getName() const { return name; }
    int getPriority() const { return priority; }
    chrono::system_clock::time_point getTime() const { return scheduledTime; }
    string getDescription() const { return description; }

    // Method to display task details
    void displayTask() const {
        time_t time = chrono::system_clock::to_time_t(scheduledTime);
        cout << "Name: " << name << "\n"
             << "Priority: " << priority << "\n"
             << "Scheduled Time: " << ctime(&time)
             << "Description: " << description << "\n";
    }
};;

// TaskScheduler class to manage tasks
class TaskScheduler {
private:
    priority_queue<Task> taskQueue;
    int totalTasks;

public:
    // Constructor
    TaskScheduler() : totalTasks(0) {}

    // Method to add a new task
    void addTask(const string& name, int priority,
                const chrono::system_clock::time_point& time,
                const string& description) {
        taskQueue.push(Task(name, priority, time, description));
        totalTasks++;
        cout << "Task added: " << name << " (Priority: " << priority << ")\n";
    }

    // Method to process the next highest priority task
    void processNextTask() {
        if (taskQueue.empty()) {
            cout << "No tasks in queue!\n";
            return;
        }

        const Task& topTask = taskQueue.top();
        cout << "\nProcessing highest priority task:\n";
        topTask.displayTask();

        taskQueue.pop();
        totalTasks--;
    }

    // Method to display scheduler statistics
    void displayStats() const {
        cout << "\nScheduler Statistics:\n";
        cout << "Total tasks in queue: " << totalTasks << "\n";
        if (!taskQueue.empty()) {
            const Task& next = taskQueue.top();
            cout << "Next task: " << next.getName()
                     << " (Priority: " << next.getPriority() << ")\n";
        }
    }

    // Method to get total number of tasks
    int getTotalTasks() const {
        return totalTasks;
    }
};;

// Test function to verify scheduler functionality
void runSchedulerTests(TaskScheduler& scheduler) {
    auto now = chrono::system_clock::now();

    // Test Case 1: Add tasks with different priorities
    cout << "\nTest Case 1: Adding tasks with different priorities\n";
    scheduler.addTask("Urgent Meeting", 10,
        now + chrono::minutes(30),
        "Emergency team meeting for project review");

    scheduler.addTask("Code Review", 5,
        now + chrono::hours(2),
        "Review pull requests for feature branch");

    scheduler.addTask("Daily Backup", 3,
        now + chrono::hours(1),
        "Perform daily system backup");

    scheduler.addTask("Documentation", 4,
        now + chrono::minutes(45),
        "Update API documentation");

    // Test Case 2: Display initial statistics
    cout << "\nTest Case 2: Checking initial statistics\n";
    scheduler.displayStats();

    // Test Case 3: Process tasks in priority order
    cout << "\nTest Case 3: Processing tasks in priority order\n";
    for (int i = 0; i < 3; ++i) {
        scheduler.processNextTask();
        scheduler.displayStats();
    }

    // Test Case 4: Adding task after processing
    cout << "\nTest Case 4: Adding new task after processing others\n";
    scheduler.addTask("New Feature", 8,
        now + chrono::hours(3),
        "Implement new feature request");
    scheduler.displayStats();

    // Test Case 5: Process remaining tasks
    cout << "\nTest Case 5: Processing remaining tasks\n";
    while (scheduler.getTotalTasks() > 0) {
        scheduler.processNextTask();
        scheduler.displayStats();
    }
}

int main() {
    cout << "Starting Task Scheduler Tests...\n";
    TaskScheduler scheduler;

    try {
        runSchedulerTests(scheduler);
    }
    catch (const exception& e) {
        cerr << "Error occurred: " << e.what() << endl;
        return 1;
    }

    cout << "\nAll tests completed successfully!\n";
    return 0;
}
