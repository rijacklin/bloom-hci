/**
 * Name:              Richard Jacklin
 * Student ID:        3113256
 * Course:            COMP482
 * Assignment Number: 3
 */

#include "./include/App.h"
#include <iostream>

int main(int argc, char **argv) {
  try {
    // Create app instance
    App app;

    // Error check
    if (!app.initialize(argc, argv)) {
      std::cout << "Failed to initialize Bloom" << std::endl;
    }

    // Run application
    app.run();
  } catch (const std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
    return 0;
  }

  return 0;
}
