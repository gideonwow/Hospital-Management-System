#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATIENTS 100
#define MAX_DOCTORS 100
#define MAX_SCHEDULES 100
#define MAX_APPOINTMENTS 100
#define MAX_PRESCRIPTIONS 100
#define MAX_BILLINGS 100

typedef struct {
    char patientID[20];
    char password[20];
    char fullName[50];
    char dob[11];
    char contactNumber[20];
    char address[100];
    char gender[10];
    char race[20];
    char maritalStatus[20];
    char medicalHistory[200];
    char allergies[200];
    char pastProcedures[200];
} Patient;

typedef struct {
    char doctorID[20];
    char password[20];
    char fullName[50];
    char dob[11];
    char contactNumber[20];
    char specialty[50];
} Doctor;

typedef struct {
    char staffNurseID[20];
    char password[20];
    char fullName[50];
    char dob[11];
    char contactNumber[20];
} StaffNurse;

typedef struct {
    char doctorID[20];
    char availableDate[100];
    char startTime[100];
    char endTime[100];
} DoctorSchedule;

typedef struct {
    char appointmentID[20];
    char doctorID[20];
    char patientID[20];
    char date[11];
    char startTime[6];
    char endTime[6];
    char reason[100];
    char status[20];
} Appointment;

typedef struct {
    char prescriptionID[20];
    char appointmentID[20];
    char doctorID[20];
    char patientID[20];
    char prescription[100];
    char dosage[20];
    char frequency[50];
    char startDate[11];
    char endDate[11];
} Prescription;

typedef struct {
    char billingID[20];
    char appointmentID[20];
    char patientID[20];
    char amount[20];
    char paymentDate[20];
    char status[50];
    char insurance[11];
} Billing;

typedef struct {
    char reportID[20];
    char appointmentID[20];
    char doctorID[20];
    char patientID[20];
    char diagnosis[100];
    char treatment[100];
    char outcome[100];
} Report;

typedef struct {
    char itemID[20];
    char itemName[50];
    int quantityAvailable;
    int minStockLevel;
    int maxStockLevel;
    float costPerUnit;
    char supplier[100];
} Inventory;





void hospitalAdministratorLogin();

void loadPatientsData(Patient *patients, int *patientCount);
void loadDoctorsData(Doctor *doctors, int *doctorCount);
void loadStaffNursesData(StaffNurse *staffNurses, int *staffNurseCount);
void displayPatients(Patient *patients, int patientCount);
void displayDoctors(Doctor *doctors, int doctorCount);
void displayStaffNurses(StaffNurse *staffNurses, int staffNurseCount);

void registerNewUser();


void addPatient();
void addDoctor();
void addStaffNurse();

void viewAppointmentTrends();

void viewInventory();
void addInventory();
void editInventory();
void deleteInventory();

char *generateID(const char *prefix, int lastID);

void patientLogin1();
void patientLogin2();
void patientMenu();
void appointmentManagement();
void bookAppointment();
void viewMyAppointments();
void rescheduleAppointment();
void cancelAppointment();
void viewEHRAndBillings();
void viewPrescription();
void viewAppointmentHistory();
void viewBillingInformation();
void readPatients();
void readDoctors();
void readDoctorSchedules();
void readAppointments();
void readPrescriptions();
void readBillings();
int authenticatePatient(const char* patientID, const char* password);



void doctorLogin();
void doctorMenu(Doctor* loggedInDoctor);
void viewDoctorSchedules();
void viewMySchedules(Doctor* loggedInDoctor);
void addMySchedule(Doctor* loggedInDoctor);
void editMySchedule(Doctor* loggedInDoctor);
void deleteMySchedule(Doctor* loggedInDoctor);
void viewEHR();
void viewReports();
void viewPatientsWithSpecificDiagnosis();


int staffNurseLogin();
void staffNurseMenu(char *fullName);
void inventoryManagement();
void reportingAnalytics();
void viewReport();
void searchSpecificSpecialty();



Patient patients[100];
Doctor doctors[100];
StaffNurse staffNurses[100];
DoctorSchedule doctorSchedules[100];
Appointment appointments[100];
Prescription prescriptions[100];
Billing billings[100];
Inventory inventory[100];
Report reports[100];
int patientCount = 0;
int doctorCount = 0;
int staffNurseCount = 0;
int scheduleCount = 0;
int appointmentCount = 0;
int prescriptionCount = 0;
int billingCount = 0;
Patient currentPatient;




/// HOSPITAL MANAGEMENT SYSTEM LOGIN MENU ///
int main() {
    int choice;

    do {
        printf("\n=================== HOSPITAL MANAGEMENT SYSTEM ====================\n");
        printf("| 1. Hospital Administrator Login                                 |\n");
        printf("| 2. Patient Login                                                |\n");
        printf("| 3. Doctor Login                                                 |\n");
        printf("| 4. Staff Nurse Login                                            |\n");
        printf("|                                                                 |\n");
        printf("| 0. Exit                                                         |\n");
        printf("===================================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                hospitalAdministratorLogin();
                break;
            case 2:
                patientLogin1();
                break;
            case 3:
                doctorLogin();
                break;
            case 4:
                staffNurseLogin();
                break;
            case 0:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
/// HOSPITAL MANAGEMENT SYSTEM LOGIN MENU ///

/// vvv HOSPITAL ADMINISTRATOR vvv ///
void hospitalAdministratorLogin() {
    char adminID[20], password[20], line[100], fullName[50];
    int loggedIn = 0;
    FILE *file = fopen("hospitaladministrator.txt", "r");

    if (!file) {
        printf("Error opening file\n");
        return;
    }

    while (!loggedIn) {
        printf("\n=================== HOSPITAL ADMINISTRATOR LOGIN ===================\n");
        printf("Enter Hospital Administrator ID: ");
        scanf("%s", adminID);
        printf("Enter password: ");
        scanf("%s", password);

        while (fgets(line, sizeof(line), file)) {
            char fileAdminID[20], filePassword[20];
            sscanf(line, "%[^|]|%[^|]|%[^\n]", fileAdminID, filePassword, fullName);

            if (strcmp(adminID, fileAdminID) == 0 && strcmp(password, filePassword) == 0) {
                loggedIn = 1;
                break;
            }
        }

        if (loggedIn) {
            printf("Login successful!\n");
            adminMenu(fullName);
        } else {
            printf("Invalid ID or password. Please try again.\n");
        }

        rewind(file); // Reset file pointer to beginning for next attempt
    }

    fclose(file);
}

void adminMenu(char fullName[]) {
    int choice;

    // Load data
    loadPatientsData(patients, &patientCount);
    loadDoctorsData(doctors, &doctorCount);
    loadStaffNursesData(staffNurses, &staffNurseCount);

    do {
        printf("\n__________HOSPITAL ADMINISTRATOR MENU__________\n");
        printf("Welcome, %s!\n", fullName);
        printf("1. Register New Users\n");
        printf("2. Display Users' Information\n");
        printf("3. Inventory Management\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerNewUser();
                break;
            case 2: {
                int disChoice;
                printf("1. Display Patients\n");
                printf("2. Display Doctors\n");
                printf("3. Display Staff Nurses\n");
                printf("Enter choice: ");
                scanf("%d", &disChoice);
                switch (disChoice) {
                    case 1:
                        displayPatients(patients, patientCount);
                        break;
                    case 2:
                        displayDoctors(doctors, doctorCount);
                        break;
                    case 3:
                        displayStaffNurses(staffNurses, staffNurseCount);
                        break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }
                break;
            }
            case 3: {
                int invChoice;
                printf("1. View Inventory\n");
                printf("2. Search Inventory\n");
                printf("Enter choice: ");
                scanf("%d", &invChoice);
                switch (invChoice) {
                    case 1:
                        viewInventory();
                        break;
                    case 2:
                        searchInventory();
                        break;
                    default:
                        printf("Invalid choice.\n");
                        break;
                }
                break;
            }
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
}

void loadPatientsData(Patient *patients, int *patientCount) {
    FILE *file = fopen("patient.txt", "r");
    if (!file) {
        printf("Could not open patient.txt\n");
        exit(1);
    }
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  patients[*patientCount].patientID,
                  patients[*patientCount].password,
                  patients[*patientCount].fullName,
                  patients[*patientCount].dob,
                  patients[*patientCount].contactNumber,
                  patients[*patientCount].address,
                  patients[*patientCount].gender,
                  patients[*patientCount].race,
                  patients[*patientCount].maritalStatus,
                  patients[*patientCount].medicalHistory,
                  patients[*patientCount].allergies,
                  patients[*patientCount].pastProcedures) != EOF) {
        (*patientCount)++;
    }
    fclose(file);
}

void loadDoctorsData(Doctor *doctors, int *doctorCount) {
    FILE *file = fopen("doctor.txt", "r");
    if (!file) {
        printf("Could not open doctor.txt\n");
        exit(1);
    }
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  doctors[*doctorCount].doctorID,
                  doctors[*doctorCount].password,
                  doctors[*doctorCount].fullName,
                  doctors[*doctorCount].dob,
                  doctors[*doctorCount].contactNumber,
                  doctors[*doctorCount].specialty) != EOF) {
        (*doctorCount)++;
    }
    fclose(file);
}

void loadStaffNursesData(StaffNurse *staffNurses, int *staffNurseCount) {
    FILE *file = fopen("staffnurse.txt", "r");
    if (!file) {
        printf("Could not open staffnurse.txt\n");
        exit(1);
    }
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  staffNurses[*staffNurseCount].staffNurseID,
                  staffNurses[*staffNurseCount].password,
                  staffNurses[*staffNurseCount].fullName,
                  staffNurses[*staffNurseCount].dob,
                  staffNurses[*staffNurseCount].contactNumber) != EOF) {
        (*staffNurseCount)++;
    }
    fclose(file);
}

