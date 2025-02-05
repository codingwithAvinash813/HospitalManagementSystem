#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Patient Class
class Patient {
public:
    int id;
    string name, disease, doctorAssigned;
    float billAmount;
    
    void addPatient();
    void displayPatients();
    void searchPatient(int);
    void updatePatient(int);
    void deletePatient(int);
};

void Patient::addPatient() {
    cout << "Enter Patient ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Patient Name (Gujarati): ";
    getline(cin, name);
    cout << "Enter Disease: ";
    getline(cin, disease);
    cout << "Enter Assigned Doctor (Gujarati): ";
    getline(cin, doctorAssigned);
    billAmount = 0; // Initially, no bill

    ofstream file("patients.txt", ios::app);
    file << id << " " << name << " " << disease << " " << doctorAssigned << " " << billAmount << endl;
    file.close();

    cout << "Patient added successfully!\n";
}

void Patient::displayPatients() {
    ifstream file("patients.txt");
    if (!file) {
        cout << "No patient records found!\n";
        return;
    }

    cout << "\nID\tName\tDisease\tDoctor\tBill(₹)\n";
    while (file >> id >> name >> disease >> doctorAssigned >> billAmount) {
        cout << id << "\t" << name << "\t" << disease << "\t" << doctorAssigned << "\t₹" << billAmount << endl;
    }
    file.close();
}

// Search Patient by ID
void Patient::searchPatient(int searchID) {
    ifstream file("patients.txt");
    bool found = false;
    while (file >> id >> name >> disease >> doctorAssigned >> billAmount) {
        if (id == searchID) {
            cout << "\nPatient Found!\n";
            cout << "ID: " << id << "\nName: " << name << "\nDisease: " << disease << "\nDoctor: " << doctorAssigned << "\nBill: ₹" << billAmount << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "Patient not found!\n";
    file.close();
}

// Update Patient Bill
void Patient::updatePatient(int searchID) {
    ifstream file("patients.txt");
    ofstream temp("temp.txt");
    bool found = false;
    while (file >> id >> name >> disease >> doctorAssigned >> billAmount) {
        if (id == searchID) {
            cout << "\nUpdating Bill for Patient: " << name << "\nEnter new Bill Amount (₹): ";
            cin >> billAmount;
            found = true;
        }
        temp << id << " " << name << " " << disease << " " << doctorAssigned << " " << billAmount << endl;
    }
    file.close();
    temp.close();
    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found)
        cout << "Bill Updated Successfully!\n";
    else
        cout << "Patient not found!\n";
}

// Delete Patient
void Patient::deletePatient(int searchID) {
    ifstream file("patients.txt");
    ofstream temp("temp.txt");
    bool found = false;
    while (file >> id >> name >> disease >> doctorAssigned >> billAmount) {
        if (id == searchID) {
            cout << "Deleting patient record: " << name << endl;
            found = true;
            continue;
        }
        temp << id << " " << name << " " << disease << " " << doctorAssigned << " " << billAmount << endl;
    }
    file.close();
    temp.close();
    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found)
        cout << "Patient Deleted Successfully!\n";
    else
        cout << "Patient not found!\n";
}

// Appointment Booking
void bookAppointment() {
    int pid, docID;
    string timeSlot;

    cout << "Enter Patient ID: ";
    cin >> pid;
    cout << "Enter Doctor ID: ";
    cin >> docID;
    cout << "Enter Time Slot (HH:MM AM/PM): ";
    cin.ignore();
    getline(cin, timeSlot);

    ofstream file("appointments.txt", ios::app);
    file << pid << " " << docID << " " << timeSlot << endl;
    file.close();

    cout << "Appointment Booked Successfully!\n";
}

// Display Appointments
void displayAppointments() {
    ifstream file("appointments.txt");
    int pid, docID;
    string timeSlot;

    cout << "\nAppointments:\nPatient ID\tDoctor ID\tTime Slot\n";
    while (file >> pid >> docID >> timeSlot) {
        cout << pid << "\t\t" << docID << "\t\t" << timeSlot << endl;
    }
    file.close();
}

// Medicine Inventory
void manageMedicines() {
    int choice;
    string medName;
    int quantity;
    
    do {
        cout << "\nMedicine Inventory:\n1. Add Medicine\n2. View Medicines\n3. Exit\nEnter Choice: ";
        cin >> choice;
        
        if (choice == 1) {
            cout << "Enter Medicine Name: ";
            cin >> medName;
            cout << "Enter Quantity: ";
            cin >> quantity;
            ofstream file("medicines.txt", ios::app);
            file << medName << " " << quantity << endl;
            file.close();
            cout << "Medicine Added Successfully!\n";
        }
        else if (choice == 2) {
            ifstream file("medicines.txt");
            cout << "\nAvailable Medicines:\n";
            while (file >> medName >> quantity) {
                cout << medName << " - " << quantity << " units\n";
            }
            file.close();
        }
    } while (choice != 3);
}

// Main Function
int main() {
    Patient p;
    int choice, pid;

    do {
        cout << "\n🏥 Hospital Management System 🏥";
        cout << "\n1. Add Patient\n2. View Patients\n3. Search Patient\n4. Update Patient Bill\n5. Delete Patient";
        cout << "\n6. Book Appointment\n7. View Appointments\n8. Manage Medicines\n9. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: p.addPatient(); break;
            case 2: p.displayPatients(); break;
            case 3: cout << "Enter Patient ID: "; cin >> pid; p.searchPatient(pid); break;
            case 4: cout << "Enter Patient ID: "; cin >> pid; p.updatePatient(pid); break;
            case 5: cout << "Enter Patient ID: "; cin >> pid; p.deletePatient(pid); break;
            case 6: bookAppointment(); break;
            case 7: displayAppointments(); break;
            case 8: manageMedicines(); break;
            case 9: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 9);

    return 0;
}
