
/* Assignment 3, Covid-19 social distancing effect simulation
 * The main aim of this assigment is getting familiar with dynamic arrays and heap management. 
 *  
 *  Please write your name and Student ID as comment below.
 *  Name and Surname:               Student ID:
 */



#include <stdio.h>
#include <stdlib.h>

int totalInfections=0;
int totalDeathCount=0;
int totalRecoveredCases=0;
int maxActiveCases=0;
int cycleCount=0;

typedef struct person{

int isInfected;

int isAlive;
int inCycle;

}person;

person createPerson(){

person x;

x.isInfected=0;
x.isAlive=1;
x.inCycle=0;
return x;

}
int probabilityInfection(person a, int percent){

if(a.isInfected==1){
return 1;
}
else {
if((rand()%100)<percent) {
totalInfections++;
return 1;
}
else{
return 0;  
}
}
}
int probabilityDeath( int percent){
if((rand()%100)<percent){
totalDeathCount++;
 return 1;
}
else return 0;


}
person **createWorld(int worldSize,int seed){
int i;
person   **personMatrix;
personMatrix = calloc(worldSize,sizeof(person *));
for (i=0; i<worldSize; ++i) personMatrix[i] = calloc(worldSize,sizeof(person));


int j;
srand(seed);
for(i=0;i<worldSize;i++){
	
   for(j=0;j<worldSize;j++){
personMatrix[i][j]=createPerson();
}

}
int a;
int b;	
for (i=0;i<(worldSize*worldSize)/20;i++){
a=rand()%worldSize;
b=rand()%worldSize;
personMatrix[a][b].isInfected=1;
personMatrix[a][b].inCycle=1;
totalInfections++;
}

	return personMatrix;

}
void cycle(person **personMatrix,int socialDistance,int worldSize,int seed){
srand(seed);

int i;
int j;
for(i=0;i<worldSize;i++){

   for(j=0;j<worldSize;j++){
	if(personMatrix[i][j].isInfected==1&&personMatrix[i][j].inCycle!=0){
	        if(j>0)personMatrix[i][j-1].isInfected=probabilityInfection(personMatrix[i][j-1],100-socialDistance);
	        if(i>0)personMatrix[i-1][j].isInfected=probabilityInfection(personMatrix[i-1][j],100-socialDistance);
	        if(j<worldSize-1)personMatrix[i][j+1].isInfected=probabilityInfection(personMatrix[i][j+1],100-socialDistance);
	        if(i<worldSize-1)personMatrix[i+1][j].isInfected=probabilityInfection(personMatrix[i+1][j],100-socialDistance);
	        if(i>0&&j>0)personMatrix[i-1][j-1].isInfected=probabilityInfection(personMatrix[i-1][j-1],100-socialDistance);
	        if(j<worldSize-1&&i<worldSize-1)personMatrix[i+1][j+1].isInfected=probabilityInfection(personMatrix[i+1][j+1],100-socialDistance);
	        if(j>0&&i<worldSize-1)personMatrix[i+1][j-1].isInfected=probabilityInfection(personMatrix[i+1][j-1],100-socialDistance);
	        if(j<worldSize-1&&i>0)personMatrix[i-1][j+1].isInfected=probabilityInfection(personMatrix[i-1][j+1],100-socialDistance);	

}
	
}
}


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
world=createWorld(10,7);
int i=0;
int j=0;
for ( i=0;i<10;i++){
printf("\n");
for(j=0;j<10;j++){
printf("%d",world[i][j].isInfected);
}
}
printf("%d",totalInfections);

cycle(world,90,10,7);
for ( i=0;i<10;i++){
printf("\n");
for(j=0;j<10;j++){
printf("%d",world[i][j].isInfected);
}
}
printf("%d",totalInfections);
}

