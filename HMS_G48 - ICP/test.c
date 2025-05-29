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
                fprintf(tempFile, "%s|%s|%s|%s\n", schedule.doctorID, schedule.availableDate, schedule.startTime, schedule.endTime);
                found = 1;
                break;
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