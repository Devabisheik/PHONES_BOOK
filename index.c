#include <stdio.h>
#include <string.h>
#include <windows.h>
#define SW_MINIMIZE 6
FILE *fp;
void delcon()
{
    char input[10], name[50][10], phone[50][20], delete[10], number[20];
    int index = 0;
    printf("Enter the contact to delete: ");
    scanf("%s", input);
    fp = fopen("sample.txt", "r");
    while (fscanf(fp, "%s%s", delete, number) == 2)
    {
        if (strcmp(delete, input) != 0)
        {
            strcpy(name[index], delete);
            strcpy(phone[index], number);
            index++;
        }
    }
    fclose(fp);
    fp = fopen("sample.txt", "w");
    int i;
    for (i = 0; i < index; i++)
        fprintf(fp, "%s %s\n", name[i], phone[i]);
    printf("\nyour contact was deleted want to press 3\n");
    fclose(fp);
}
void search()
{
    char store[10];
    char cmp[10];
    char mod[10];
    char tmp[20];
    char url[50] = "whatsapp://send?phone=";
    char message[20];
    int found = 1, i;
    fp = fopen("sample.txt", "r+");
    printf("Enter a contact or ph.no to search: ");
    scanf("%s", cmp);
    while (!feof(fp))
    {
        fscanf(fp, "%s", tmp);
        fscanf(fp, "%s", store);
        for (i = 0; i < 10; i++)
        {
            if (store[i] == cmp[i])
            {
                found = 0;
            }
            else
            {
                found = 1;
                break;
            }
        }
        if (strcmp(cmp, tmp) == 0 || found == 0)
        {
            printf("NAME: %s", tmp);
            printf("\nPH.NUMBER: %s\n", store);
            while (getchar() != '\n'); // it will refresh before i using
            printf("Enter a message: ");
            fgets(message, sizeof(message), stdin);
            // scanf("%s",message);
            strcat(url, store);
            strcat(url, "&text=");
            strcat(url, message);
            // ShellExecute(0, "open", url, 0, 0, SW_SHOWNORMAL);
            ShellExecute(0, "open",url, 0, 0, SW_MINIMIZE);
            break;
        }
    }
    fclose(fp);
}

void datafill(char ch[10])
{
    int ph[10];

    fp = fopen("sample.txt", "a");
    fprintf(fp, "\n%s", ch);
    printf("Enter phone number: ");
    scanf("%s", ph);
    fprintf(fp, "\t%s", ph);
    fclose(fp);
}
void read()
{
    printf("            ENTIRE CONTACT LIST \n");
    char cont1[15], cont2[15];
    fp = fopen("sample.txt", "r");
    while (fscanf(fp, "%s %s", cont1, cont2) == 2)
    {
        printf("%s %s\n", cont1, cont2);
    }
    fclose(fp);
}
void main()
{
    int dos = 1, i;
    while (dos)
    {

        printf("\n1) to create contact\n");
        printf("5) to delete contact\n");
        printf("3) to view contact\n");
        printf("4) to search contact\n");
        printf("6) to exist\n");
        printf("press the above butoon: ");
        scanf("%d", &dos);
        switch (dos)
        {
        case 1:
        {
            int tr = 0;
            char buff[30];
            char sear[10];
            printf("Enter your name: ");
            scanf("%s", sear);
            printf("checking....\n");
            fp = fopen("sample.txt", "r");
            while (!feof(fp))
            {
                fscanf(fp, "%s", buff);
                tr = strcmp(buff, sear);
                fgets(buff, 30, fp);
                if (tr == 0)
                {
                    printf("already stored:%s", buff);
                    break;
                }
            }
            if (tr != 0)
            {
                printf("proceed to further step\n");
                datafill(sear);
            }
            break;
        }
        case 3:
        {
            read();
            break;
        }
        case 4:
        {
            search();
            break;
        }
        case 5:
        {
            delcon();
            break;
        }
        case 6:
        {
            printf("\nyou are existed,thank you");
            dos = 0;
            break;
        }
        default:
        {
            printf("please,check correct number in above descripion");
        }
        }
    }
}
