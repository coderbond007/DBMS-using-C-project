/*************************************************************DBMS PROJECT*************************************************************************
* Project deals with database managment of the Person GENES. The Databse stores the information about the Person name, age, GENE information 
* (ACGT format).
*
* In the scientific researches GENES information is stored as well as their match percentage with the sample GENE to refine the searches accordingly.
* A database is too created to get results and find out the region(range of percentage) where match percentages are are most frequently occured.
* This helps them to make medicines, perform experiments with minimum risks.
*
* Current program have capacity to store and process the data of upto 1000 persons with their GENE length upto 500 charecters.
* Program also supports for the RANGE QUERIES giving information about the users lying in the range with the details of match percentage and age.
*
* This sample Database is created using rand() in C.
* 
* To enable fast queries processing, program uses Levenshtein Matching algorithm to compute the match percentage between two strings and AVL Tree to
* store the match percetage accordingly.
***************************************************************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "tree.h"
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

int levenshteinmatch(char* s1, char* s2);

int main(int argc, char const *argv[])
{
	/* CODE */
	node* root = NULL;

	FILE* f = fopen("database.txt","r");

	// If no such file exists
	if(f == NULL) {
		printf("No such file exists in the directory\n");
		return 0;
	}

	// Sample GENE from which each users GENE will be matched
	char sample[500] = "GCCCCCACAGCTGAAATGGGGGCCTTCCGCATACATGATTACATGTCGGCAGTTACTGCGCTTTCACCCGGGACCACTTGTGGAAAAACTCTCTGAGTATCCCTCCGGAAGACATACATGCTGAGCTAGCCGATAAGCCGCGTAATATGGAAACAAATACGGTGACAGTGTTCAATCTAATCTACCTATTTGCGTGGGACCTTGAATTTAAAAGATCAGTTGGGTGATTATGAAGTCATCTTATCCAGTAGGAAATCCTACCTTGCTCGAACATAACCCTATGAGCGAGTAGCGAGGTACGGTAGCTAGACTTCTGAAGCTCGCTTACCCTGAAGAGACGGATTAACAAGGGTGGATTAGCTAAGTTGTAAGGGTCTGTAATATGGATAACTCGCAGTATGCGGTCCTGTTCGTGTCCTTAAGGGCAGCATCGTATTTCAGCGCAGTATACTGAGCTACCTCTGTTCATGATCGTATTTCCGTACTAGCTCGCACAGAGG";
	

	// Input from the file e.g.      Name Age Gene (all in a single line)
	char nam[100],genes[500];
	int new_age;

	// Taking input from file until End Of File is not reached
	while( fscanf (f,"%s %d %s",nam,&new_age,genes) != EOF) {

		// Memory alloted to a node and initialised accordingly
		node* new_node = getnode();
		strcpy(new_node->name,nam);
		strcpy(new_node->gene,genes);
		new_node->age = new_age;
		new_node->left = new_node->right = NULL;
		new_node->height = 1;

		// levenshteinmatch(sample,genes) / 5 is done because to we are taking GENES length to be 500.
		// And to calculate % we multiply the number by 100. So 500 is reduced to 5. Thus computing the correct results.
		// To compute more refine results we can use FLOAT or DOUBLE data type to store the match percentage.
		new_node->matchpercentage = levenshteinmatch(sample,genes) / 5;

		// Data is inserted in the tree.
		root = insert(root,new_node);
	}

	// Takes the range of input in the form of L R where L <= R and L and R are two integers
	printf("Enter the range to receive all names with their ages having GENES matching percentage lying in the range\n");
	printf("Input in form e.g. 24 56\n");
	int left_bound, right_bound;
	scanf("%d %d",&left_bound, &right_bound);
	if(left_bound > right_bound || left_bound < 0 || right_bound > 100){
		printf("Invalid range\n");
	} else {
		printf("Type 1 for increasing order of GENE matching percentage\n"
				"Type 2 for decreasing order of GENE matching percentage\n");
		int order;
		scanf("%d", &order);
		if(order == 1){
			// Displays the data in the increasing order of match percentage
			printf("\nName           Match - Percentage      Age\n");
			printincreasing(root,left_bound,right_bound);
		} else if(order == 2) {
			// Displays the data in the decreasing order of match percentage
			printf("\nName           Match - Percentage      Age\n");
			printdecreasing(root,left_bound,right_bound);
		} else {
			printf("Invalid input\n");
			return 0;
		}
	}
	fclose(f);
	return 0;
}

int levenshteinmatch(char* s1, char* s2)
{
	unsigned int x,y;
	unsigned int dist[501][501];
	dist[0][0] = 0;
	for(x = 1; x <= 500; x++) {
		dist[x][0] = dist[x - 1][0] + 1;
	}
	for(y = 1; y <= 500; y++) {
		dist[0][y] = dist[0][y - 1] + 1;
	}
	for(x = 1; x <= 500; x++){
		for(y = 1; y <= 500; y++) {
			dist[x][y] = MIN3( dist[x - 1][y] +1, dist[x][y - 1] + 1, dist[x - 1][y - 1] + (s1[y - 1] == s2[x - 1] ? 0 : 1));
		}
	}
	return dist[500][500];
}