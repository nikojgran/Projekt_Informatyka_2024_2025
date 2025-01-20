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
    void HandleNickState(sf::Event* event);
    void HandleWonState(sf::Event* event);
    void HandleChooseState(sf::Event* event);
    void HandleHelpState(sf::Event* event);
    void SaveScoreToFile();
    void LoadScoresFromFile();
    void ExitApp();

    enum class AppState {
        MENU,
        NICK,
        CHOOSE,
        GAME,
        LEADERBOARD,
        PAUSE,
        HELP,
        GAME_OVER,
        WON
    };
    
    struct PlayerScore {
        std::string nick;
        int score;
    };

    sf::RenderWindow m_window;
    int m_levelIndex;
    DrawManager m_drawManager;
    AppState m_appState;
    std::string m_playerNick;
    int m_playerScore;
    std::string m_currentNick;
    std::vector<PlayerScore> m_leaderboard;
};

