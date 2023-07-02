#ifndef ROSILDA_H_INCLUDED
#define ROSILDA_H_INCLUDED

int  editByPlateNumber(FILE* f1,struct vehicle **head) {
    char plate_nr[40];
    int cnt;
    struct vehicle *curr=NULL;
    float newprice;
    int newres;
    f1 = fopen("vehicle.txt", "r");
    if(f1==NULL){
        printf("File 2 cannot be opened\n");
        return 1;
    }
    fscanf(f1,"%d",&cnt);
    printf("\nEnter the plate nr of the vehicle you want to modify : ");
    scanf("%s",plate_nr);

   curr=*head;
   if (curr==NULL){
       printf("No vehicles");
       return cnt;
   }
    while (curr!=NULL) {
        if (strcmp(curr->plate_nr, plate_nr) == 0) {
            break;
        }
        curr=curr->next;
    }
    if(curr==NULL){
        printf("The plate number was not found\n");
        return 1;
    }
            int option;
    printf("Enter :\n-1 if you want to change daily price\n"
           "-2 if you want to change reservation\n ");
             scanf("%d",&option);
            switch (option) {
            case 1:
                printf("Enter new Daily Price: ");
                    scanf("%f",&newprice);
                    curr->daily_price=newprice;
                    break ;
            case 2:
                printf("Enter new number of reservation: ");
                scanf("%d",&newres);
                curr->reservations=newres;
                break;
            default:
                printf("Invalid option.\n");
                return 1;
            }

    fclose(f1);
    return cnt;
        }




void addVehicles(FILE* f1)
{
    int cnt;
if(f1==NULL){
    printf("F1 can not be open !!!");
    return;
}
struct vehicle v;
    fscanf(f1,"%d",&cnt);

    fseek(f1, 0, SEEK_END); //shkon ne fund te filet
    // Ask the user to enter vehicle details
    printf("Enter New Vehicle Details:\n");
    printf("Plate Number: ");
    scanf("%s", v.plate_nr);
    fprintf(f1, "%s ", v.plate_nr);

    printf("Year: ");
    scanf("%d", &(v.year));
    fprintf(f1, "%d ", v.year);

    printf("Model: ");
    scanf(" %[^\n]", v.model);
    fprintf(f1, "%s ", v.model);

    printf("Fuel Type: ");
    scanf(" %[^\n]", v.fuel_type);
    fprintf(f1, "%s ", v.fuel_type);

    printf("Consumption: ");
    scanf("%lf", &(v.consumption));
    fprintf(f1, "%.2lf ", v.consumption);

    printf("Number of Seats: ");
    scanf("%d", &(v.seats));
    fprintf(f1, "%d ", v.seats);

    printf("Daily Price: ");
    scanf("%f", &(v.daily_price));
    fprintf(f1, "%.2f ", v.daily_price);

    printf("Reservations: ");
    scanf("%d", &(v.reservations));
    fprintf(f1, "%d \n", v.reservations);
    fseek(f1, 0, SEEK_SET);//modify at the begging of the file
    cnt++;
    fprintf(f1,"%d",cnt);

    fflush(f1);
    fclose(f1);
}
void displayVehiclesInfo(FILE* f1)
{
    struct vehicle v;
    int cnt;
    printf("Display Vehicle Information:\n");
    fscanf(f1,"%d",&cnt);
    // Read and display information of all vehicles
    while (fscanf(f1, "%s %d %s %s %lf %d %f %d", v.plate_nr, &v.year, v.model, v.fuel_type, &v.consumption, &v.seats, &v.daily_price, &v.reservations) != EOF )
    {
        printf("Plate number of the vehicle is : %s\n", v.plate_nr);
        printf("Year: %d\n", v.year);
        printf("Model: %s\n", v.model);
        printf("Fuel Type: %s\n", v.fuel_type);
        printf("Consumption: %.2lf\n", v.consumption);
        printf("Number of Seats: %d\n", v.seats);
        printf("Daily Price: %.2f\n", v.daily_price);
        printf("Reservations: %d\n", v.reservations);
        printf("\n");
    }

    fclose(f1);
}

#endif // ROSILDA_H_INCLUDED
