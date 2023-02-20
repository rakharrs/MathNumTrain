#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

float **newMat(int l,int c);
float *newVect(int dim);
void problem(char* message);
void getData(int*dim,float***A,float**b,float**x);
void showMatrice(float **matrice,float *vecteur,int l,int c);
void showResultat(float* resultat,int taille);
void triangularisation_n_dimension(float **matrice,float *vector,int dim);
void gauss(float **matrice,float *vector,float*result,int dim);
void displayVector(int dim,int*p,float*b);
void solverTriangSupPiv(int dim,float**A,float*b,int*p,float*result);
void pivot(float **a, int i, int j);
void gaussPiv2(int dim,float**A,float*b,float*x);
void gaussPiv(int dim,float**A,float*b,float*x);
float**factorisationCholesky(float**A, int dim);
float**transposee(float**B, int dim);
void triangulaireinf(float**T, float*v, float*u, int dim); //B*y = b
void triangulairesup(float**S, float*u, float*w, int dim); //B*y = b
void displayResult(float**A ,float**B, float*y, float*x, float*b, int dim);
void showVect(float*vecteur, int l, char n);

int main(){
///Donnees
	int dim = 1;
	float** A = NULL;
	float* b = NULL;
	float* x = NULL;
	float**B = NULL;
	float * y = NULL;
	float**Bt = NULL;
	getData(&dim,&A,&b,&x);
///Traitement

	//DEBUT GAUSS
 
	//gaussPiv2(dim, A, b, x);
	
	//FIN GAUSS
	//showMatrice(B,x,dim,dim);

	//gauss(A,b,x,dim);
	
	//gaussPiv(dim,A,b,x);
	//DEBUT CHOLESKY

	B = factorisationCholesky(A, dim);	//FACTORISATION CHOLOSKY
	y = newVect(dim);

	Bt = transposee(B, dim);	//B TRANSPOSEE
	triangulaireinf(B, b, y, dim);	//RESOLUTION TRIANGLE INFERIEURE
	triangulairesup(Bt, y, x, dim);	//RESOLUTION TRIANGLE SUPERIEUREx

	//FIN CHOLESK

///Resultats
	
	displayResult(A ,B, y, x, b, dim);
	return 0;
}

void displayResult(float**A ,float**B, float*y, float*x, float*b, int dim){
	printf("Matrice A de dimension %i, %i\n", dim, dim);
	showMatrice(A, NULL, dim, dim);
	printf("Vecteur b\n");
	showVect(b, dim, 'y');
	printf("B=\n");
	showMatrice(B,x,dim,dim);
	printf("Y=\n");
	showVect(y, dim, 'y');
	printf("X=\n");
	showVect(x, dim, 'x');
}

void triangulairesup(float**S, float*u, float*w, int dim){
	//float*x = newVect(dim);
	for(int i = dim-1; i>=0; i--){
		float sm = 0;
		for(int j = i+1;j<dim; j++){
			sm += (S[i][j]*w[j]);
		}
		w[i] = (1/S[i][i])*(u[i]-sm);
	}
	//*vx = x;
}

void triangulaireinf(float**T, float*v, float*u, int dim){
	//float*y = newVect(dim);
	for(int i = 0; i < dim; i++){
		float sm = 0;
		for(int j=0; j < i ; j++){
			sm += (T[i][j])*(u[j]);
		}
		u[i] = (1/T[i][i])*(v[i]-sm);
	}
	//*vy = y;
}

float**transposee(float**B, int dim){
	float**b = newMat(dim, dim);
	for(int i=0; i<dim; i++){
		for(int j=i; j<dim; j++){
			b[i][j] = B[j][i];
		}
	}
	return b;
}

float**factorisationCholesky(float**A, int dim){
	
	float**b = newMat(dim, dim);
	for(int i=0; i<dim; i++){				//ligne
		for(int j=0; j<i;j++){				//colonne
			float sm = 0; 
			for(int k=0; k<j;k++){			//somme
				sm += (b[i][k]*b[j][k]);
			}
			b[i][j] = (A[i][j] - sm)/b[j][j];
		} 
		float sm2 = 0;
		for(int k=0; k<i;k++){
			sm2 += b[i][k]*b[i][k];
		}
		b[i][i] = sqrt(A[i][i] - sm2);
	}
	return b;
}

void getData(int*dim,float***A,float**b,float**x){
	float **M=NULL, *v=NULL, *sol=NULL;
	FILE*pf=NULL;  
	
	pf = fopen("data0.txt","r");
	if(pf!=NULL){
		fscanf(pf,"%d",dim);	//Recupere la dimension
		M = newMat(*dim,*dim);		//alloue de la place pour la matrice
		v = newVect(*dim);		//aloue de la place pour le second menbre
		sol = newVect(*dim);	//aloue de la place pour la solution
		for(int i=0;i<*dim;i++){
			for(int j=0;j<*dim;j++){
				fscanf(pf,"%f",&M[i][j]);	//lit les donnees ligne par lign
			}
		}
		for(int i=0;i<*dim;i++){
			fscanf(pf,"%f",&v[i]);
		}
		fclose(pf);
		for(int i=0;i<*dim;i++) sol[i]=0;	//initialise les valeurs de solution 
	}
	else{
		problem("can't open file");
		exit(2);
	}
	*A = M;
	*b = v;
	*x = sol;	
}

float** newMat(int l,int c){
	float **A = NULL;
	A = malloc(l*sizeof(float*));
	if(A==NULL) problem("Ne peut pas allouer une matrice");
	for(int i=0;i<l;i++){
		A[i] = malloc(c*sizeof(float));
		if(A[i]==NULL) problem("Ne peut pas allouer une ligne de matrice");
	}
	return A;
}

void problem(char* message){
	printf("%s\n",message);
	exit(2);
}

float *newVect(int dim){
	float *V = NULL;
	V = malloc(dim*sizeof(float));
	if(V==NULL) problem("Ne peut pas allouer un vecteur");
	return V;
}

void showMatrice(float **matrice,float *vecteur,int l,int c){
	for(int i=0;i<l;i++){
		for(int j=0;j<c;j++){
			printf("\t %2.f ",matrice[i][j]);
		}
		printf("\n");
	}
} 

void showVect(float*vecteur, int l, char n){
	for(int j=0;j<l;j++){
		printf("\t %g \n",vecteur[j]);
	}
}
void showResultat(float* resultat,int taille){
	printf("Resultats: \n");
	for(int i=0;i<taille;i++){
		printf("\t x%i = %g \n",i,resultat[i]);
	}
}


void displayVector(int dim,int*p,float*b){
	for(int j=0;j<dim;j++){
		b[j] = b[p[j]];
	}
}
