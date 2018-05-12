#define RAD_RES_MAX 200    // Nombre max de pas par revolution Nema17
#define RES_Z_AXIS  150    // Nombre max de points sur 15cm avec un tour/mm
 

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

typedef Facet* Solid;		
		

//######################################################################
//########################      Shortcuts      #########################
//######################################################################
void dispVertex(Vertex ver);
void dispVector(Vector vect);
void dispFacet(Facet facet);
void dispSolid(Solid solid, int NB_facets);

void generateFile(Solid s, int NB_facets);
void genVertex(Vertex ver, FILE* fp);
void genVector(Vector vect, FILE* fp);
void genFacet(Facet facet, FILE* fp);
void genSolid(Solid solid,int NB_facets, FILE* fp);

Vertex likelyRandomVertex(int level,int precision,int circle_pos, int max);
float  randomCoordinate();
Vertex randomVertex();
Facet  randomFacet();
Solid  randomSolid(int NB_facets);

Vertex getVertex(float x,float y, float z);
Vector getVector(Vertex A ,Vertex B);
Facet  getFacet(Vector normal, Vertex ver1,Vertex ver2, Vertex ver3);
Facet  makeFacet(Vertex ver1, Vertex ver2, Vertex ver3);
Solid  allocateSolid(int NB_facets);

Vector crossProduct(Vector a,Vector b);
void   setNormal(Facet *fptr);


