#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void menu(float **a, float *b, int *i);

void getDonnee(float*** A, float** B);

void resolution(float **a, float *b, float*x, int tailleA);

void triangularisation(float ** a, float *b, int taille);

float** alloc2D(int l, int c);

float* alloc1D(int l);

//void displayResult(float ** a, float *b, float *x, int taille);

void displayResult(float ** a, float *b, float *x, int taille, int* p);

void getData(char* filepath, float*** A, float** B, float** x, int* dim);

void displayMatrice(float** M, int dim, int* p);

void gaussPivot(int dim, float** A, float* b, float* x);

void triangularisationWpiv(float **a, float *b, int* p, int dim);

void solveTriangleSupPiv(int dim, float** A, float* b, int* p, float* x);

int maxLigne(float** A, int k, int col, int dim);

float** cholesky(float** A, int dim);

int main(){
	printf("\nResolution d'un systeme d'equation lineaire par triangularisation\n\n");

//	Entrée des donnees
	float** a = NULL; 	// Matrice A
	float* b = NULL; 	// Vecteur du second membre
	float* x = NULL; 	// solution
	int n = 3; 			//taille de la matrice
	int i = 0;

	getData("data1.txt", &a, &b, &x, &n);

//	traitement (Méthode de Gauss)
	gaussPivot(n, a, b, x);

//	sortie 
	//displayResult(a, b, x, n);
	
	return 0;
}

void getDonnee(float*** A, float ** B){

	float * b = alloc1D(3);
	float ** a = alloc2D(3,3);
	
	a[0][0] = 4;
	a[0][1] = 8;
	a[0][2] = 12;
	a[1][0] = 3;
	a[1][1] = 8;
	a[1][2] = 13;
	a[2][0] = 2;
	a[2][1] = 9;
	a[2][2] = 18;
	b[0] = 4;
	b[1] = 5;
	b[2] = 11;

	A[0] = a;
	B[0] = b;
}

int max(float** a, int n, int k, int* p) {
    float max = 0;
    int index = 0;
    for (int i = k+1; i < n; i++) {
        if (max < fabs(a[p[i]][k])) {
            max = a[p[i]][k];
            index = i;
        }
    }
    return index;
}



void getData(char* filepath, float*** A, float** B, float** x, int* dim){
// Pointeur des données
	float** M = NULL, *v = NULL, *sol = NULL;
	FILE *pf = NULL;
	pf = fopen(filepath, "r");
	if(pf != NULL){
		fscanf(pf, "%i", dim);

		M = alloc2D(*dim, *dim);
		v = alloc1D(*dim);
		sol = alloc1D(*dim);

		for (int i = 0; i < *dim; i++)
		{
			for (int j = 0; j < *dim; j++)
			{
				fscanf(pf, "%f", &M[i][j]);		// Lit les données ligne par ligne
			}
			
		}
		for (int i = 0; i < *dim; i++)
		{
			fscanf(pf, "%f", &v[i]);
		}

		fclose(pf);
		for (int i = 0; i < *dim; i++)
		{
			sol[i] = 0;
		}
	}else{
		printf("can't open file");
	}

	*A = M; *B = v; *x = sol;
}

void displayMatrice(float** M, int dim, int* p){

	for(int i=0;i<dim;i++){

		for(int j=0;j<dim;j++){

			printf(" %g\t",M[p[i]][j]);
		}
		
		printf("\n");
	}
	printf("\n");
}

void gaussPivot(int dim, float** A, float* b, float* x){
	int* p = NULL;
	int lpiv = 0, t = 0;
	float piv = 0;

	p = malloc(dim*sizeof(int));;
	for (int i = 0; i < dim; i++) p[i] = i;

	printf("La matrice à triangularisée du problème \n\n");

	displayMatrice(A, dim, p);

	triangularisationWpiv(A, b, p, dim);

	solveTriangleSupPiv(dim, A, b, p, x);

	displayResult(A, b, x, dim, p);
	
	free(p);
}

void resolution(float **a, float *b, float *x, int tailleA){

	int n = tailleA;

	for(int i = n-1; i >= 0;i--){

		float temp = 1/a[i][i];
		float sm = 0;

		for(int j=i+1;j<=n-1;j++){

			sm += a[i][j]*x[j];
		}

		temp = temp*(b[i]-sm);
		x[i] = temp;
	}
}

void displayResult(float ** a, float *b, float *x, int taille, int* p){
		printf("Les solutions de la matrice est : \n\n");
	for(int i=0;i<taille;i++){
		for(int j=0;j<taille;j++){
			printf(" %g\t",a[p[i]][j]);
		}
		
		// Affichage de la solution x
		printf("|\t%g\t", x[p[i]]);

		// Affichage du second membre (b)
		printf("|\t%g", b[p[i]]);
		
		printf("\n");
	}

	printf("\n");
}

