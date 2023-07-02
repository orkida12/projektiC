#ifndef TEA_H_INCLUDED
#define TEA_H_INCLUDED
#define MAX_LINE_LENGTH 500000
#include <time.h>
#include "ORKIDA.h"
typedef struct vehicle v;
typedef struct reservation r;
v* createVehicleNode(char plate_nr[], int year, char model[], char fuel_type[], double consumption, int seats, float daily_price, int reservations)
{
    v* newNode = (v*)malloc(sizeof(v));
    strcpy(newNode->plate_nr, plate_nr);
    newNode->year = year;
    strcpy(newNode->model, model);
    strcpy(newNode->fuel_type, fuel_type);
    newNode->consumption = consumption;
    newNode->seats = seats;
    newNode->daily_price = daily_price;
    newNode->reservations = reservations;
    newNode->next = NULL;

    return newNode;
}

void insertVehicleNode(v** head, v* newNode)
{
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        v* current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}
void printVehicleList(v* head)
{
    v* current = head;
    while (current != NULL)
    {
        printf("Plate: %s\n", current->plate_nr);
        printf("Year: %d\n", current->year);
        printf("Model: %s\n", current->model);
        printf("Fuel Type: %s\n", current->fuel_type);
        printf("Consumption: %.2f\n", current->consumption);
        printf("Seats: %d\n", current->seats);
        printf("Daily Price: %.2f\n", current->daily_price);
        printf("Reservations: %d\n", current->reservations);
        printf("----------------------\n");
        current = current->next;
    }
}

r* createReservationNode(char reservation_ID[], char date[], char user_ID[], int nr_days, float total_price)
{
    r* newNode = (r*)malloc(sizeof(r));
    strcpy(newNode->reservation_ID, reservation_ID);
    strcpy(newNode->date, date);
    strcpy(newNode->user_ID, user_ID);
    newNode->nr_days = nr_days;
    newNode->total_price = total_price;
    newNode->next = NULL;
    return newNode;
}