void displayPatients(Patient *patients, int patientCount) {
    printf("=================================================================================================================================================================\n");
    printf("| Patient ID | Password | Full Name    | Date of Birth | Contact Number | Address                        | Gender | Race  | Marital Status | Medical History | Allergies | Past Procedures |\n");
    printf("=================================================================================================================================================================\n");
    for (int i = 0; i < patientCount; i++) {
        printf("| %-11s | %-8s | %-12s | %-13s | %-14s | %-30s | %-6s | %-5s | %-14s | %-15s | %-9s | %-16s |\n",
               patients[i].patientID, patients[i].password, patients[i].fullName, patients[i].dob, patients[i].contactNumber,
               patients[i].address, patients[i].gender, patients[i].race, patients[i].maritalStatus,
               patients[i].medicalHistory, patients[i].allergies, patients[i].pastProcedures);
    }
    printf("=================================================================================================================================================================\n");
}

void displayDoctors(Doctor *doctors, int doctorCount) {
    printf("===============================================================================================\n");
    printf("| Doctor ID | Password | Full Name        | Date of Birth | Contact Number | Specialty           |\n");
    printf("===============================================================================================\n");
    for (int i = 0; i < doctorCount; i++) {
        printf("| %-9s | %-8s | %-16s | %-13s | %-14s | %-19s |\n",
               doctors[i].doctorID, doctors[i].password, doctors[i].fullName, doctors[i].dob, doctors[i].contactNumber,
               doctors[i].specialty);
    }
    printf("===============================================================================================\n");
}

void displayStaffNurses(StaffNurse *staffNurses, int staffNurseCount) {
    printf("=================================================================\n");
    printf("| Staff Nurse ID | Password | Full Name    | Date of Birth | Contact Number |\n");
    printf("=================================================================\n");
    for (int i = 0; i < staffNurseCount; i++) {
        printf("| %-14s | %-8s | %-12s | %-13s | %-14s |\n",
               staffNurses[i].staffNurseID, staffNurses[i].password, staffNurses[i].fullName, staffNurses[i].dob,
               staffNurses[i].contactNumber);
    }
    printf("=================================================================\n");
}



