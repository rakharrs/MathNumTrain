#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void displayMatricePiv(int dim,float**A,int*p);
void displayVector(int dim,int*p,float*b);
void gaussPiv(int dim, float **a, float *b, float*x);
void problem(char* message);
float **newMat(int dim);
float *newVect(int dim);
void menu(float **a, float *b, int *i);
void donneeDure(float**a, float *b);
void resolution(float **a, float *b, float*x);
void triangularisation(float **a, float *b, int taille);
float**allocation2D(int l, int c);
float*allocation1D(int l);
void getData(int*dim, float***a, float**b, float **x);
void entreeDonnees(float ** a, float* b);
void displayResult(float ** a, float *b, float *x, int taille);
void solve(int dim, float**a, float *b, int*p, float*x);
void pivot(float **a, int i, int j);
void echange_ligne_Vecteur(float* vecteur , int ligne1 , int ligne2 , int dim);

int main(){
	printf("Resolution d'un systeme d'equation lineaire\n");
//donnee 
	float**a; //matrice
	float*b; //
	float*x; //solution
	int dim = 3; 
	
	getData(&dim, &a, &b, &x);
	gaussPiv(dim, a, b, x);
	//donneeDure(a, b);
//	entreeDonnees(a,b);
//traitement
	
//sortie 
	displayResult(a,b,x,dim);
	
	return 0;
}
void pivot(float **a, int i, int j) {
	float *tmp;
	tmp = a[i];
	a[i] = a[j];
 	a[j] = tmp;
}

void gaussPiv(int dim, float **a, float *b, float*x){
	int*p =NULL;
	p = malloc(dim*sizeof(int));	//tableau de pointeur de ligne pour le pivot
	int lpiv = 0;
	
	for(int i = 0;i<dim; i++) p[i] = i;
	//TRIANGULARISATION	
	
	for(int k=0; k<dim-1; k++){
//ETO MIJERY HOE NGEZA VE LE LIGNE MANARAKA
//LE MAX IO LE LIGNE COMPARENA
//MANDEHA IO DE LE A[0][0] VE SUP AM A[1][0] DE AVEO A[1][1] DE AVEO A[2][2]
		float max = a[k][k];
		for (int j = k+1; j < dim; j++) {
	            if (fabs(a[j][k]) > fabs(max)) {
	                	lpiv = j;
				max = a[j][k];
	            }
	        }
	        // Echange des lignes
	        if (lpiv != k) {
	            pivot(a, k, lpiv);
	            echange_ligne_Vecteur(b ,lpiv , k , dim);
			//lpiv++;
	        }
		for(int i=k+1;i<dim;i++){
				for(int j=k+1;j<dim;j++){
					a[p[i]][j] -= (a[p[i]][k]/a[p[k]][k]*a[p[k]][j]);
				}
				b[p[i]] -= (a[p[i]][k]/a[p[k]][k]*b[p[k]]);
				a[p[i]][k] =0;
		}
		lpiv = k+1;
	}
	solve(dim, a, b, p, x);
	free(p);
}
void echange_ligne_Vecteur(float* vecteur , int ligne1 , int ligne2 , int dim){
		float t=vecteur[ligne2];
		vecteur[ligne2]=vecteur[ligne1];
		vecteur[ligne1]=t;
	}
	
void displayMatricePiv(int dim,float**A,int*p){
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim;j++){
			A[i][j] = A[p[i]][j];
		}
	}
}

void displayVector(int dim,int*p,float*b){
	for(int j=0;j<dim;j++){
		b[j] = b[p[j]];
	}
}
void solve(int dim, float**a, float *b, int*p, float*x){
	float s = 0;
	for(int i=dim-1;i>=0;i--){
		s = 0;
		for(int j = i+1; j<dim;j++){
			s+=a[p[i]][j]*x[j];
		}
		x[i] = (b[p[i]]-s)/a[p[i]][i];
	}
}

void donneeDure(float**a, float *b){
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
}
void resolution(float **a, float *b, float *x){
	int n = 3;
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
void displayResult(float ** a, float*b, float *x, int taille){
	printf("Les solutions de la matrice  par la mthode de Gauss\n");
	for(int i=0;i<taille;i++){
		for(int j=0;j<taille;j++){
			printf("| %g",a[i][j]);
		}
		printf(" | %g", b[i]);
		printf(" | x[%i] = %g",i, x[i]);
		printf("\n");
	}
}

void triangularisation(float **a, float *b, int taille){
	int n = taille;
	for(int k=0; k<=n-2; k++){
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

void getData(int*dim, float***a, float **b, float ** x){
		
		float ** m= NULL, *sol =NULL, *v =NULL;
		FILE *pf= NULL;
		pf = fopen("data0.txt","r");
		if(pf!=NULL){
				fscanf(pf, "%d", dim);
				m = newMat(*dim);
				v = newVect(*dim);
				sol = newVect(*dim);
				for(int i=0; i< *dim;i++){
					for(int j=0; j< *dim; j++){
							fscanf(pf,"%f",&m[i][j]); //lit les donnees ligne par lign
						}
				}
				for(int i=0; i< *dim;i++){
					fscanf(pf,"%f",&v[i]); //lit les donnees ligne par lign
				}
				fclose(pf);
				for(int i=0; i< *dim; i++){ 
					sol[i]=0; //vecteur solution
				}
		}
		else{
			problem("can't open file");
		}
		*a = m;
		*b = v;
		*x = sol;
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
float*allocation1D(int l){
	float*b = malloc(3*sizeof(float));
	return b;
}
float**allocation2D(int l, int c){
	float**a = malloc(l*sizeof(float*));
	for(int i=0; i<l;i++){
		a[i] = malloc(c*sizeof(float));
	}
	return a;
}
float *newVect(int dim){
	float* v = NULL;
	v = malloc(dim*sizeof(float));
	if(v == NULL) problem("NE PEUT PAS ALLOUER UN VECTEUR");
	return v;
}
float **newMat(int dim){
		float** A = NULL;
		A = malloc(dim*sizeof(float*));
		if(A == NULL) problem("NE PEUT PAS ALLOUER UNE MATRICE");
		for(int i=0; i <dim; i++){
				A[i] = malloc(dim*sizeof(float));
				if(A[i] == NULL) problem("NE PEUT ALLOUER UN LIGNE DE MATRICE");
		}
		return A;
}
void problem(char* message){
		printf("%s\n", message);
		exit(2);
}

