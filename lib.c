#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"lib.h"
#include<math.h>

//######################################################################
//#############################      TEST      #########################
//######################################################################
Facet randomFacet(){
	Facet facet;

	Vertex ver1=randomVertex();
	Vertex ver2=randomVertex();
	Vertex ver3=randomVertex();

	Vector vec1=getVector(ver1,ver2);
	Vector vec2=getVector(ver1,ver3);
	Vector normal=crossProduct(vec1,vec2);

	facet.normal=normal;
	facet.v1=ver1;
	facet.v2=ver2;
	facet.v3=ver3;

return facet;
}
//######################################################################
Facet makeFacet(Vertex ver1, Vertex ver2, Vertex ver3){
	Facet facet;

	Vector vec1=getVector(ver1,ver2);
	Vector vec2=getVector(ver1,ver3);
	Vector normal=crossProduct(vec1,vec2);

	facet.normal=normal;
	facet.v1=ver1;
	facet.v2=ver2;
	facet.v3=ver3;

return facet;
}


//#######################################################################"
Solid allocateSolid(int NB_facets){
	Solid sol = malloc(NB_facets * sizeof(Facet));
	for(int i=0; i< NB_facets; i++){
		sol[i]= randomFacet();
	}

return sol;
}

//######################################################################
//###################      DISPLAY FUNCTIONS      ######################
//######################################################################
void dispVertex(Vertex ver){
	printf("	vertex %f %f %f\n",ver.x,ver.y,ver.z);
}

//######################################################################
void dispVector(Vector vect){
	printf("facet normal %f %f %f\n",vect.vx,vect.vy,vect.vz);
}

//######################################################################
void dispFacet(Facet facet){
	dispVector(facet.normal);
	printf("outer loop\n");
        dispVertex(facet.v1);
	dispVertex(facet.v2);
	dispVertex(facet.v3);
	printf("	endloop\n");
	printf("endfacet\n");
}
//######################################################################
void dispSolid(Solid solid, int NB_facets){
	printf("solid object\n");
	for(int i=0; i<NB_facets ;i++){
		dispFacet(solid[i]);	
	}
	printf("endsolid object\n");
}



//######################################################################
//###################    INITIALISING FUNCTIONS   ######################
//######################################################################
float randomCoordinate(){
	int inf=-5, sup=5;
	int rando = rand();
	return (float)(inf + (rando % (sup - inf +1)));
}

//######################################################################
//GENERATES POINTS ON A CONE TO TEST THE RECONSTRUCTION
Vertex likelyRandomVertex(int level,int precision,int circle_pos, int max){
	int inf=5/*, sup=6*/;
  	int radius = rand();
        //radius=(float)(inf+0.2*level+2*cos(rand())+ (radius % (sup - inf +1))); //with noise
	radius=(float)(inf+(0.2*precision*level));
	float angle = (6.28/max)*(circle_pos); 	
	Vertex ver;
	ver.x = radius*cos(angle);
	ver.y = radius*sin(angle);	
return ver;
}

//######################################################################
Vertex randomVertex(){
	Vertex ver;
	ver.x=randomCoordinate();
	ver.y=randomCoordinate();
        ver.z=randomCoordinate();
return ver;
}

//######################################################################
Solid randomSolid(int NB_facets){
	Solid solid= allocateSolid(NB_facets);

	Facet facet;

	for(int i=0;i<NB_facets;i++){	
		facet= randomFacet();
		solid[i]=facet;	
	}

return solid;
}

//######################################################################
Vertex getVertex(float x,float y, float z){
	Vertex ver;	
	ver.x= x;
	ver.y= y;
	ver.z= z;

return ver;
}


//######################################################################
Vector getVector(Vertex A ,Vertex B){
	Vector AB;

	AB.vx = B.x - A.x;
	AB.vy = B.y - A.y;
	AB.vz = B.z - A.z;

return AB;
}
//######################################################################
Facet getFacet(Vector normal, Vertex ver1,Vertex ver2, Vertex ver3){
	Facet facet;

	facet.normal=normal;
	facet.v1= ver1;
	facet.v2= ver2;
	facet.v3= ver3;

return facet;
}


//######################################################################
//#####################     MATHS FUNCTIONS      #######################
//######################################################################



//######################################################################
Vector crossProduct(Vector a,Vector b){
	Vector cp;
		
	cp.vx=  (a.vy * b.vz - b.vy * a.vz);
	cp.vy= -(a.vx * b.vz - b.vx * a.vz);
	cp.vz=  (a.vx * b.vy - b.vx * a.vy);

return cp;
}
//######################################################################

void setNormal(Facet *fptr){
	Vector A = getVector(fptr->v1,fptr->v2);
	Vector B = getVector(fptr->v1,fptr->v3);

fptr->normal= crossProduct(A,B);

}


//######################################################################
//#####################  FILE GENERATION FUNCTIONS   ###################
//######################################################################

void generateFile(Solid s, int NB_facets){
	FILE* fp;
	fp = fopen("fichier.stl", "w");
	fprintf(fp,"solid object\n");
	genSolid(s,NB_facets,fp);
	fprintf(fp,"endsolid object");
	fclose(fp);
	printf("FILE GENERATED\n");
}

//######################################################################
void genVertex(Vertex ver, FILE* fp){
	fprintf(fp,"	vertex %f %f %f\n",ver.x,ver.y,ver.z);
}

//######################################################################
void genVector(Vector vect, FILE* fp){
	fprintf(fp,"facet normal %f %f %f\n",vect.vx,vect.vy,vect.vz);
}

//######################################################################
void genFacet(Facet facet, FILE* fp){
	genVector(facet.normal,fp);
	fprintf(fp,"outer loop\n");
        genVertex(facet.v1,fp);
	genVertex(facet.v2,fp);
	genVertex(facet.v3,fp);
	fprintf(fp,"	endloop\n");
	fprintf(fp,"endfacet\n");
}
//######################################################################
void genSolid(Solid solid,int NB_facets, FILE* fp){
	fprintf(fp,"solid object\n");
	for(int i=0; i<NB_facets ;i++){
		genFacet(solid[i],fp);	
	}
	fprintf(fp,"endsolid object\n");
}


