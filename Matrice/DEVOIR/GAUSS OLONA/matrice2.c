#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void getData(int* dim , float***A , float** b , float** x);
void problem(char* message);
float* newVect(int dim);
float** newMat(int dim);
void solveTriangSup(int dim , float**A , float*b , float* x);
void gauss(int dim , float** A , float* b , float* x);
void solution_finale(float** matrice  , float*vecteur,  int ligne , int colonne , float**solution);
int recherche_max(float** matrice , int ligne , int colonne , int dim );
void transformer_la_matrice(float** matrice , float* vecteur ,  int dim );
void permutation(float** matrice , int ligne1 , int ligne2 , int dim);
void permutation_vecteur(float* vecteur , int ligne1 , int ligne2 , int dim);
void afficher_vecteur(float* vecteur , int ligne);
void afficher_matrice(float** matrice , int ligne , int colonne);
void afficher_matrice_et_vecteur(float** matrice , float* vecteur , int ligne , int colonne);
void affichage_du_resultat(float* vecteur , int ligne );
void afficher_equation(float** matrice , float* vecteur , int ligne , int colonne);
int main(int argc, char **argv)
{
///---------------donne
	int dim=0 ; 
	float** A=NULL;
	float* b = NULL;
	float* resultat= NULL;
	getData(&dim , &A, &b , &resultat);
	printf("trouvons les solutions de cette equation : \n");
	afficher_equation(A, b , dim , dim);
	
///--------------traitement

	//printf("\n");
	//printf("max %d\n" , recherche_max(A , 0 , 0 , 3));
	//rintf("--------------------\n");
	//solveTriangSup(dim , A, b , resultat);
	//solveTriangSup(dim , A, b , resultat);
	transformer_la_matrice(A, b , dim);
	//permutation(A , 0 , 1 , 3);
	solution_finale( A  , b,   dim , dim , &resultat);

///-----------------resultat

	printf("les solutions de l'equation : ");
	affichage_du_resultat(resultat , dim);
	return 0;
}
void getData(int* dim , float***A , float** b , float** x){ // x pour le resultat
/// Pointeur pour les donnees 
	float** M= NULL , *v = NULL , *sol= NULL;
	FILE *pf=NULL;
	
	pf= fopen("data.txt","r");
	if(pf!=NULL){
			fscanf(pf,"%d" , dim);		//recuperer la dimension
			M=newMat(*dim);				//allouer de la place pour la matrice
			v = newVect(*dim);		//allouer de la place pour la second membre
			sol= newVect(*dim);		// allouer de la place pour la solution
			for(int i=0 ; i<*dim ; i++ ){
				for(int j=0 ; j<*dim ; j++){
					fscanf(pf , "%f" ,&M[i][j] );		//lit les donner ligne par ligne
				}
			}
			for(int i=0 ; i<*dim ; i++)
				fscanf(pf , "%f" , &v[i]);
			fclose(pf);
			for(int i=0; i<*dim ; i++) sol[i]=0; 	//initialiser le vecteur solution
	}else{
		problem("Can't open file");
		exit(2);
	}
	
/// Revoie les adresses des contenue vers main
	*A=M;
	*b=v;
 	*x=sol;

}
 void problem(char* message){
	 printf("%s\n ", message);
	 exit(2);
}
float** newMat(int dim){
	float** A =NULL;
	A = malloc(dim*sizeof(float*));
	if(A==NULL) problem("Ne peut allouer une matirce");
	for(int i=0; i<dim ; i++){
		A[i]=malloc(dim*sizeof(float));
		if(A[i]==NULL) problem("Ne peut allouer une ligne de matrice");
	}
	return A;
}

	float* newVect(int dim){
		float*v= NULL;
		v= malloc(dim*sizeof(float));
		if(v==NULL) problem("ne peut allouer un vecteur");
		return v;
	}
