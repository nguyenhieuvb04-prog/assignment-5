#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char firstname[50];
    char lastname[50];
    int age;
} Student;

// So sánh theo firstname
int cmp_firstname(const void *a, const void *b) {
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;
    return strcmp(s1->firstname, s2->firstname);
}

// So sánh theo lastname
int cmp_lastname(const void *a, const void *b) {
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;
    return strcmp(s1->lastname, s2->lastname);
}

// apply function pointer
void apply(Student *arr, int n, void (*func)(Student *)) {
    for (int i = 0; i < n; i++) {
        func(&arr[i]);
    }
}

// in nếu age > 20
void isolder(Student *s) {
    if (s->age > 20) {
        printf("%s %s %d\n", s->firstname, s->lastname, s->age);
    }
}

int main() {
    Student arr[] = {
        {"An", "Nguyen", 19},
        {"Binh", "Tran", 22},
        {"Cuong", "Le", 21},
        {"Dung", "Pham", 18}
    };

    int n = sizeof(arr)/sizeof(arr[0]);

    // Sort theo firstname
    qsort(arr, n, sizeof(Student), cmp_firstname);
    printf("Sort by firstname:\n");
    for(int i = 0; i < n; i++) {
        printf("%s %s %d\n", arr[i].firstname, arr[i].lastname, arr[i].age);
    }

    // Sort theo lastname
    qsort(arr, n, sizeof(Student), cmp_lastname);
    printf("\nSort by lastname:\n");
    for(int i = 0; i < n; i++) {
        printf("%s %s %d\n", arr[i].firstname, arr[i].lastname, arr[i].age);
    }

    // Apply
    printf("\nAge > 20:\n");
    apply(arr, n, isolder);

    return 0;
}