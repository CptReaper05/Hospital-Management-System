#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 50
#define MAX_APPOINTMENTS 100
#define MAX_BILLS 100
#define MAX_USERS 5

//structures 
struct Patient {
    int id;
    char name[100];
    int age;
    char disease[100];
    char history[500];
};

struct Doctor {
    int id;
    char name[100];
    char specialization[100];
    char contact[20];
};

struct Appointment {
    int patient_id;
    int doctor_id;
    char date[20];
    char time[10];
};

struct Bill {
    int patient_id;
    float treatment_cost;
    float medication_cost;
    float total_cost;
};

struct User {
    char username[20];
    char password[20];
};

//login
struct User users[MAX_USERS] = {
    {"admin", "admin123"},
    {"doctor1", "doc123"},
    {"nurse", "nurse123"}
};

int authenticate() {
    char username[20], password[20];
    printf("\n🔑 Login to HMS\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("\n✅ Login successful!\n");
            return 1;
        }
    }
    printf("\n❌ Invalid credentials. Try again!\n");
    return 0;
}
//patient management
void addPatient(struct Patient *patients, int *patientCount) {
    printf("Enter Patient ID: ");
    scanf("%d", &patients[*patientCount].id);
    printf("Enter Name: ");
    scanf("%s", patients[*patientCount].name);
    printf("Enter Age: ");
    scanf("%d", &patients[*patientCount].age);
    printf("Enter Disease: ");
    scanf("%s", patients[*patientCount].disease);
    printf("Enter Medical History: ");
    scanf(" %[^\n]", patients[*patientCount].history);
    
    (*patientCount)++;
    printf("✅ Patient added successfully!\n");
}

void viewPatients(struct Patient *patients, int patientCount) {
    printf("\n👩‍⚕️ Patient Records:\n");
    for (int i = 0; i < patientCount; i++) {
        printf("ID: %d | Name: %s | Age: %d | Disease: %s\n", 
                patients[i].id, patients[i].name, patients[i].age, patients[i].disease);
    }
}
void searchPatient(struct Patient *patients, int patientCount) {
    char searchName[100];
    printf("\nEnter patient name to search: ");
    scanf("%s", searchName);

    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].name, searchName) == 0) {
            printf("\n✅ Patient Found: ID: %d | Name: %s | Age: %d | Disease: %s\n",
                   patients[i].id, patients[i].name, patients[i].age, patients[i].disease);
            return;
        }
    }
    printf("\n❌ Patient not found.\n");
}

void sortPatients(struct Patient *patients, int patientCount) {
    for (int i = 0; i < patientCount - 1; i++) {
        for (int j = 0; j < patientCount - i - 1; j++) {
            if (strcmp(patients[j].name, patients[j + 1].name) > 0) {
                struct Patient temp = patients[j];
                patients[j] = patients[j + 1];
                patients[j + 1] = temp;
            }
        }
    }
    printf("✅ Patients sorted successfully!\n");
}

void savePatientsToFile(struct Patient *patients, int patientCount) {
    FILE *file = fopen("patients.txt", "w");
    if (file == NULL) {
        printf("❌ Error opening file for saving patient data.\n");
        return;
    }
    for (int i = 0; i < patientCount; i++) {
        fprintf(file, "%d,%s,%d,%s,%s\n", patients[i].id, patients[i].name,
                patients[i].age, patients[i].disease, patients[i].history);
    }
    fclose(file);
}

void saveDoctorsToFile(struct Doctor *doctors, int doctorCount) {
    FILE *file = fopen("doctors.txt", "w");
    if (file == NULL) {
        printf("❌ Error opening file for saving doctor data.\n");
        return;
    }
    for (int i = 0; i < doctorCount; i++) {
        fprintf(file, "%d,%s,%s,%s\n", doctors[i].id, doctors[i].name,
                doctors[i].specialization, doctors[i].contact);
    }
    fclose(file);
}

void saveAppointmentsToFile(struct Appointment *appointments, int appointmentCount) {
    FILE *file = fopen("appointments.txt", "w");
    if (file == NULL) {
        printf("❌ Error opening file for saving appointments.\n");
        return;
    }
    for (int i = 0; i < appointmentCount; i++) {
        fprintf(file, "%d,%d,%s,%s\n", appointments[i].patient_id, 
                appointments[i].doctor_id, appointments[i].date, appointments[i].time);
    }
    fclose(file);
}


void saveBillsToFile(struct Bill *bills, int billCount) {
    FILE *file = fopen("bills.txt", "w");
    if (file == NULL) {
        printf("❌ Error opening file for saving bills.\n");
        return;
    }
    for (int i = 0; i < billCount; i++) {
        fprintf(file, "%d,%.2f,%.2f,%.2f\n", bills[i].patient_id, 
                bills[i].treatment_cost, bills[i].medication_cost, bills[i].total_cost);
    }
    fclose(file);
}


// doctor management 
void addDoctor(struct Doctor *doctors, int *doctorCount) {
    printf("Enter Doctor ID: ");
    scanf("%d", &doctors[*doctorCount].id);
    printf("Enter Name: ");
    scanf("%s", doctors[*doctorCount].name);
    printf("Enter Specialization: ");
    scanf("%s", doctors[*doctorCount].specialization);
    printf("Enter Contact Number: ");
    scanf("%s", doctors[*doctorCount].contact);

    (*doctorCount)++;
    printf("✅ Doctor added successfully!\n");
}