/*void displayResult(float ** a, float*b, float *x, int taille){
	printf("Les solutions de la matrice est : \n\n");
	for(int i=0;i<taille;i++){
		for(int j=0;j<taille;j++){
			printf(" %g\t",a[i][j]);
		}
		
		// Affichage de la solution x
		printf("|\t%g\t", x[i]);

		// Affichage du second membre (b)
		printf("|\t%g", b[i]);
		
		printf("\n");
	}

	printf("\n");
}*/

void triangularisation(float **a, float *b, int taille){
	int n = taille;
	for(int k=0; k<=n-2; k++){

		// Élimination
		for(int i=k+1;i<=n-1;i++){
			for(int j=k+1;j<=n-1;j++){
				float t = a[i][j] - ((a[i][k]/a[k][k])*a[k][j]);
				a[i][j] = t;
			}
			b[i] = b[i] - ((a[i][k]/a[k][k])*b[k]);	
			a[i][k] = 0;
		} 
	}
}

void solveTriangleSupPiv(int dim, float** A, float* b, int* p, float* x){

	int n = dim;
    for (int i = n-1; i >= 0; i--) {
        float somme = 0;
        for (int j = i+1; j < n; j++) {
            somme += A[p[i]][j] * x[p[j]];
        }
        x[p[i]] = (1 / A[p[i]][i]) * (b[p[i]] - somme);
    }
}

void triangularisationWpiv(float **a, float *b, int* p, int dim){
		int n = dim;
	    float epsilone = 1e-6;
    for (int k = 0; k <= n-2; k++) {
        if (fabs(a[p[k]][k]) <= epsilone) {
            int index = max(a, n, k, p);
            int temp = p[k];
            p[k] = p[index];
            p[index] = temp;
        }
        for (int i = k+1; i < n; i++) {
            for (int j = k+1; j < n; j++) {
                a[p[i]][j] = a[p[i]][j] - (a[p[i]][k]/a[p[k]][k]) * a[p[k]][j];
            }
            b[p[i]] = b[p[i]] - (a[p[i]][k]/a[p[k]][k]) * b[p[k]];
            a[p[i]][k] = 0;
        }
    }
	/*int n = dim;

	int lpiv = 0, t = 0;

	float piv = 0;

	float eps = 1e-6;

	for(int k=0; k<=n-2; k++){

		if (fabs(a[p[k]][k]) <= eps) {
			
            int index = max(a, n-1, k, *p);
            int temp = p[k];
            p[k] = p[index];
            p[index] = temp;
        }
		
		for(int i=k+1;i<=n-1;i++){



			for(int j=k+1;j<=n-1;j++){
				//Recherche du pivot
				
				float t = a[p[i]][j] - ((a[i][k]/a[p[k]][k])*a[p[k]][j]);
				a[i][j] = t;
			}
			b[p[i]] = b[p[i]] - ((a[p[i]][k]/a[p[k]][k])*b[p[k]]);	
			a[p[i]][k] = 0;
		} 
	}*/

}

int maxLigne(float** A, int k, int col, int dim){
	int val = 0;
	for (int i = k; i < dim; i++)
	{

		if(fabs(A[i][col]) > fabs(A[val][col])){

			val = i;
		}
		//val = 1;
	}

	return val;
}



void entreeDonnees(float ** a, float * b){
	int n = 3;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			printf("a[%i][%i]\n",i,j);
			float r = 0;
			scanf("%g", &r);
			a[i][j] = r;
		}
	}
	for(int i=0; i<n; i++){
		printf("b[%i]\n",i);
		scanf("%g", &b[i]);
	}
}

float* alloc1D(int l){
	float*b = malloc(3*sizeof(float));
	return b;
}

float** alloc2D(int l, int c){
	float**a = malloc(l*sizeof(float*));
	for(int i=0; i<l;i++){
		a[i] = malloc(c*sizeof(float));
	}
	return a;
}

float** cholesky(float** A, int dim){
	float** B = alloc2D(dim, dim);
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < i; j++)
		{
			float sum = 0;
			for (int k = 0; k < j-1; k++)
			{
				sum += B[i][k] * B[j][k];
			}
			B[i][j] = (1/B[j][j])*(A[i][j] - sum);
		}
		float sum2 = 0;
		for (int k2 = 0; k2 < i-1; k2++)
		{	
			sum2 += pow(B[i][k2],2);
		}
			
			B[i][i] = sqrt(A[i][i] - sum2);
		
	}
	return B;
	
}
