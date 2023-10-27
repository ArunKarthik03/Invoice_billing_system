#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items
{
                char item[30];
                float price;
                int quantity;
};

struct orders
{
                char customer[50];
                char date[10];
                int number_of_items;
                struct items itm[50];
};

void generateBillHeader(char name[50],char date[30])
{
                printf("\n\n");
                printf("\t      C-Restaurant");
                printf("\n\t --------------------");
                printf("\nDate:%s",date);
                printf("\nInvoice to %s",name);
                printf("\n");
                printf("----------------------------------------\n");
                printf("Items\t\t");
                printf("Quantity\t");
                printf("Total\t\t");
                printf("\n---------------------------------------");
                printf("\n\n");
}

void generateBillBody(char item[30],int quantity,float price)
{
                printf("%s\t\t",item);
                printf("%d\t\t",quantity);
                printf("%.2f\t\t",quantity*price);
                printf("\n\n");
}

void generateBillFooter(float total)
{
                printf("\n");
                float discount=0.1*total;
                float nettotal=total-discount;
                float cgst=0.09*nettotal,grandtotal=nettotal+2*cgst;
                printf("----------------------------------------\n");
                printf("sub total\t\t\t%.2f",total);
                printf("\nDiscount @10%s\t\t\t%.2f","%",discount);
                printf("\n\t\t\t\t--------");
                printf("\nNet total\t\t\t%.2f",nettotal);
                printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
                printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
                printf("\n-----------------------------------------");
                printf("\nGrand total\t\t\t%.2f",grandtotal);
                printf("\n-----------------------------------------\n");
}

int main()
{
                //Dash board
                struct orders ord;
                struct orders ordd;
                int option,n;
                FILE *fptr;
                char savebill='y',continue_flag='y';
                char name[50];
                while(continue_flag == 'y')
                {
                float total=0;
                int invoicefound=0;
                printf("\n\n\t\t================= *C-Restaurant* ================\t\t\n\n");
                printf("\nPlease select your prefered operation : ");
                printf("\n\n1.Generate Invoice\n");
                printf("\n2.Show all Invoice\n");
                printf("\n3.search Invoice\n");
                printf("\n4.Exit\n");
                printf("\nPlease enter your chioce : ");
                scanf("%d",&option);
                fgetc(stdin);
                switch(option)
                {
                                case 1:
                                                system("clear");
                                                printf("\nPlease enter the name of the customer : ");
                                                fgets(ord.customer,50,stdin);
                                                ord.customer[strlen(ord.customer)-1]=0;//to get \n(enetr) in fgetd
                                                strcpy(ord.date,__DATE__);
                                                printf("\nEnter the No.of items : ");
                                                scanf("%d",&n);
                                                ord.number_of_items=n;
                                                for(int i=0;i<n;i++)
                                                {
                                                                fgetc(stdin);
                                                                printf("\n\n");
                                                                printf("\nPlease enter the item[%d] : ",i+1);
                                                                fgets(ord.itm[i].item,30,stdin);
                                                                ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
                                                                printf("\nPlease enter the quantity : ");
                                                                scanf("%d",&ord.itm[i].quantity);
                                                                printf("\nPlease enter the unit price : ");
                                                                scanf("%f",&ord.itm[i].price);
                                                                total+=ord.itm[i].quantity * ord.itm[i].price;
                                                }
                                            generateBillHeader(ord.customer,ord.date);
                                                for(int i=0;i<ord.number_of_items;i++)
                                                {
                                                                generateBillBody(ord.itm[i].item,ord.itm[i].quantity,ord.itm[i].price);
                                                }
                                                generateBillFooter(total);
                                                printf("\nDo yo want to save the invoice [y/n] : ");
                                                scanf("%s",&savebill);
                                                if(savebill == 'y')
                                                {
                                                                fptr=fopen("Res.dat","a+");
                                                                fwrite(&ord,sizeof(struct orders),1,fptr);
                                                                if(fwrite != NULL)
                                                                {
                                                                                printf("\nSuccessfully saved\n\n");
                                                                }
                                                                else
                                                                {
                                                                                printf("\nError in saving the invoice\n\n");
                                                                }
                                                                fclose(fptr);
                                                }
                                                break;
                                case 2:
                                                system("clear");
                                                fptr=fopen("Res.dat","r");
                                                printf("\n ******** Your previous Invoice ********\n");
                                                while(fread(&ordd,sizeof(struct orders),1,fptr))
                                                {
                                                float tot=0;
                                                generateBillHeader(ordd.customer,ordd.date);
                                                for(int i=0;i<ordd.number_of_items;i++)
                                                {
                                                                generateBillBody(ordd.itm[i].item,ordd.itm[i].quantity,ordd.itm[i].price);
                                                                tot+=ordd.itm[i].quantity * ordd.itm[i].price;
                                                }
                                                generateBillFooter(tot);
                                                }
                                                fclose(fptr);
                                                break;
                                case 3:
                                                printf("\nEnter name of the customer : ");
                        fgets(name,50,stdin);
                                                name[strlen(name)-1]=0;
                        system("clear");
                        fptr=fopen("Res.dat","r");
                        printf("\n\t******** Invoice of %s ********\n",name);
                        while(fread(&ordd,sizeof(struct orders),1,fptr))
                        {
                        float tot=0;
                                                if(!strcmp(ordd.customer,name))
                                                {
                        generateBillHeader(ordd.customer,ordd.date);
                        for(int i=0;i<ordd.number_of_items;i++)
                        {
                                  generateBillBody(ordd.itm[i].item,ordd.itm[i].quantity,ordd.itm[i].price);
                                  tot+=ordd.itm[i].quantity * ordd.itm[i].price;
                        }
                        generateBillFooter(tot);
                                                invoicefound=1;
                        }
                                                }
                                                if(!invoicefound)
                                                {
                                                                printf("\nSorry the invoice for %s doesnot exit\n",name);
                                                }
                        fclose(fptr);
                        break;
                                case 4:
                                                printf("\n\t\tThank you..bye bye\n\n\n");
                                                exit(1);
                                                break;
                                default :
                                                printf("\nInvalid option..\n");

                }
                printf("\nDo you want to continue another operation[y/n] : ");
                scanf("%s",&continue_flag);
                printf("\n\n");
                }

}