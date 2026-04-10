#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <list>
#include <stack>
#include <ctime>
#include <iomanip>
#include <limits>
using namespace std;

struct Activity {
    string timestamp;
    string description;
    Activity(string ts, string desc) : timestamp(ts), description(desc) {}
};

struct BSTNode {
    Activity activity;
    BSTNode* left;
    BSTNode* right;
    BSTNode(Activity a) : activity(a), left(nullptr), right(nullptr) {}
};

class ActivityBST { // Binary Search Tree (BST) class
private:
    BSTNode* root;
    void insert(BSTNode*& node, const Activity& activity) { //to insert an activity into the BST
        if (node == nullptr) {
            node = new BSTNode(activity);
        } else if (activity.timestamp < node->activity.timestamp) {
            insert(node->left, activity);
        } else {
            insert(node->right, activity);
        }
    }
    void display_in_order(BSTNode* node) const { //to display the BST in in-order (sorted by timestamp)
        if (node != nullptr) {
            display_in_order(node->left);
            cout << node->activity.timestamp << " - " << node->activity.description << endl;
            display_in_order(node->right);
        }
    }
public:
    ActivityBST() : root(nullptr) {}
    void insert(const Activity& activity) {
        insert(root, activity);
    }
    void display() const { //Public function to display all activities (sorted by timestamp)
        display_in_order(root);
    }
};

class Person {
public:
    string name, ID;
    int age;
    float weight,height;
    Person(string n, string id, int a, float w, float h) : name(n), ID(id), age(a), weight(w), height(h) {}
    virtual void show_info() {
        cout << "Name: " << name << endl;
        cout << "ID: " << ID << endl;
        cout << "Age: " << age << endl;
        cout << "Weight: " << weight << " Kg" << endl;
        cout << "Height: " << height << " cm" << endl;
    }
    virtual ~Person() {}
};

class Bronze : public Person {
private:
    float initialWeight;
public:
	int waterIntake=0;
    list<float> weightLog;  // Linked list to track weight logs
    float weightGoal;            
  
    Bronze(string n, string id, int a, float w, float h)
        : Person(n, id, a, w, h), weightGoal(0.0), initialWeight(w) {
        weightLog.push_back(w); // Add initial weight to log
    }

    void add_weight(float weight) {
        weightLog.push_back(weight);
    }

    void set_weight_goal(float goal) {
        weightGoal = goal;
        if (initialWeight > weightGoal) {
            cout << "Your initial weight (" << initialWeight << " kg) is greater than your goal (" << weightGoal << " kg)." << endl;
            cout << "\nSuggestions to reduce weight:" << endl;
            cout << "* Incorporate daily exercise (e.g., brisk walking, jogging)." << endl;
            cout << "* Follow a calorie deficit diet." << endl;
        } else if (initialWeight < weightGoal) {
            cout << "Your initial weight (" << initialWeight << " kg) is less than your goal (" << weightGoal << " kg)." << endl;
            cout << "\nSuggestions to increase weight:" << endl;
            cout << "* Add more protein-rich and calorie-dense foods to your diet." << endl;
            cout << "* Perform strength training to build muscle." << endl;
        } else {
            cout << "Your weight matches your goal. Maintain your current habits!" << endl;
        }
    }

    void show_weight_progress() {
        cout << "Weight Log: ";
        for (float w : weightLog)
            cout << w << " " << "Kg";
        cout << endl;
        if (weightGoal > 0.0) {
            cout << "Weight Goal: " << weightGoal << " kg" << endl;
            if (!weightLog.empty()) {
                float currentWeight = weightLog.back();
                if (currentWeight > weightGoal) {
                    cout << "Your current weight is greater than your goal by " << (currentWeight - weightGoal) << " kg." << endl;
                } else if (currentWeight < weightGoal) {
                    cout << "You are " << (weightGoal - currentWeight) << " kg away from your goal." << endl;
                } else {
                    cout << "You have reached your weight goal!" << endl;
                }
            } else {
                cout << "No weight logs yet." << endl;
            }
        } else {
            cout << "No weight goal set." << endl;
        }
    }
    void track_water_intake(int amount) {
		waterIntake += amount;
        cout << "Added " << amount << " glasses of water. Total water intake: " << waterIntake << " glasses." << endl;
        if (waterIntake < 8) {
            cout << "Your water intake is below the recommended 8 glasses (2000 ml) per day." << endl;
            cout << "Suggestions to increase water intake:" << endl;
            cout << "1. Keep a water bottle with you throughout the day." << endl;
            cout << "2. Set reminders to drink water regularly." << endl;
        } else {
            cout << "Great job! You have met the recommended daily water intake." << endl;
        }
    }
    void show_info() override {
        Person::show_info();
        cout << "Initial Weight: " << initialWeight << " kg" << endl;
        cout << "Total Water Intake: " << waterIntake << " glasses" << endl;
        show_weight_progress();  // Display weight progress as part of info
    }
};

