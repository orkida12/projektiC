#ifndef ORKIDA_H_INCLUDED
#define ORKIDA_H_INCLUDED

void Orkida_Create_List_Reservation(FILE* f2,struct  reservation **head,struct reservation **tail,int cnt){
if (f2 == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }
    struct reservation *newRes=NULL,*prev=NULL;

fscanf(f2,"%d",&cnt);
 for(int i=0;i<cnt;i++){

        newRes=(struct reservation*)malloc(sizeof (struct reservation));

        fscanf(f2,"%s %s %s %d %f %s",newRes->reservation_ID, newRes->date, newRes->user_ID,&newRes->nr_days,&newRes->total_price,newRes->plate_nr);
            newRes->next=NULL;
            if(*head==NULL){
                *head=newRes;
            }
            else{
                prev->next=newRes;
            }
            prev=newRes;

    }
    *tail=prev;
    fclose(f2);
}


void Orkida_sort_DailyPrice(FILE *f1,struct vehicle *head_v){
 int count_v;
    printf("Hello \n You can find all vehicles based on their daily price below  :D");
   struct vehicle *curr=NULL,*next_node=NULL;
   struct vehicle temp;
   curr=head_v;

    if(curr==0) {
        printf("\nThere are no reservation until now !\n");
        return;
    }

    while (curr!=NULL){
        next_node=curr->next;
        while (next_node!=NULL){
            if(next_node->daily_price<curr->daily_price){
                temp=*curr;
                *curr=*next_node;
                *next_node=temp;
                temp.next=curr->next;
                curr->next=next_node->next;
                next_node->next=temp.next;
            }
            next_node=next_node->next;
        }
        curr=curr->next;
    }

curr=head_v;
   fscanf(f1, "%d", &count_v);
   printf("%d",count_v);
   int i=1;
   while(curr!=NULL){
        printf("\nVehicle %d\n",i);
        printf("The plate_nr Id is :%s\n ",curr->plate_nr);
        printf("The model is : %s\n",curr->model);
        printf("The year : %d\n",curr->year);
        printf("The fuel type : %s\n",curr->fuel_type);
        printf("The consumption : %.2lf Euro\n",curr->consumption);
        printf("The seats are %d\n",curr->seats);
        printf("The daily price is %f\n",curr->daily_price);
        printf("The reservation is  %d",curr->reservations);
        printf("_________________________________________________________________________________");
i++;
        curr=curr->next;

    }
    fclose(f1);
}


void Orkida_Create_LinkedList_Vehicle(FILE *f1 ,struct vehicle **head,struct vehicle **tail){

if (f1 == NULL)
    {
        printf("Failed to open the file.\n");
        return;
    }
  struct vehicle *NewNode=NULL;
  struct vehicle *prev=NULL;
 int count_v;
  fscanf(f1, "%d", &count_v);

  for(int i=0;i<count_v;i++){

      NewNode= (struct vehicle*)malloc(sizeof (struct vehicle));
      fscanf(f1,"%s %s %d %[^0-9] %lf %d %f %d",NewNode->plate_nr,NewNode->model,&NewNode->year,NewNode->fuel_type,&NewNode->consumption,&NewNode->seats,&NewNode->daily_price,&NewNode->reservations);
      NewNode->next=NULL;
      if(i==0){
          *head=NewNode;
      }
      else{
         prev->next=NewNode;
      }
      prev=NewNode;
  }
  *tail=prev;

   fclose(f1);
      }


void Orkida_Print_All_Ves(FILE *f1,struct vehicle *head){

    if(head==0)
        printf("\nThere are no reservation until now !\n");
      int i=1;
   while(head!=NULL){
        printf("\nVeichle %d \n",i);
        printf("The plate_nr Id is :%s \n ",head->plate_nr);
        printf("The model is : %s \n",head->model);
        printf("The year is : %d \n",head->year);
        printf("The fuel type is : %s \n",head->fuel_type);
        printf("The consumption : %.2lf Euro\n",head->consumption);
        printf("The seats are %d \n",head->seats);
        printf("The daily price is %.2f \n",head->daily_price);
        printf("The reservation is  %d \n",head->reservations);
        printf("_______________________________________________________________________________________________");
i++;
        head=head->next;

    }
        fclose(f1);
}

int Orkida_Delete_Reservation(FILE* f2,struct reservation **head_r,int cnt_r) {

    char resID[30];
if (f2 == NULL)
    {
        printf("Failed to open the file.\n");
        return 1;
    }
    struct reservation *prev=NULL,*curr=NULL;
printf("%d",cnt_r);
    curr = *head_r;

        printf("Enter reservation ID\n");
        scanf("%s", resID);

        while (curr != NULL) {
            if (strcmp(curr->reservation_ID, resID) == 0) {
                break;
            }
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL) {
            printf("\nThe reservation was not found!\nCheck your reservation ID again");
        } else if (prev == NULL) {
            *head_r = curr->next;
            free(curr);
            printf("The reservation got deleted ");
            cnt_r--;
        } else {
            prev->next = curr->next;
            free(curr);
            printf("\nThe reservation got deleted\n");
            cnt_r--;
        }
    fclose(f2);
    return cnt_r;


    }

