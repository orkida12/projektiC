#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "ORKIDA.h"
#include "TEA.h"
#include "ERA.h"
#include "ROSILDA.h"
void  modify(int number_res,FILE *f2){
    int cnt_r;
    f2 = fopen("Reservation.txt", "r+");
    fscanf(f2,"%d",&cnt_r);
    cnt_r+=number_res;
    fseek(f2, 0, SEEK_SET);
    fprintf(f2,"%d",cnt_r);

    fclose(f2);

}

int cnt_v=11;

int main()
{

    struct vehicle v[250];
    struct reservation r[150];
    struct client c[100];
    FILE* f1;
    FILE* f2;
    FILE* f3;

struct reservation *head_r=NULL,*tail_r=NULL;
struct vehicle *head_v=NULL,*tail_v=NULL;
struct client *head_c=NULL,*tail_c=NULL;

    int option, option2, clientoption, manageroption;
    char pass[20];
    int user_choice = 0;
    int attempts = 0;
    int found = 0;
    char user[30];
    int cnt_r;



    f1 = fopen("vehicle.txt", "r+");
    if (f1 == NULL)
    {
        printf("Error opening vehicle.txt\n");
        return 1;
    }

    f2 = fopen("Reservation.txt", "r+");
    if (f2 == NULL)
    {
        printf("Error opening Reservation.txt\n");
        return 1;
    }

    f3 = fopen("client.txt", "r+");
    if (f3 == NULL)
    {
        printf("Error opening client.txt\n");
        return 1;
    }

      design1();
      design2();
   /* printf("If you would like to obtain additional information about us, please press -1 to inquire more details about our company!\n");
    scanf("%d", &user_choice);

    if (user_choice == -1)
    {
        // bonus paragraph era
        // bonus picture tea
    }
    */
    Orkida_create_list_Client(f3,&head_c,&tail_c);
    while (1)
    {
        printf("Are you a user or a manager?\nPress 1 for Client\nPress 2 for Manager\nPress 0 to Exit\n");
        scanf("%d", &option);

        if (option == 0)
        {
            printf("Exiting the program...\n");
            break;
        }
        else if (option == 1)
        {
            printf("Are you registered?\nPress 1 for Yes\nPress 2 for No\n");
            scanf("%d", &option2);
            if (option2 == 2)
            {
                addClientFile("client.txt",c);
                const char* filename= "client.txt";
                // printf("Your unique ID identifier is %d",c.client_ID);
            }
            else
            {
                printf("Please enter your ID:\n");
                scanf("%s", user);
     //TO SEARCH USER BY ID USE SAVE IN ARRAY AND SEARCH USER
                 const char *filename= "client.txt";
              int cnt = 100;
             struct client c[cnt];
          saveInArray(filename,c, cnt);
          searchUserByID(c,cnt,user);

            }


            printf("\n----------------------------------------\n");
            printf("\n---------------- MENU ---------------\n");
            printf("-   1. Display Available Vehicles (Press 1)         - \n");       // era
            printf("-   2. Display Available Vehicles after a certain x number of days (Press 2)     - \n");       // era
            printf("-   3. Display vehicles based on daily price (Press 3)      - \n");     // orkida
            printf("-   4. Delete your reservation (Press 4)            - \n");       // orkida
            printf("-   5. Create Reservation (Press 5)      - \n");       // tea
            printf("-   0. Exit MENU (Press 0)\n");
            printf("------------------------------------\n");
            printf("What action do you want to perform?\n");
            scanf("%d", &clientoption);
            switch (clientoption)
            {
                case 1:
                   checkCarAvailability(f2) ;//era
                    break;
                case 2:
                    availableAfterDays(f2);// era
                    break;
                case 3:
                    Orkida_Create_LinkedList_Vehicle(f1,&head_v,&tail_v);
                  Orkida_sort_DailyPrice(f1,head_v);
                  //Orkida_Print_All_Ves(f1,head_v);


                    break;
                case 4:
                     fscanf(f2,"%d",&cnt_r);
                    Orkida_Create_List_Reservation(f2,&head_r,&tail_r,cnt_r);
                     // Orkida_Print_All_Res(f2,head_r,cnt_r);
                    fscanf(f2,"%d",&cnt_r);
                    cnt_r=Orkida_Delete_Reservation(f2,&head_r,cnt_r);

                    Orkida_update_file_res(head_r,cnt_r);

                    // orkida
                    break;
             case 5:

    initialize_random();
    rewind(f1);
    int number_res=0;
    number_res = create_reservation(user, f1, f3, f2, number_res);

                    modify(number_res,f2);


     rewind(f2);


   //Orkida_Create_List_Reservation(f2,&head_r,&tail_r,cnt_r);
  // Orkida_update_file_res(head_r,cnt_r);

    break;



                case 0:
                    printf("Exiting the program...\n");
                    break;
                default:
                    printf("Invalid option. Please try again.\n");
                    break;
            }

            if (clientoption == 0)
                break;
        }
        else if (option == 2)
        {
            attempts = 0;
            while (attempts < 3)
            {
                printf("Please enter the password:\n");
                scanf("%s", pass);

                if (strcmp(pass, "happyDay") == 0)
                {
                    printf("Welcome to the manager user interface!\n");
                    found = 1;
                    break;
                }
                else
                {
                    attempts++;
                    if (attempts < 3)
                    {
                        printf("Incorrect password. Please try again. (%d chances left)\n", 3 - attempts);
                    }
                    else
                    {
                        printf("You have exceeded the maximum number of attempts.\n");
                        break;
                    }
                }
            }

            if (found)
            {
                while (1)
                {
                    printf("\n----------------------------------------\n");
                    printf("\n---------------- MENU ---------------\n");
                    printf("-   1. Display vehicle information (Press 1)         - \n");       // rosilda
                    printf("-   2. Add vehicle (Press 2)     - \n");       // rosilda
                    printf("-   3. Save reservation with a total cost exceeding x (Press 3)      - \n");       // orkida
                    printf("-   4. Display reservations (Press 4)            - \n");       // orkida
                    printf("-   5. Delete vehicles (Press 5)      - \n");       // era
                    printf("-   6. Edit by plate number (Press 6)      - \n");       // rosilda
                    printf("-   7. Print all data (Press 7)      - \n");       // orkida+tea
                    printf("-   0. Exit MENU (Press 0)\n");
                    printf("------------------------------------\n");

                    printf("What action do you want to perform?\n");
                    scanf("%d", &manageroption);
                    switch (manageroption)
                    {
                        case 1:
                              displayVehiclesInfo(f1);
                            //display vehicle rosilda
                            break;
                        case 2:
                              addVehicles(f1);

                            // add vehicle rosilda
                            break;
                        case 3:
                            Orkida_Create_List_Reservation(f2,&head_r,&tail_r,cnt_r);
                            Orkida_ExidingTotalCost1(head_r);
                            //total cost x orkida
                            break;
                        case 4:
                            Orkida_Create_List_Reservation(f2,&head_r,&tail_r,cnt_r);
                            Orkida_Print_All_Res(f2,head_r,cnt_r);
                            // display reservations orkida
                            break;
                        case 5:
                            Orkida_Create_LinkedList_Vehicle(f1,&head_v,&tail_v);
                           // Orkida_Print_All_Ves(f1,head_v);
                            fscanf(f1,"%d",&cnt_v);

                            cnt_v=remove_vehicle(&head_v,f1);
                            //
                            Orkida_Update_Ves(head_v,cnt_v);
                            //delete vehicles era
                            break;
                        case 6:
                        {
                            Orkida_Create_LinkedList_Vehicle(f1,&head_v,&tail_v);
                            cnt_v=editByPlateNumber(f1,&head_v);
                            // Orkida_Print_All_Ves(f1,head_v);
                           //fseek(f1, 0, SEEK_SET); //go the begging of a file

                            Orkida_Update_Ves(head_v,cnt_v);
                            break;
                        }
                        case 7:
                        {
                            printf("\nAll information about reservation is:\n");
                            Orkida_Create_List_Reservation(f2,&head_r,&tail_r,cnt_r);
                            Orkida_Print_All_Res(f2,head_r,cnt_r);
                            printf("\n\nAll information about vehicles :\n");
                            Orkida_Create_LinkedList_Vehicle(f1,&head_v,&tail_v);
                            Orkida_Print_All_Ves(f1,head_v);
                            printf("\n\nAll information about clients:\n");
                            Orkida_create_list_Client(f3,&head_c,&tail_c);
                            Orkida_print_Client(head_c);
                            //print files orkida+tea
                            break;
                        }
                        case 0:
                            printf("Exiting the program...\n");
                            break;
                        default:
                            printf("Invalid option. Please try again.\n");
                            break;
                    }

                    if (manageroption == 0)
                        break;
                }
            }
        }
        else
        {
            printf("Invalid option. Please try again.\n");
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);

    return 0;
}