class Silver : public Bronze {
public:
    int diet, goals,systolic, diastolic;    
    Silver(string n, string id, int a, float w, float h, int d, int g) : Bronze(n, id, a, w, h), 
	diet(d), goals(g) , systolic(0), diastolic(0){}
     void check_blood_pressure() {
    	int systolic, diastolic;
        cout << "Enter your systolic blood pressure: ";
        cin >> systolic;
        cout << "Enter your diastolic blood pressure: ";
        cin >> diastolic;
        if (systolic < 90 || diastolic < 60) {
            cout << "Your blood pressure is low. Consider staying hydrated and eating a balanced diet." << endl;
        } else if (systolic > 120 || diastolic > 80) {
            cout << "Your blood pressure is high. Limit salt intake and consult a doctor if necessary." << endl;
        } else {
            cout << "Your blood pressure is normal. Keep up the good work!" << endl;
        }
    }
    void show_info() override {
        Bronze::show_info();
        cout << "Diet Goal (Calories): " << diet << endl;
        cout << "Daily Exrercise goal in hours:  " << goals << endl;
    }   
};

class Gold : public Silver {
public:
    queue<string> reminders;  // Queue for reminders
    int sleepTime;
    Gold(string n, string id, int a, float w, float h, int d, int g, int s) : Silver(n, id, a, w, h, d, g), sleepTime(s) {}
        
    void add_reminder(string reminder) {
        reminders.push(reminder);
    }
    void process_reminders() {
        while (!reminders.empty()) {
            cout << "Reminder: " << reminders.front() << endl;
            reminders.pop();
        }
    }
    void process_sleepTime(int sleepTime){
    	if (sleepTime < 8) {
            cout << "You should take sufficient sleep. Aim for at least 8 hours." << endl;
        } else if (sleepTime > 8) {
            cout << "You are oversleeping. Try to maintain a balanced sleep schedule." << endl;
        } else {
            cout << "Your sleep duration is good. Keep it up!" << endl;
        }
	}
    void show_info() override {
        Silver::show_info();
        cout << "Sleep Time: " << sleepTime << " hours" << endl;
        cout << "Pending Reminders: " << reminders.size() << endl;
    }
};
// Global variables
map<string, Person*> peopleMap;  // Map for user data
stack<string> activityHistory;  // Stack for tracking activity history
ActivityBST activityTree;       // Binary Search Tree to store activity history

void display_activity_history() { // Function to display the activity history using the BST
    cout << "Activity History (Sorted by Timestamp):" << endl;
    activityTree.display();
}
void add_activity(const string& activity) { // Function to add an activity to the history (BST)
     // Get the current time
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    // Format the time as "YYYY-MM-DD HH:MM"
    char timestamp[20];  // Buffer for formatted date-time
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M", localTime);

    // Insert the activity with the real-time timestamp
    activityTree.insert(Activity(timestamp, activity));
}