void registerNewUser() {
    int choice;
    printf("1. Patient\n");
    printf("2. Doctor\n");
    printf("3. Staff Nurse\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addPatient();
            break;
        case 2:
            addDoctor();
            break;
        case 3:
            addStaffNurse();
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}

void addPatient() {
    Patient patient;
    int lastID = 0;
    FILE *file = fopen("patient.txt", "a+");
    char line[500];

    if (!file) {
        printf("Error opening file\n");
        return;
    }

    // Generate Patient ID
    while (fgets(line, sizeof(line), file)) {
        lastID++;
    }
    strcpy(patient.patientID, generateID("PAT-", lastID + 1));
    printf("Patient ID is %s\n", patient.patientID);

    // Get other details
    printf("Enter Password: ");
    scanf("%s", patient.password);
    printf("Enter Full Name: ");
    scanf(" %[^\n]", patient.fullName);
    printf("Enter Date of Birth (YYYY-MM-DD): ");
    scanf("%s", patient.dob);
    printf("Enter Contact Number: ");
    scanf("%s", patient.contactNumber);
    printf("Enter Address: ");
    scanf(" %[^\n]", patient.address);
    printf("Enter Gender: ");
    scanf("%s", patient.gender);
    printf("Enter Race: ");
    scanf("%s", patient.race);
    printf("Enter Marital Status: ");
    scanf("%s", patient.maritalStatus);
    printf("Enter Medical History: ");
    scanf(" %[^\n]", patient.medicalHistory);
    printf("Enter Allergies: ");
    scanf(" %[^\n]", patient.allergies);
    printf("Enter Past Procedures: ");
    scanf(" %[^\n]", patient.pastProcedures);

    // Write to file
    fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n", patient.patientID, patient.password, patient.fullName, patient.dob, patient.contactNumber, patient.address, patient.gender, patient.race, patient.maritalStatus, patient.medicalHistory, patient.allergies, patient.pastProcedures);

    fclose(file);
}

void addDoctor() {
    Doctor doctor;
    int lastID = 0;
    FILE *file = fopen("doctor.txt", "a+");
    char line[500];

    if (!file) {
        printf("Error opening file\n");
        return;
    }

    // Generate Doctor ID
    while (fgets(line, sizeof(line), file)) {
        lastID++;
    }
    strcpy(doctor.doctorID, generateID("DOC-", lastID + 1));
    printf("Doctor ID is %s\n", doctor.doctorID);

    // Get other details
    printf("Enter Password: ");
    scanf("%s", doctor.password);
    printf("Enter Full Name: ");
    scanf(" %[^\n]", doctor.fullName);
    printf("Enter Date of Birth (YYYY-MM-DD): ");
    scanf("%s", doctor.dob);
    printf("Enter Contact Number: ");
    scanf("%s", doctor.contactNumber);
    printf("Enter Specialty: ");
    scanf(" %[^\n]", doctor.specialty);

    // Write to file
    fprintf(file, "%s|%s|%s|%s|%s|%s\n", doctor.doctorID, doctor.password, doctor.fullName, doctor.dob, doctor.contactNumber, doctor.specialty);

    fclose(file);
}

void addStaffNurse() {
    StaffNurse nurse;
    int lastID = 0;
    FILE *file = fopen("staffnurse.txt", "a+");
    char line[500];

    if (!file) {
        printf("Error opening file\n");
        return;
    }

    // Generate Staff Nurse ID
    while (fgets(line, sizeof(line), file)) {
        lastID++;
    }
    strcpy(nurse.staffNurseID, generateID("ST-", lastID + 1));
    printf("Staff Nurse ID is %s\n", nurse.staffNurseID);

    // Get other details
    printf("Enter Password: ");
    scanf("%s", nurse.password);
    printf("Enter Full Name: ");
    scanf(" %[^\n]", nurse.fullName);
    printf("Enter Date of Birth (YYYY-MM-DD): ");
    scanf("%s", nurse.dob);
    printf("Enter Contact Number: ");
    scanf("%s", nurse.contactNumber);

    // Write to file
    fprintf(file, "%s|%s|%s|%s|%s\n", nurse.staffNurseID, nurse.password, nurse.fullName, nurse.dob, nurse.contactNumber);

    fclose(file);
}

void viewAppointmentTrends() {
    FILE *file = fopen("appointment.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    char month[10];
    int year;
    printf("Enter month (e.g., May 2024): ");
    scanf("%s %d", month, &year);

    // Determine month number
    int monthNumber;
    if (strcmp(month, "January") == 0) monthNumber = 1;
    else if (strcmp(month, "February") == 0) monthNumber = 2;
    else if (strcmp(month, "March") == 0) monthNumber = 3;
    else if (strcmp(month, "April") == 0) monthNumber = 4;
    else if (strcmp(month, "May") == 0) monthNumber = 5;
    else if (strcmp(month, "June") == 0) monthNumber = 6;
    else if (strcmp(month, "July") == 0) monthNumber = 7;
    else if (strcmp(month, "August") == 0) monthNumber = 8;
    else if (strcmp(month, "September") == 0) monthNumber = 9;
    else if (strcmp(month, "October") == 0) monthNumber = 10;
    else if (strcmp(month, "November") == 0) monthNumber = 11;
    else if (strcmp(month, "December") == 0) monthNumber = 12;
    else {
        printf("Invalid month\n");
        return;
    }

    char line[500], date[11];
    int appointmentCounts[31] = {0};

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%*[^|]|%*[^|]|%*[^|]|%10s", date);

        // Check if the date matches the specified month and year
        int yearFromFile, monthFromFile, dayFromFile;
        sscanf(date, "%d-%d-%d", &yearFromFile, &monthFromFile, &dayFromFile);

        if (yearFromFile == year && monthFromFile == monthNumber) {
            appointmentCounts[dayFromFile - 1]++;
        }
    }

    printf("Appointment Trends for %s %d\n", month, year);
    printf("---------------------------------------\n");
    printf("| Date       | Number of Appointments |\n");
    printf("|------------|------------------------|\n");
    for (int i = 0; i < 31; i++) {
        if (appointmentCounts[i] > 0) {
            printf("| %04d-%02d-%02d | %-22d |\n", year, monthNumber, i + 1, appointmentCounts[i]);
        }
    }
    printf("---------------------------------------\n");

    fclose(file);
}

void viewInventory() {
    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    char line[500];
    printf("======================================================================================================================================\n");
    printf("| Item Name           | Item ID | Quantity Available | Min Stock Level | Max Stock Level | Cost per Unit (RM) | Supplier             |\n");
    printf("======================================================================================================================================\n");

    while (fgets(line, sizeof(line), file)) {
        char itemID[20], itemName[50], supplier[100];
        int quantityAvailable, minStockLevel, maxStockLevel;
        float costPerUnit;

        sscanf(line, "%[^|]|%[^|]|%d|%d|%d|%f|%[^\n]", itemID, itemName, &quantityAvailable, &minStockLevel, &maxStockLevel, &costPerUnit, supplier);

        printf("| %-18s | %-7s | %-18d | %-15d | %-15d | %-17.2f | %-20s |\n", itemName, itemID, quantityAvailable, minStockLevel, maxStockLevel, costPerUnit, supplier);
    }

    printf("======================================================================================================================================\n");

    fclose(file);
}



void searchInventory() {
    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    char searchTerm[50];
    printf("Enter item name or ID to search: ");
    scanf("%49s", searchTerm);

    char line[500];
    int found = 0;
    printf("======================================================================================================================================\n");
    printf("| Item Name           | Item ID | Quantity Available | Min Stock Level | Max Stock Level | Cost per Unit (RM) | Supplier             |\n");
    printf("======================================================================================================================================\n");

    while (fgets(line, sizeof(line), file)) {
        char itemID[20], itemName[50], supplier[100];
        int quantityAvailable, minStockLevel, maxStockLevel;
        float costPerUnit;

        sscanf(line, "%[^|]|%[^|]|%d|%d|%d|%f|%[^\n]", itemID, itemName, &quantityAvailable, &minStockLevel, &maxStockLevel, &costPerUnit, supplier);

        if (strstr(itemID, searchTerm) != NULL || strstr(itemName, searchTerm) != NULL) {
            printf("| %-18s | %-7s | %-18d | %-15d | %-15d | %-17.2f | %-20s |\n", itemName, itemID, quantityAvailable, minStockLevel, maxStockLevel, costPerUnit, supplier);
            found = 1;
        }
    }

    if (!found) {
        printf("No items found matching '%s'\n", searchTerm);
    }

    printf("======================================================================================================================================\n");

    fclose(file);
}




char *generateID(const char *prefix, int lastID) {
    static char id[20];
    snprintf(id, sizeof(id), "%s%03d", prefix, lastID);
    return id;
}
/// ^^^ HOSPITAL ADMINISTRATOR ^^^ ///










/// vvv PATIENT vvv ///
void patientLogin1() {
    readPatients();
    readDoctors();
    readDoctorSchedules();
    readAppointments();
    readPrescriptions();
    readBillings();
    patientLogin2();
    return 1;
}

void readPatients() {
    FILE* file = fopen("patient.txt", "r");
    if (file == NULL) {
        printf("Unable to open patient.txt\n");
        exit(1);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
               patients[patientCount].patientID, patients[patientCount].password, patients[patientCount].fullName,
               patients[patientCount].dob, patients[patientCount].contactNumber, patients[patientCount].address,
               patients[patientCount].gender, patients[patientCount].race, patients[patientCount].maritalStatus,
               patients[patientCount].medicalHistory, patients[patientCount].allergies, patients[patientCount].pastProcedures);
        patientCount++;
    }
    fclose(file);
}

void readDoctors() {
    FILE* file = fopen("doctor.txt", "r");
    if (file == NULL) {
        printf("Unable to open doctor.txt\n");
        exit(1);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
               doctors[doctorCount].doctorID, doctors[doctorCount].password, doctors[doctorCount].fullName,
               doctors[doctorCount].dob, doctors[doctorCount].contactNumber, doctors[doctorCount].specialty);
        doctorCount++;
    }
    fclose(file);
}

void readDoctorSchedules() {
    FILE* file = fopen("doctorschedule.txt", "r");
    if (file == NULL) {
        printf("Unable to open doctorschedule.txt\n");
        exit(1);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^\n]\n",
               doctorSchedules[scheduleCount].doctorID, 
               doctorSchedules[scheduleCount].availableDate,
               doctorSchedules[scheduleCount].startTime, 
               doctorSchedules[scheduleCount].endTime);
        scheduleCount++;
    }
    fclose(file);
}

void readAppointments() {
    FILE* file = fopen("appointment.txt", "r");
    if (file == NULL) {
        printf("Unable to open appointment.txt\n");
        exit(1);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
               appointments[appointmentCount].appointmentID, 
               appointments[appointmentCount].doctorID,
               appointments[appointmentCount].patientID, 
               appointments[appointmentCount].date,
               appointments[appointmentCount].startTime, 
               appointments[appointmentCount].endTime,
               appointments[appointmentCount].reason, 
               appointments[appointmentCount].status);
        appointmentCount++;
    }
    fclose(file);
}

void readPrescriptions() {
    FILE* file = fopen("prescription.txt", "r");
    if (file == NULL) {
        printf("Unable to open prescription.txt\n");
        exit(1);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
               prescriptions[prescriptionCount].prescriptionID, 
               prescriptions[prescriptionCount].appointmentID,
               prescriptions[prescriptionCount].doctorID, 
               prescriptions[prescriptionCount].patientID,
               prescriptions[prescriptionCount].prescription, 
               prescriptions[prescriptionCount].dosage,
               prescriptions[prescriptionCount].frequency, 
               prescriptions[prescriptionCount].startDate,
               prescriptions[prescriptionCount].endDate);
        prescriptionCount++;
    }
    fclose(file);
}

