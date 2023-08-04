#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Function.h"

int main() {
    int choice;
    int numRecipesToAdd;
    int recipeToDelete;

    // Get the initial number of recipes from the file
    int numRecipes = getNumRecipes("Recipes.txt"); // Get the number of recipes from "Recipes.txt"

    do {
        displayMenu();
        int scanfResult = scanf("%d", &choice);
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Consume any remaining characters in the input buffer
        if (scanfResult != 1) {
            printf("Invalid input. Please enter a number.\n");
        }
        else {

            switch (choice) {
            case 1:
                // Show the number of recipes in the file and list all the recipes
                showRecipesFromFile("Recipes.txt");
                break;
            case 2:
                printf("Enter the number of additional recipes to add: ");
                scanf("%d", &numRecipesToAdd);
                getchar(); // Consume the newline character left by scanf
                // Open or create the file if it's not existed
                FILE* file = openFile("Recipes.txt", "a"); // Open file name "Recipes.txt" for appending

                for (int i = 0; i < numRecipesToAdd; i++) {
                    char name[100];
                    char ingredients[500];
                    char instructions[1000];

                    printf("Enter the name of Recipe %d: ", i + 1);
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = '\0';

                    printf("Enter the ingredients of Recipe %d: ", i + 1);
                    fgets(ingredients, sizeof(ingredients), stdin);
                    ingredients[strcspn(ingredients, "\n")] = '\0';

                    printf("Enter the instructions of Recipe %d: ", i + 1);
                    fgets(instructions, sizeof(instructions), stdin);
                    instructions[strcspn(instructions, "\n")] = '\0';

                    addRecipe(name, ingredients, instructions);
                    // Write the data to file
                    writeRecipeToFile(file, &recipeDatabase[i]);
                }
                fclose(file);
                break;
            case 3:
                // Delete a recipe
                printf("Enter the recipe number to delete: ");
                int scanfResult = scanf("%d", &recipeToDelete);
                while ((c = getchar()) != '\n' && c != EOF); 

                if (scanfResult != 1) {
                    printf("Invalid input. Please enter a number.\n");
                }
                else {
                    if (recipeToDelete < 1 || recipeToDelete > numRecipes) {
                        printf("Invalid recipe number. Please enter a valid recipe number.\n");
                    }
                    else {
                        deleteRecipeFromFile("Recipes.txt", recipeToDelete);
                        numRecipes--;
                    }
                }
            case 4:
                // Generate and display a random recipe
                generateRecipe("Recipes.txt");
                break;

            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
    } while (choice != 5);
    return 0;
}