void insertReservationNode(r** head, r* newNode)
{
    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        r* current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

void printReservationList(r* head)
{

    r* current = head;
    while (current != NULL)
    {
        printf("Reservation ID: %s\n", current->reservation_ID);
        printf("Date: %s\n", current->date);
        printf("User ID: %s\n", current->user_ID);
        printf("Number of Days: %d\n", current->nr_days);
        printf("Total Price: %.2f\n", current->total_price);
        printf("----------------------\n");
        current = current->next;
    }
}
void initialize_random()
{
    srand(time(NULL));
}

void search_by_year(char user[], FILE* f1, FILE* f2, int year)
{
    char input[30];
    struct vehicle v;
    struct reservation r;
    char line[MAX_LINE_LENGTH];

    int found = 0;
    rewind(f1);
    int attempts = 0;
    do
    {
        while (fgets(line, sizeof(line), f1))
        {
            if (sscanf(line, "%s %s %d %s %lf %d %f", v.plate_nr, v.model, &v.year, v.fuel_type, &v.consumption, &v.seats, &v.daily_price) == 7)
            {
                if (v.year == year)
                {
                    printf("The vehicle with plate number %s, model %s, number of seats %d, and daily price %.2f was produced in the year %d.\n", v.plate_nr, v.model, v.seats, v.daily_price, year);
                    found = 1;
                }
            }
        }

        if (!found)
        {
            attempts++;
            if (attempts >= 3)
            {
                printf("No vehicles were produced in the year %d. You have exceeded the maximum number of attempts.\n", year);
                break;  // Exit the loop and go back to the menu
            }
            else
            {
                printf("No vehicles were produced in the year %d. Please try again. (%d chances left)\n", year, 3 - attempts);
                printf("Enter the year: \n");
                scanf("%d", &year);
                rewind(f1);  // Reset the file pointer to the beginning
            }
        }
    }
    while (!found);

    if (found)
    {

        printf("What's the plate number of the car you want to reserve? \n");
        scanf("%s", input);


        printf("Enter reservation date (dd.mm.yyyy): \n");
        scanf("%s", r.date);

        printf("Enter number of days: \n");
        scanf("%d", &r.nr_days);

        float total_price = v.daily_price * r.nr_days;
        total_price=Orkida_Apply_Discount(total_price,r.nr_days,r.date);

        char reservation_ID[12];
        sprintf(reservation_ID, "RES-%08d", rand() % 100000000);

        fprintf(f2, "%s    %s  %s    %d   %.0f %s \n", reservation_ID, r.date, user, r.nr_days,total_price, input);
        printf("Reservation created successfully!\nThe total price you have to pay is: %.2f\n", total_price);

    }
     fclose(f2);
}

void search_by_model(char user[], FILE* f1, FILE* f2, char model[])
{
    char input[30];
    struct vehicle v;
    struct reservation r;
    char line[MAX_LINE_LENGTH];

    int found = 0;
    rewind(f1);

    int attempts = 0;
    do
    {
        while (fgets(line, sizeof(line), f1))
        {
            if (sscanf(line, "%s %s %d %s %lf %d %f", v.plate_nr, v.model, &v.year, v.fuel_type, &v.consumption, &v.seats, &v.daily_price) == 7)
            {
                if (strcmp(v.model, model) == 0)
                {
                    printf("The vehicle with plate number %s, made in year %d, number of seats %d, and daily price %.2f has the model %s.\n", v.plate_nr, v.year, v.seats, v.daily_price, model);
                    found = 1;
                }
            }
        }

        if (!found)
        {
            attempts++;
            if (attempts >= 3)
            {
                printf("We have no vehicles in %s model. You have exceeded the maximum number of attempts.\n", model);
                break;
            }
            else
            {
                printf("We have no vehicles in %s model. Please try again. (%d chances left)\n", model, 3 - attempts);
                printf("Enter the model: \n");
                scanf("%s", model);
                rewind(f1);
            }
        }
    }
    while (!found);

    if (found)
    {

        printf("What's the plate number of the car you want to reserve? \n");
        scanf("%s", input);


        printf("Enter reservation date (dd.mm.yyyy): \n");
        scanf("%s", r.date);

        printf("Enter number of days: \n");
        scanf("%d", &r.nr_days);

        float total_price = v.daily_price * r.nr_days;
        total_price=Orkida_Apply_Discount(total_price,r.nr_days,r.date);
        char reservation_ID[12];
        sprintf(reservation_ID, "RES-%08d", rand() % 100000000);


        fprintf(f2, "%s    %s  %s    %d   %.0f %s \n", reservation_ID, r.date, user, r.nr_days,total_price, input);
        printf("Reservation created successfully!\nThe total price you have to pay is: %.2f\n", total_price);
    }

    fclose(f2);
}
void search_by_fuel_type(char user[], FILE* f1, FILE* f2, char fuel_type[])
{
    char input[30];
    struct vehicle v;
    struct reservation r;
    char line[MAX_LINE_LENGTH];

    int found = 0;
    rewind(f1);

    int attempts = 0;
    do
    {
        while (fgets(line, sizeof(line), f1))
        {
            if (sscanf(line, "%s %s %d %s %lf %d %f", v.plate_nr, v.model, &v.year, v.fuel_type, &v.consumption, &v.seats, &v.daily_price) == 7)
            {
                if (strcmp(v.fuel_type, fuel_type) == 0)
                {
                    printf("The vehicle with plate number %s, made in year %d, with model %s, and daily price %.2f runs on %s.\n", v.plate_nr, v.year, v.model, v.daily_price, fuel_type);
                    found = 1;
                }
            }
        }

        if (!found)
        {
            attempts++;
            if (attempts >= 3)
            {
                printf("We have no vehicles running on %s fuel type. You have exceeded the maximum number of attempts.\n", fuel_type);
                break;
            }
            else
            {
                printf("We have no vehicles running on %s fuel type. Please try again. (%d chances left)\n", fuel_type, 3 - attempts);
                printf("Enter the fuel type: \n");
                scanf("%s", fuel_type);
                rewind(f1);
            }
        }
    }
    while (!found);

    if (found)
    {

        printf("What's the plate number of the car you want to reserve? \n");
        scanf("%s", input);


        printf("Enter reservation date (dd.mm.yyyy): \n");
        scanf("%s", r.date);

        printf("Enter number of days: \n");
        scanf("%d", &r.nr_days);


        float total_price = v.daily_price * r.nr_days;

        total_price=Orkida_Apply_Discount(total_price,r.nr_days,r.date);

        char reservation_ID[12];
        sprintf(reservation_ID, "RES-%08d", rand() % 100000000);

        fprintf(f2, "%s    %s  %s    %d   %.0f %s \n", reservation_ID, r.date, user, r.nr_days,total_price, input);
        printf("Reservation created successfully!\nThe total price you have to pay is: %.2f\n", total_price);
    }

    fclose(f2);
}
void search_by_seats(char user[], FILE* f1, FILE* f2, int seats)
{
    char input[30];
    struct vehicle v;
    struct reservation r;
    char line[MAX_LINE_LENGTH];

    int found = 0;
    rewind(f1);

    int attempts = 0;
    do
    {
        while (fgets(line, sizeof(line), f1))
        {
            if (sscanf(line, "%s %s %d %s %lf %d %f", v.plate_nr, v.model, &v.year, v.fuel_type, &v.consumption, &v.seats, &v.daily_price) == 7)
            {
                if (v.seats == seats)
                {
                    printf("The vehicle with plate number %s, made in year %d, with model type %s, and a daily price of %.2f.\n", v.plate_nr, v.year, v.model, v.daily_price);
                    found = 1;
                }
            }
        }

        if (!found)
        {
            attempts++;
            if (attempts >= 3)
            {
                printf("We have no vehicles with %d seats. You have exceeded the maximum number of attempts.\n", seats);
                break;
            }
            else
            {
                printf("We have no vehicles with %d seats. Please try again. (%d chances left)\n", seats, 3 - attempts);
                printf("Enter the number of seats: \n");
                scanf("%d", &seats);
                rewind(f1);
            }
        }
    }
    while (!found);

    if (found)
    {

        printf("What's the plate number of the car you want to reserve? \n");
        scanf("%s", input);

        printf("Enter reservation date (dd.mm.yyyy): \n");
        scanf("%s", r.date);

        printf("Enter number of days: \n");
        scanf("%d", &r.nr_days);


        float total_price = v.daily_price * r.nr_days;
        total_price=Orkida_Apply_Discount(total_price,r.nr_days,r.date);

        char reservation_ID[12];
        sprintf(reservation_ID, "RES-%08d", rand() % 100000000);


        fprintf(f2, "%s    %s  %s    %d   %.0f %s \n", reservation_ID, r.date, user, r.nr_days,total_price, input);
        printf("Reservation created successfully!\nThe total price you have to pay is: %.2f\n", total_price);
    }

    fclose(f2);
}
void search_by_price(char user[], FILE* f1, FILE* f2, float price)
{
    char input[30];
    struct vehicle v;
    struct reservation r;
    char line[MAX_LINE_LENGTH];

    int found = 0;
    rewind(f1);

    int attempts = 0;
    do
    {
        while (fgets(line, sizeof(line), f1))
        {
            if (sscanf(line, "%s %s %d %s %lf %d %f", v.plate_nr, v.model, &v.year, v.fuel_type, &v.consumption, &v.seats, &v.daily_price) == 7)
            {
                if (v.daily_price <= price)
                {
                    printf("The vehicle with plate number %s, made in year %d and model %s\n", v.plate_nr, v.year, v.model);
                    found = 1;
                }
            }
        }

        if (!found)
        {
            attempts++;
            if (attempts >= 3)
            {
                printf("We have no vehicles within the price of %.2f. You have exceeded the maximum number of attempts.\n", price);
                break;  // Exit the loop and go back to the menu
            }
            else
            {
                printf("We have no vehicles within the price of %.2f. Please try again. (%d chances left)\n", price, 3 - attempts);
                printf("Enter the maximum daily price: \n");
                scanf("%f", &price);
            }
        }
        rewind(f1);
    }
    while (!found);

    if (found)
    {

        printf("What's the plate number of the car you want to reserve? \n");
        scanf("%s", input);


        printf("Enter reservation date (dd.mm.yyyy): \n");
        scanf("%s", r.date);

        printf("Enter number of days: \n");
        scanf("%d", &r.nr_days);


        float total_price = v.daily_price * r.nr_days;
        total_price=Orkida_Apply_Discount(total_price,r.nr_days,r.date);

        char reservation_ID[12];
        sprintf(reservation_ID, "RES-%08d", rand() % 100000000);


        fprintf(f2, "%s    %s  %s    %d   %.0f %s \n", reservation_ID, r.date, user, r.nr_days,total_price, input);
        printf("Reservation created successfully!\nThe total price you have to pay is: %.2f\n", total_price);
    }

    fclose(f2);
}
void print_top_three_reserved(struct vehicle vehicles[], int vehicleCount)
{

    for (int i = 0; i < vehicleCount - 1; i++)
    {
        for (int j = 0; j < vehicleCount - i - 1; j++)
        {
            if (vehicles[j].reservations < vehicles[j + 1].reservations)
            {
                struct vehicle temp = vehicles[j];
                vehicles[j] = vehicles[j + 1];
                vehicles[j + 1] = temp;
            }
        }
    }


    printf("Top Three Reserved Cars:\n");
    for (int i = 0; i < 3 && i < vehicleCount; i++)
    {
        printf("--------------------\n");
        printf("Plate Number: %s\n", vehicles[i].plate_nr);
        printf("Model: %s\n", vehicles[i].model);
        printf("Number of Reservations: %d\n", vehicles[i].reservations);
        printf("----------------------------\n");
    }
}

void print_three_most_reserved_cars()
{
    FILE* file = fopen("vehicle.txt", "r");
    if (file == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }

    struct vehicle vehicles[400]; // Assuming a maximum of 100 vehicles
    int vehicleCount = 0;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file))
    {
        struct vehicle v;
        if (sscanf(line, "%s %s %d %s %lf %d %f %d",
                   v.plate_nr, v.model, &v.year, v.fuel_type,
                   &v.consumption, &v.seats, &v.daily_price, &v.reservations) == 8)
        {
            vehicles[vehicleCount] = v;
            vehicleCount++;
        }
    }

    fclose(file);

    if (vehicleCount == 0)
    {
        printf("No vehicles found.\n");
    }
    else
    {
        print_top_three_reserved(vehicles, vehicleCount);
    }
}
void print_clients_by_reservation(FILE* f3, FILE* f2)
{
    int count_r;
    struct reservation r[150];
    struct client c[250];
    int num_reservations = 0;
    int num_clients = 0;

    rewind(f2);
    rewind(f3);

    if (f2 == NULL)
    {
        printf("Failed to open the reservation file.\n");
        return;
    }

    fscanf(f2, "%d", &count_r);
    for (int i = 0; i < count_r; i++)
    {
        fscanf(f2, "%s %s %s %d %lf %s", r[num_reservations].reservation_ID, r[num_reservations].date, r[num_reservations].user_ID, &r[num_reservations].nr_days, &r[num_reservations].total_price, r[num_reservations].plate_nr);
        num_reservations++;
    }

    if (f3 == NULL)
    {
        printf("Failed to open the client file.\n");
        return;
    }

    while (fscanf(f3, "%s %s %s %s %[^0-9] %s", c[num_clients].client_ID, c[num_clients].name, c[num_clients].surname, c[num_clients].passport_ID, c[num_clients].state, c[num_clients].phone_nr) == 6)
    {
        num_clients++;
    }

    fclose(f2);
    fclose(f3);

    for (int i = 0; i < num_reservations; i++)
    {
        if (r[i].user_ID[0] == '\0')
        {
            continue;
        }

        int count = 1;

        for (int j = i + 1; j < num_reservations; j++)
        {
            if (strcmp(r[i].user_ID, r[j].user_ID) == 0)
            {
                count++;
                r[j].user_ID[0] = '\0';
            }
        }

        if (count > 3)
        {
            printf("--------------------\n");
            printf("User ID: %s\n", r[i].user_ID);

            for (int k = 0; k < num_clients; k++)
            {
                if (strcmp(r[i].user_ID, c[k].client_ID) == 0)
                {

                    printf("Name: %s\n", c[k].name);
                    printf("Surname: %s\n", c[k].surname);
                    printf("Client ID: %s\n", c[k].client_ID);
                    printf("--------------------\n");
                    break;
                }
            }
        }
    }
}

