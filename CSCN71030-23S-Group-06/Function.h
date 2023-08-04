#pragma once
#define MAX_RECIPES 100
#define MAX_LINE_LENGTH 1000
struct Recipe {
    char name[100];
    char ingredients[500];
    char instructions[1000];
};


struct Recipe recipeDatabase[MAX_RECIPES]; // An Array of structure to store multiple recipes.
void addRecipe(const char* name, const char* ingredients, const char* instructions);
FILE* openFile(const char* filename, const char* mode);
void writeRecipeToFile(FILE* file, const struct Recipe* recipe);
void showRecipesFromFile(const char* filename);
void displayMenu();
int getNumRecipes();
void deleteRecipeFromFile(const char* filename, int recipeNumber);
//struct Recipe generaterecipe();