void readBillings() {
    FILE* file = fopen("billing.txt", "r");
    if (file == NULL) {
        printf("Unable to open billing.txt\n");
        exit(1);
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
               billings[billingCount].billingID, 
               billings[billingCount].appointmentID,
               billings[billingCount].patientID, 
               billings[billingCount].amount,
               billings[billingCount].paymentDate,
               billings[billingCount].status,
               billings[billingCount].insurance);
        billingCount++;
    }
    fclose(file);
}

void patientLogin2() {
    char patientID[20];
    char password[20];

    printf("\n========================== PATIENT LOGIN ==========================\n");
    printf("Enter Patient ID: ");
    scanf("%s", patientID);
    printf("Enter password: ");
    scanf("%s", password);

    if (authenticatePatient(patientID, password)) {
        patientMenu();
    } else {
        printf("Invalid Patient ID or password.\n");
        main();
    }
}

int authenticatePatient(const char* patientID, const char* password) {
    for (int i = 0; i < patientCount; i++) {
        if (strcmp(patients[i].patientID, patientID) == 0 && strcmp(patients[i].password, password) == 0) {
            currentPatient = patients[i];
            return 1;
        }
    }
    return 0;
}

void patientMenu() {
    int choice;
    while (1) {
        printf("___PATIENT MENU___\n");
        printf("1. Appointment Management\n");
        printf("2. View EHR & Billings\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                appointmentManagement();
                break;
            case 2:
                viewEHRAndBillings();
                break;
            case 0:
                main();
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void appointmentManagement() {
    int choice;
    printf("1. View Doctor Schedules\n");
    printf("2. Book An Appointment\n");
    printf("3. View My Appointment\n");
    printf("4. Reschedule My Appointment\n");
    printf("5. Cancel My Appointment\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            viewDoctorSchedules();
            break;
        case 2:
            bookAppointment();
            break;
        case 3:
            viewMyAppointments();
            break;
        case 4:
            rescheduleAppointment();
            break;
        case 5:
            cancelAppointment();
            break;
        case 0:
            patientMenu();
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

void bookAppointment() {
    char doctorID[20], date[11], startTime[6], endTime[6];
    viewDoctorSchedules();

    printf("Enter the Doctor ID (DOC-XXX): ");
    scanf("%s", doctorID);
    printf("Enter the date (YYYY-MM-DD): ");
    scanf("%s", date);
    printf("Enter the start time (HH:MM): ");
    scanf("%s", startTime);
    printf("Enter the end time (HH:MM): ");
    scanf("%s", endTime);

    int found = 0;
    for (int i = 0; i < scheduleCount; i++) {
        if (strcmp(doctorSchedules[i].doctorID, doctorID) == 0 &&
            strcmp(doctorSchedules[i].availableDate, date) == 0 &&
            strcmp(doctorSchedules[i].startTime, startTime) == 0 &&
            strcmp(doctorSchedules[i].endTime, endTime) == 0) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("The schedule is not available.\n");
        return;
    }

    for (int i = 0; i < appointmentCount; i++) {
        if (strcmp(appointments[i].doctorID, doctorID) == 0 &&
            strcmp(appointments[i].date, date) == 0 &&
            strcmp(appointments[i].startTime, startTime) == 0 &&
            strcmp(appointments[i].endTime, endTime) == 0 &&
            (strcmp(appointments[i].status, "Scheduled") == 0 || strcmp(appointments[i].status, "Rescheduled") == 0)) {
            printf("The slot is already booked.\n");
            return;
        }
    }

    Appointment newAppointment;
    sprintf(newAppointment.appointmentID, "APP-%03d", appointmentCount + 1);
    strcpy(newAppointment.doctorID, doctorID);
    strcpy(newAppointment.patientID, currentPatient.patientID);
    strcpy(newAppointment.date, date);
    strcpy(newAppointment.startTime, startTime);
    strcpy(newAppointment.endTime, endTime);
    printf("Enter the reason for the appointment: ");
    getchar();
    fgets(newAppointment.reason, 100, stdin);
    newAppointment.reason[strcspn(newAppointment.reason, "\n")] = 0; // Remove trailing newline
    strcpy(newAppointment.status, "Scheduled");

    appointments[appointmentCount++] = newAppointment;

    FILE* file = fopen("appointment.txt", "a");
    if (file == NULL) {
        printf("Unable to open appointment.txt\n");
        return;
    }
    fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%s\n",
            newAppointment.appointmentID, newAppointment.doctorID, newAppointment.patientID,
            newAppointment.date, newAppointment.startTime, newAppointment.endTime,
            newAppointment.reason, newAppointment.status);
    fclose(file);

    printf("Appointment booked successfully.\n");
}

void viewMyAppointments() {
    printf("=================================================================================================================\n");
    printf("| Appointment ID | Patient ID | Patient Name | Doctor ID | Doctor Name | Date       | Start Time | End Time | Reason           | Status    |\n");
    printf("=================================================================================================================\n");
    for (int i = 0; i < appointmentCount; i++) {
        if (strcmp(appointments[i].patientID, currentPatient.patientID) == 0 &&
            (strcmp(appointments[i].status, "Scheduled") == 0 || strcmp(appointments[i].status, "Rescheduled") == 0)) {

            char doctorName[50];
            for (int j = 0; j < doctorCount; j++) {
                if (strcmp(appointments[i].doctorID, doctors[j].doctorID) == 0) {
                    strcpy(doctorName, doctors[j].fullName);
                    break;
                }
            }

            printf("| %-13s | %-10s | %-12s | %-8s | %-11s | %-10s | %-10s | %-8s | %-15s | %-9s |\n",
                   appointments[i].appointmentID, appointments[i].patientID, currentPatient.fullName,
                   appointments[i].doctorID, doctorName, appointments[i].date, appointments[i].startTime,
                   appointments[i].endTime, appointments[i].reason, appointments[i].status);
        }
    }
    printf("=================================================================================================================\n");
}

void rescheduleAppointment() {
    char appointmentID[20];
    viewMyAppointments();

    printf("Enter Appointment ID: ");
    scanf("%s", appointmentID);

    Appointment* appt = NULL;
    for (int i = 0; i < appointmentCount; i++) {
        if (strcmp(appointments[i].appointmentID, appointmentID) == 0 &&
            strcmp(appointments[i].patientID, currentPatient.patientID) == 0) {
            appt = &appointments[i];
            break;
        }
    }

    if (appt == NULL) {
        printf("Appointment not found.\n");
        return;
    }

    if (strcmp(appt->status, "Rescheduled") == 0) {
        printf("Cannot reschedule an appointment that has already been rescheduled.\n");
        return;
    }

    strcpy(appt->status, "Rescheduled");

    char date[11], startTime[6], endTime[6];
    printf("Enter new date (YYYY-MM-DD): ");
    scanf("%s", date);
    printf("Enter new start time (HH:MM): ");
    scanf("%s", startTime);
    printf("Enter new end time (HH:MM): ");
    scanf("%s", endTime);

    for (int i = 0; i < appointmentCount; i++) {
        if (strcmp(appointments[i].doctorID, appt->doctorID) == 0 &&
            strcmp(appointments[i].date, date) == 0 &&
            strcmp(appointments[i].startTime, startTime) == 0 &&
            strcmp(appointments[i].endTime, endTime) == 0 &&
            (strcmp(appointments[i].status, "Scheduled") == 0 || strcmp(appointments[i].status, "Rescheduled") == 0)) {
            printf("The slot is already booked.\n");
            return;
        }
    }

    strcpy(appt->date, date);
    strcpy(appt->startTime, startTime);
    strcpy(appt->endTime, endTime);

    FILE* file = fopen("appointment.txt", "w");
    if (file == NULL) {
        printf("Unable to open appointment.txt\n");
        return;
    }

    for (int i = 0; i < appointmentCount; i++) {
        fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%s\n",
                appointments[i].appointmentID, appointments[i].doctorID, appointments[i].patientID,
                appointments[i].date, appointments[i].startTime, appointments[i].endTime,
                appointments[i].reason, appointments[i].status);
    }
    fclose(file);

    printf("Appointment rescheduled successfully.\n");
}

void cancelAppointment() {
    char appointmentID[20];
    viewMyAppointments();

    printf("Enter Appointment ID: ");
    scanf("%s", appointmentID);

    Appointment* appt = NULL;
    for (int i = 0; i < appointmentCount; i++) {
        if (strcmp(appointments[i].appointmentID, appointmentID) == 0 &&
            strcmp(appointments[i].patientID, currentPatient.patientID) == 0) {
            appt = &appointments[i];
            break;
        }
    }

    if (appt == NULL) {
        printf("Appointment not found.\n");
        return;
    }

    printf("Are you sure you want to cancel this appointment? (YES/NO): ");
    char confirm[4];
    scanf("%s", confirm);
    if (strcmp(confirm, "YES") != 0) {
        printf("Cancellation aborted.\n");
        return;
    }

    strcpy(appt->status, "Cancelled");

    FILE* file = fopen("appointment.txt", "w");
    if (file == NULL) {
        printf("Unable to open appointment.txt\n");
        return;
    }

    for (int i = 0; i < appointmentCount; i++) {
        fprintf(file, "%s|%s|%s|%s|%s|%s|%s|%s\n",
                appointments[i].appointmentID, appointments[i].doctorID, appointments[i].patientID,
                appointments[i].date, appointments[i].startTime, appointments[i].endTime,
                appointments[i].reason, appointments[i].status);
    }
    fclose(file);

    printf("Appointment cancelled successfully.\n");
}

void viewEHRAndBillings() {
    printf("==================================================================================================================================\n");
    printf("| Patient ID | Full Name  | Date of Birth | Contact Number | Address      | Gender | Race  | Marital Status | Medical History   | Allergies   | Past Procedures   |\n");
    printf("==================================================================================================================================\n");
    printf("| %-9s | %-10s | %-12s | %-13s | %-13s | %-6s | %-5s | %-13s | %-15s | %-10s | %-15s |\n",
           currentPatient.patientID, currentPatient.fullName, currentPatient.dob, currentPatient.contactNumber, currentPatient.address,
           currentPatient.gender, currentPatient.race, currentPatient.maritalStatus, currentPatient.medicalHistory, currentPatient.allergies, currentPatient.pastProcedures);
    printf("==================================================================================================================================\n");

    int ehrChoice;
    printf("1. View Prescription\n");
    printf("2. View Appointment History\n");
    printf("3. View Billing Information\n");
    printf("Enter your choice: ");
    scanf("%d", &ehrChoice);

    switch (ehrChoice) {
        case 1:
            viewPrescription();
            break;
        case 2:
            viewAppointmentHistory();
            break;
        case 3:
            viewBillingInformation();
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

void viewPrescription() {
    printf("========================================================================================================================\n");
    printf("| Prescription ID | Appointment ID | Doctor ID | Patient ID | Prescription | Dosage | Frequency | Start Date | End Date |\n");
    printf("========================================================================================================================\n");
    for (int i = 0; i < prescriptionCount; i++) {
        if (strcmp(prescriptions[i].patientID, currentPatient.patientID) == 0) {
            printf("| %-15s | %-14s | %-8s | %-10s | %-12s | %-6s | %-9s | %-10s | %-8s |\n",
                   prescriptions[i].prescriptionID, prescriptions[i].appointmentID, prescriptions[i].doctorID,
                   prescriptions[i].patientID, prescriptions[i].prescription, prescriptions[i].dosage,
                   prescriptions[i].frequency, prescriptions[i].startDate, prescriptions[i].endDate);
        }
    }
    printf("========================================================================================================================\n");
}

void viewAppointmentHistory() {
    printf("===========================================================================================\n");
    printf("| Appointment ID | Doctor ID | Patient ID | Date | Start Time | End Time | Reason | Status |\n");
    printf("===========================================================================================\n");
    for (int i = 0; i < appointmentCount; i++) {
        if (strcmp(appointments[i].patientID, currentPatient.patientID) == 0) {
            printf("| %-13s | %-8s | %-10s | %-10s | %-10s | %-8s | %-6s | %-8s |\n",
                   appointments[i].appointmentID, appointments[i].doctorID, appointments[i].patientID,
                   appointments[i].date, appointments[i].startTime, appointments[i].endTime,
                   appointments[i].reason, appointments[i].status);
        }
    }
    printf("===========================================================================================\n");
}

void viewBillingInformation() {
    printf("========================================================================================\n");
    printf("| Billing ID | Appointment ID | Patient ID | Amount | Payment Date | Status | Insurance |\n");
    printf("========================================================================================\n");
    for (int i = 0; i < billingCount; i++) {
        if (strcmp(billings[i].patientID, currentPatient.patientID) == 0) {
            printf("| %-10s | %-14s | %-10s | %-6s | %-12s | %-6s | %-8s |\n",
                   billings[i].billingID, billings[i].appointmentID, billings[i].patientID,
                   billings[i].amount, billings[i].paymentDate, billings[i].status, billings[i].insurance);
        }
    }
    printf("========================================================================================\n");
}
/// ^^^ PATIENT ^^^ ///










/// vvv DOCTOR vvv ///
void doctorLogin() {
    char doctorID[20], password[20];
    FILE *file;
    Doctor doctor;
    int loginSuccess = 0;
    printf("\n=========================== DOCTOR LOGIN ==========================\n"); 
    printf("Enter Doctor ID: ");
    scanf("%s", doctorID);
    printf("Enter password: ");
    scanf("%s", password);

    file = fopen("doctor.txt", "r");
    if (file == NULL) {
        perror("Error opening doctor.txt");
        return;
    }

    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                  doctor.doctorID, doctor.password, doctor.fullName, 
                  doctor.dob, doctor.contactNumber, doctor.specialty) != EOF) {
        if (strcmp(doctorID, doctor.doctorID) == 0 && strcmp(password, doctor.password) == 0) {
            loginSuccess = 1;
            break;
        }
    }

    fclose(file);

    if (loginSuccess) {
        printf("Login successful. Welcome, Dr %s!\n", doctor.fullName);
        doctorMenu(&doctor);
    } else {
        printf("Invalid Doctor ID or password.\n");
    }
}

void doctorMenu(Doctor* loggedInDoctor) {
    int choice;

    while (1) {
        printf("__________DOCTOR MENU__________\n");
        printf("Welcome, Dr %s!\n", loggedInDoctor->fullName);
        printf("1. Doctor Scheduler\n");
        printf("2. View EHR\n");
        printf("3. Reporting & Analytics\n\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("1. View Doctor Schedules\n");
                printf("2. View My Schedules\n");
                printf("3. Add My Schedules\n");
                printf("4. Edit My Schedules\n");
                printf("5. Delete My Schedules\n");
                printf("0. Back\n");
                printf("Enter choice: ");
                scanf("%d", &choice);
                getchar(); // consume newline
                switch (choice) {
                    case 1:
                        viewDoctorSchedules();
                        break;
                    case 2:
                        viewMySchedules(loggedInDoctor);
                        break;
                    case 3:
                        addMySchedule(loggedInDoctor);
                        break;
                    case 4:
                        editMySchedule(loggedInDoctor);
                        break;
                    case 5:
                        deleteMySchedule(loggedInDoctor);
                        break;
                    case 0:
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
                break;
            case 2:
                viewEHR();
                break;
            case 3:
                printf("1. View Reports\n");
                printf("2. View Patients with Specific Diagnosis\n");
                printf("0. Back\n");
                printf("Enter choice: ");
                scanf("%d", &choice);
                getchar(); // consume newline
                switch (choice) {
                    case 1:
                        viewReports();
                        break;
                    case 2:
                        viewPatientsWithSpecificDiagnosis();
                        break;
                    case 0:
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
                break;
            case 0:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void viewDoctorSchedules() {
    FILE *file;
    Doctor doctor;
    DoctorSchedule schedule;
    Appointment appointment;
    int found;

    file = fopen("doctor.txt", "r");
    if (file == NULL) {
        perror("Error opening doctor.txt");
        return;
    }

    printf("===============================================================================================\n");
    printf("| Doctor ID | Full Name    | Specialty   | Available Date | Start Time - End Time | Status    | \n");
    printf("===============================================================================================\n");

    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                  doctor.doctorID, doctor.password, doctor.fullName, 
                  doctor.dob, doctor.contactNumber, doctor.specialty) != EOF) {
        
        FILE *schedFile = fopen("doctorschedule.txt", "r");
        if (schedFile == NULL) {
            perror("Error opening doctorschedule.txt");
            fclose(file);
            return;
        }

        while (fscanf(schedFile, "%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                      schedule.doctorID, schedule.availableDate, 
                      schedule.startTime, schedule.endTime) != EOF) {
            if (strcmp(doctor.doctorID, schedule.doctorID) == 0) {
                found = 0;
                FILE *appFile = fopen("appointment.txt", "r");
                if (appFile != NULL) {
                    while (fscanf(appFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                                  appointment.appointmentID, appointment.doctorID, appointment.patientID, 
                                  appointment.date, appointment.startTime, appointment.endTime, 
                                  appointment.reason, appointment.status) != EOF) {
                        if (strcmp(appointment.doctorID, schedule.doctorID) == 0 && 
                            strcmp(appointment.date, schedule.availableDate) == 0 && 
                            strcmp(appointment.startTime, schedule.startTime) == 0 && 
                            strcmp(appointment.endTime, schedule.endTime) == 0) {
                            printf("| %-9s | %-11s | %-11s | %-13s | %-18s | %-9s |\n", 
                                   doctor.doctorID, doctor.fullName, doctor.specialty, 
                                   schedule.availableDate, 
                                   strcat(strcat(schedule.startTime, " - "), schedule.endTime), 
                                   appointment.status);
                            found = 1;
                            break;
                        }
                    }
                    fclose(appFile);
                }
                if (!found) {
                    printf("| %-9s | %-11s | %-11s | %-13s | %-18s | Available |\n", 
                           doctor.doctorID, doctor.fullName, doctor.specialty, 
                           schedule.availableDate, 
                           strcat(strcat(schedule.startTime, " - "), schedule.endTime));
                }
            }
        }

        fclose(schedFile);
    }

    printf("===============================================================================================\n");

    fclose(file);
}

void viewMySchedules(Doctor* loggedInDoctor) {
    FILE *schedFile, *appFile;
    DoctorSchedule schedule;
    Appointment appointment;
    int found;

    schedFile = fopen("doctorschedule.txt", "r");
    if (schedFile == NULL) {
        perror("Error opening doctorschedule.txt");
        return;
    }

    printf("===========================================================================================================\n");
    printf("| Doctor ID | Full Name    | Specialty   | Available Date | Start Time - End Time | Status    | Patient ID |\n");
    printf("===========================================================================================================\n");

    while (fscanf(schedFile, "%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                  schedule.doctorID, schedule.availableDate, 
                  schedule.startTime, schedule.endTime) != EOF) {
        if (strcmp(loggedInDoctor->doctorID, schedule.doctorID) == 0) {
            found = 0;
            appFile = fopen("appointment.txt", "r");
            if (appFile != NULL) {
                while (fscanf(appFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                              appointment.appointmentID, appointment.doctorID, appointment.patientID, 
                              appointment.date, appointment.startTime, appointment.endTime, 
                              appointment.reason, appointment.status) != EOF) {
                    if (strcmp(appointment.doctorID, schedule.doctorID) == 0 && 
                        strcmp(appointment.date, schedule.availableDate) == 0 && 
                        strcmp(appointment.startTime, schedule.startTime) == 0 && 
                        strcmp(appointment.endTime, schedule.endTime) == 0) {
                        printf("| %-9s | %-11s | %-11s | %-13s | %-18s | %-9s | %-9s |\n", 
                               schedule.doctorID, loggedInDoctor->fullName, loggedInDoctor->specialty, 
                               schedule.availableDate, 
                               strcat(strcat(schedule.startTime, " - "), schedule.endTime), 
                               appointment.status, appointment.patientID);
                        found = 1;
                        break;
                    }
                }
                fclose(appFile);
            }
            if (!found) {
                printf("| %-9s | %-11s | %-11s | %-13s | %-18s | Available | -         |\n", 
                       schedule.doctorID, loggedInDoctor->fullName, loggedInDoctor->specialty, 
                       schedule.availableDate, 
                       strcat(strcat(schedule.startTime, " - "), schedule.endTime));
            }
        }
    }

    printf("===========================================================================================================\n");

    fclose(schedFile);
}

void addMySchedule(Doctor* loggedInDoctor) {
    FILE *file;
    DoctorSchedule schedule;

    strcpy(schedule.doctorID, loggedInDoctor->doctorID);
    printf("Enter Available Date (YYYY-MM-DD): ");
    scanf("%s", schedule.availableDate);
    printf("Enter Start Time (HH:MM): ");
    scanf("%s", schedule.startTime);
    printf("Enter End Time (HH:MM): ");
    scanf("%s", schedule.endTime);

    file = fopen("doctorschedule.txt", "a");
    if (file == NULL) {
        perror("Error opening doctorschedule.txt");
        return;
    }

    fprintf(file, "%s|%s|%s|%s\n", schedule.doctorID, schedule.availableDate, schedule.startTime, schedule.endTime);
    fclose(file);

    printf("Schedule added successfully.\n");
}

int hasAppointment(char* doctorID, char* date, char* startTime, char* endTime) {
    FILE *appointmentFile;
    Appointment appointment;

    appointmentFile = fopen("appointment.txt", "r");
    if (appointmentFile == NULL) {
        perror("Error opening appointment.txt");
        return 0;
    }

    while (fscanf(appointmentFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  appointment.appointmentID, appointment.doctorID, appointment.patientID,
                  appointment.date, appointment.startTime, appointment.endTime,
                  appointment.reason, appointment.status) != EOF) {
        if (strcmp(appointment.doctorID, doctorID) == 0 &&
            strcmp(appointment.date, date) == 0 &&
            strcmp(appointment.startTime, startTime) == 0 &&
            strcmp(appointment.endTime, endTime) == 0) {
            fclose(appointmentFile);
            return 1;
        }
    }

    fclose(appointmentFile);
    return 0;
}

void editMySchedule(Doctor* loggedInDoctor) {
    FILE *file, *tempFile;
    DoctorSchedule schedule;
    char date[11], startTime[6], newStartTime[6], newEndTime[6];
    int found = 0, scheduleUpdated = 0;

    printf("Enter the date (YYYY-MM-DD) of the schedule to edit: ");
    scanf("%s", date);
    printf("Enter the start time (HH:MM) of the schedule to edit: ");
    scanf("%s", startTime);

    file = fopen("doctorschedule.txt", "r");
    if (file == NULL) {
        perror("Error opening doctorschedule.txt");
        return;
    }

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temp.txt");
        fclose(file);
        return;
    }

    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  schedule.doctorID, schedule.availableDate,
                  schedule.startTime, schedule.endTime) != EOF) {
        if (strcmp(schedule.doctorID, loggedInDoctor->doctorID) == 0 &&
            strcmp(schedule.availableDate, date) == 0 &&
            strcmp(schedule.startTime, startTime) == 0) {
            found = 1;
            if (hasAppointment(schedule.doctorID, schedule.availableDate, schedule.startTime, schedule.endTime)) {
                printf("Cannot edit the schedule because there is an appointment.\n");
                fprintf(tempFile, "%s|%s|%s|%s\n", schedule.doctorID, schedule.availableDate, schedule.startTime, schedule.endTime);
            } else {
                printf("Enter new Start Time (HH:MM): ");
                scanf("%s", newStartTime);
                printf("Enter new End Time (HH:MM): ");
                scanf("%s", newEndTime);
                fprintf(tempFile, "%s|%s|%s|%s\n", schedule.doctorID, schedule.availableDate, newStartTime, newEndTime);
                scheduleUpdated = 1;
            }
        } else {
            fprintf(tempFile, "%s|%s|%s|%s\n", schedule.doctorID, schedule.availableDate, schedule.startTime, schedule.endTime);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("doctorschedule.txt");
        rename("temp.txt", "doctorschedule.txt");
        if (scheduleUpdated) {
            printf("Schedule updated successfully.\n");
        }
    } else {
        remove("temp.txt");
        printf("Schedule not found.\n");
    }
}

void deleteMySchedule(Doctor* loggedInDoctor) {
    FILE *file, *tempFile;
    DoctorSchedule schedule;
    char date[11], startTime[6];
    int found = 0;

    printf("Enter the date (YYYY-MM-DD) of the schedule to delete: ");
    scanf("%s", date);
    printf("Enter the start time (HH:MM) of the schedule to delete: ");
    scanf("%s", startTime);

    file = fopen("doctorschedule.txt", "r");
    if (file == NULL) {
        perror("Error opening doctorschedule.txt");
        return;
    }

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("Error opening temp.txt");
        fclose(file);
        return;
    }

    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^\n]\n",
                  schedule.doctorID, schedule.availableDate,
                  schedule.startTime, schedule.endTime) != EOF) {
        if (strcmp(schedule.doctorID, loggedInDoctor->doctorID) == 0 &&
            strcmp(schedule.availableDate, date) == 0 &&
            strcmp(schedule.startTime, startTime) == 0) {
            if (hasAppointment(schedule.doctorID, schedule.availableDate, schedule.startTime, schedule.endTime)) {
                printf("Cannot delete the schedule because there is an appointment.\n");
                found = 1;
                // Write the schedule back to the temp file since it can't be deleted
                fprintf(tempFile, "%s|%s|%s|%s\n", schedule.doctorID, schedule.availableDate, schedule.startTime, schedule.endTime);
            } else {
                found = 1;
                // Skip writing this schedule to temp file to delete it
            }
        } else {
            fprintf(tempFile, "%s|%s|%s|%s\n", schedule.doctorID, schedule.availableDate, schedule.startTime, schedule.endTime);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove("doctorschedule.txt");
        rename("temp.txt", "doctorschedule.txt");
        if (!hasAppointment(loggedInDoctor->doctorID, date, startTime, schedule.endTime)) {
            printf("Schedule deleted successfully.\n");
        }
    } else {
        remove("temp.txt");
        printf("Schedule not found.\n");
    }
}

void viewEHR() {
    FILE *file;
    char patientID[20];
    Appointment appointment;
    Prescription prescription;
    Report report;

    printf("Enter Patient ID: ");
    scanf("%s", patientID);

    file = fopen("appointment.txt", "r");
    if (file == NULL) {
        perror("Error opening appointment.txt");
        return;
    }

    printf("==================================================\n");
    printf("| Appointments for Patient ID: %s\n", patientID);
    printf("==================================================\n");

    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                  appointment.appointmentID, appointment.doctorID, appointment.patientID, 
                  appointment.date, appointment.startTime, appointment.endTime, 
                  appointment.reason, appointment.status) != EOF) {
        if (strcmp(appointment.patientID, patientID) == 0) {
            printf("| Appointment ID: %s\n", appointment.appointmentID);
            printf("| Doctor ID: %s\n", appointment.doctorID);
            printf("| Date: %s\n", appointment.date);
            printf("| Time: %s - %s\n", appointment.startTime, appointment.endTime);
            printf("| Reason: %s\n", appointment.reason);
            printf("| Status: %s\n", appointment.status);
            printf("--------------------------------------------------\n");
        }
    }

    fclose(file);

    file = fopen("prescription.txt", "r");
    if (file == NULL) {
        perror("Error opening prescription.txt");
        return;
    }

    printf("==================================================\n");
    printf("| Prescriptions for Patient ID: %s\n", patientID);
    printf("==================================================\n");

    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                  prescription.prescriptionID, prescription.appointmentID, prescription.doctorID, 
                  prescription.patientID, prescription.prescription, prescription.dosage, 
                  prescription.frequency, prescription.startDate, prescription.endDate) != EOF) {
        if (strcmp(prescription.patientID, patientID) == 0) {
            printf("| Prescription ID: %s\n", prescription.prescriptionID);
            printf("| Appointment ID: %s\n", prescription.appointmentID);
            printf("| Doctor ID: %s\n", prescription.doctorID);
            printf("| Prescription: %s\n", prescription.prescription);
            printf("| Dosage: %s\n", prescription.dosage);
            printf("| Frequency: %s\n", prescription.frequency);
            printf("| Start Date: %s\n", prescription.startDate);
            printf("| End Date: %s\n", prescription.endDate);
            printf("--------------------------------------------------\n");
        }
    }

    fclose(file);

    file = fopen("report.txt", "r");
    if (file == NULL) {
        perror("Error opening report.txt");
        return;
    }

    printf("==================================================\n");
    printf("| Reports for Patient ID: %s\n", patientID);
    printf("==================================================\n");

    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                  report.reportID, report.appointmentID, report.doctorID, 
                  report.patientID, report.diagnosis, report.treatment, 
                  report.outcome) != EOF) {
        if (strcmp(report.patientID, patientID) == 0) {
            printf("| Report ID: %s\n", report.reportID);
            printf("| Appointment ID: %s\n", report.appointmentID);
            printf("| Doctor ID: %s\n", report.doctorID);
            printf("| Diagnosis: %s\n", report.diagnosis);
            printf("| Treatment: %s\n", report.treatment);
            printf("| Outcome: %s\n", report.outcome);
            printf("--------------------------------------------------\n");
        }
    }

    fclose(file);
}

