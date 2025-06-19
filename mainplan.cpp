#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
using namespace std;

// 📘 Subject class
class Subject {
private:
    string name;
    int totalMarks;
    int obtainedMarks;

public:
    void inputDetails() {
        cout << "\nEnter subject name: ";
        cin >> name;
        cout << "Enter total marks: ";
        cin >> totalMarks;
        cout << "Enter obtained marks: ";
        cin >> obtainedMarks;
    }

    void displayDetails() const {
        cout << "\nSubject: " << name;
        cout << "\nTotal Marks: " << totalMarks;
        cout << "\nObtained Marks: " << obtainedMarks;
        cout << "\nPercentage: " << getPercentage() << "%";
        cout << "\nGrade: " << getGrade() << "\n";
    }

    void saveToFile(ofstream& file) const {
        file << "\nSubject: " << name;
        file << "\nTotal Marks: " << totalMarks;
        file << "\nObtained Marks: " << obtainedMarks;
        file << "\nPercentage: " << getPercentage() << "%";
        file << "\nGrade: " << getGrade() << "\n";
    }

    float getPercentage() const {
        return ((float)obtainedMarks / totalMarks) * 100;
    }

    string getGrade() const {
        float percent = getPercentage();
        if (percent >= 90) return "A+";
        else if (percent >= 80) return "A";
        else if (percent >= 70) return "B";
        else if (percent >= 60) return "C";
        else if (percent >= 50) return "D";
        else if (percent >= 40) return "E";
        else return "F";
    }

    int getObtained() const { return obtainedMarks; }
    int getTotalMarks() const { return totalMarks; }
    string getName() const { return name; }
};

// User registration
struct User {
    string username;
    string password;
    string recovery;
};

bool registerUser(User& user) {
    cout << "\n👤 Create New Account\n";
    cout << "Choose a username: ";
    cin >> user.username;
    cout << "Choose a password: ";
    cin >> user.password;
    cout << "Security question - What is your favourite thing? ";
    cin.ignore();
    getline(cin, user.recovery);
    ofstream out("user_credentials.txt");
    out << user.username << "\n" << user.password << "\n" << user.recovery;
    out.close();
    return true;
}

bool login(User& user) {
    ifstream in("user_credentials.txt");
    if (!in) {
        cout << "\nNo user found.\n";
        return registerUser(user);
    }
    string storedUser, storedPass, storedRecovery;
    getline(in, storedUser);
    getline(in, storedPass);
    getline(in, storedRecovery);
    in.close();

    string username, password;
    cout << "\n🔐 Login\nUsername: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == storedUser && password == storedPass) {
        user.username = storedUser;
        cout << "\n✅ Login successful!\n";
        return true;
    } else {
        cout << "\n❌ Incorrect credentials. Forgot password? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y') {
            string ans;
            cout << "\nAnswer the recovery question to reset.\nWhat is your favourite thing? ";
            cin.ignore();
            getline(cin, ans);
            if (ans == storedRecovery) {
                cout << "\n✅ Correct! Enter new password: ";
                string newpass;
                cin >> newpass;
                ofstream out("user_credentials.txt");
                out << storedUser << "\n" << newpass << "\n" << storedRecovery;
                out.close();
                cout << "\nPassword reset successful. Please restart program.\n";
            } else {
                cout << "\n❌ Incorrect recovery answer.\n";
            }
        }
        return false;
    }
}

// GPA and Grade Point
int getGradePoint(string grade) {
    if (grade == "A+") return 10;
    else if (grade == "A") return 9;
    else if (grade == "B") return 8;
    else if (grade == "C") return 7;
    else if (grade == "D") return 6;
    else if (grade == "E") return 5;
    else return 0;
}

void calculateGPA() {
    int subjects;
    cout << "\n📊 GPA Calculator – Enter number of subjects: ";
    cin >> subjects;
    float totalPoints = 0, totalCredits = 0;

    for (int i = 0; i < subjects; i++) {
        string grade;
        float credit;
        cout << "\nSubject " << i + 1;
        cout << "\nEnter credit: ";
        cin >> credit;
        cout << "Enter grade (A+, A, B, C, D, E, F): ";
        cin >> grade;
        totalCredits += credit;
        totalPoints += credit * getGradePoint(grade);
    }

    float gpa = totalPoints / totalCredits;
    cout << "\n✅ GPA for this semester: " << gpa << "\n";

    ofstream file("C:\\Users\\tammanna\\Desktop\\Smart Planner\\gpa_report.txt", ios::app);
    file << "Semester GPA: " << gpa << "\n";
    file.close();
    cout << "📁 GPA saved to gpa_report.txt\n";
}

