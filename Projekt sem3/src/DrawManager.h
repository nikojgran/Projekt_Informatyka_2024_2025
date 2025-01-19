#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#define FONT_PATH "./assets/fonts/font.ttf"
#define BG_TEXTURE_PATH "./assets/backgrounds/menu.jpeg"


class DrawManager
{
public:
    DrawManager(sf::Vector2u windowSize);

    bool InitializeResources();
    void DrawMenu(sf::RenderWindow* window);
    void DrawPause(sf::RenderWindow* window);
    void DrawGameOver(sf::RenderWindow* window);
    void DrawPlayer(sf::RenderWindow* window);
    void MovePlayerLeft(sf::RenderWindow* window);
    void MovePlayerRight(sf::RenderWindow* window);
    void DrawBall(sf::RenderWindow* window);
    bool MoveBall(sf::RenderWindow* window);
    bool BounceBall();
    void CollisionBall();
    void DrawBlocks(sf::RenderWindow* window);
    void InitializePlayer();
    void InitializeBall();
    void InitializeBlocks();
    void LoadLevel(int* levelIndex);
    bool WonGame(int* m_levelIndex);
    


private:
    bool LoadFont();
    bool LoadBackgroundTexture();
    void SetupText(sf::Text& text, const sf::Font& font, const std::string& content,
        unsigned int characterSize, const sf::Color& color,
        sf::Text::Style style, float xPos, float yPos);
    void InitializeBackgroundSprite();
    void InitializeMenuContent();
    void InitializePauseContent();
    void InitializeGameOver();
    void InitializeLevels(int *m_levelIndex);
    
    int currentLevel = 0;
    
    void InitializeGameContent();

    struct MenuContent {
        sf::Text title, playOption, exitOption;
    };

    struct PauseContent {
        sf::Text title, continueOption, menuReturnOption, exitOption;
    };

    struct GameContent 
    {
        sf::RectangleShape m_player;
        sf::CircleShape m_ball;
        sf::Vector2f m_ball_velocity;
        std::vector<sf::RectangleShape> m_blocks;
        sf::Text time, score, level, help;
        float m_player_velocity;
    };
    
    struct OverContent 
    {
        sf::Text over, again, score, exit;
        sf::ConvexShape splash;
    };

    sf::Vector2u m_windowSize;

    sf::Font m_font;
    sf::Texture m_bgTexture;
    sf::Sprite m_bgSprite;

    MenuContent m_menuContent;
    PauseContent m_pauseContent;
    GameContent m_gameContent;
    OverContent m_overContent;

};  

    


