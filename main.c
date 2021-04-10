/* Assignment 3, Covid-19 social distancing effect simulation
 * The main aim of this assigment is getting familiar with dynamic arrays and heap management. 
 *  
 *  Please write your name and Student ID as comment below.
 *  Name and Surname:               Student ID:
 */



#include <stdio.h>
#include <stdlib.h>

typedef struct person{

int isInfected;

int isAlive;


}person;

person createPerson(int isInfected){

person x;

x.isInfected=isInfected;
x.isAlive=1;
return x;

}

person **createWorld(int worldSize,int seed){
int i;
person   **personMatrix;
personMatrix = calloc(worldSize,sizeof(person *));
for (i=0; i<worldSize; ++i)
   personMatrix[i] = calloc(worldSize,sizeof(person));


int j;
int random;
srand(seed);
for(i=0;i<worldSize;i++){
	
   for(j=0;j<worldSize;j++){

random=rand()%20;
if(!random){
personMatrix[i][j]=createPerson(1);
}
else{
personMatrix[i][j]=createPerson(0);
}
}

}	
	return personMatrix;

}


int main( int argc, char *argv[] )  {

   printf("Program name %s\n", argv[0]);
 
   if( argc == 5 ) {
	printf("The first argument supplied is %d\n", atoi(argv[1]));
	printf("The second argument supplied is %d\n", atoi(argv[2]));
  	printf("The third argument supplied is %d\n", atoi(argv[3]));
	printf("The forth argument supplied is %d\n", atoi(argv[4]));
   }
   else if( argc > 5 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("Expected 4 arguments but only %d argument passed.\n", argc-1);
   }
      

person **world;
world=createWorld(10,9);
int i=0;
int j=0;
for ( i=0;i<10;i++){
printf("\n");
for(j=0;j<10;j++){
printf("%d",world[i][j].isInfected);
}
}


}