void main_menu(Person* currUser) { // Main menu for the person
    int choice;
    cout << "\nWelcome to the Health and Fitness Tracker!\n" << endl;
    cout << "1. View Information" << endl;
    
    if (Bronze* bronzeUser = dynamic_cast<Bronze*>(currUser)) {
        cout << "2. Set Weight Goal" << endl;
        cout << "3. Track Weight Progress" << endl;
        cout << "4. Track Water Intake" << endl;
    }
    if (Silver* silverUser = dynamic_cast<Silver*>(currUser)) {
    	cout << "5. Check Blood Pressure" << endl;
        cout << "6. Check Diet (Calories Intake)" << endl;
        cout << "7. Set Goals for daily exercise" << endl;
    }
    if (Gold* goldUser = dynamic_cast<Gold*>(currUser)) {
        cout << "8. Set Reminder" << endl;
        cout << "9. Update Sleep Time" << endl;
    }
    cout << "10. View Activity History" << endl;
    cout << "11. Sign Out\n" << endl;
    cout << "Please select an option: ";
    cin >> choice;
    add_activity("Entered main menu");
    // Menu options
    switch (choice) {
        case 1:
            currUser->show_info();
            add_activity("Viewed Information");
            break;
        case 2:
            if (Bronze* bronzeUser = dynamic_cast<Bronze*>(currUser)) {
                float weightGoal;
                cout << "Enter your weight goal (kg): ";
                cin >> weightGoal;
                bronzeUser->set_weight_goal(weightGoal);
                add_activity("Set weight goal");
            } else {
                cout << "This option is not available for your membership type." << endl;
            }
            break;
        case 3:
            if (Bronze* bronzeUser = dynamic_cast<Bronze*>(currUser)) {
                bronzeUser->show_weight_progress();
                add_activity("Tracked weight progress");
            } else {
                cout << "This option is not available for your membership type." << endl;
            }
            break;
    
        case 4:
            if (Bronze* bronzeUser = dynamic_cast<Bronze*>(currUser)) {
                int water;
                cout << "Enter the amount of water you drank (glasses): ";
                cin >> water;
                bronzeUser->track_water_intake(water);
                add_activity("Tracked water intake");
            } else {
                cout << "This option is not available for your membership type." << endl;
            }
            break;
            
        case 5:
            if (Silver* silverUser = dynamic_cast<Silver*>(currUser)) {
                silverUser->check_blood_pressure();
                add_activity("Checked blood pressure");
            } else {
                cout << "This option is not available for your membership type." << endl;
            }
            break;    
            
        case 6:
            if (Silver* silverUser = dynamic_cast<Silver*>(currUser)) {
                cout << "Diet goal (Calories Intake): " << silverUser->diet << " calories" << endl;
                add_activity("Checked diet");
            } else {
                cout << "This option is not available for your membership type." << endl;
            }
            break;
        case 7:
            if (Silver* silverUser = dynamic_cast<Silver*>(currUser)) {
                int goal;
                cout << "Enter your daily exercise goal (hours): ";
                cin >> goal;
                silverUser->goals = goal;
                cout << "Daily exercise goal set to " << goal << " hours." << endl;
                add_activity("Set daily goals");
            } else {
                cout << "This option is not available for your membership type." << endl;
            }
            break;
        case 8:
            if (Gold* goldUser = dynamic_cast<Gold*>(currUser)) {
                string reminder;
                cout << "Enter a reminder: ";
                cin.ignore();
                getline(cin, reminder);
                goldUser->add_reminder(reminder);
                cout << "Reminder added!" << endl;
                add_activity("Set reminder");
            } else {
                cout << "This option is not available for your membership type." << endl;
            }
            break;
        case 9:
            if (Gold* goldUser = dynamic_cast<Gold*>(currUser)) {
                int sleepTime;
                cout << "Enter your new sleep time (hours): ";
                cin >> sleepTime;
                goldUser->sleepTime = sleepTime;
                cout << "Sleep time updated to " << sleepTime << " hours." << endl;
                goldUser->process_sleepTime(sleepTime);
                add_activity("Updated sleep time");
            } else {
                cout << "This option is not available for your membership type." << endl;
            }
            break;
        case 10:
            display_activity_history();
            add_activity("Viewed activity history");
            break;
        case 11:
            cout << "Signed Out Successfully.\n" << endl;
            add_activity("Signed Out");
            return;
        default:
            cout << "Invalid choice!" << endl;
            break;
    }

    // Return to menu
    main_menu(currUser);
}