void  Orkida_update_file_res(struct reservation *head_r,int cnt_r){
    struct reservation* curr=NULL;
    curr=head_r;
    FILE*f2=NULL;
    f2=fopen("Reservation.txt","w");

    fprintf(f2,"%d\n",cnt_r);
    if(cnt_r!=0){

        while (curr!=NULL){
            fprintf(f2,"%s %s %s %d %f %s\n",curr->reservation_ID,curr->date,curr->user_ID,curr->nr_days,curr->total_price,curr->plate_nr);

            curr=curr->next;
        }
    }
    fclose(f2);
}

void Orkida_Print_All_Res(FILE* f2,struct reservation *head,int cnt){
int i=1;
    if(head==0)
        printf("\nThere are no reservation until now !\n");
while(head!=NULL){
        printf("\nReservation %d \n",i);
        printf("The reservation id is :%s \n ",head->reservation_ID);
        printf("The date of reservation is : %s \n",head->date);
        printf("The client ID is : %s \n",head->user_ID);
        printf("The nr of days for this reservation is : %d \n",head->nr_days);
        printf("The total price for the reservation is : %.2f Euro\n",head->total_price);
        printf("The plate number is  : %s \n",head->plate_nr);
        printf("__________________________________________________________________________________________________");

        head=head->next;
i++;
    }
    fclose(f2);

}

void Orkida_ExidingTotalCost1(struct reservation *head){   //create file
        float price;
        FILE *newFile;
        newFile= fopen("newfile.txt","w");
        if(newFile==NULL){
            printf("\nNewFile can not be open\n");
            return;
        }
    printf("\nEnter a price to see the reservations which exceed this price \n");
    scanf("%f",&price);

    while (head!=NULL){
        if(head->total_price>price){
            fprintf(newFile,"%s  %s  %s  %d  %0.2f\n",head->reservation_ID,head->date,head->user_ID,head->nr_days,head->total_price);
        }
        head=head->next;
    }

    fclose(newFile);
    }
void Orkida_create_list_Client(FILE *f3,struct client **head_c,struct client **tail){
    int count_c;
    struct client *prev=NULL,*newNode=NULL;
    if(f3==NULL){
        printf("File f3 cannot be open ");
        return;
    }
     fscanf(f3, "%d", &count_c);
    for(int i=0;i<count_c;i++){
        newNode=(struct client*) malloc(sizeof (struct client));
        fscanf(f3,"%s%s%s%s%[^0-9]%s",newNode->client_ID,newNode->name,newNode->surname,newNode->passport_ID,newNode->state,newNode->phone_nr);
        newNode->next=NULL;
        if(i==0){
            *head_c=newNode;
        }
        else{
            prev->next=newNode;
        }
        prev=newNode;
    }
    *tail=prev;
    fclose(f3);

}

void Orkida_print_Client(struct client *head){
 int count_c,i=1;

    while (head!=NULL){
        printf("Client %d:\n",i);
        printf("Client Id :%s\n ",head->client_ID);
        printf("Name: %s\n",head->name);
        printf("Surname: %s\n",head->surname);
        printf("Passport ID: %s\n",head->passport_ID);
        printf("State %s \n",head->state);
        printf("Phone nr %s\n",head->phone_nr);
        printf("____________________________________________________________________________________\n");

        head=head->next;
        i++;

    }


}
float Orkida_Apply_Discount(float total_price,int nr_days,char date[]){
    int day,month,year;
    sscanf(date,"%d.%d.%d",&day,&month,&year);
    if(nr_days==7){
            total_price=total_price-((0.1)*total_price);
        }
        else if(nr_days==14){
            total_price=total_price-((0.15)*total_price);
        }
        if(month==2){
            if(day==28||day==29){
                total_price=total_price-((0.2)*total_price);
            }
        }
        else if(month==1 || month==3 ||month==5 ||month==7||month==8||month==10||month==12){
            if(day==31){
               total_price=total_price-((0.2)*total_price);
            }
        }
        else
            if(day==30){
               total_price=total_price-((0.2)*total_price);
            }


        else if(nr_days==30||nr_days==31){
           total_price=total_price-((0.2)*total_price);
        }
return total_price;
    }


    void Orkida_Update_Ves(struct vehicle *head_v,int cnt_v){
       FILE *f1=NULL;
        struct vehicle* curr=NULL;

        curr=head_v;
        f1=fopen("vehicle.txt","w");
      if(f1==NULL){
          printf("File f1 can not be open");
      }

        fprintf(f1,"%d\n",cnt_v);


            while (curr!=NULL){
                fprintf(f1,"%s %s %d %s %lf %d %.2f %d\n",curr->plate_nr,curr->model,curr->year,curr->fuel_type,curr->consumption,curr->seats,curr->daily_price,curr->reservations);

                curr=curr->next;
            }

        fclose(f1);

}




#endif // ORKIDA_H_INCLUDED
