#ifndef ERA_H_INCLUDED
#define ERA_H_INCLUDED
int remove_vehicle(struct vehicle **head_v,FILE* f1)
{
    int cnt;
    struct vehicle *curr=NULL,*prev=NULL;
    char plate_nr[40];
fopen("vehicle.txt", "r");
    if(f1==NULL){
        printf("File 1 cannot be open ");
        return 1;
    }

    fscanf(f1,"%d",&cnt);

    curr=*head_v;
    printf("\nEnter the plate number of the vehicle you want to remove: \n");
    scanf("%s",plate_nr);

    if(curr==NULL){
        printf("No vehicles ");
        return 1;
    }

    while (curr!=NULL) {
        if (strcmp(curr->plate_nr, plate_nr) == 0) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }
        if(prev==NULL){
            *head_v=curr->next;
            free(curr);
            printf("\nThe vehicle got removed\n");
            cnt--;
        }
        else if(curr==NULL){
            printf("The vehicle wan not found");
        }
        else{
            prev->next = curr->next;
            free(curr);
            printf("\nThe vehicle got removed \n");
            cnt--;
        }


    fclose(f1);

    return cnt;

}

void saveInArray(const char *filename, struct client c[], int cnt)
{
        struct vehicle v[400];
    struct reservation r[150];
//saving file elements in an array of structures, so it is easier to access their content
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Failed to open file named %s\n", filename);
    }

    for (int i = 0; i < cnt; i++)
    {
        fscanf(fptr,"%s %s %s %s %[^0-9] %s", c[i].client_ID, c[i].name, c[i].surname, c[i].passport_ID, c[i].state, c[i].phone_nr);
        //  printf ("%s %s %s %s %s %s\n", c[i].client_ID, c[i].name, c[i].surname, c[i].passport_ID, c[i].state, c[i].phone_nr);
    }
    fclose(fptr);

}
void searchUserByID(struct client c[], int cnt,char user[])
{
          struct vehicle v[400];
    struct reservation r[150];

    int found = 0;
    for (int i = 0; i < cnt; i++)
    {
        if (strcmp(c[i].client_ID, user) == 0) // Client found
        {
            printf ("\n----------------------------------------------------------\n");
            printf("The client with ID: \"%s\" exists. Client's credentials are:\n"
                   "ID: %s\n"
                   "Name: %s\n"
                   "Surname: %s\n"
                   "Passport ID: %s\n"
                   "State: %s\n"
                   "Phone number: %s\n",
                   user, c[i].client_ID, c[i].name, c[i].surname, c[i].passport_ID, c[i].state, c[i].phone_nr);
            printf ("\n----------------------------------------------------------");
            found = 1;
            break;
        }
    }

    if (found != 1)
    {
        printf("The user with the ID \"%s\" does not exist!\nPlease try a valid ID!\n", user); // Client not found
    }
}
//Displaying for current day:
void checkCarAvailability(FILE*f2)
{
    struct vehicle v[400];
    struct reservation r[150];
    struct client c[250];
    int count_r;
    if (f2 == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    int numRes = 0;
    char line[70];
    char nrDaysString[200];
    char totalPriceString[200];

    fscanf(f2, "%d", &count_r);
    printf("%d",count_r);
    for (int i = 0; i < count_r; i++)
    {
        fscanf(f2, "%s %s %s %d %lf %s", r[numRes].reservation_ID, r[numRes].date, r[numRes].user_ID, &r[numRes].nr_days, &r[numRes].total_price, r[numRes].plate_nr);
        numRes++;
    }
    fclose(f2);

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int currentYear = tm->tm_year + 1900;
    int currentMonth = tm->tm_mon + 1;
    int currentDay = tm->tm_mday;

    int targetDay = currentDay;
    int targetMonth = currentMonth;
    int targetYear = currentYear;

    if (targetDay > 30)
    {
        targetDay -= 30;
        targetMonth++;
        if (targetMonth > 12)
        {
            targetMonth = 1;
            targetYear++;
        }
    }
    int availableCars = 0;
    printf ("\n\t\t~~~~~CURRENT AVAILABLE VEHICLES ARE:~~~\n");
    for (int i = 0; i < numRes; i++)
    {
        int day, month, year;
        sscanf(r[i].date, "%d.%d.%d", &day, &month, &year);
        int lastReservationDay = day + r[i].nr_days;
        int lastReservationMonth = month;
        int lastReservationYear = year;

        if (lastReservationDay > 30)
        {
            lastReservationDay -= 30;
            lastReservationMonth++;
            if (lastReservationMonth > 12)
            {
                lastReservationMonth = 1;
                lastReservationYear++;
            }
        }

        if (lastReservationYear > targetYear ||
                (lastReservationYear == targetYear && lastReservationMonth > targetMonth) ||
                (lastReservationYear == targetYear && lastReservationMonth == targetMonth && lastReservationDay >= targetDay))
        {
            printf("\t\tReservation ID: %s\n", r[i].reservation_ID);
            printf("\t\tDate: %s\n", r[i].date);
            printf("\t\tUser ID: %s\n", r[i].user_ID);
            printf("\t\tPlate Number: %s\n", r[i].plate_nr);
            printf("\n\t\t----------------------------------------------------\n");
            availableCars++;
        }
    }

    if (availableCars == 0)
    {
        printf("There are no cars available in this current day! Don't forget to check in again tomorrow! :)");
    }
}

//available after x days:
void availableAfterDays(FILE* f2)
{
         struct vehicle v[400];
    struct reservation r[150];
    struct client c[250];
    if (f2 == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }
    int numDays,count_r;
    printf ("Enter the number of days for which you want to find available vehicles: \n");
    scanf ("%d", &numDays);
    int numRes = 0;
    char line[70];
    char nrDaysString[200];
    char totalPriceString[200];
      fscanf(f2, "%d", &count_r);
    for (int i = 0; i < count_r; i++)
    {
        fscanf(f2, "%s %s %s %d %lf %s", r[numRes].reservation_ID, r[numRes].date, r[numRes].user_ID, &r[numRes].nr_days, &r[numRes].total_price, r[numRes].plate_nr);
        numRes++;
    }

    fclose(f2);
//calculating the current time (when the program is running)
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    int currentYear = tm->tm_year + 1900;
    int currentMonth = tm->tm_mon + 1;
    int currentDay = tm->tm_mday;

    int xDay = currentDay + numDays;
    int xMonth = currentMonth;
    int xYear = currentYear;

    if (xDay > 30)
    {
        xDay -= 30;
        xMonth++;
        if (xMonth > 12)
        {
            xMonth = 1;
            xMonth++;
        }
    }

    int availableVehicle = 0;
    printf ("\n\t~~~~~AVAILABLE VEHICLES AFTER %d DAYS ARE:~~~\n",numDays);
    for (int i = 0; i < numRes; i++)
    {
        int day, month, year;
        sscanf(r[i].date, "%d.%d.%d", &day, &month, &year);
        int lastReservationDay = day + r[i].nr_days;
        int lastReservationMonth = month;
        int lastReservationYear = year;

        if (lastReservationDay > 30)
        {
            lastReservationDay -= 30;
            lastReservationMonth++;
            if (lastReservationMonth > 12)
            {
                lastReservationMonth = 1;
                lastReservationYear++;
            }
        }

        if (lastReservationYear > xYear ||
                (lastReservationYear == xYear && lastReservationMonth > xMonth) ||
                (lastReservationYear == xYear && lastReservationMonth == xMonth && lastReservationDay >= xDay))
        {
            printf("\tReservation ID: %s\n", r[i].reservation_ID);
            printf("\tDate: %s\n", r[i].date);
            printf("\tUser ID: %s\n", r[i].user_ID);
            printf("\tPlate Number: %s\n", r[i].plate_nr);
            printf("\n\t----------------------------------------------------\n");
            availableVehicle++;
        }
    }

    if (availableVehicle== 0)
    {
        printf("No cars available after the specified target date.\n");
    }
}
void addClientFile(const char* filename, struct client c[]) {
    FILE* f3 = fopen(filename, "a");
    if (f3 == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    struct client newClient;

    printf("\n~You are being registered.~\n");
    printf("Please enter:\n");
    printf ("----------------------------------------------------------\n");
    printf(" Client ID: ");
    scanf("%s", newClient.client_ID);
    printf("Name: ");
    scanf("%s", newClient.name);
    printf("Surname: ");
    scanf("%s", newClient.surname);
    printf("Passport ID: ");
    scanf("%s", newClient.passport_ID);
    printf("State: ");
    scanf("%s", newClient.state);
    printf("Phone number: ");
    scanf("%s", newClient.phone_nr);

    fseek(f3, 0, SEEK_END);
    fprintf(f3,"\n");
    fprintf(f3, "%s  %s  %s  %s  %s  %s\n", newClient.client_ID,newClient.name,newClient.surname,newClient.passport_ID,newClient.state,newClient.phone_nr);

    fclose(f3);
    printf("You are added as  a new client  successfully! :D\n");
    printf("-----------------------------------------------------\n");
}
#endif // ERA_H_INCLUDED
