#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person {
    char name[50];
    int age;
    struct Person *father;
    struct Person *mother;
} Person;

Person* create_person(const char *name, int age)
{
    Person *person = malloc(sizeof(Person));
    if (person == NULL)
    {
        return NULL;
    }

    strcpy(person->name, name);
    person->age = age;
    person->father = NULL;
    person->mother = NULL;
    return person;
}
   
void read_person_info(const char *role, char *name_out, int *age_out)
{
    while (1)
{
    printf("Enter name of %s: ", role);
    fgets(name_out, 50, stdin);
    name_out[strcspn(name_out, "\n")] = '\0';

    if (strlen(name_out) == 0)
    {
        printf("Name cannot be empty, Please enter again.\n");
        continue;
    }

    printf("Enter age of %s: ", role);
    if (scanf("%d", age_out) != 1)
    {
        printf("Invalid age, Enter a number.\n");
        continue;
    }
    if (*age_out < 0)
    {
        printf("Age cannot be negative.\n");
        continue;
    }
    getchar(); 
    break;
}
}

void link_parents(Person *child, Person *father, Person *mother)
{
    child->father = father;
    child->mother = mother;
}

void print_family_relationships(const Person *me)
{
    printf("\n=== FAMILY TREE RELATIONSHIPS ===\n");

    printf("\n1. YOURSELF:\n");
    printf("   Name: %s | Age: %d\n", me->name, me->age);

    printf("\n2. PARENTS:\n");
    printf("   Father: %s | Age: %d\n",
           me->father->name, me->father->age);

    printf("   Mother: %s | Age: %d\n",
           me->mother->name, me->mother->age);

    printf("\n3. PATERNAL GRANDPARENTS:\n");
    printf("   Grandfather: %s | Age: %d\n",
           me->father->father->name,
           me->father->father->age);

    printf("   Grandmother: %s | Age: %d\n",
           me->father->mother->name,
           me->father->mother->age);

    printf("\n4. MATERNAL GRANDPARENTS:\n");
    printf("   Grandfather: %s | Age: %d\n",
           me->mother->father->name,
           me->mother->father->age);

    printf("   Grandmother: %s | Age: %d\n",
           me->mother->mother->name,
           me->mother->mother->age);
}

void free_family_tree(Person *people[], int count)
{
    for (int i = 0; i < count; i++)
    {
        free(people[i]);
    }
} 

   int main(void)
{
    char name[50];
    int age;

    Person *paternal_grandfather;
    Person *paternal_grandmother;
    Person *maternal_grandfather;
    Person *maternal_grandmother;
    Person *father;
    Person *mother;
    Person *me;

    read_person_info("Paternal Grandfather", name, &age);
    paternal_grandfather = create_person(name, age);
    
    read_person_info("Paternal Grandmother", name, &age);
    paternal_grandmother = create_person(name, age);

    read_person_info("Maternal Grandfather", name, &age);
    maternal_grandfather = create_person(name, age);

    read_person_info("Maternal Grandmother", name, &age);
    maternal_grandmother = create_person(name, age);

    read_person_info("Father", name, &age);
    father = create_person(name, age);

    read_person_info("Mother", name, &age);
    mother = create_person(name, age);

    read_person_info("Yourself", name, &age);
    me = create_person(name, age);

    printf("All 7 family members name and age entered\n");

    link_parents(father, paternal_grandfather, paternal_grandmother);
    link_parents(mother, maternal_grandfather, maternal_grandmother);
    link_parents(me, father, mother);
    
    print_family_relationships(me);

    Person *people[] = {
    paternal_grandfather,
    paternal_grandmother,
    maternal_grandfather,
    maternal_grandmother,
    father,
    mother,
    me
};

    free_family_tree(people, 7);
    printf("Memory cleanup completed");
    return 0;
}
   

