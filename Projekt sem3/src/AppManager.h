#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "DrawManager.h"

class AppManager
{
public:
    AppManager();
    void StartApp();
private:
    void DispatchState();
    bool m_levelLoaded = false;
    void HandleEvent(sf::Event* event);
    void HandleGameInputs();
    void DispatchEvent(sf::Event* event);
    void HandleMenuState(sf::Event* event);
    void HandleGameState(sf::Event* event);
    void HandlePauseState(sf::Event* event);
    void HandleOverState(sf::Event* event);
    void ExitApp();

    enum class AppState {
        MENU,
        GAME,
        PAUSE,
        HELP,
        GAME_OVER
    };

    sf::RenderWindow m_window;
    int m_levelIndex;
    DrawManager m_drawManager;
    AppState m_appState;
};

