#include "AppManager.h"

AppManager::AppManager() :
    m_window(sf::VideoMode(1280, 720), "Game"),
    m_drawManager(m_window.getSize()),
    m_appState(AppState::MENU),
    m_levelIndex(2),
    m_playerScore(0){}

void AppManager::StartApp()
{
    if (!m_drawManager.InitializeResources(&m_playerScore))
    {
        return;
    }
    m_window.setFramerateLimit(60);

    while (m_window.isOpen()) {
        sf::Event event;
        HandleEvent(&event);

        HandleGameInputs();

        m_window.clear();

        DispatchState();

        m_window.display();
    }
}
void AppManager::DispatchState()
{
    switch (m_appState) {
        case AppState::MENU:
            m_drawManager.DrawMenu(&m_window);
            break;

        case AppState::GAME:
            m_drawManager.DrawPlayer(&m_window);
            m_drawManager.DrawBall(&m_window);
            if (!m_levelLoaded) {
                m_drawManager.LoadLevel(&m_levelIndex);
                m_levelLoaded = true;
            }
            m_drawManager.DrawBlocks(&m_window);
                
            
            if (m_drawManager.MoveBall(&m_window, &m_playerScore)) {
                m_appState = AppState::GAME_OVER;
            }
            if (m_drawManager.WonGame(&m_levelIndex)) {
                m_appState = AppState::WON;
                m_drawManager.LoadLevel(&m_levelIndex);
                
            }
            
            break;

        case AppState::PAUSE:
            m_drawManager.DrawPause(&m_window);
            break;

        case AppState::GAME_OVER:
            m_drawManager.InitializeGameOver(&m_playerScore);
            m_drawManager.DrawGameOver(&m_window);
            m_drawManager.InitializePlayer();
            m_drawManager.InitializeBall();
            m_levelIndex = 1;
            m_levelLoaded = false;
            break;

        case AppState::NICK:
            m_drawManager.DrawNickInput(&m_window, &m_currentNick);
            break;

        case AppState::WON:
            m_drawManager.InitializeGameWon(&m_playerScore);
            m_drawManager.DrawGameWon(&m_window);
            break;
    }
}

void AppManager::HandleEvent(sf::Event* event)
{
    while (m_window.pollEvent(*event)) {

        if (event->type == sf::Event::Closed) {
            m_window.close();
        }

        DispatchEvent(event);
    }
    
}

void AppManager::DispatchEvent(sf::Event* event)
{
    switch (m_appState) {
        case AppState::MENU:
            HandleMenuState(event);
            break;
        case AppState::GAME:
            HandleGameState(event);
            break;
        case AppState::PAUSE:
            HandlePauseState(event);
            break;
        case AppState::GAME_OVER:
            HandleOverState(event);
            break;
        case AppState::NICK:
            HandleNickState(event);
            break;
        case AppState::WON:
            HandleWonState(event);
            break;
    }
}

void AppManager::HandleMenuState(sf::Event* event)
{
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::Num1) {
            m_appState = AppState::NICK;

        }
        else if (event->key.code == sf::Keyboard::Num2) {
            ExitApp();
        }
    }
}

void AppManager::HandleGameState(sf::Event* event)
{
    if (event->type == sf::Event::KeyPressed) {

        if (event->key.code == sf::Keyboard::Escape) {
            m_appState = AppState::PAUSE;
        }

    };

  
 

}

void AppManager::HandlePauseState(sf::Event* event)
{
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::Num1) {
            m_appState = AppState::GAME;
        }
        else if (event->key.code == sf::Keyboard::Num2) {
            m_appState = AppState::MENU;
        }
        else if (event->key.code == sf::Keyboard::Num3) {
            ExitApp();
        }
    }
}

void AppManager::HandleOverState(sf::Event* event)
{
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::Num1) {
            m_appState = AppState::MENU;
        }
        
    }

}

void AppManager::HandleNickState(sf::Event* event)
{
    if (event->type == sf::Event::TextEntered) {
        if (event->text.unicode < 128) { 
            if (event->text.unicode == 8 && !m_currentNick.empty()) {
                m_currentNick.pop_back(); 
            }
            else if (event->text.unicode != 8) {
                m_currentNick += static_cast<char>(event->text.unicode); 
            }
        }
    }

    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::Enter) {
            m_appState = AppState::GAME;
        }
    }
}

void AppManager::HandleWonState(sf::Event* event)
{
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::Num1) {
            m_appState = AppState::MENU;
        }

    }
}


void AppManager::ExitApp()
{
    m_window.close();
}

void AppManager::HandleGameInputs()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_drawManager.MovePlayerLeft(&m_window);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_drawManager.MovePlayerRight(&m_window);
    }

}