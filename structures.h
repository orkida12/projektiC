#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

struct vehicle
{
    char plate_nr[40];
    char model[30];
    int year;
    char fuel_type[30];
    double consumption;
    int seats;
    float daily_price;
    int reservations;
    struct vehicle *next;

} ;

struct client
{
    char client_ID[30];
    char name[30];
    char surname [30];
    char passport_ID[30];
    char state[30];
    char phone_nr[30];
    struct client *next;
};

struct reservation
{
    char reservation_ID[30];
    char date[30];
    char user_ID[30];
    int nr_days;
    float total_price;
    char plate_nr[40];
    struct reservation *next;
} ;
void design1()
{

    printf("\n\t\t\t\t*************************************************************");
    printf("\n\t\t\t\t*****                                                   *****");
    printf("\n\t\t\t\t*****              Vehicle Rental Company               *****");
    printf("\n\t\t\t\t*****                                                   *****");
    printf("\n\t\t\t\t*************************************************************");;
    printf("\n\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\t\tWELCOME TO \RETO_McQueen\" VEHICLE RENTAL COMPANY, DESIGNED TO SIMPLIFY AND ENHANCE YOUR RENTAL EXPERIENCE!");
    printf("\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("\n\t\t**********************************************************************************************************\n");
    printf ("\t\tOur company is costumer-centered with a mission to provide facilities regarding the rental process our \n\
        \tclients are willing to take.We have currently 150 available vehicles of various models and around 100 \n\
        \tregistered clients who are continuously making reservation for their favorite cars!\n\
        \tThis program is designed to offer the best user experience for every user(clients and managers) \n\
                \t\t\t\tthat have access in this program.\n");
    printf("\n\t\t_____________________________________________________________________________________________________________\n");
}



void design2 ()
{
    printf("\t\t\t\t\t********************************************************\n");
    printf("\t\t\t\t\t*           These actions can consist of               *\n");
    printf("\t\t\t\t\t********************************************************\n");
    printf("\t\t\t\t\t*                                                      *\n");
    printf("\t\t\t\t\t*  1. Displaying all vehicle information               *\n");
    printf("\t\t\t\t\t*  2. Displaying available vehicles at the current time*\n");
    printf("\t\t\t\t\t*  3. Displaying vehicles available after X days       *\n");
    printf("\t\t\t\t\t*  4. Creating a new reservation                       *\n");
    printf("\t\t\t\t\t*  5. Adding a new vehicle                             *\n");
    printf("\t\t\t\t\t*  6. Searching for a vehicle by license plate number  *\n");
    printf("\t\t\t\t\t*  7. Sorting vehicles by daily rental price           *\n");
    printf("\t\t\t\t\t*  8. Displaying the top 3 most reserved vehicles      *\n");
    printf("\t\t\t\t\t*  9. Displaying all reservations                      *\n");
    printf("\t\t\t\t\t* 10. Removing a vehicle                               *\n");
    printf("\t\t\t\t\t* 11. Canceling a reservation                          *\n");
    printf("\t\t\t\t\t* 12. Displaying clients with more than 3 rentals      *\n");
    printf("\t\t\t\t\t* 13. Saving reservations with total cost exceeding X  *\n");
    printf("\t\t\t\t\t* 14. Modifying vehicle information                    *\n");
    printf("\t\t\t\t\t*                                                      *\n");
    printf("\t\t\t\t\t********************************************************\n");

}

#endif // STRUCTURES_H_INCLUDED
