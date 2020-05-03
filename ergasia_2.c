#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rectangle read_number();
void menu(struct rectangle *,int );
int find_rectangle(int ,struct rectangle *,char *,int);
//δ ερώτημα
int intersection(struct rectangle *,struct rectangle *);

struct point 
{
	float x;
	float y;
};

struct rectangle 
{
	struct point top_left;
	struct point bottom_right;
	char color[10];
};

//-----main-----//
int main(int argc, int **argv)
{
	system("chcp 1253");
	int N;
	struct rectangle *data_file;
	read_number();
    return 0;
}

struct rectangle read_number()  // Reading first line and saving the number to a variable
{
    int N,i,len;
	char fileText[100];
	struct rectangle *data_file;
	float v;
	
    FILE *data;
    if((data=fopen("data.txt","r"))==NULL)
    {
    	printf("Λάθος κατα το άνοιγμα του αρχείου");
    	exit(1);
	}

    fscanf(data,"%s %d",fileText,&N);
	data_file=(struct rectangle*)malloc(N*sizeof(struct rectangle));
	for(i=0;i<N;++i)
	{
		
			fscanf(data,"%s",&(data_file+i)->top_left.x);
			fscanf(data,"%s",&(data_file+i)->top_left.y);
			fscanf(data,"%s",&(data_file+i)->bottom_right.x);
			fscanf(data,"%s",&(data_file+i)->bottom_right.y);
			fscanf(data,"%s",&(data_file+i)->color);
		/*	printf(" %s",&(data_file+0+i*5)->top_left.x);
			printf(" %s",&(data_file+1+i*5)->top_left.y);
			printf(" %s",&(data_file+2+i*5)->bottom_right.x);
			printf(" %s",&(data_file+3+i*5)->bottom_right.y);
			printf(" %s",&(data_file+4+i*5)->color);
			printf("\n");  
			v=atof(&(data_file+0+i*5)->top_left);    */
	}
	fclose(data);
	menu(data_file,N);                                     							//kalesma menu
    return *data_file;
}

void menu(struct rectangle *data_file,int N)
{
	char colour[10],answer[5],stop[5];
	int choice,k,new_i,first,second;
	struct rectangle *point;
	do{
		new_i=0;
	//	system("cls");
		do{
			printf("\n=====Επιλωγή χρώματος=====\n1.red\n2.green \n3.blue\n");
			scanf("%s",colour);
			fflush(stdin);
			if(strcmp(colour,"red")!=0 && strcmp(colour,"green")!=0 && strcmp(colour,"blue")!=0)
			{
				printf("Λάθος εισαγωγή στοιχείων\n");
			}
		}while(strcmp(colour,"red")!=0 && strcmp(colour,"green")!=0 &&strcmp(colour,"blue")!=0);
		
		do{
			printf("\n=====Επιλογή ενέργειας=====\n1.Τομή \n2.Μέγιστο Εμβαδό \n3.Μέγιστη Περίμετρος\n");
			scanf("%d",&choice);
		}while(choice!=1 && choice!=2 && choice!=3);
		printf("Πληκτρολογήστε('STOP') για να σταματήσετε ή πατήστε 1 για συνέχεια\n");
		scanf("%s",answer);
		if(strcmp(answer,"STOP")==0) exit(2);
		
		first=(find_rectangle(new_i,data_file,colour,N)); 				//kalesma find_rectangle
		point[first].top_left.x=(data_file+first)->top_left.x;
		printf("%d\n",first);
		first=first+1;
		second=(find_rectangle(first,data_file,colour,N));   
		point[second].top_left.x=(data_file+second)->top_left.x;                							
		printf("%d",second);
	//	switch(choice)
	//	{
	//		case '1':	
	//	}
		k=strcmp(answer,"STOP");
	}while(k!=0);
}

int find_rectangle(int new_i, struct rectangle *data_file,char *colour,int N)
{
    
    int i;
    for (i=new_i;i<N;i++)
    {
        
        if (strcmp((data_file+i)->color,colour)==0)
        {
            new_i=i;
            break;
        }
    }
    return new_i;
}