void viewReports() {
    FILE *file;
    Report report;

    file = fopen("report.txt", "r");
    if (file == NULL) {
        perror("Error opening report.txt");
        return;
    }

    printf("==================================================\n");
    printf("| Reports\n");
    printf("==================================================\n");

    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                  report.reportID, report.appointmentID, report.doctorID, 
                  report.patientID, report.diagnosis, report.treatment, 
                  report.outcome) != EOF) {
        printf("| Report ID: %s\n", report.reportID);
        printf("| Appointment ID: %s\n", report.appointmentID);
        printf("| Doctor ID: %s\n", report.doctorID);
        printf("| Patient ID: %s\n", report.patientID);
        printf("| Diagnosis: %s\n", report.diagnosis);
        printf("| Treatment: %s\n", report.treatment);
        printf("| Outcome: %s\n", report.outcome);
        printf("--------------------------------------------------\n");
    }

    fclose(file);
}

void viewPatientsWithSpecificDiagnosis() {
    FILE *file;
    Report report;
    char diagnosis[100];

    printf("Enter the diagnosis to search for: ");
    scanf(" %[^\n]", diagnosis);

    file = fopen("report.txt", "r");
    if (file == NULL) {
        perror("Error opening report.txt");
        return;
    }

    printf("==================================================\n");
    printf("| Patients with Diagnosis: %s\n", diagnosis);
    printf("==================================================\n");

    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                  report.reportID, report.appointmentID, report.doctorID, 
                  report.patientID, report.diagnosis, report.treatment, 
                  report.outcome) != EOF) {
        if (strcmp(report.diagnosis, diagnosis) == 0) {
            printf("| Report ID: %s\n", report.reportID);
            printf("| Appointment ID: %s\n", report.appointmentID);
            printf("| Doctor ID: %s\n", report.doctorID);
            printf("| Patient ID: %s\n", report.patientID);
            printf("| Diagnosis: %s\n", report.diagnosis);
            printf("| Treatment: %s\n", report.treatment);
            printf("| Outcome: %s\n", report.outcome);
            printf("--------------------------------------------------\n");
        }
    }

    fclose(file);
}

