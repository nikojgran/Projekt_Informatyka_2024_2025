#include "AppManager.h"

AppManager::AppManager() :
    m_window(sf::VideoMode(1280, 720), "Game"),
    m_drawManager(m_window.getSize()),
    m_appState(AppState::MENU),
    m_levelIndex(1){}

void AppManager::StartApp()
{
    if (!m_drawManager.InitializeResources())
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
                
            
            if (m_drawManager.MoveBall(&m_window)) {
                m_appState = AppState::GAME_OVER;
            }
            if (m_drawManager.WonGame(&m_levelIndex)) {
                m_appState = AppState::GAME_OVER;
            }
            
            break;
        case AppState::PAUSE:
            m_drawManager.DrawPause(&m_window);
            break;
        case AppState::GAME_OVER:
            m_drawManager.DrawGameOver(&m_window);
            m_drawManager.InitializePlayer();
            m_drawManager.InitializeBall();
            m_levelLoaded = false;
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

    }
}

void AppManager::HandleMenuState(sf::Event* event)
{
    if (event->type == sf::Event::KeyPressed) {
        if (event->key.code == sf::Keyboard::Num1) {
            m_appState = AppState::GAME;
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