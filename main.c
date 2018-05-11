#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"lib.h"



//#####################################################################################
//###############################  FUNCTION SIGNATURES ################################
//#####################################################################################
Vertex** VMatrix_allocate(int NB_points_rad,int NB_points_z);
void VMatrix_init(Vertex** vertexMatrix, int NB_points_rad, int NB_points_z);
void VMatrix_free(Vertex** vertexMatrix, int NB_points_rad, int NB_points_z);
void VMatrix_disp(Vertex** vertexMatrix, int NB_points_rad, int NB_points_z);
//######################################################################################
//##################################      MAIN      ####################################
//######################################################################################
int main(){

//SEED INIT FOR RANDOM
	srand(time(NULL));

//PARAMETRES
	int precision = 1;    					// 1 MAX .....10 MIN 
	int NB_points_rad = RAD_RES_MAX/precision ;		
	int NB_points_z = RES_Z_AXIS/precision; 
		
//CREATION DE LA MATRICE REPRESENTANT UN NUAGE DE POINT ACQUIS
	Vertex** nuage = VMatrix_allocate(NB_points_rad, NB_points_z);
	VMatrix_init(nuage, NB_points_rad,NB_points_z);

	VMatrix_disp(nuage, NB_points_rad,NB_points_z);

	VMatrix_free(nuage, NB_points_rad,NB_points_z);
	return 0;
}
//#######################################################################################
//#######################################################################################
void VMatrix_disp(Vertex** vertexMatrix,int NB_points_rad,int NB_points_z){
	for(int i =0; i< NB_points_rad; i++){
		for(int j=0; j<NB_points_z; j++){
			dispVertex(vertexMatrix[i][j]);
		}
	}


}
//#######################################################################################
//ALLOCATION 
Vertex** VMatrix_allocate(int NB_points_rad,int NB_points_z){
	Vertex** vertexMatrix = malloc(NB_points_rad*sizeof(Vertex*));

	for(int i=0; i<NB_points_rad; i++){
		vertexMatrix[i] = malloc(NB_points_z*sizeof(Vertex));
		for(int j =0 ; j<NB_points_z; j++){
			(vertexMatrix[i][j]).x = 0;
			(vertexMatrix[i][j]).y = 0;
			(vertexMatrix[i][j]).z = 0;	
		}
	}
	
return vertexMatrix; 
}


//#######################################################################################
//INITIALISATION
void VMatrix_init(Vertex** vertexMatrix, int NB_points_rad, int NB_points_z){
	for(int i=0; i<NB_points_rad; i++){
		for(int j=0; j<NB_points_z; j++){
			//TOBE REPLACED BY VERTEX AQCUIRED FROM ARDUINO THROUGH SERIAL
			vertexMatrix[i][j] = randomVertex(); 
		}
	}
}

//#######################################################################################
//FREE
void VMatrix_free(Vertex** vertexMatrix, int NB_points_rad, int NB_points_z){
	for(int i=0; i<NB_points_rad; i++){
		free(vertexMatrix[i]);	
	}
	free(vertexMatrix);
}
