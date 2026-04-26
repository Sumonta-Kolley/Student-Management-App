#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>


struct student {
    long long int rno;
    char name[50];
    float marks;
};


void add_student();
void display_all();
void search_student();
void delete_student();

int main() {
    int ch;

    while(1) {
        printf("\n\n*** Student Record System ***\n");
        printf("1. Add Record\n");
        printf("2. View All Records\n");
        printf("3. Search Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        
        if (scanf("%d", &ch) != 1) {
            printf("\nInvalid input! Please enter a number.\n");
            while(getchar() != '\n'); 
            continue;
        }

        switch(ch) {
            case 1: 
                add_student(); 
                break;
            case 2: 
                display_all(); 
                break;
            case 3: 
                search_student(); 
                break;
            case 4: 
                delete_student(); 
                break;
            case 5:
                printf("\nExiting program...\n");
                exit(0);
            default:
                printf("\nWrong choice! Try again.\n");
        }
    }
    return 0;
}

void add_student() {
    FILE *fp;
    struct student st = {0}; 
    
   
    fp = fopen("student_data.bin", "ab");
    if(fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n-- Enter Details --\n");
    printf("Roll No: ");
    if (scanf("%lld", &st.rno) != 1) {
        printf("Invalid Roll Number! Must be an integer.\n");
        while(getchar() != '\n'); 
        fclose(fp);
        return;
    }
    
    
    while(getchar() != '\n'); 
    
    printf("Name: ");
    fgets(st.name, 50, stdin);
   
    st.name[strcspn(st.name, "\n")] = 0; 
    
    printf("Marks: ");
    if (scanf("%f", &st.marks) != 1) {
        printf("Invalid Marks! Must be a number.\n");
        while(getchar() != '\n'); 
        fclose(fp);
        return;
    }

   
    fwrite(&st, sizeof(st), 1, fp);
    fclose(fp);
    
    printf("\nRecord added successfully!\n");
}

void display_all() {
    FILE *fp;
    struct student st = {0};
    
    fp = fopen("student_data.bin", "rb");
    if(fp == NULL) {
        printf("\nFile is empty or not found!\n");
        return;
    }

    printf("\n*** All Students ***\n");
    printf("Roll No\t\tName\t\tMarks\n");
    printf("--------------------------------------------------\n");
    
    
    while(fread(&st, sizeof(st), 1, fp) == 1) {
        printf("%lld\t\t%s\t\t%.2f\n", st.rno, st.name, st.marks);
    }
    
    fclose(fp);
}

void search_student() {
    FILE *fp;
    struct student st = {0};
    long long int roll_search;
    int flag = 0; 
    
    fp = fopen("student_data.bin", "rb");
    if(fp == NULL) {
        printf("\nNo data to search!\n");
        return;
    }

    printf("\nEnter roll no to search: ");
    if (scanf("%lld", &roll_search) != 1) {
        printf("Invalid input!\n");
        while(getchar() != '\n');
        fclose(fp);
        return;
    }

    while(fread(&st, sizeof(st), 1, fp) == 1) {
        if(st.rno == roll_search) {
            printf("\nRecord Found!\n");
            printf("Name: %s\n", st.name);
            printf("Marks: %.2f\n", st.marks);
            flag = 1;
            break;
        }
    }

    if(flag == 0) {
        printf("\nStudent not found in records.\n");
    }
    
    fclose(fp);
}

void delete_student() {
    FILE *fp1, *fp2;
    struct student st = {0};
    long long int roll_del;
    int flag = 0;
    
    fp1 = fopen("student_data.bin", "rb");
    fp2 = fopen("temp.bin", "wb");
    
    if(fp1 == NULL) {
        printf("\nNo data available!\n");
        return;
    }

    printf("\nEnter roll no to delete: ");
    if (scanf("%lld", &roll_del) != 1) {
        printf("Invalid input!\n");
        while(getchar() != '\n');
        fclose(fp1);
        fclose(fp2);
        remove("temp.bin");
        return;
    }

    while(fread(&st, sizeof(st), 1, fp1) == 1) {
        
        if(st.rno != roll_del) {
            fwrite(&st, sizeof(st), 1, fp2);
        } else {
            flag = 1;
        }
    }

    fclose(fp1);
    fclose(fp2);

    remove("student_data.bin");
    rename("temp.bin", "student_data.bin");

    if(flag == 1) {
        printf("\nRecord deleted!\n");
    } else {
        printf("\nRoll no not found.\n");
    }
}
