#define SIZE 10 

//######################################################################
//########################    DATA TYPES      ##########################
//######################################################################
typedef struct {
		float x;
		float y;
		float z;
		} Vertex;

typedef struct {
		float vx;
		float vy;
		float vz;		
		} Vector;

typedef struct {
		Vector normal;
		Vertex v1;
		Vertex v2;
		Vertex v3;		
		} Facet;

typedef struct {
		Facet facetsList[SIZE];		
		} Solid;

//######################################################################
//########################      Shortcuts      #########################
//######################################################################
void dispVertex(Vertex ver);
void dispVector(Vector vect);
void dispFacet(Facet facet);
void dispSolid(Solid solid);

void generateFile(Solid s);
void genVertex(Vertex ver, FILE* fp);
void genVector(Vector vect, FILE* fp);
void genFacet(Facet facet, FILE* fp);
void genSolid(Solid solid, FILE* fp);


float  randomCoordinate();
Vertex randomVertex();
Facet  randomFacet();
Solid  randomSolid();

Vertex getVertex(float x,float y, float z);
Vector getVector(Vertex A ,Vertex B);
Facet  getFacet(Vector normal, Vertex ver1,Vertex ver2, Vertex ver3);


Vector crossProduct(Vector a,Vector b);
void   setNormal(Facet *fptr);


