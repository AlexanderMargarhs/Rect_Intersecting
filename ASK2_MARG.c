#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rectangle read_number();
void MENU(struct rectangle *,int );
int find_rectangle(int ,struct rectangle *,char *,int);
float MAX(float ,float );
float MIN(float ,float );
struct rectangle save(struct rectangle *,struct rectangle *,int);
struct rectangle intersection(struct rectangle *,struct rectangle *);
int max_area(struct rectangle *,char *);
int max_perim(struct rectangle *,char *);

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

int main() 
{
	system("chcp 1253"); //For the messages
	struct rectangle *File_Data;
	read_number();
    return 0;
}

struct rectangle read_number()  // Reading first line and saving the number to a variable
{
    int N,i,j;
	char Temp_Text[100],*TEMP,Dump[7];
	const char Tr[2] = " ";
	struct rectangle *File_Data;
	float val;
    FILE *fp;
    
    if((fp=fopen("data.txt","r"))==NULL)
    {
    	printf("Error!Failed to open the file.");
    	exit(1);
	}
	fgets(Temp_Text,100,fp);
	TEMP=strtok(Temp_Text,Tr); 
	TEMP=strtok(NULL,Tr);	
	N=atoi(TEMP); //Save the number of rectangles to the variable N
	File_Data=(struct rectangle*)malloc(N*sizeof(struct rectangle)); //Get the exact size of the array 
	
	for(i=0;i<N;i++)
	{
		fgets(Temp_Text,100,fp);
		TEMP=strtok(Temp_Text,Tr);	//Gets the top left x from the data file
		val=atof(TEMP);	//Change type to float
		(File_Data+i)->top_left.x=val; 
		TEMP=strtok(NULL,Tr);	//Gets the top left y from the data file
		val=atof(TEMP);
		(File_Data+i)->top_left.y=val;
		TEMP=strtok(NULL,Tr);	//Gets the bottom right x from the data file
		val=atof(TEMP);
		(File_Data+i)->bottom_right.x=val;
		TEMP=strtok(NULL,Tr);	//Gets the bottom right y from the data file
		val=atof(TEMP);
		(File_Data+i)->bottom_right.y=val;
		TEMP=strtok(NULL,Tr);	//Gets the color from the data file 
		strcpy(Dump,TEMP);
		Dump[strlen(Dump)-1]=0; //We delete \n
	strcpy((File_Data+i)->color,Dump);
	}
	fclose(fp);
	MENU(File_Data,N);
	return *File_Data;
}