void viewGPAHistory() {
    ifstream file("C:\\Users\\tammanna\\Desktop\\Smart Planner\\gpa_report.txt");
    if (!file) {
        cout << "\n⚠️ GPA history not found!";
        return;
    }
    cout << "\n📂 GPA History:\n";
    string line;
    float highest = 0;
    vector<float> gpas;
    while (getline(file, line)) {
        cout << line << "\n";
        if (line.find("Semester GPA:") != string::npos) {
            float gpa = stof(line.substr(line.find(":") + 1));
            gpas.push_back(gpa);
            if (gpa > highest) highest = gpa;
        }
    }
    if (!gpas.empty()) {
        cout << "\n🏆 Highest GPA so far: " << highest << "\n";
    }
    file.close();
}

void goalSection() {
    string goalFile = "C:\\Users\\tammanna\\Desktop\\Smart Planner\\goals.txt";
    int choice;
    cout << "\n📌 Goal Section\n1. View\n2. Add\n3. Edit\n4. Delete\nEnter: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        ifstream in(goalFile);
        string line;
        cout << "\n📝 Your Goals:\n";
        while (getline(in, line)) cout << line << "\n";
        in.close();
    } else if (choice == 2) {
        ofstream out(goalFile, ios::app);
        string goal;
        cout << "\nEnter today's goal: ";
        getline(cin, goal);
        out << goal << "\n";
        out.close();
    } else if (choice == 3) {
        cout << "\nFeature not added yet.\n";
    } else if (choice == 4) {
        ofstream out(goalFile);
        out.close();
        cout << "\n✅ All goals deleted.\n";
    }
}

int main() {
    User user;
    if (!login(user)) return 0;

    vector<Subject> subjects;
    int choice;

    while (true) {
        cout << "\n\n========= MENU =========";
        cout << "\n1. Add Subjects";
        cout << "\n2. View Report";
        cout << "\n3. Edit Subject Marks";
        cout << "\n4. Exit";
        cout << "\n5. GPA Calculator";
        cout << "\n6. View GPA History";
        cout << "\n7. Write or View Goals";
        cout << "\n8. Delete Subject by Name";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int n;
            cout << "\nHow many subjects? ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                Subject subj;
                cout << "\n--- Subject " << i + 1 << " ---";
                subj.inputDetails();
                subjects.push_back(subj);
            }
        } else if (choice == 2) {
            if (subjects.empty()) {
                cout << "\n⚠️ No subjects to display!";
                continue;
            }
            float total = 0, obtained = 0;
            int topIndex = 0;
            cout << "\n========= Performance Report =========";
            for (int i = 0; i < subjects.size(); i++) {
                subjects[i].displayDetails();
                total += subjects[i].getTotalMarks();
                obtained += subjects[i].getObtained();
                if (subjects[i].getObtained() > subjects[topIndex].getObtained()) {
                    topIndex = i;
                }
            }
            float overall = (obtained / total) * 100;
            cout << "\nTotal Marks: " << total;
            cout << "\nTotal Obtained: " << obtained;
            cout << "\nOverall Percentage: " << overall << "%";
            cout << "\nTopper: " << subjects[topIndex].getName()
                 << " with " << subjects[topIndex].getObtained() << " marks";

            ofstream file("C:\\Users\\tammanna\\Desktop\\Smart Planner\\report.txt");
            for (int i = 0; i < subjects.size(); i++) {
                subjects[i].saveToFile(file);
                file << "\n";
            }
            file << "\nTotal Marks: " << total;
            file << "\nTotal Obtained: " << obtained;
            file << "\nOverall Percentage: " << overall << "%";
            file << "\nTopper: " << subjects[topIndex].getName()
                 << " with " << subjects[topIndex].getObtained() << " marks";
            file.close();
            cout << "\n\n✅ Report saved to Desktop!";

        } else if (choice == 3) {
            string editName;
            cout << "\nEnter subject name to edit: ";
            cin >> editName;
            bool found = false;
            for (auto& s : subjects) {
                if (s.getName() == editName) {
                    cout << "\nEditing subject: " << editName;
                    s.inputDetails();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "\n⚠️ Subject not found!";

        } else if (choice == 8) {
            string delName;
            cout << "\nEnter subject name to delete: ";
            cin >> delName;
            bool deleted = false;
            for (auto it = subjects.begin(); it != subjects.end(); ++it) {
                if (it->getName() == delName) {
                    subjects.erase(it);
                    cout << "\n✅ Subject deleted.";
                    deleted = true;
                    break;
                }
            }
            if (!deleted) cout << "\n⚠️ Subject not found!";

        } else if (choice == 4) {
            cout << "\n👋 Logging out...";
            break;
        } else if (choice == 5) {
            calculateGPA();
        } else if (choice == 6) {
            viewGPAHistory();
        } else if (choice == 7) {
            goalSection();
        } else {
            cout << "\n❌ Invalid choice.";
        }
    }
    return 0;
}