/// ^^^ DOCTOR ^^^ ///










/// vvv STAFF NURSE vvv ///
int staffNurseLogin() {
    FILE *fp;
    char staffNurseID[20], password[20], line[200];
    char fullName[50];
    int loginSuccess = 0;

    printf("\n======================== STAFF NURSE LOGIN ========================\n"); 
    printf("Enter Staff Nurse ID: ");
    scanf("%s", staffNurseID);
    printf("Enter password: ");
    scanf("%s", password);

    fp = fopen("staffnurse.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 0;
    }

    while (fgets(line, sizeof(line), fp)) {
        StaffNurse nurse;
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]", nurse.staffNurseID, nurse.password, nurse.fullName, nurse.dob, nurse.contactNumber);

        if (strcmp(staffNurseID, nurse.staffNurseID) == 0 && strcmp(password, nurse.password) == 0) {
            strcpy(fullName, nurse.fullName);
            loginSuccess = 1;
            break;
        }
    }

    fclose(fp);

    if (loginSuccess) {
        staffNurseMenu(fullName);
    }

    return loginSuccess;
}

void staffNurseMenu(char *fullName) {
    int choice;

    while (1) {
        printf("__________STAFF NURSE MENU__________\n");
        printf("Welcome, %s!\n", fullName);
        printf("1. View Doctor Schedules\n");
        printf("2. Inventory Management\n");
        printf("3. Reporting & Analytics\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewDoctorSchedules();
                break;
            case 2:
                inventoryManagement();
                break;
            case 3:
                reportingAnalytics();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}



void addInventory() {
    Inventory inventory;
    int lastID = 0;
    FILE *file = fopen("inventory.txt", "a+");
    char line[500];

    if (!file) {
        printf("Error opening file\n");
        return;
    }

    // Generate Item ID
    while (fgets(line, sizeof(line), file)) {
        lastID++;
    }
    strcpy(inventory.itemID, generateID("I-", lastID + 1));
    printf("Item ID is %s\n", inventory.itemID);

    // Get other details
    printf("Enter Item Name: ");
    scanf(" %[^\n]", inventory.itemName);
    printf("Enter Quantity Available: ");
    scanf("%d", &inventory.quantityAvailable);
    printf("Enter Min Stock Level: ");
    scanf("%d", &inventory.minStockLevel);
    printf("Enter Max Stock Level: ");
    scanf("%d", &inventory.maxStockLevel);
    printf("Enter Cost per Unit (RM): ");
    scanf("%f", &inventory.costPerUnit);
    printf("Enter Supplier: ");
    scanf(" %[^\n]", inventory.supplier);

    // Write to file
    fprintf(file, "%s|%s|%d|%d|%d|%.2f|%s\n", inventory.itemID, inventory.itemName, inventory.quantityAvailable, inventory.minStockLevel, inventory.maxStockLevel, inventory.costPerUnit, inventory.supplier);

    fclose(file);
}


void editInventory() {
    char itemID[20], line[500];
    int found = 0;
    printf("Enter Item ID: ");
    scanf("%s", itemID);

    FILE *file = fopen("inventory.txt", "r+");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Error opening temp file\n");
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        char fileItemID[20];
        sscanf(line, "%[^|]", fileItemID);

        if (strcmp(itemID, fileItemID) == 0) {
            found = 1;
            Inventory inventory;

            printf("Enter new Item Name: ");
            scanf(" %[^\n]", inventory.itemName);
            printf("Enter new Quantity Available: ");
            scanf("%d", &inventory.quantityAvailable);
            printf("Enter new Min Stock Level: ");
            scanf("%d", &inventory.minStockLevel);
            printf("Enter new Max Stock Level: ");
            scanf("%d", &inventory.maxStockLevel);
            printf("Enter new Cost per Unit (RM): ");
            scanf("%f", &inventory.costPerUnit);
            printf("Enter new Supplier: ");
            scanf(" %[^\n]", inventory.supplier);

            fprintf(temp, "%s|%s|%d|%d|%d|%.2f|%s\n", fileItemID, inventory.itemName, inventory.quantityAvailable, inventory.minStockLevel, inventory.maxStockLevel, inventory.costPerUnit, inventory.supplier);
        } else {
            fputs(line, temp);
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
        printf("Inventory item updated successfully.\n");
    } else {
        printf("Item ID not found.\n");
        remove("temp.txt");
    }
}

void deleteInventory() {
    char itemID[20], line[500];
    int found = 0;
    printf("Enter Item ID: ");
    scanf("%s", itemID);

    FILE *file = fopen("inventory.txt", "r");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Error opening temp file\n");
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        char fileItemID[20];
        sscanf(line, "%[^|]", fileItemID);

        if (strcmp(itemID, fileItemID) == 0) {
            found = 1;
        } else {
            fputs(line, temp);
        }
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
        printf("Inventory item deleted successfully.\n");
    } else {
        printf("Item ID not found.\n");
        remove("temp.txt");
    }
}



void inventoryManagement() {
    int choice;

    while (1) {
        printf("1. View Inventory\n");
        printf("2. Add Inventory\n");
        printf("3. Edit Inventory\n");
        printf("4. Delete Inventory\n");
        printf("0. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewInventory();
                break;
            case 2:
                addInventory();
                break;
            case 3:
                editInventory();
                break;
            case 4:
                deleteInventory();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void reportingAnalytics() {
    int choice;

    while (1) {
        printf("1. View Report\n");
        printf("2. Search Specific Unit\n");
        printf("0. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewReport();
                break;
            case 2:
                searchSpecificSpecialty();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void viewReport() {
    FILE *fp;
    char line[300];
    Report report;

    fp = fopen("report.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("==================================================\n");
    printf("| Reports\n");
    printf("==================================================\n");

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", report.reportID, report.appointmentID, report.doctorID, report.patientID, report.diagnosis, report.treatment, report.outcome);
        printf("--------------------------------------------------\n");
        printf("| Report ID      : %s\n", report.reportID);
        printf("| Appointment ID : %s\n", report.appointmentID);
        printf("| Doctor ID      : %s\n", report.doctorID);
        printf("| Patient ID     : %s\n", report.patientID);
        printf("| Diagnosis      : %s\n", report.diagnosis);
        printf("| Treatment      : %s\n", report.treatment);
        printf("| Outcome        : %s\n", report.outcome);
        printf("--------------------------------------------------\n");
    }

    fclose(fp);
}

void searchSpecificSpecialty() {
    FILE *fp, *doctorFp;
    char specialty[50], line[300];
    Report report;
    Doctor doctor;
    int found = 0;

    printf("Enter Unit: ");
    getchar(); // consume newline character
    fgets(specialty, sizeof(specialty), stdin);
    specialty[strcspn(specialty, "\n")] = '\0'; // remove newline character

    fp = fopen("report.txt", "r");
    doctorFp = fopen("doctor.txt", "r");

    if (fp == NULL || doctorFp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("==================================================\n");
    printf("| Reports for Unit: %s\n", specialty);
    printf("==================================================\n");

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", report.reportID, report.appointmentID, report.doctorID, report.patientID, report.diagnosis, report.treatment, report.outcome);

        rewind(doctorFp); // reset the doctor file pointer to the beginning for each report
        while (fgets(line, sizeof(line), doctorFp)) {
            sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", doctor.doctorID, doctor.password, doctor.fullName, doctor.dob, doctor.contactNumber, doctor.specialty);

            if (strcmp(report.doctorID, doctor.doctorID) == 0 && strcmp(doctor.specialty, specialty) == 0) {
                found = 1;
                printf("--------------------------------------------------\n");
                printf("| Report ID      : %s\n", report.reportID);
                printf("| Appointment ID : %s\n", report.appointmentID);
                printf("| Doctor ID      : %s\n", report.doctorID);
                printf("| Patient ID     : %s\n", report.patientID);
                printf("| Diagnosis      : %s\n", report.diagnosis);
                printf("| Treatment      : %s\n", report.treatment);
                printf("| Outcome        : %s\n", report.outcome);
                printf("| Unit           : %s\n", doctor.specialty);
                printf("--------------------------------------------------\n");
                break;
            }
        }
    }

    if (!found) {
        printf("No reports found for unit: %s\n", specialty);
    }

    fclose(fp);
    fclose(doctorFp);
}

/// ^^^ STAFF NURSE ^^^ ///