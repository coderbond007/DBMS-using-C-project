# DBMS-using-C-project
**Scientific Database Management of Genes**

GENES Data of many persons is maintained with their match percentage(matched with a reference gene), age and name is maintained efficiently.
Files include

1. **tree.c** - contains the Data Structure *AVL Tree* for efficiently maintaining the Genes data with fast query processing
2. **tree.h** - header file which contains details of functions used in tree.c
3. **project.c** - This is a driver program which takes the input from a file and calculates the match percentage with reference GENE.
4. **database.txt** - This file contains the sample database of 10 people with their NAME, AGE and GENE(1000 characters length)

GENE Matching is performed using ***Levenshtein Match***.