void sign_in() { // Function to sign in
    string id;
    cout << "Enter your ID to sign in: ";
    cin >> id;
    if (peopleMap.find(id) != peopleMap.end()) {
        cout << "Sign-in successful!" << endl;
        main_menu(peopleMap[id]);  // Redirect to the main menu after successful sign-in
    } else {
        cout << "Invalid ID! Please try again." << endl;
        sign_in();
    }
}

void create_new_user() { // Function to create a new user
    string name, id;
    int age, height, membershipType;
    float weight;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter the ID: ";
    cin >> id;
    while (true) {
       cout << "Enter age: ";
       cin >> age;

        // Check if the input failed (non-numeric input)
       if (cin.fail()) {
           cout << "Invalid input: Please enter a valid number for age." << endl;

            // Clear the error flag and ignore the rest of the invalid input
           cin.clear(); // clears the error flag
           cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores the rest of the invalid input
           continue; 
        }
        break;
    }
    while (true) {
       cout << "Enter your weight (kg): ";
       cin >> weight;
       if (cin.fail()) {
           cout << "Invalid input: Please enter a valid weight." << endl;
           cin.clear();
           cin.ignore(numeric_limits<streamsize>::max(), '\n');
           continue; 
        }
        break;
    }
    while (true) {
       cout << "Enter your height (cm): ";
       cin >> height;
       if (cin.fail()) {
           cout << "Invalid input: Please enter a valid height." << endl;
           cin.clear(); 
           cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
           continue;
        }
        break;
    }

    cout << "Select your membership type:" << endl;
    cout << "1. Bronze" << endl;
    cout << "2. Silver" << endl;
    cout << "3. Gold" << endl;
    cout << "Please select (1-3): ";
    cin >> membershipType;
    Person* newUser = nullptr;
    switch (membershipType) {
        case 1:
            newUser = new Bronze(name, id,age, weight, height); //to view the information
            break;
        case 2: {
            int diet, goals;
            cout << "Enter your diet goal (calories): ";
            cin >> diet;
            cout << "Enter your daily exercise goals (hours): ";
            cin >> goals;
            newUser = new Silver(name, id, age, weight, height, diet, goals);
            break;
        }
        case 3: {
            int diet, goals, sleepTime;
            cout << "Enter your daily diet goal (calories): ";
            cin >> diet;
            cout << "Enter your fitness goal for the day (hours of exercise): ";
            cin >> goals;
            cout << "Enter your average sleep time (hours): ";
            cin >> sleepTime;
            newUser = new Gold(name, id, age, weight, height, diet, goals, sleepTime);
            break;
        }
        default:
            cout << "Invalid membership type!" << endl;
            return;
    }
    peopleMap[id] = newUser;
    cout << "Account created successfully!" << endl;
    // Redirect to the main screen after creating an account
    int choice;
    cout << "\nWhat would you like to do next?" << endl;
    cout << "1. Sign In" << endl;
    cout << "2. Create Another Account" << endl;
    cout << "3. Exit" << endl;
    cout << "Please select an option: ";
    cin >> choice;
    switch (choice) {
        case 1:
            sign_in();
            break;
        case 2:
            create_new_user();
            break;
        case 3:
            cout << "Exiting program..." << endl;
            exit(0);
        default:
            cout << "Invalid option!" << endl;
            break;
    }
}
int main() {
    peopleMap["B123"] = new Silver("Batool", "B123", 18, 45.0, 157.48,2000,2); // Pre-add a user to the map
    peopleMap["W123"] = new Gold("Wafa", "W123", 20, 48.0, 165,1000,3,6);
    peopleMap["N123"] = new Bronze("Nimra", "N123", 19, 50.0, 170);
    while (true) {
        cout << "Welcome to the Health and Fitness Tracker!" << endl;
        cout << "1. Sign In" << endl;
        cout << "2. Create Account" << endl;
        cout << "3. Exit" << endl;
        cout << "Please select an option: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            sign_in();
        } else if (choice == 2) {
            create_new_user();
        } else if (choice == 3) {
            cout << "Exiting program..." << endl;
            return 0;
        } else {
            cout << "Invalid option! Please try again." << endl;
        }
    }
    return 0;
}
