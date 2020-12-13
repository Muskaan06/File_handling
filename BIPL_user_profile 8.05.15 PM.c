//
//  main.c
//  BIPL_user_profile
//
//  Created by Muskaan Maurya on 24/03/20.
//  Copyright © 2020 Muskaan Maurya. All rights reserved.
//

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define FILE_ADD_SUCCESS 0
#define FILE_OPEN_READ 1
#define FILE_OPEN_APPEND 2
#define FILE_DELETE_SUCCESS 3
#define FILE_SEARCH_SUCCESS 4
#define FILE_DISPLAY_SUCCESS 5

struct address{
    char location[50];
    char pin_code[10];
    char city[50];
    char state[50];
};
struct address add;
struct user_info{
    char uid[10];
    char first_name[128];
    char last_name[128];
    struct address add;
    char sex[10];
    char designation[10];
};
struct user_info info;

//function prototypes
void input_function(void);
unsigned char add_user_info(void);
int file_mode(void);
unsigned char search_user_info_uid(void);
unsigned char search_user_info_firstname(void);
unsigned char search_user_info_lastname(void);
unsigned char search_user_by_state(void);
unsigned char search_user_by_sex(void);
unsigned char search_user_by_city(void);
unsigned char delete_user_info(void);
unsigned char view_all_user(void);

int main() {
    
                input_function();
                return 0;
    
}

