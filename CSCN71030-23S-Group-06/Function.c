#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Function.h"
#include <stdlib.h>
int numRecipes = 0; // Keeps track of the number of recipes in the database

void addRecipe(const char* name, const char* ingredients, const char* instructions) {
    if (numRecipes < MAX_RECIPES) {
        strcpy(recipeDatabase[numRecipes].name, name);
        strcpy(recipeDatabase[numRecipes].ingredients, ingredients);
        strcpy(recipeDatabase[numRecipes].instructions, instructions);
        numRecipes++;
    }
    else {
        printf("Recipe database is full. Cannot add more recipes.\n");
        return -1; // indicate failure
    }
}

FILE* openFile(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }
    return file;
}

void writeRecipeToFile(FILE* file, const struct Recipe* recipe) {
    fprintf(file, "Name: %s\nIngredients: %s\nInstructions: %s\n", recipe->name, recipe->ingredients, recipe->instructions);
    fprintf(file, "----------\n"); // Add a separator between recipes for better readability
    if (ferror(file)) {
        printf("Error occurred while writing to the file.\n");
    }
}

void showRecipesFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char line[1000];
        int recipeNumber = 1; // Initialize the recipe number
        int foundRecipe = 0; // Initialize the flag to 0 (not found)

        while (fgets(line, sizeof(line), file) != NULL) {
            if (strstr(line, "Name: ") != NULL) {
                if (!foundRecipe) {
                    printf("Recipes in the file:\n");
                    foundRecipe = 1; // Set the flag to 1 (recipe found)
                }
                printf("Recipe %d:\n", recipeNumber);
                recipeNumber++; // Increment the recipe number for the next recipe
            }
            printf("%s", line);
        }

        fclose(file);

        if (!foundRecipe) {
            printf("There is no recipe in the database yet.\n");
        }
    }
    else {
        printf("Error: Could not open the file.\n");
    }
}




void displayMenu() {
    printf(" _____ ____  ____ ___  _   ____  ____  ____  _  __ _  _      _____ \n");
    printf("/  __//  _ \\/ ___\\  \\//  /   _\\/  _ \\/  _ \\/ |/ // \\/ \\  /|/  __/ \n");
    printf("|  \\  | / \\||    \\ \\  /   |  /  | / \\|| / \\||   / | || |\\ ||| |  _  \n");
    printf("|  /_ | |-||\\___ | / /    |  \\__| \\_/|| \\_/||   \\ | || | \\||| |_/\\ \n");
    printf("\\____\\\\_/ \\|\\____//_/     \\____/\\____/\\____/\\_|\\_\\\\_/\\_/  \\|\\____/ \n");

    printf("\nMenu:\n");
    printf("1. Show the existing recipes.\n");
    printf("2. Add recipes.\n");
    printf("3. Delete recipes.\n");
    printf("4. Generate random recipe\n");
    printf("5. Exit.\n");
    printf("Enter your choice: ");
}



// New function to get the number of recipes stored in the file
int getNumRecipes(const char* filename) {
    int count = 0;
    FILE* file = fopen(filename, "r"); // Open file for reading
    if (file != NULL) {
        char line[1000];
        while (fgets(line, sizeof(line), file) != NULL) {
            if (strstr(line, "Name: ") != NULL) {
                count++;
            }
        }
        fclose(file);
    }
    return count;
}

// Function to delete a recipe from the file
void deleteRecipeFromFile(const char* filename, int recipeNumber) {
    FILE* file = fopen(filename, "r"); // Open the file for reading
    FILE* tempFile = fopen("temp.txt", "w"); // Open a temporary file for writing

    if (file != NULL && tempFile != NULL) {
        char line[1000];
        int currentRecipeNumber = 0; // Initialize the current recipe number

        while (fgets(line, sizeof(line), file) != NULL) {
            if (strstr(line, "Name: ") != NULL) {
                currentRecipeNumber++;
                if (currentRecipeNumber == recipeNumber) {
                    // Skip the lines corresponding to the recipe to be deleted
                    for (int i = 0; i < 3; i++) {
                        fgets(line, sizeof(line), file);
                    }
                }
                else {
                    // Write the lines of other recipes (not to be deleted) to the temporary file
                    fputs(line, tempFile);
                }
            }
            else {
                // Write non-recipe lines to the temporary file
                fputs(line, tempFile);
            }
        }

        fclose(file);
        fclose(tempFile);

        // Replace the original file with the temporary file
        remove(filename);
        rename("temp.txt", filename);

        printf("Recipe %d deleted successfully.\n", recipeNumber);
    }
    else {
        printf("Error: Could not open the file or the temporary file.\n");
    }
}





void generateRecipe(const char* filename) {
    int numRecipes = getNumRecipes("Recipes.txt"); 

    if (numRecipes == 0) {
        printf("No recipes available.\n");
        return;
    }

    srand(time(NULL));

    char targetIngredient[100]; // User input for the ingredient to search
    printf("Please enter an ingredient that you would like to use in a recipe: ");
    fgets(targetIngredient, sizeof(targetIngredient), stdin);
    targetIngredient[strcspn(targetIngredient, "\n")] = '\0'; // Remove newline

    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        char line[1000];
        int recipeNumber = 0;
        int foundRecipe = 0;
        int matchingRecipeIndices[MAX_RECIPES];
        int matchingCount = 0;

        while (fgets(line, sizeof(line), file) != NULL) {
            if (strstr(line, "Name: ") != NULL) {
                recipeNumber++;
            }

            if (strstr(line, targetIngredient) != NULL) {
                matchingRecipeIndices[matchingCount++] = recipeNumber;
            }
        }

        fclose(file);

        if (matchingCount == 0) {
            printf("No recipes found with the specified ingredient.\n");
        }
        else {
            int randomIndex = matchingRecipeIndices[rand() % matchingCount];

            file = fopen(filename, "r");
            if (file != NULL) {
                recipeNumber = 0;
                int printRecipe = 0;

                while (fgets(line, sizeof(line), file) != NULL) {
                    if (strstr(line, "Name: ") != NULL) {
                        recipeNumber++;
                        if (recipeNumber == randomIndex) {
                            printf("Randomly generated recipe with the ingredient '%s':\n", targetIngredient);
                            printRecipe = 1;
                        }
                    }

                    if (printRecipe) {
                        printf("%s", line);
                    }
                }

                fclose(file);
            }
            else {
                printf("Error: Could not open the file.\n");
            }
        }
    }
    else {
        printf("Error: Could not open the file.\n");
    }
}