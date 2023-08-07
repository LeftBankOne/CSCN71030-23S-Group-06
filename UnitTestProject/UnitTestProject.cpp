#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "CppUnitTest.h"
#
#include <iostream>
#define MAX_RECIPES 100
#define MAX_LINE_LENGTH 1000
struct Recipe {
	char name[100];
	char ingredients[500];
	char instructions[1000];
};

extern "C" struct Recipe recipeDatabase[MAX_RECIPES]; // An Array of structure to store multiple recipes.
extern "C" void addRecipe(const char* name, const char* ingredients, const char* instructions);
extern "C" FILE* openFile(const char* filename, const char* mode);
extern "C" void writeRecipeToFile(FILE* file, const struct Recipe* recipe);
extern "C" void showRecipesFromFile(const char* filename);
extern "C" void displayMenu();
extern "C" int getNumRecipes(const char* filename);
extern "C" void deleteRecipeFromFile(const char* filename, int recipeNumber);
extern "C" void generateRecipe(const char* filename);



using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTestProject
{
	TEST_CLASS(UnitTestProject)
	{
	public:
      

        TEST_METHOD(TestAddRecipe)
        {
            // Initialize any necessary data structures and variables
            int numRecipes = 0;
            const int MaxRecipes = 10;

            // Test adding a recipe
            addRecipe("Recipe 1", "Ingredients 1", "Instructions 1");
            Assert::AreEqual(1, numRecipes);

            // Test adding another recipe
            addRecipe("Recipe 2", "Ingredients 2", "Instructions 2");
            Assert::AreEqual(2, numRecipes);
        }
        
        TEST_METHOD(TestWriteAndShowRecipes)
        {
            const char* testFileName = "TestRecipes.txt";

            FILE* file = fopen(testFileName, "w");
            if (file != NULL) {
                // Write some initial data to the test file if needed
                // For example, you can write a header line:
                fprintf(file, "Test Recipes:\n");
                fclose(file);
            }
            else {
                Assert::Fail(L"Failed to create the test file.");
            }

            // Test writing and showing recipes
            struct Recipe recipe;
            strcpy(recipe.name, "Test Recipe");
            strcpy(recipe.ingredients, "Test Ingredients");
            strcpy(recipe.instructions, "Test Instructions");
            writeRecipeToFile(file, &recipe);
            fclose(file);

            std::stringstream buffer;
            std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

            showRecipesFromFile("TestRecipes.txt");
            std::string expectedOutput = "Recipes in the file:\nRecipe 1:\nName: Test Recipe\nIngredients: Test Ingredients\nInstructions: Test Instructions\n----------\n";
            Assert::AreEqual(expectedOutput, buffer.str());

            std::cout.rdbuf(oldCoutBuffer);
        }

        TEST_METHOD(TestGenerateRecipe)
        {
            const char* testFileName = "TestRecipes.txt";

            FILE* file = fopen(testFileName, "w");
            if (file != NULL) {
                // Write some initial data to the test file if needed
                // For example, you can write a header line:
                fprintf(file, "Test Recipes:\n");
                fclose(file);
            }
            else {
                Assert::Fail(L"Failed to create the test file.");
            }

            // Test generating a recipe
            struct Recipe recipe;
            strcpy(recipe.name, "Test Recipe");
            strcpy(recipe.ingredients, "Test Ingredients");
            strcpy(recipe.instructions, "Test Instructions");
            writeRecipeToFile(file, &recipe);
            fclose(file);

            std::stringstream buffer;
            std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

            generateRecipe("TestRecipes.txt");
            std::string expectedOutput = "Randomly generated recipe with the ingredient 'Test Ingredients':\nRecipe 1:\nName: Test Recipe\nIngredients: Test Ingredients\nInstructions: Test Instructions\n----------\n";
            Assert::AreEqual(expectedOutput, buffer.str());

            std::cout.rdbuf(oldCoutBuffer);
        }

        TEST_METHOD(TestDeleteRecipe)
        {
            const char* testFileName = "TestRecipes.txt";

            FILE* file = fopen(testFileName, "w");
            if (file != NULL) {
                // Write some initial data to the test file if needed
                // For example, you can write a header line:
                fprintf(file, "Test Recipes:\n");
                fclose(file);
            }
            else {
                Assert::Fail(L"Failed to create the test file.");
            }
            // Test deleting a recipe
            struct Recipe recipe;
            strcpy(recipe.name, "Test Recipe");
            strcpy(recipe.ingredients, "Test Ingredients");
            strcpy(recipe.instructions, "Test Instructions");
            writeRecipeToFile(file, &recipe);
            fclose(file);

            deleteRecipeFromFile(testFileName, 1);
            Assert::AreEqual(0, getNumRecipes(testFileName));
        }
		
	};
}
