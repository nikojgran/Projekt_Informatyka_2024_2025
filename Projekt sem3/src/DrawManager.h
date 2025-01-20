#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#define FONT_PATH "./assets/fonts/font.ttf"
#define BG_TEXTURE_PATH "./assets/backgrounds/menu.jpeg"
#define LVL1_BLOCK_PATH "./assets/blocks/lvl1.png"
#define LVL2_BLOCK_PATH "./assets/blocks/lvl2.png"
#define LVL1_PIC_PATH "./assets/levels/lvl1.png"
#define LVL2_PIC_PATH "./assets/levels/lvl2.png"

class DrawManager
{
public:
    DrawManager(sf::Vector2u windowSize);

    bool InitializeResources(int* m_playerScore);
    void DrawMenu(sf::RenderWindow* window);
    void DrawPause(sf::RenderWindow* window);
    void DrawGameContent(sf::RenderWindow* window);
    void DrawGameOver(sf::RenderWindow* window);
    void DrawGameWon(sf::RenderWindow* window);
    void DrawPlayer(sf::RenderWindow* window);
    void DrawChoose(sf::RenderWindow* window);
    void DrawHelp(sf::RenderWindow* window);
    void MovePlayerLeft(sf::RenderWindow* window);
    void MovePlayerRight(sf::RenderWindow* window);
    void DrawBall(sf::RenderWindow* window);
    bool MoveBall(sf::RenderWindow* window, int* m_playerScore);
    bool BounceBall();
    void CollisionBall(int* m_playerScore);
    void DrawBlocks(sf::RenderWindow* window);
    void DrawNickInput(sf::RenderWindow* window, std::string* m_currentNick);
    void InitializePlayer();
    void InitializeBall();
    void InitializeBlocks();
    void LoadLevel(int* levelIndex);
    bool WonGame(int* m_levelIndex);
    void InitializeGameOver(int* m_playerScore);
    void InitializeGameWon(int* m_playerScore);
    void InitializeGameContent(int* m_playerScore, int* m_levelIndex);

private:
    bool LoadFont();
    bool LoadBackgroundTexture();
    bool LoadLevelTexture();
    void SetupText(sf::Text& text, const sf::Font& font, const std::string& content,
        unsigned int characterSize, const sf::Color& color,
        sf::Text::Style style, float xPos, float yPos);
    void InitializeBackgroundSprite();
    void InitializeMenuContent();
    void InitializeHelpContent();
    void InitializePauseContent();
    void InitializeChooseContent();
    
    void InitializeLevels(int *m_levelIndex);
    
    int currentLevel = 0;
    
    
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
        sf::Text score, level, help;
        sf::Texture lvl1Block, lvl2Block;
        float m_player_velocity;
    };

    struct NickContent 
    {
        sf::Text  m_nickInputText, m_currentNickText;
    };
    
    struct OverContent 
    {
        sf::Text over, score, exit;
        sf::ConvexShape splash;
    };
    struct WonContent
    {
        sf::Text won, score, exit;
    };
    struct ChooseContent
    {
        sf::Text choose, lvl1, lvl2, exit;
        sf::Texture lvl1pic, lvl2pic;
        sf::Sprite lvl1sprite, lvl2sprite;
    };
    struct HelpContent
    {
        sf::Text title, desc, left, right, pause;
    };

    sf::Vector2u m_windowSize;

    sf::Font m_font;
    sf::Texture m_bgTexture;
    sf::Sprite m_bgSprite;

    MenuContent m_menuContent;
    PauseContent m_pauseContent;
    GameContent m_gameContent;
    OverContent m_overContent;
    NickContent m_nickContent;
    WonContent m_wonContent;
    ChooseContent m_chooseContent;
    HelpContent m_helpContent;
};