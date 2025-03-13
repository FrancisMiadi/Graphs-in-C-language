// Name:Francis Miadi
// ID: 1210100
// section:4



#include <stdio.h>
#include <stdlib.h>
#include<string.h>
// the tree structure
struct student{
char Name[50];
int ID;
char City[25];
int cID;
char Date[10];
struct student* Left;
struct student* Right;

};
typedef struct student* Student;
Student Insert(int id , Student S);
Student Find(int id,Student S);
Student MakeEmpty(Student S );
Student Delete(int id, Student S);
Student FindMin(Student S );
Student InsertSN(char[], char[] ,int, Student S);
Student ListST(Student s1 ,Student);
void printTree(Student S);
void saveToFile(Student S,FILE * out);
Student InsertFromFile(int id , Student S,FILE*in);
Student openFile(Student S);
int sizeOfFile();
void printForCity(Student s,char[]);
void printMates(Student s,int cID);

int main()
{
       Student S =NULL;

S=openFile(S);// opens the file , if it contains data then it will load it

   int key ;
  do{
    printf("\nplease choose an option :-\n");
    printf("1- Insert a student\n");
    printf("2- Find a student and update his data(the update is optional)\n");
    printf("3- List all students by names\n");
    printf("4- List all students from a specific city\n");
    printf("5- List all classes with it's students\n");
    printf("6- Delete a student\n");
    printf("7- save data in a file\n");
    printf("8- Exit\n");
        scanf("%d",&key);

    switch(key){
        case 1: {
                int id;
                printf("Enter the id of the new Student\n");
                scanf("%d",&id);
                S = Insert(id,S);
                break;
        }

        case 2: {
                int Sid,op;
                Student res=NULL;
                printf("Enter the id of the student that you want to search for \n");
                scanf("%d",&Sid);
                res =Find(Sid,S);// check if the student id exists
                if(res){
                  printf("\nStudent Found and his data is:\n");
                  printf("ID : %d\n",res->ID);
                  printf("Name : %s\n",res->Name);
                  printf("Address : %s\n",res->City);
                  printf("Class id : %d\n",res->cID);
                  printf("Date of Enrollment : %s\n",res->Date);
                  printf("\nDO YOU WANT TO UPDATE ANY OF HIS INFO?,pick an option\n");
                  printf("1-Yes\n");
                  printf("2-No\n");
                  scanf("%d",&op) ;
                  if(op==1){
                  int stopflag=1,updt;
                  while(stopflag==1) {
                    printf("\nthe student's  data is\n");
                    printf("ID : %d\n",res->ID);
                  printf("Name : %s\n",res->Name);
                  printf("Address : %s\n",res->City);
                  printf("Class id : %d\n",res->cID);
                  printf("Date of Enrollment : %s\n",res->Date);
                    printf("\nchoose what you want to update\n");
                    printf("1-ID\n");
                    printf("2-Name\n");
                    printf("3-Class ID\n");
                    printf("4-Address\n");
                    printf("5-date of enrollment\n");
                    printf("6-exit updating");
                    scanf("%d",&updt);
                    switch(updt){//update cases
                    case 1:{
                        int id;
                    printf("Enter the new ID\n");
                    scanf("%d",&id);
                    if(!Find(id,S))
                       (res->ID)=id;
                       else printf("The id number is for another student\n");
                        break;
                    }
                    case 2:{
                    printf("Enter the new Name\n");
                    scanf("%s",res->Name);break;
                    }
                    case 3:{
                    printf("Enter the new class ID\n");
                    scanf("%d",&(res->cID));break;
                    }
                    case 4:{
                     printf("Enter the new city Name\n");
                    scanf("%s",res->City);break;
                    }
                    case 5:{
                     printf("Enter the new date of enrollment\n");
                    scanf("%s",res->Date);break;
                    }
                    case 6:{ stopflag=0;
                    break;
                    }
                    default:printf("no such option!");


                  }

                  }
                }
                    }
                    else printf("Student does not exist in our school\n");
                    break;
                    }

                    case 3:{
                        if(S==NULL)
                            printf("there is no students in our system!\n");
                        else{
                Student names =NULL;
                  names=  ListST(S,names);// fill a list with student names
                  printTree(names);
                  }
                break;

                    }
                    case 4:{
                    char Cname[25];
                    Student Names =NULL;
                    printf("Enter a name of the city \n");
                    scanf("%s",Cname);
                    Names=ListST(S,Names);//fill the list so we can search for students from the same city
                    printForCity(Names,Cname);
                    break;
                    }

                    case 5:{
                        if(S==NULL)
                            printf("there is no students in our system!\n");
                            else{
                    Student mates = NULL;
                    for(int i=1;i<13;i++){// go across the 12 classes and get the class mates
                         mates=ListST(S,mates);
                         printMates(mates,i);

                   mates = MakeEmpty(mates);
                                        }

                            }
                    break;

                    }
                    case 6:{
                    int ID;
                    printf("Enter the student's id that you want to erase his data\n");
                    scanf("%d",&ID);
                    S=Delete(ID,S);
                    break;
                    }
                    case 7:{
                    FILE *out;
                    out =fopen("students.data","a");
                    if(out!=NULL){
                    saveToFile(S,out);
                    printf("The data saved successfully in the file\n");
                    printf("And it is saved in the next format\n");
                    printf("Each student's data occupies five lines in the file\n");
                    printf("First line is for the ID\n");
                    printf("Second line is for the Name\n");
                    printf("Third line is for the city name\n");
                    printf("Forth line is for the class ID\n");
                    printf("Fifth line is for the Date Of Enrollment\n");
                    }
                    else{
                        printf("ERROR\n");
                    }
                    break;
                    }
                    case 8:{
                    key =0;
                    break;
                    }
                    default: printf("no such choice!");
    }


   }  while(key!=0);


    return 0;
}
Student MakeEmpty(Student S ){
if( S != NULL ){

MakeEmpty( S->Left );    // Recursively make the left subtree empty


MakeEmpty( S->Right );      // Recursively make the right subtree empty

free( S );
}

return NULL;
}
Student Find(int id,Student S){
if(S==NULL)
    return NULL;// if not found ,return null
else if(id<S->ID)// if the id that we are searching for is less than the current id , go to the left subtree
    return Find(id,S->Left);
else if(id>S->ID)// if the id that we are searching for is greater than the current id , go to the right subtree
    return Find(id,S->Right);
else return S;// when found return s
}
// a function to insert data to a binary search tree , ordered base on the id
Student Insert(int id , Student S){

if(S==NULL){
    S = (struct student*)malloc(sizeof(struct student) );// here we create the node that will handle the data

    if(S==NULL)
        printf("Out Of Space!");
    else{
        S->ID=id;
        S->Left=S->Right=NULL;
        printf("Enter:");// we take the nodes from the user
        printf("\n 1- the Student's Name: ");
        printf("\nNOTE:ENTER It IN THE NEXT FORMAT ( FirstName-Last-Name )");
        scanf("%s",S->Name);
        printf("\n 2- his home address(city name): ");scanf("%s",S->City);
        printf("\n 3- id of his class: ");scanf("%d",&(S->cID));
        printf("\n 4- Date of Enrollment: ");scanf("%s",S->Date);


    }
}
 // If the value is less than the current node's id, recurse on the left subtree
else if(id < S->ID){

    S->Left=Insert(id,S->Left);
}
 // If the value is greater than the current node's id, recurse on the right subtree
else if (id> S->ID){

    S->Right = Insert(id,S->Right);
}
 return S;

}
Student Delete(int id, Student S){
    Student temp;

    if (S == NULL)
    {
        printf("No such ID");
    }
    else if (id < S->ID) /* Go left */
    {
        S->Left = Delete(id, S->Left);
    }
    else if (id > S->ID) /* Go right */
    {
        S->Right = Delete(id, S->Right);
    }
    else /* Found element to be deleted */
    {
        if (S->Left && S->Right) /* Two children */
        {
            /* Replace with the smallest in the right subtree */
            temp = FindMin(S->Right);
            S->ID = temp->ID;
            S->Right = Delete(S->ID, S->Right);
        }
        else /* One or zero children */
        {
            temp = S;
            if (S->Left == NULL) /* Also handles 0 children */
            {
                S = S->Right;
            }
            else if (S->Right == NULL)
            {
                S = S->Left;
            }
            free(temp);
        }
    }

    return S;
}
// keep going through the left subtrees until we reach the smaller value
Student FindMin(Student S ){
if( S == NULL)
return NULL;
else if( S-> Left == NULL)
return S;
else return FindMin( S->Left );
}
// a function that inserts strings to a tree
// and give each node student name ,city name and class id
// the filled tree will be a tree that is ordered base on the students name
Student InsertSN(char name[] ,char city[],int cId, Student S){
if(S==NULL){
    S = (struct student*)malloc(sizeof(struct student) );

    if(S==NULL)
        printf("Out Of Space!");
    else{
        strcpy(S->Name,name); // it assigns the received data to the tree nodes
    strcpy(S->City,city);
    S->cID=cId;
        S->Left=S->Right=NULL;
    }
}
 // If the name is less than the current node's name in the order, recurse on the left subtree

else if(strcmp(name,S->Name)<0){
    S->Left=InsertSN(name,city,cId,S->Left);
}
 // If the name is greater than the current node's name in the order, recurse on the right subtree

else if (strcmp(name,S->Name)>=0){

    S->Right = InsertSN(name,city,cId,S->Right);

}
 return S;

}
// a function to fill a tree ordered base on the students name
Student ListST(Student s1, Student Names ){
int num=0;
if (s1 == NULL) {
        return NULL;
    }
Names = InsertSN(s1->Name,s1->City,s1->cID,Names);
ListST(s1->Left,Names);
ListST(s1->Right,Names);
return Names;
}
// a function that goes in traversal in-order through a tree and print the name of the students
void printTree(Student s) {
    if (s == NULL) {
        return;
    }
    printTree(s->Left);
    printf("%s\n", s->Name);
    printTree(s->Right);

}
// a function in which we go through the tree by recursion and save it's data in the file
void saveToFile(Student S,FILE * out){

 if (S == NULL) {
        return;
    }
fprintf(out,"\n%d\n",S->ID);

fprintf(out,"%s\n",S->Name);
fprintf(out,"%s\n",S->City);
fprintf(out,"%d\n",S->cID);
fprintf(out,"%s\n",S->Date);
    saveToFile(S->Left,out);


    saveToFile(S->Right,out);


}
// a function that check if the file contains data
// if yes we load it and use it's data
Student openFile(Student S){
FILE *in;
in=fopen("students.data","r");
int id,status,cId,i=0;
status=fscanf(in,"%d",&id);

if(status==EOF){// if it does not contain data,return null

return NULL;
}
    S=InsertFromFile(id,S,in);

while(i<((sizeOfFile()/5)-1)){// divided by 5 because we have 5 data fields , so we have 5 times lines than the number of ids
        //and minus 1 because we already scanned an id out of the loop
    fscanf(in,"%d",&id);
        S=InsertFromFile(id,S,in);// we add the id to the tree
i++;

}
fclose(in);
return S;
}

