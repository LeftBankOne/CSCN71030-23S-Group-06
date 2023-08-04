#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Function.h"

int main() {
  

    //TEST #1                                            
    // Get the initial number of recipes from the file
    int numRecipes = getNumRecipes();
    //should be 7 as there are currently no recipes stored in file 
    printf("Initial getNumRecipes() function testing, expected output: 7 output given %d\n", numRecipes); 
    if (numRecipes == 7)       //WHEN OPENING NEW FILE IT STARTS FROM 2 RECIPES SO THIS WILL BE SET TO 2 AND WILL BE INCREMENTED EVERY TIME PROGRAM COMPILES AGAIN AS NEW RECIPE IS ADDED TO FILE EACH TIME
        printf("Test #1 for getNumRecipes = passed\n");
    else
        printf("Test #1 for getNumRecipes = failed\n");

    //PASSED!

    
    //TEST #2
    //This test will test the addRecipe function and also the numRecipes function
    FILE* file = openFile("TestingRecipes.txt", "a"); // Open file name "Recipes.txt" for appending
     addRecipe("sunny side eggs", "eggs, butter, salt", "1. heat butter in pan 2. crack eggs let cook 3. add salt to taste");
     writeRecipeToFile(file, &recipeDatabase[0]); //saving the added recipe to file now
     fclose(file);

     int newNumRecipes = getNumRecipes();
     //Testing add recipe and get number of recipes functions 
     if (newNumRecipes == numRecipes + 1)
         printf("Test #2 for addRecipe and getNumRecipes = passed\n");
     else
         printf("Test #2 for addRecipe and getNumRecipes = failed\n");

     //PASSED!
    

    return 0;
}


