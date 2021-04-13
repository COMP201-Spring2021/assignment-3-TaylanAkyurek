
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
int isImmune;
}person;

person createPerson(){

person x;

x.isInfected=0;
x.isAlive=1;
x.inCycle=0;
x.isImmune=0;
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
 return 0;
}
else return 1;


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
if(personMatrix[a][b].isInfected==0)personMatrix[a][b].isInfected=1;
else{
i--;
}
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
	if(personMatrix[i][j].isAlive==1&&personMatrix[i][j].isInfected==1&&personMatrix[i][j].inCycle!=0){
	        if(j>0&&personMatrix[i][j-1].isImmune==0)personMatrix[i][j-1].isInfected=probabilityInfection(personMatrix[i][j-1],100-socialDistance);
	        if(i>0&&personMatrix[i-1][j].isImmune==0)personMatrix[i-1][j].isInfected=probabilityInfection(personMatrix[i-1][j],100-socialDistance);
	        if(j<worldSize-1&&personMatrix[i][j+1].isImmune==0)personMatrix[i][j+1].isInfected=probabilityInfection(personMatrix[i][j+1],100-socialDistance);
	        if(i<worldSize-1&&personMatrix[i+1][j].isImmune==0)personMatrix[i+1][j].isInfected=probabilityInfection(personMatrix[i+1][j],100-socialDistance);
	        if(i>0&&j>0&&personMatrix[i-1][j-1].isImmune==0)personMatrix[i-1][j-1].isInfected=probabilityInfection(personMatrix[i-1][j-1],100-socialDistance);
	        if(j<worldSize-1&&i<worldSize-1&&personMatrix[i+1][j+1].isImmune==0)personMatrix[i+1][j+1].isInfected=probabilityInfection(personMatrix[i+1][j+1],100-socialDistance);
	        if(j>0&&i<worldSize-1&&personMatrix[i+1][j-1].isImmune==0)personMatrix[i+1][j-1].isInfected=probabilityInfection(personMatrix[i+1][j-1],100-socialDistance);
	        if(j<worldSize-1&&i>0&&personMatrix[i-1][j+1].isImmune==0)personMatrix[i-1][j+1].isInfected=probabilityInfection(personMatrix[i-1][j+1],100-socialDistance);	

}
	
}
}
int caseNumber=0;
for(i=0;i<worldSize;i++){

   for(j=0;j<worldSize;j++){
 if(personMatrix[i][j].isInfected==1){
caseNumber++;
personMatrix[i][j].inCycle++;
if(personMatrix[i][j].inCycle==4){
personMatrix[i][j].isAlive=probabilityDeath(40);
if(personMatrix[i][j].isAlive==1){
personMatrix[i][j].isInfected=0;
personMatrix[i][j].isImmune=1;
totalRecoveredCases++;
}
else{
personMatrix[i][j].isInfected=0;
personMatrix[i][j].isImmune=1;
}
}
}
}
}
if(caseNumber>maxActiveCases)maxActiveCases=caseNumber;
}
void printArray(person **personMatrix,int worldSize){
int i;
int j;
for ( i=0;i<worldSize;i++){
printf("\n");
for(j=0;j<worldSize;j++){
printf("%d",personMatrix[i][j].isInfected);
}
}
printf("\n");
for ( i=0;i<worldSize;i++){
printf("\n");
for(j=0;j<worldSize;j++){
printf("%d",personMatrix[i][j].isAlive);
}
}
printf("\n");
for ( i=0;i<worldSize;i++){
printf("\n");
for(j=0;j<worldSize;j++){
printf("%d",personMatrix[i][j].isImmune);
}
}
printf("\n");
for ( i=0;i<worldSize;i++){
printf("\n");
for(j=0;j<worldSize;j++){
printf("%d",personMatrix[i][j].inCycle);
}
}
printf("\n %d %d %d %d",totalInfections,totalDeathCount,totalRecoveredCases,maxActiveCases);
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
int a=atoi(argv[1]); 
int b=atoi(argv[2]);
int c=atoi(argv[3]);
int d=atoi(argv[4]);
   

person **world;
world=createWorld(a,d);

FILE * fPointer;
fPointer=fopen("CYCLENUM.txt","w");
int i;
int j;
int k;
for(k=0;k<c;k++){
fprintf(fPointer,"\n");
for ( i=0;i<a;i++){
fprintf(fPointer,"\n");
for(j=0;j<a;j++){
if(world[i][j].isAlive==1){
fprintf(fPointer,"%d ",world[i][j].isInfected);
}
else{
fprintf(fPointer,"* ");
}
}
}
cycle(world,b,a,d);
fprintf(fPointer,"\n");
}
fprintf(fPointer,"\n %d %d %d %d",totalInfections,totalDeathCount,totalRecoveredCases,maxActiveCases);

fclose(fPointer);
}