void MENU(struct rectangle *File_Data,int N) //The MENU prints the messages and the choices of the User ,with error messages if he types something wrong
{
	char New_Color[10],Ans[5];
	int Choice,result,k,New_i,First_Rect,Next_Rect,i;
	float Max;
	struct rectangle *Rect1,*Rect2;
	Rect1=(struct rectangle*)malloc(sizeof(struct rectangle));
	Rect2=(struct rectangle*)malloc(sizeof(struct rectangle));
	k=1;
	do
	{
		New_i=0;
		do
		{
			printf("\n業嵩OLOR業愧n1)red\n2)blue\n3)green\nANSWER: ");
			scanf("%s",New_Color);
			fflush(stdin);
			if(strcmp(New_Color,"red")!=0 && strcmp(New_Color,"green")!=0 && strcmp(New_Color,"blue")!=0)
			{
				system("cls");
				printf("Wrong choice of color ,please write the color of your choice again\n");
			}
		}
		while(strcmp(New_Color,"red")!=0 && strcmp(New_Color,"green")!=0 &&strcmp(New_Color,"blue")!=0);
		do
		{
			printf("\n業幹UNCTIONS業愧nA)Intersection\nB)Max Area\nC)Max Perimeter\n'STOP' For Termination\nAnswer: ");
			scanf("%s",&Ans);
			fflush(stdin);
			system("cls");
			if (strcmp(Ans,"A")!=0 && strcmp(Ans,"B")!=0 && strcmp(Ans,"C")!=0 && strcmp(Ans,"STOP")!=0)
            {
                printf("Wrong choice of function,please type 'A','B','C' or 'STOP' \n");
            }
		}
		while(strcmp(Ans,"A")!=0 && strcmp(Ans,"B")!=0 && strcmp(Ans,"C")!=0 && strcmp(Ans,"STOP")!=0);
		First_Rect=(find_rectangle(New_i,File_Data,New_Color,N)); 
		Rect1[0]=save(&Rect1[0],File_Data,First_Rect);
		First_Rect=First_Rect+1;//So that the loop starts from the next rectangle
		Next_Rect=(find_rectangle(First_Rect,File_Data,New_Color,N));
		Rect2[0]=save(&Rect2[0],File_Data,Next_Rect);
		if(strcmp(Ans,"A")==0) 
		{
			Choice=1;
		}
		else if(strcmp(Ans,"B")==0) 
		{
			Choice=2;
		}
		else if(strcmp(Ans,"C")==0) 
		{
			Choice=3;
		}
		else 
		{
			Choice=4;
		}
		switch(Choice)
		{
			case 1:
					for(i=Next_Rect;i<N;i++)
					{
						intersection(&Rect1[0],&Rect2[0]);	
						if(Rect1[0].top_left.x==Rect1[0].bottom_right.x) //If they have the same value means that it is not a rectangle ,but, a straight line
						{
							printf("Empty Set(Intersection:0) between %d & %d rectangle\n",First_Rect,Next_Rect+1);
						}
						else
						{
							printf("Intersection:1 between %d & %d rectangle and the coordinates are\n",First_Rect,Next_Rect+1);
							printf("Top Left X=%.1f Top Left Y=%.1f Bottom Right X=%.1f Bottom Right Y=%.1f\n\n",Rect1[0].top_left.x, Rect1[0].top_left.y, Rect1[0].bottom_right.x, Rect1[0].bottom_right.y);
						}
						Next_Rect=find_rectangle(Next_Rect+1,File_Data,New_Color,N);
						Rect1[0]=save(&Rect1[0],File_Data,First_Rect-1); //Reset the data for the first Array
						Rect2[0]=save(&Rect2[0],File_Data,Next_Rect); //Save the new data for the next rectangle 
						if(Next_Rect==0) break;	 //Break in case there is no other rectangle
					}
					break;
			case 2:	result=max_area(File_Data,New_Color);
					printf ("The position of the rectangle with the max area is:%d\n",result+1);
					Max=((File_Data[result].bottom_right.x-File_Data[result].top_left.x)*(File_Data[result].top_left.y-File_Data[result].bottom_right.y));
					printf("The max area of that rectangle is:%.02f\n",Max);
					break;
			case 3:	result=max_perim(File_Data,New_Color);
					printf("The position of the rectangle with the max perimeter is:%d\n",result+1);
					Max=((File_Data[result].bottom_right.x-File_Data[result].top_left.x)+(File_Data[result].top_left.y-File_Data[result].bottom_right.y))*2;
					printf("The max perimeter of that rectangle is:%.02f\n",Max);
					break;	
			case 4: k=0; 
					break;
		}
	}
	while(k!=0);
	free(Rect1);
	free(Rect2);
	free(File_Data);
}


int find_rectangle(int New_i, struct rectangle *File_Data,char *New_Color,int N)//For finding the next rectangle of the chosen color
{
    int i;
    
  	for(i=New_i;i<N;i++)
	{
        if (strcmp(File_Data[i].color,New_Color)==0) return i;
	}
    return 0;
}


struct rectangle intersection(struct rectangle *First_Rect,struct rectangle *Next_Rect) //This is for Finding the InterSection between the two rectangles and fill the first Array with 0 if it is an Empty Set 
{																						//or Finds the coordinates of the intersection
	float MAX_X,MIN_X,MIN_Y,MAX_Y;
    if((First_Rect[0].top_left.x > Next_Rect[0].bottom_right.x || Next_Rect[0].top_left.x > First_Rect[0].bottom_right.x) || (First_Rect[0].top_left.y < Next_Rect[0].bottom_right.y || Next_Rect[0].top_left.y < First_Rect[0].bottom_right.y))
	{
		First_Rect[0].top_left.x=0; //We can't use the save function ,because we have to fill it with 0 
		First_Rect[0].top_left.y=0;
		First_Rect[0].bottom_right.x=0;
		First_Rect[0].bottom_right.y=0;
		return *First_Rect;
	}	
    MAX_X=MAX(First_Rect[0].top_left.x,Next_Rect[0].bottom_right.x);
    MIN_Y=MIN(Next_Rect[0].top_left.y,First_Rect[0].top_left.y);
    MIN_X=MIN(Next_Rect[0].bottom_right.x,First_Rect[0].bottom_right.x);
	MAX_Y=MAX(First_Rect[0].bottom_right.y,Next_Rect[0].bottom_right.y);
  	First_Rect[0].top_left.x=MAX_X;
  	First_Rect[0].top_left.y=MIN_Y;
  	First_Rect[0].bottom_right.x=MIN_X;
  	First_Rect[0].bottom_right.y=MAX_Y;
	return *First_Rect; 
}