int create_reservation(char user[], FILE* f1, FILE* f3, FILE* f2,int cnt_r)
{
    v* headv = NULL;
    r* headr = NULL;
    v* newNodev;
    r* newNoder;

    while (1)
    {
        newNodev = (v*)malloc(sizeof(v));
        if (fscanf(f1, "%s\t%s\t%d\t%s\t%lf\t%d\t%f\t%d", newNodev->plate_nr, newNodev->model, &newNodev->year, newNodev->fuel_type, &newNodev->consumption, &newNodev->seats, &newNodev->daily_price, &newNodev->reservations) == EOF)
        {
            free(newNodev);
            break;
        }
        newNodev->next = NULL;
        insertVehicleNode(&headv, newNodev);
    }

    while (1)
    {
        newNoder = (r*)malloc(sizeof(r));
        if (fscanf(f2, "%s %s %s %d %f", newNoder->reservation_ID, newNoder->date, newNoder->user_ID, &newNoder->nr_days, &newNoder->total_price) == EOF)
        {
            free(newNoder);
            break;
        }
        newNoder->next = NULL;
        insertReservationNode(&headr, newNoder);
    }

//printReservationList(headr);
//printVehicleList(headv);


    printf("Choose the option by which you want to search:\n");
    int option, year, seats;
    char model[30];
    float range;
    char fuel_type[30];

    for (;;)
    {
        printf("\nMENU:\n");
        printf("1 - By year\n2 - By model ID\n3 - By fuel type\n4 - By number of seats\n5 - By daily price\n6 - Three most reserved cars\n7- Name,surname and ID of clients who have rented +3 times\n0 - Stop\n");
        printf("Enter an option: \n");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        {
            printf("Enter the year: \n");
            scanf("%d", &year);

            search_by_year(user, f1, f2, year);
            cnt_r++;

            break;
        }
        case 2:
        {
            printf("Enter the model: \n");
            scanf("%s", model);

            search_by_model(user, f1, f2, model);
            cnt_r++;

            break;
        }
        case 3:
        {
            printf("Enter the fuel type:\n");
            scanf("%s", fuel_type);

            search_by_fuel_type(user, f1, f2, fuel_type);
 cnt_r++;
            break;
        }
        case 4:
        {
            printf("Enter the number of seats: \n");
            scanf("%d", &seats);

            search_by_seats(user, f1, f2, seats);
          cnt_r++;
            break;
        }
        case 5:
        {
            printf("Enter the maximum daily price: \n");
            scanf("%f", &range);

            search_by_price(user, f1, f2, range);
           cnt_r++;
            break;
        }
        case 6:
        {
            print_three_most_reserved_cars();
            break;
        }
        case 7:
        {
            print_clients_by_reservation(f3, f2);

            break;
        }
        case 0:
        {
            fclose(f2);
            return cnt_r;
        }
        default:
        {
            printf("Invalid option. Please try again.\n");
            break;
        }
        }
    }

}


#endif // TEA_H_INCLUDED

