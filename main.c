#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include"lib.h"

#define H_FACTOR 0.5
int precision;
int k ;        // Nombre de facets dans solid crée 
//#####################################################################################
//###############################  FUNCTION SIGNATURES ################################
//#####################################################################################
Vertex** VMatrix_allocate(int NB_layers,int NB_points_niv);
void VMatrix_init(Vertex** vertexMatrix, int NB_layers, int NB_points_niv);
void VMatrix_free(Vertex** vertexMatrix, int NB_layers, int NB_points_niv);
void VMatrix_disp(Vertex** vertexMatrix, int NB_layers, int NB_points_niv);
void VMatrix_to_stl (Vertex** VMat, int NB_layers, int NB_points_niv);
//######################################################################################
//##################################      MAIN      ####################################
//######################################################################################
int main(int argc , char* argv[]){
	
	if( argc != 2 ) {
      		printf("Usage avec un entier (1-10): ./test <precision>\n");
		return 0;
   	}
//SEED INIT FOR RANDOM
	srand(time(NULL));

//CONVERTING INPUT PRECISION FROM STRING TO INT
	
	char* ptr = NULL;
   	long ret;
   	ret = strtol(argv[1], &ptr, 10);
		
	
	precision = (int) ret;    					// 1 MAX .....10 MIN 
	int NB_layers = RES_Z_AXIS/precision; 	
	int NB_points_niv = RAD_RES_MAX/precision ;
		
//CREATION DE LA MATRICE REPRESENTANT UN NUAGE DE POINT ACQUIS
	Vertex** grille = VMatrix_allocate(NB_layers, NB_points_niv);
	VMatrix_init(grille, NB_layers,NB_points_niv);
	
	VMatrix_to_stl (grille, NB_layers, NB_points_niv);


	VMatrix_free (grille, NB_layers,NB_points_niv);
	return 0;
}
//#######################################################################################
Facet* FacetArray_allocate(int NB_layers, int NB_points_niv){

	// Calculation method on that red paper on your desk
	int NB_facets= 	2*(NB_layers * NB_points_niv) + 2 *NB_layers; 
	Facet* facetArray = malloc (NB_facets*sizeof(Facet));
	return facetArray;	
}

//#######################################################################################
void FacetArray_free(Facet* facet_array){

		free(facet_array);	
}
//#######################################################################################
void VMatrix_to_stl (Vertex** VMat, int NB_layers, int NB_points_niv){

	int k=0; // nombre de facet qui seront crées pendant l'iteration
	int modj = NB_points_niv;
	
	
	Facet* facet_array = FacetArray_allocate( NB_layers, NB_points_niv);	

	// start at -1 to add closing virtual point	
	for(int i=-1; i<NB_layers; i++ ){
		for(int j=0; j<NB_points_niv; j++ ){
			//Refer to the draft paper half cut on your desk

			if(i!=(NB_layers-1) && (i!=-1)){
				facet_array[k]   = makeFacet( VMat[i][j]           ,VMat[i][(j+1)%modj] ,VMat[i+1][j]);
				facet_array[k+1] = makeFacet( VMat[i][(j+1)%modj]  ,VMat[i+1][j]        ,VMat[i+1][(j+1)%modj]);
				k=k+2;
			}
			else if(i==NB_layers-1){	
				//closing object from top				
				Vertex virtual_up = getVertex(0,0, i*H_FACTOR*precision );
				facet_array[k]   = makeFacet( VMat[i][j]           ,VMat[i][(j+1)%modj]   ,virtual_up);
				k++;
			}
			else{
				//closing object from down
				Vertex virtual_down = getVertex(0,0,0 );
				facet_array[k]   = makeFacet( VMat[i+1][j]  ,VMat[i+1][(j+1)%modj]   ,virtual_down);
				k++;
			}
			
		}
	}
	
	Solid solid = allocateSolid(k) ;
	for(int i= 0; i<k; i++){		
		solid[i] = facet_array[i];
		//dispFacet(solid[i]);
	}
	generateFile(solid,k);
	//k est le nombre de facets
	printf("%d facets generated\n",k);
	FacetArray_free(facet_array);
	free(solid);
}
//#######################################################################################
void VMatrix_disp(Vertex** vertexMatrix,int NB_layers,int NB_points_niv){
	for(int i =0; i< NB_layers; i++){
		for(int j=0; j<NB_points_niv; j++){
			dispVertex(vertexMatrix[i][j]);
		}
	}


}
//#######################################################################################
//ALLOCATION 
Vertex** VMatrix_allocate(int NB_layers,int NB_points_niv){
	Vertex** vertexMatrix = malloc(NB_layers*sizeof(Vertex*));

	for(int i=0; i<NB_layers; i++){
		vertexMatrix[i] = malloc(NB_points_niv*sizeof(Vertex));
		for(int j =0 ; j<NB_points_niv; j++){
			(vertexMatrix[i][j]).x = 0;
			(vertexMatrix[i][j]).y = 0;
			(vertexMatrix[i][j]).z = 0;	
		}
	}
	
return vertexMatrix; 
}


//#######################################################################################
//INITIALISATION
void VMatrix_init(Vertex** vertexMatrix, int NB_layers, int NB_points_niv){

	for(int i=0; i<NB_layers; i++){	
		for(int j=0; j<NB_points_niv; j++){	
			//TOBE REPLACED BY COORDINATES AQCUIRED FROM ARDUINO THROUGH SERIAL
			Vertex v = likelyRandomVertex(i,precision, j, NB_points_niv);
			(vertexMatrix[i][j]).x = v.x;
			(vertexMatrix[i][j]).y = v.y;
			(vertexMatrix[i][j]).z = i*H_FACTOR*precision ; //replace Z component with real one
		}
	}
}

//#######################################################################################
//FREE
void VMatrix_free(Vertex** vertexMatrix, int NB_layers, int NB_points_niv){
	for(int i=0; i<NB_layers; i++){
		free(vertexMatrix[i]);	
	}
	free(vertexMatrix);
}