struct rectangle save(struct rectangle *Rect, struct rectangle *File_Data, int point) //For Saving data so that the MENU function isn't clustered
{
		Rect[0].top_left.x=(File_Data+point)->top_left.x;
		Rect[0].top_left.y=(File_Data+point)->top_left.y;
		Rect[0].bottom_right.x=(File_Data+point)->bottom_right.x;
		Rect[0].bottom_right.y=(File_Data+point)->bottom_right.y;
		return *Rect;
}

float MAX(float var1,float var2) //This is for finding the MAX value from two variables 
{
	float MAX;
	if (var1>var2)	
	{
		MAX=var1;
	}
	else	
	{
		MAX=var2;
	}
	return MAX;
}

float MIN(float var1,float var2) //This is for finding the MIN value from two variables 
{
	float MIN;
	if (var1<var2)	
	{
		MIN=var1;
	}
	else	
	{
		MIN=var2;
	}
	return MIN;
}


int max_area(struct rectangle *File_Data,char *New_Color) //Find the Max Area put the j in the Max_j variable and change the Max_Area so that the if statement work
{
	int j,N,max_j;
	float Top_Left_X,Bottom_Right_X,Top_Left_Y,Bottom_Right_Y,Area,Max_Area;
	char Temp[50],Find_Color[100];
	FILE *Data;
	j=0;
	max_j=j;
	Max_Area=0;
	Data=fopen("data.txt","r");
	fscanf(Data,"%s %d",Temp,&N);
	fclose(Data);
	for (j=0;j<N;j++)
	{
			Top_Left_X=File_Data[j].top_left.x;
			Top_Left_Y=File_Data[j].top_left.y;
			Bottom_Right_X=File_Data[j].bottom_right.x;
			Bottom_Right_Y=File_Data[j].bottom_right.y;
			strcpy(Find_Color,(File_Data[j].color));
			if(strcmp(Find_Color,New_Color)==0)
			{
				Area=((Top_Left_Y - Bottom_Right_Y) * (Bottom_Right_X - Top_Left_X));
				if(Max_Area<Area)
				{
					Max_Area=Area;
					max_j=j;
				}
			}
	}
	return max_j;
}


int max_perim(struct rectangle *File_Data,char *New_Color) //Same as the Max Area ,but, we have a different type for the perimeter
{
	int j,N,max_j;
	float Top_Left_X,Bottom_Right_X,Top_Left_Y,Bottom_Right_Y,Perim,Max_Perim=0;
	char Temp[50],Find_Color[100];
	FILE *Data;
	j=0;
	max_j=j;
	Data=fopen("data.txt","r");
	fscanf(Data,"%s %d",Temp,&N);
	fclose(Data);
	for (j=0;j<N;j++)
	{
		Top_Left_X=File_Data[j].top_left.x;
		Top_Left_Y=File_Data[j].top_left.y;
		Bottom_Right_X=File_Data[j].bottom_right.x;
		Bottom_Right_Y=File_Data[j].bottom_right.y;
		strcpy(Find_Color,(File_Data[j].color));
		if(strcmp(Find_Color,New_Color)==0)
		{
			Perim=((Top_Left_Y - Bottom_Right_Y) + (Bottom_Right_X - Top_Left_X))*2;
			if(Max_Perim<Perim)
			{
				Max_Perim=Perim;
				max_j=j;
			}
		}
	}
	return max_j;
}