//	void gauss(int dim , float** A , float* b , float* x){
///triangularisation de A 
	//	for(int k=0 ; k<dim ; k++){
		//	for(int i=k+1 ; i<dim ; i++){
			//	for(int j=k+1 ; j< dim  ; j++)
				//	A[i][j]-= (A[i][k]/A[k][k]*A[k][j]);
				// b[i] -=(A[i][k]/ A[k][k]*b[k]);
				//A[i][k]=0;
			// }  
		//}	
		//solveTriangSup( dim , A , b , x);
		
	//}
	void transformer_la_matrice(float** matrice , float* vecteur,  int dim ){
		int k=0;
		int i=0;
		int j=0;
		int max=0;
		for( k=0 ; k<dim ; k++){
			max=recherche_max(matrice , k , k , dim);
			//printf("\n");
			//afficher_matrice_et_vecteur(matrice , vecteur , dim , dim);
			
			if(max!=k){
				permutation(matrice , max , k , dim);
				permutation_vecteur(vecteur , max , k , dim);
				//printf("\n");
				//afficher_matrice_et_vecteur(matrice , vecteur , dim , dim);	
			}
			
			for(i=k+1 ; i<dim ; i++){
			
				for(j=k+1 ; j<dim ; j++){
					matrice[i][j]=(matrice[i][j] - (((matrice[i][k])/ (matrice[k][k]))* (matrice[k][j])));
				}
				vecteur[i]=vecteur[i]-((matrice[i][k]/matrice[k][k])*vecteur[k]);
				(matrice[i][k])=0;
			}	
		}
			printf("\n");
			printf("apres la triangularisation , l'equation devient : ");
			afficher_equation(matrice , vecteur , dim , dim);
		
	}
	
	

	void solveTriangSup(int dim , float**matrice , float*vecteur , float* x){
		int k=0;
		int i=0;
		int j=0;
		for( k=0 ; k<dim ; k++){
			for(i=k+1 ; i<dim ; i++){
				for(j=k+1 ; j<dim ; j++){
					matrice[i][j]=(matrice[i][j] - (((matrice[i][k])/ (matrice[k][k]))* (matrice[k][j])));
				}
				vecteur[i]=vecteur[i]-((matrice[i][k]/matrice[k][k])*vecteur[k]);
				(matrice[i][k])=0;
			}
		}
		//printf("apres la triangularisation , l'Ă©quation devient : ");
		//afficher_matrice_et_vecteur(matrice , vecteur , dim , dim);
		
	}
	
	void solution_finale(float** matrice  , float*vecteur,  int ligne , int colonne , float** solution){
		float* resultat= malloc(ligne*sizeof(float)) ;
		resultat[ligne-1]=(1/matrice[ligne-1][ligne-1])*vecteur[ligne-1];
		int i=0;
		int j=0;
		float somme=0; 
		for(i=ligne-2 ; i>=0 ; i--){
			for(j=i+1 ; j<ligne ; j++ ){
				somme= somme+(matrice[i][j]*resultat[j]);
			}
			resultat[i]=(1/matrice[i][i])*(vecteur[i]-somme);
			somme=0;
		}
		*solution = resultat;
	}
	
	int recherche_max(float** matrice , int ligne , int colonne , int dim ){
		int resultat=ligne;
		float max=matrice[ligne][colonne];
		for(int i= ligne ; i<dim ; i++){
			if(fabs(max)< fabs(matrice[i][colonne])){
				resultat=i ;
				max= matrice[i][colonne];
			}
			
		}
		return resultat;
	}
	
	
	void permutation(float** matrice , int ligne1 , int ligne2 , int dim){
		float*t=matrice[ligne2];
		matrice[ligne2]=matrice[ligne1];
		matrice[ligne1]=t;
	}
	
	void permutation_vecteur(float* vecteur , int ligne1 , int ligne2 , int dim){
		float t=vecteur[ligne2];
		vecteur[ligne2]=vecteur[ligne1];
		vecteur[ligne1]=t;
	}
	
	
	void afficher_matrice(float** matrice , int ligne , int colonne){
		printf("\n");
		for(int i=0 ; i<ligne ; i++){		
			for(int j=0 ; j<colonne ; j++){
				printf("%g ", matrice[i][j]);
			}		
			printf("\n");
		}
		printf("\n");	
	}
	
	void afficher_vecteur(float* vecteur , int ligne){
		printf("\n");
		for(int i=0 ; i<ligne ; i++){		
			printf("%g ", vecteur[i]);
		}
		printf("\n");	
	}
	
	void afficher_matrice_et_vecteur(float** matrice , float* vecteur , int ligne , int colonne){
		printf("\n");
		for(int i=0 ; i<ligne ; i++){		
			for(int j=0 ; j<colonne ; j++){
				printf("%g ", matrice[i][j]);
			}
			printf("%g ", vecteur[i]);
			printf("\n");
		}
		printf("\n");	
	}
	
	void affichage_du_resultat(float* vecteur , int ligne ){
		printf("les solutions de l'equation : ");
		printf("\n");
		for(int i=0 ; i< ligne ; i++){
			printf("x%d = %g ;",i , vecteur[i] );
		}
		printf("\n");
	}
	
	void afficher_equation(float** matrice , float* vecteur , int ligne , int colonne){
		printf("\n");
		for(int i=0 ; i<ligne ; i++){		
			for(int j=0 ; j<colonne ; j++){
				printf(" %g ", matrice[i][j] );
			}
			printf("= %g ", vecteur[i]);
			printf("\n");
		}
		printf("\n");	
	}
	
	
	