void input_function(){
                int choice,status;
                printf("\nfollowing operations are allowed in the file.Choose!:\n1) Add user information\n2) Search by employe id\n3) Search by first name\n4)  Search by last name\n5) Search by State\n6) Search by Sex\n7) Search by City\n8) Delete user info\n9) view whole user info\n10) Search user information\n");
                scanf("%d",&choice);
                switch (choice){
                                case 1:
                                        status=add_user_info();
                                        if(status==FILE_ADD_SUCCESS)
                                            printf("\ndata addition successful\n");
                                        break;
                                case 2:
                                        status=search_user_info_uid();
                                        if(status==FILE_SEARCH_SUCCESS)
                                            printf("\ndata search successful\n");
                                        break;
                                case 3:
                                        status=search_user_info_firstname();
                                        if(status==FILE_SEARCH_SUCCESS)
                                            printf("\ndata search successful\n");
                                        break;
                                case 4:
                                        status=search_user_info_lastname();
                                        if(status==FILE_SEARCH_SUCCESS)
                                            printf("\ndata search successful\n");
                                        break;
                                case 5:
                                        status=search_user_by_state();
                                        if(status==FILE_SEARCH_SUCCESS)
                                            printf("\ndata search successful\n");
                                        break;
                                case 6:
                                        status=search_user_by_sex();
                                        if(status==FILE_SEARCH_SUCCESS)
                                            printf("\ndata search successful\n");
                                        break;
                                case 7:
                                        status=search_user_by_city();
                                        if(status==FILE_SEARCH_SUCCESS)
                                            printf("\ndata search successful\n");
                                        break;
                                case 8:
                                        status=delete_user_info();
                                        if(status==FILE_DELETE_SUCCESS)
                                            printf("\ndeletion successful");
                                        break;
                                case 9:
                                        status=view_all_user();
                                        if(status==FILE_DISPLAY_SUCCESS)
                                            printf("\n display successful");
                                        break;
                        
                                default:printf("\nwrong input");
                        
                }
}
//function to check existance of the file
int file_mode(){
                FILE *fp_input;
                if ((fp_input = fopen("BIPL.txt", "rb")))
                {
                    fclose(fp_input);
                    return (FILE_OPEN_APPEND);
                }
                return (FILE_OPEN_READ);
}
//function to add info to file
unsigned char add_user_info(){
                FILE *fp_input;
                int open; char flag='y';
                open=file_mode();
                if(open==FILE_OPEN_APPEND)
                    fp_input=fopen("BIPL.txt","ab");
                else
                    fp_input=fopen("BIPL.txt", "wb");
                if(fp_input==NULL){
                            printf("\ncannot open file");
                            exit(0);
                }
                fseek(fp_input,0,SEEK_END);
                while(flag=='y'){
                            printf("enter the following info\n1) UID\n2) First Name\n3) Last Name\n4) Address (Location, Pin Code, City, State)\n5) Sex\n6) Designation\n");
                            scanf("%s%s%s%s%s%s%s%s%s",info.uid,info.first_name,info.last_name,info.add.location,info.add.pin_code,info.add.city,info.add.state,info.sex,info.designation);
                          //  printf("uid=%s  location=%s  pincode=%s  citi=%s  state=%s",info.uid,info.add.location,info.add.pin_code,info.add.city,info.add.state);
                            fwrite(&info,sizeof(info),1,fp_input);
                            fwrite("\n", sizeof("\n"), 1, fp_input);
                            printf("\n do you want to continue?(y/n) ");
                            fflush(stdin);
                            flag=getchar();
                }
                fclose(fp_input);
                return (FILE_ADD_SUCCESS);
    
}
//function to search for user info through uid
unsigned char search_user_info_uid(){
                FILE *fp_input;
                int open; char temp[10];
                open=file_mode();
                if(open==FILE_OPEN_READ){
                            printf("\nfile is empty");
                            exit(0);
                }
                fp_input=fopen("BIPL.txt", "rb");
                if(fp_input==NULL){
                            printf("\ncannot open file");
                            exit(0);
                }
                printf("\nenter the uid to search");
                fflush(stdin);
                scanf("%[^\n]s",temp);
                while((fread(&info,sizeof(info),1,fp_input))==1){
                            if(strcmp(info.uid, temp)==0){
                                printf("\nuser name: %s %s\naddress: %s %s %s %s\nsex: %s\ndesignation: %s",info.first_name,info.last_name,info.add.location,info.add.pin_code,info.add.city,info.add.state,info.sex,info.designation);
                                return(FILE_SEARCH_SUCCESS);
                            }
                            fseek(fp_input,(sizeof("\n")),SEEK_CUR);
                }
                printf("\nthe user doesn't exist");
                fclose(fp_input);
                return(FILE_SEARCH_SUCCESS);
    
}
//function to search for user info through firstname
unsigned char search_user_info_firstname(void){
                FILE *fp_input;int counter=0;
                int open; char temp[10];
                open=file_mode();
                if(open==FILE_OPEN_READ){
                            printf("\nfile is empty");
                            exit(0);
                }
                fp_input=fopen("BIPL.txt", "rb");
                if(fp_input==NULL){
                            printf("\ncannot open file");
                            exit(0);
                }
                printf("\nenter the firstname of user to search  ");
                fflush(stdin);
                scanf("%[^\n]s",temp);
                while((fread(&info,sizeof(info),1,fp_input))==1){
                            if(strcmp(info.first_name, temp)==0){
                                printf("\nuser name: %s %s\naddress: %s %s %s %s\nsex: %s\ndesignation: %s",info.first_name,info.last_name,info.add.location,info.add.pin_code,info.add.city,info.add.state,info.sex,info.designation);
                                counter++;
                            }
                            fseek(fp_input,(sizeof("\n")),SEEK_CUR);
                }
                if(counter==0){
                    printf("\nthe user doesn't exist");
                    fclose(fp_input);
                    return(FILE_SEARCH_SUCCESS);
                }
                else{
                    fclose(fp_input);
                    return(FILE_SEARCH_SUCCESS);
                }
}
//function to search for user info through lastname
unsigned char search_user_info_lastname(void){
                FILE *fp_input;int counter=0;
                int open; char temp[10];
                open=file_mode();
                if(open==FILE_OPEN_READ){
                            printf("\nfile is empty");
                            exit(0);
                }
                fp_input=fopen("BIPL.txt", "rb");
                if(fp_input==NULL){
                            printf("\ncannot open file");
                            exit(0);
                }
                printf("\nenter the lastname of user to search  ");
                fflush(stdin);
                scanf("%[^\n]s",temp);
                while((fread(&info,sizeof(info),1,fp_input))==1){
                            if(strcmp(info.last_name, temp)==0){
                                printf("\nuser name: %s %s\naddress: %s %s %s %s\nsex: %s\ndesignation: %s",info.first_name,info.last_name,info.add.location,info.add.pin_code,info.add.city,info.add.state,info.sex,info.designation);
                                counter++;
                            }
                            fseek(fp_input,(sizeof("\n")),SEEK_CUR);
                }
                if(counter==0){
                    printf("\nthe user doesn't exist");
                    fclose(fp_input);
                    return(FILE_SEARCH_SUCCESS);
                }
                else{
                    fclose(fp_input);
                    return(FILE_SEARCH_SUCCESS);
                }
}
//function to search for user info through state
unsigned char search_user_by_state(){
                FILE *fp_input;int counter=0;
                int open; char temp[10];
                open=file_mode();
                if(open==FILE_OPEN_READ){
                            printf("\nfile is empty");
                            exit(0);
                }
                fp_input=fopen("BIPL.txt", "rb");
                if(fp_input==NULL){
                            printf("\ncannot open file");
                            exit(0);
                }
                printf("\nenter the state of user to search  ");
                fflush(stdin);
                scanf("%[^\n]s",temp);
                while((fread(&info,sizeof(info),1,fp_input))==1){
                            if(strcmp(info.add.state, temp)==0){
                                printf("\nuser name: %s %s\naddress: %s %s %s %s\nsex: %s\ndesignation: %s",info.first_name,info.last_name,info.add.location,info.add.pin_code,info.add.city,info.add.state,info.sex,info.designation);
                                counter++;
                            }
                            fseek(fp_input,(sizeof("\n")),SEEK_CUR);
                }
                if(counter==0){
                            printf("\nthe user doesn't exist");
                            fclose(fp_input);
                            return(FILE_SEARCH_SUCCESS);
                }
                else{
                    fclose(fp_input);
                     return(FILE_SEARCH_SUCCESS);
                }
}
//function to search for user info through sex
unsigned char search_user_by_sex(){
                FILE *fp_input;int counter=0;
                int open; char temp[10];
                open=file_mode();
                if(open==FILE_OPEN_READ){
                            printf("\nfile is empty");
                            exit(0);
                }
                fp_input=fopen("BIPL.txt", "rb");
                if(fp_input==NULL){
                            printf("\ncannot open file");
                            exit(0);
                }
                printf("\nenter the sex of user to search  ");
                fflush(stdin);
                scanf("%[^\n]s",temp);
                while((fread(&info,sizeof(info),1,fp_input))==1){
                            if(strcmp(info.sex, temp)==0){
                                printf("\nuser name: %s %s\naddress: %s %s %s %s\nsex: %s\ndesignation: %s",info.first_name,info.last_name,info.add.location,info.add.pin_code,info.add.city,info.add.state,info.sex,info.designation);
                                counter++;
                            }
                            fseek(fp_input,(sizeof("\n")),SEEK_CUR);
                }
                if(counter==0){
                            printf("\nthe user doesn't exist");
                            fclose(fp_input);
                            return(FILE_SEARCH_SUCCESS);
                }
                else{
                            fclose(fp_input);
                            return(FILE_SEARCH_SUCCESS);
                }
}
//function to search for user info through sex
unsigned char search_user_by_city(){
                FILE *fp_input;int counter=0;
                int open; char temp[10];
                open=file_mode();
                if(open==FILE_OPEN_READ){
                            printf("\nfile is empty");
                            exit(0);
                }
                fp_input=fopen("BIPL.txt", "rb");
                if(fp_input==NULL){
                            printf("\ncannot open file");
                            exit(0);
                }
                printf("\nenter the city of user to search  ");
                fflush(stdin);
                scanf("%[^\n]s",temp);
                while((fread(&info,sizeof(info),1,fp_input))==1){
                            if(strcmp(info.add.city, temp)==0){
                                printf("\nuser name: %s %s\naddress: %s %s %s %s\nsex: %s\ndesignation: %s",info.first_name,info.last_name,info.add.location,info.add.pin_code,info.add.city,info.add.state,info.sex,info.designation);
                                counter++;
                            }
                            fseek(fp_input,(sizeof("\n")),SEEK_CUR);
                }
                if(counter==0){
                            printf("\nthe user doesn't exist");
                            fclose(fp_input);
                            return(FILE_SEARCH_SUCCESS);
                }
                else{
                    fclose(fp_input);
                    return(FILE_SEARCH_SUCCESS);
                }
}
//function to delete user information
unsigned char delete_user_info(){
                FILE *fp_input,*fp_temp;char flag='y';
                int open; char temp[10];int counter=0;
                open=file_mode();
                if(open==FILE_OPEN_READ){
                            printf("\nfile is empty");
                            exit(0);
                }
                fp_input=fopen("BIPL.txt", "rb");
                if(fp_input==NULL){
                            printf("\ncannot open file");
                            exit(0);
                }
                while(flag=='y'){
                    printf("\nenter the uid of user to delete :  " );
                    fflush(stdin);
                    scanf("%[^\n]s",temp);
                    fp_temp=fopen("temp.txt","wb");
                    if(fp_temp==NULL){
                            printf("\ncannot open file");
                            exit(0);
                    }
                    while((fread(&info,sizeof(info),1,fp_input))==1){
                            if(strcmp(info.uid, temp)!=0){
                                    fwrite(&info,sizeof(info),1,fp_temp);
                                    fwrite("\n", sizeof("\n"), 1, fp_temp);
                            }
                            counter++;
                            fseek(fp_input,(sizeof("\n")),SEEK_CUR);
                    }
                    fclose(fp_input);
                    fclose(fp_temp);
                    remove("BIPL.txt");
                    rename("temp.txt","BIPL.txt");
                    fp_input=fopen("BIPL.txt","rb+");
                    printf("do you want to delete another record(y/n): ");
                    fflush(stdin);
                    flag=getchar();
                }
                if(counter==0){
                        printf("\nuser doesn't exist");
                        fclose(fp_input);
                        return(FILE_DELETE_SUCCESS);
                }
                else{
                        fclose(fp_input);
                        return(FILE_DELETE_SUCCESS);
                }
}
//function to view all the users
unsigned char view_all_user(){
                FILE *fp_input;
                int open;
                open=file_mode();
                if(open==FILE_OPEN_READ){
                            printf("\nfile is empty");
                            exit(0);
                }
                fp_input=fopen("BIPL.txt", "rb");
                if(fp_input==NULL){
                            printf("\ncannot open file");
                            exit(0);
                }
                while((fread(&info,sizeof(info),1,fp_input))==1){
                            printf("\nuser name: %s %s\naddress: %s %s %s %s\nsex: %s\ndesignation: %s",info.first_name,info.last_name,info.add.location,info.add.pin_code,info.add.city,info.add.state,info.sex,info.designation);
                            fseek(fp_input,(sizeof("\n")),SEEK_CUR);
                }
                fclose(fp_input);
                return(FILE_DISPLAY_SUCCESS);
}