Student InsertFromFile(int id , Student S,FILE*in){
if(S==NULL){
    S = (struct student*)malloc(sizeof(struct student) );

    if(S==NULL)
        printf("Out Of Space!");
    else{
        S->ID=id;
        S->Left=S->Right=NULL;
       fscanf(in,"%s",S->Name);
        fscanf(in,"%s",S->City);
fscanf(in,"%d",&(S->cID));
            fscanf(in,"%s",S->Date);
    }
}
 // If the value is less than the current node's id, recurse on the left subtree
else if(id < S->ID){

    S->Left=InsertFromFile(id,S->Left,in);
}
 // If the value is greater than the current node's id, recurse on the right subtree
else if (id> S->ID){

    S->Right = InsertFromFile(id,S->Right,in);
}
 return S;

}
int sizeOfFile(){ // a function for calculation the size of the file
    char x;         // in other words the number of numbers in the file
    int count=0;
FILE *IN;
IN=fopen("students.data","r");                 //  checking the file validity steps
if(IN == NULL){
    printf("ERROR-can't open the file");
    exit(1);
}
while((x=fgetc(IN))!=EOF){//counting until reaching the end of file
    if(x=='\n')
        count++;
}
fclose(IN);

return count;

}
// a function that prints the student from a specific city
// it goes recursively through the tree that filled base on the students names (from the left to the right)
void printForCity(Student s,char name[]) {
    if (s == NULL) {
        return;
    }
    printForCity(s->Left,name);
if(strcmp(name,s->City)==0){
    printf("%s\n", s->Name);
}
    printForCity(s->Right,name);
}
// a function that prints the students from each class
// it goes recursively through the tree that filled base on the students names (from the left to the right)

void printMates(Student s,int cID){
if (s == NULL) {
        return;
    }
    printMates(s->Left,cID);
if(cID==s->cID){
    printf("\n%s is from CLASS %d\n", s->Name,cID);
}
    printMates(s->Right,cID);
}


