void viewDoctors(struct Doctor *doctors, int doctorCount) {
    printf("\n👨‍⚕️ Doctor List:\n");
    for (int i = 0; i < doctorCount; i++) {
        printf("ID: %d | Name: %s | Specialization: %s | Contact: %s\n", 
                doctors[i].id, doctors[i].name, doctors[i].specialization, doctors[i].contact);
    }
}
void searchDoctor(struct Doctor *doctors, int doctorCount) {
    char searchName[100];
    printf("\nEnter doctor name to search: ");
    scanf("%s", searchName);

    for (int i = 0; i < doctorCount; i++) {
        if (strcmp(doctors[i].name, searchName) == 0) {
            printf("\n✅ Doctor Found: ID: %d | Name: %s | Specialization: %s | Contact: %s\n",
                   doctors[i].id, doctors[i].name, doctors[i].specialization, doctors[i].contact);
            return;
        }
    }
    printf("\n❌ Doctor not found.\n");
}

void sortAppointments(struct Appointment *appointments, int appointmentCount) {
    for (int i = 0; i < appointmentCount - 1; i++) {
        for (int j = 0; j < appointmentCount - i - 1; j++) {
            if (strcmp(appointments[j].date, appointments[j + 1].date) > 0) {
                struct Appointment temp = appointments[j];
                appointments[j] = appointments[j + 1];
                appointments[j + 1] = temp;
            }
        }
    }
    printf("✅ Appointments sorted by date successfully!\n");
}

void loadPatientsFromFile(struct Patient *patients, int *patientCount) {
    FILE *file = fopen("patients.txt", "r");
    if (file == NULL) {
        printf("No previous patient data found.\n");
        return;
    }
    while (fscanf(file, "%d,%[^,],%d,%[^,],%[^\n]", &patients[*patientCount].id, 
                  patients[*patientCount].name, &patients[*patientCount].age, 
                  patients[*patientCount].disease, patients[*patientCount].history) != EOF) {
        (*patientCount)++;
    }
    fclose(file);
}


//appointment 
void scheduleAppointment(struct Appointment *appointments, int *appointmentCount) {
    printf("Enter Patient ID: ");
    scanf("%d", &appointments[*appointmentCount].patient_id);
    printf("Enter Doctor ID: ");
    scanf("%d", &appointments[*appointmentCount].doctor_id);
    printf("Enter Date (DD/MM/YYYY): ");
    scanf("%s", appointments[*appointmentCount].date);
    printf("Enter Time (HH:MM): ");
    scanf("%s", appointments[*appointmentCount].time);

    (*appointmentCount)++;
    printf("✅ Appointment scheduled successfully!\n");
}

void viewAppointments(struct Appointment *appointments, int appointmentCount) {
    printf("\n📅 Appointments:\n");
    for (int i = 0; i < appointmentCount; i++) {
        printf("Patient ID: %d | Doctor ID: %d | Date: %s | Time: %s\n",
                appointments[i].patient_id, appointments[i].doctor_id, 
                appointments[i].date, appointments[i].time);
    }
}
// bill & payment 
void generateBill(struct Bill *bills, int *billCount) {
    printf("Enter Patient ID: ");
    scanf("%d", &bills[*billCount].patient_id);
    printf("Enter Treatment Cost: ");
    scanf("%f", &bills[*billCount].treatment_cost);
    printf("Enter Medication Cost: ");
    scanf("%f", &bills[*billCount].medication_cost);

    bills[*billCount].total_cost = bills[*billCount].treatment_cost + bills[*billCount].medication_cost;
    printf("✅ Bill generated! Total: ₹%.2f\n", bills[*billCount].total_cost);
    
    (*billCount)++;
}
//main menu
int main() {
    struct Patient patients[MAX_PATIENTS];
    struct Doctor doctors[MAX_DOCTORS];
    struct Appointment appointments[MAX_APPOINTMENTS];
    struct Bill bills[MAX_BILLS];

    int patientCount = 0, doctorCount = 0, appointmentCount = 0, billCount = 0;

    if (!authenticate()) return 0;  // User authentication check

    int choice;
    while (1) {
        printf("\n🏥 Hospital Management System\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. Add Doctor\n");
        printf("4. View Doctors\n");
        printf("5. Schedule Appointment\n");
        printf("6. View Appointments\n");
        printf("7. Generate Bill\n");
        printf("8. Search Patient\n");
        printf("9. Search Doctor\n");
        printf("10. Sort Patients by Name\n");
        printf("11. Sort Appointments by Date\n");
        printf("12. Save Data to File & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: addPatient(patients, &patientCount); break;
            case 2: viewPatients(patients, patientCount); break;
            case 3: addDoctor(doctors, &doctorCount); break;
            case 4: viewDoctors(doctors, doctorCount); break;
            case 5: scheduleAppointment(appointments, &appointmentCount); break;
            case 6: viewAppointments(appointments, appointmentCount); break;
            case 7: generateBill(bills, &billCount); break;
            case 8: searchPatient(patients, patientCount); break;
            case 9: searchDoctor(doctors, doctorCount); break;
            case 10: sortPatients(patients, patientCount); break;
            case 11: sortAppointments(appointments, appointmentCount); break;
            case 12: 
                savePatientsToFile(patients, patientCount);
                saveDoctorsToFile(doctors, doctorCount);
                saveAppointmentsToFile(appointments, appointmentCount);
                saveBillsToFile(bills, billCount);
                printf("\n✅ Data Saved! Exiting program...\n");
                exit(0);
            default: 
                printf("\n❌ Invalid choice! Please try again.\n");
        }
    }
    return 0;
}


void handleError(const char *msg) {
    fprintf(stderr, "❌ ERROR: %s\n", msg);
    exit(1);
}
