
#include "FinalCreditsEvent.h"
#include <iostream>
#include <chrono>
#include <thread>


void FinalCreditsEvent::ShowEndingChoice() {
    std::cout << "=== FINAL CHOICE ===\n";
    std::cout << "1. Destroy the Hellgate (Seal evil forever)\n";
    std::cout << "2. Claim the Hellgate's power (Join the demons)\n";
    std::cout << "Your destiny awaits... Choose wisely: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
        GoodEnding();
        break;
    case 2:
        EvilEnding();
        break;
    default:
        std::cout << "Indecisive to the end... The gate collapses on its own.\n";
        GoodEnding();
        break;
    }
}

void FinalCreditsEvent::GoodEnding() {
    std::cout << "\n\n=== THE HERO'S LEGACY ===\n";
    std::cout << "With one final mighty blow, you shatter the Hellgate.\n";
    std::cout << "The demons scream as they're pulled back into the abyss.\n";
    std::cout << "The land begins to heal, and you're celebrated as the savior.\n";
    std::cout << "Though the scars of war remain, a new age of peace dawns.\n";

    // Bonus for good ending
    
    std::this_thread::sleep_for(std::chrono::seconds(10));
}

void FinalCreditsEvent::EvilEnding() {
    std::cout << "\n\n=== THE DARK LORD RISES ===\n";
    std::cout << "You place your hand upon the Hellgate, absorbing its power.\n";
    std::cout << "Your humanity burns away as demonic energy courses through you.\n";
    std::cout << "The surviving demons bow before their new master.\n";
    std::cout << "The world trembles as a new era of darkness begins.\n";


    std::this_thread::sleep_for(std::chrono::seconds(10));
}

void FinalCreditsEvent::Start() {
    std::cout << "\n\n=== CONGRATULATIONS! ===\n";
    std::cout << "You have defeated the final boss and completed the game!\n\n";

    ShowCredits();
    ShowEndingChoice();
    std::cout << "\n\nThank you for playing!\n";
    std::this_thread::sleep_for(std::chrono::seconds(10));
}

void FinalCreditsEvent::ShowCredits() {
    std::cout << "=== FINAL CREDITS ===\n";
    std::cout << "Game Developer: [Your Name]\n";
    std::cout << "Design: [Your Name]\n";
    std::cout << "Special Thanks To:\n";
    std::cout << "- All playtesters\n";
    std::cout << "- The C++ community\n";



}

