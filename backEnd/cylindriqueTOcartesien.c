//Pour compiler (ne pas oublier le -lm pour inclure le math.h)
//gcc -Wall -lm cylindriqueTOcartesien.c -o cylindriqueTOcartesien

//Mathis du futur : 
//Modifie le CENTRE et la val de conversion (30)    regarder : ICI


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define CENTRE 346 //ICI
#define FACTEUR_CONV_CM 30 //ICI
#define COEF 1000 //IIC

int conversion_cm(int val_capteur)
{
 int cm;
 cm = val_capteur/FACTEUR_CONV_CM; //ICI
 return cm;
}



int main()
{
  FILE *f_lecture; //fichier recup donnée
  FILE *f_ecriture;
  f_lecture = fopen("/var/www/html/backEnd/data_brut.txt", "r");   
  f_ecriture = fopen("/var/www/html/backEnd/data.txt", "w");
  
  int nb_mesure;
  int nb_tour;
  int tmp;
  int rayon;
  float x, y, z;
  
  x=0.0;
  
  if(f_lecture!=NULL)
    {
        
        if(fscanf(f_lecture, "%d", &nb_mesure)!=EOF)
        {
        printf("%d\n", nb_mesure);
        fscanf(f_lecture, "%d", &nb_tour);
        printf("%d\n", nb_tour);
    
        fprintf(f_ecriture, "%d\n", (int)(200/(float)nb_mesure));
        
        for(int i =0; i<nb_tour;i++)
        {
         for(int j=0; j<nb_mesure;j++)
         {
            fscanf(f_lecture, "%d", &tmp);
            
            rayon = conversion_cm(tmp - CENTRE);
            
            //Passage cylindrique/cartesien
            x = rayon * cos( (2*M_PI*j)/(float)nb_mesure );
            y = rayon * sin( (2*M_PI*j)/(float)nb_mesure );
            z = i * 0.1;
/*
            x *= COEF;
            y *= COEF;
            z *= COEF;
            
            int x_int = (int)x;
            int y_int = (int)y;
            int z_int = (int)z;
            
*/
            //Ecriture des coordonnées dans le txt final
            fprintf(f_ecriture, "%f\n", x);
            fprintf(f_ecriture, "%f\n", y);
            fprintf(f_ecriture, "%f\n", z);
            

            
            printf("x : %f\n",x);
            printf("y : %f\n",y);
            printf("z : %f\n\n",z);
         }
        }
    }
    }
    
    fclose(f_lecture); //fermeture
    //fclose(f_ecriture);
}