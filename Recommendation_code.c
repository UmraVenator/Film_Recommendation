/* Omada ergasthriou: B'
Zachos Odysseas A'etos, AM: 1080548
Iliakis Aggelos A'etos, AM: 1072391
Hmeromhnia syggrafhs: 13/5/2020
Leitourgia Proggrammatos:Protash tainiwn se theath.
*/



#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 6

int main()


{

	float m,s,MD,sum,Ssim,Ssimn;
	float reviews[ROWS][COLS];
	float mean_reviews[ROWS];
	float mean_centered_matrix[ROWS][COLS];
	float similarity[ROWS];
	float u[ROWS];
	FILE * fp;
	int i,j,k,t;
    
	
	fp=fopen("reviews.txt","r");
	printf("Recommendation process for file: reviews.txt \n\n\n");
	
	
printf("\n\nThe initial reviews' Matrix is: \n");   /*Elegxos gia antikatastasi toy 100 me to ? */
printf("--------------------------------- \n\n\n");	
for(i=0;i<ROWS;i++) 
	{
		for(j=0;j<COLS;j++) 
		{
			fscanf(fp,"%f ",&reviews[i][j]);
		
		if(reviews[i][j] !=100)
		{printf("%.f\t\t",reviews[i][j]);
		}
		else
		printf("? \t\t");
			
			 
		}
		printf("\n\n");
 	}
	
	fclose(fp); 
	


printf("\n\nThe Mean Value for each user's reviews is: \n");
printf("------------------------------------------ \n");
for(i=0;i<ROWS;i++)
{
	k = 0;
    s = 0;
	for(j=0;j<COLS;j++)
	{
		if(reviews[i][j]!=100) /* Me elegxo den lamvanontai yp opsin ta 100 (ayta pou den exoun aksiologhsh) */
		{
			s += reviews[i][j];
			k = k+1;
		}
		
		else 
		{
			s = s;
			k = k;
		}
		
		
	}
mean_reviews[i]=s/k;
printf("\n\n %.1f",mean_reviews[i]);	
}



printf("\n\n\n\nThe Mean-centered Matrix is: \n");
printf("---------------------------- \n\n\n");
for(i=0;i<ROWS;i++)
{
	for(j=0;j<COLS;j++)
	{
		if(reviews[i][j]!=100)
		{
			mean_centered_matrix[i][j] = reviews[i][j]- mean_reviews[i]; /*Xrhsh typou evreshs kai antikatastash me ta stoixeia twn pinakwn gia kathe grammh*/
			printf("%.2f\t\t ", mean_centered_matrix[i][j]);
		}
		else
		{
			mean_centered_matrix[i][j] = 100;
			printf("?\t\t ");
		}
	}
printf("\n\n");
}


printf("\n\nThe Manhattan Similarity between Helen and all the other users is:\n"); /* Me elegxo den lamvanontai yp opsin ta 100 (ayta pou den exoun aksiologhsh) sto manhattan similarity*/
printf("---------------------------------------------------------------------\n\n");

i = 2;
for(t=0;t<ROWS;t++)
{
  sum = 0;
	for(j=0;j<COLS;j++)
	{
		if((mean_centered_matrix[t][j]!=100)&&(mean_centered_matrix[i][j]!=100))
		{
			MD = mean_centered_matrix[i][j] - mean_centered_matrix[t][j];
			if((mean_centered_matrix[i][j] - mean_centered_matrix[t][j])<0) /*Exasfalisi 8etikou arithmou me elegxo */
			MD = - MD; 
			
			else
			MD = MD;
	    }  
	    else 
	    MD = 0;
	    sum += MD;
	}

similarity[t] = 1 / (1 + sum);
printf("%.6f\n\n",similarity[t]);	
	
}


k=0;
for(j=0;j<COLS;j++)
{
	if(reviews[2][j]==100)
	{Ssim=0;
	 Ssimn=0;
	 	for(i=0;i<ROWS;i++)
		{
			if(reviews[i][j]!=100)
			{
			Ssim = Ssim + similarity[i];
			Ssimn = Ssimn + (similarity[i] * mean_centered_matrix[i][j]); 
						
			}
		}
		u[k++]=mean_reviews[2] + (Ssimn/Ssim); /*Dhmiourgia enos pinaka me theseis toses oses kai oi tainies pou den eide h elenh kai stoixeia tis provlepseis an tis eixe dei*/
	}
}

	for(i=0;i<k;i++)



printf("\n\nRecommended movies (ranked) for user Helen are:\n");
printf("---------------------------------------------------------\n\n");
if (u[0]>u[1]) /* u[0] gia Star Wars I kai u[2] gia The Lord of the Rings III */
{
printf("1. Star Wars 1\t\t\t\t\t\t\t\t(estimated rating: %f)\n\n",u[0]);
printf("2. Lord of The Rings 3\t\t\t\t\t\t\t(estimated rating: %f)\n\n",u[1]);
}
else
{
printf("1. Lord of The Rings 3\t\t\t(estimated rating: %f)\n\n",u[1]);
printf("2. Star Wars 1\t\t\t\t\t\t\t(estimated rating: %f)\n\n",u[0]);
}
	
	

	
	
	
	
return 0;
}
