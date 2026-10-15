#include <stdio.h>

struct Student
{
    int rollNo;
    char name[30];
    float marks;
};

int main()
{
    struct Student s;

    printf("Enter Roll No: ");
    scanf("%d", &s.rollNo);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    printf("\n----- Student Details -----\n");
    printf("Roll No : %d\n", s.rollNo);
    printf("Name    : %s\n", s.name);
    printf("Marks   : %.2f\n", s.marks);

    return 0;
}