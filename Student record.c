#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    FILE *fp,*ft;
    char another,choice;
    struct student
    {
        char name[21];
        int age;
        int rollno;
    };
    struct student s;
    char studname[21];
    long int recsize;
    //Opening file
    fp = fopen("Student_Record_r1.txt","rb+");
    //Check if opened correctly
    if(fp == NULL)
    {
        fp = fopen("Student_Record_r1.txt","wb+");
        if(fp == NULL)
        {
            puts("Can't open file");
            exit(1);
        }
    }

    recsize = sizeof(s);

    while(1)
    {
        printf("1.Add records\n");
        printf("2.List records\n");
        printf("3.Modify records\n");
        printf("4.Delete records\n");
        printf("0.Exit\n");
        printf("Your choice\n");

        fflush(stdin);
        //choice = getchar();
        //scanf("%c",&choice);
        scanf("%c",&choice);
        switch(choice)
        {
            case '1' :
                fseek(fp,0,SEEK_END);
                another = 'Y';
                while(another == 'Y')
                {
                    printf("Enter name,age and rollno in order\n");
                    scanf("%s%d%d",s.name,&s.age,&s.rollno);
                    fwrite(&s,recsize,1,fp);
                    printf("Add another record\n");
                    scanf("%c",&another);
                    scanf("%c",&another);
                 //   another = getchar();
                }
                break;
            case '2' :
                rewind(fp);
                while(fread(&s,recsize,1,fp) == 1)
                    printf("%s %d %d\n",s.name,s.age,s.rollno);
                break;
            case '3' :
                another = 'Y';
                while(another == 'Y')
                {
                    printf("Enter name of student to modify\n");
                    scanf("%s",studname);
                    rewind(fp);
                    while(fread(&s,recsize,1,fp) == 1)
                    {
                        if(strcmp(s.name,studname)==0)
                        {
                            printf("Enter new name,age and rollno in order\n");
                            scanf("%s %d %d",s.name,&s.age,&s.rollno);
                            fseek(fp,-recsize,SEEK_CUR);
                            fwrite(&s,recsize,1,fp);
                            break;
                        }
                    }
                    printf("Modify another record\n");
                    scanf("%c",&another);
                    scanf("%c",&another);
                    
                }
                break;
            case '4' :
                another = 'Y';
                while(another == 'Y')
                {
                    printf("Enter student name to delete\n");
                    scanf("%s",studname);
                    ft = fopen("Temp.dat","wb");
                    rewind(fp);
                    while(fread(&s,recsize,1,fp) == 1)
                    {
                        if(strcmp(s.name,studname) != 0)
                            fwrite(&s,recsize,1,ft);
                    }
                    fclose(fp);
                    fclose(ft);
                    remove("Student_Record_r1.txt");
                    rename("Temp.dat","Student_record_r1.txt");
                    fp = fopen("Student_record_r1.txt","rb+");
                    printf("Delete another record?\n");
                    scanf("%c",&another);
                    scanf("%c",&another);
                }
                break;
            case '0' :
                fclose(fp);
                exit(0);
        }
    }
    return 0;
}
