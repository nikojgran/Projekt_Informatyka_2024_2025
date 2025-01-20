#include "DrawManager.h"


DrawManager::DrawManager(sf::Vector2u windowSize) : m_windowSize(windowSize) {}

bool DrawManager::InitializeResources(int* m_playerScore)
{
    if (!LoadFont() || !LoadBackgroundTexture() || !LoadLevelTexture())  {
        return false;
    }

    InitializeBackgroundSprite();
    InitializeMenuContent();
    InitializePauseContent();
    
    InitializePlayer();
    InitializeBall();

    return true;
}

void DrawManager::DrawMenu(sf::RenderWindow* window)
{
    window->draw(m_bgSprite);
    window->draw(m_menuContent.title);
    window->draw(m_menuContent.playOption);
    window->draw(m_menuContent.exitOption);
}

void DrawManager::DrawPause(sf::RenderWindow* window)
{
    window->draw(m_pauseContent.title);
    window->draw(m_pauseContent.continueOption);
    window->draw(m_pauseContent.menuReturnOption);
    window->draw(m_pauseContent.exitOption);
}

void DrawManager::DrawGameOver(sf::RenderWindow* window)
{
    window->draw(m_overContent.splash);
    m_overContent.splash.rotate(0.5f);

    window->draw(m_overContent.over);
    window->draw(m_overContent.score);
    window->draw(m_overContent.exit);
    

}

void DrawManager::DrawGameWon(sf::RenderWindow* window)
{
    window->draw(m_wonContent.won);
    window->draw(m_wonContent.score);
    window->draw(m_wonContent.exit);
}

void DrawManager::DrawPlayer(sf::RenderWindow* window)
{

    window->draw(m_gameContent.m_player);
}

void DrawManager::DrawChoose(sf::RenderWindow* window)
{
    window->draw(m_chooseContent.choose);
    window->draw(m_chooseContent.lvl1);
    window->draw(m_chooseContent.lvl2);
    window->draw(m_chooseContent.exit);
    window->draw(m_chooseContent.lvl1sprite);
    window->draw(m_chooseContent.lvl2sprite);
}

void DrawManager::MovePlayerLeft(sf::RenderWindow* window)
{
    if (m_gameContent.m_player.getPosition().x > 0) {
        m_gameContent.m_player.move(-m_gameContent.m_player_velocity, 0);
    }
}

void DrawManager::MovePlayerRight(sf::RenderWindow* window)
{
    if (m_gameContent.m_player.getPosition().x + m_gameContent.m_player.getSize().x < m_windowSize.x) {
        m_gameContent.m_player.move(m_gameContent.m_player_velocity, 0);
    }
}

void DrawManager::DrawBall(sf::RenderWindow* window)
{
    window->draw(m_gameContent.m_ball);
}

bool DrawManager::MoveBall(sf::RenderWindow* window, int* m_playerScore)
{
    m_gameContent.m_ball.move(m_gameContent.m_ball_velocity);
    if (BounceBall()) {
        InitializePlayer();
        InitializeBall();
        InitializeBlocks();
        return true;
    }
    CollisionBall(m_playerScore);
    return false;

}

bool DrawManager::BounceBall()
{
    if (m_gameContent.m_ball.getPosition().x <= 0 || (2*m_gameContent.m_ball.getRadius()) + m_gameContent.m_ball.getPosition().x >= m_windowSize.x) {
        m_gameContent.m_ball_velocity.x = -m_gameContent.m_ball_velocity.x;
    }
    if (m_gameContent.m_ball.getPosition().y <= 0 ) {
        m_gameContent.m_ball_velocity.y = -m_gameContent.m_ball_velocity.y;
    }
    if ((2 * m_gameContent.m_ball.getRadius()) + m_gameContent.m_ball.getPosition().y >= m_windowSize.y) {

        return true;
    }
   
    return false;
}

void DrawManager::CollisionBall(int *m_playerScore)
{

    sf::FloatRect m_ball_bounds = m_gameContent.m_ball.getGlobalBounds();
    sf::FloatRect m_player_bounds = m_gameContent.m_player.getGlobalBounds();

    if (m_ball_bounds.intersects(m_player_bounds)) {

        m_gameContent.m_ball_velocity.y = -m_gameContent.m_ball_velocity.y;

        float ballCenterX = m_ball_bounds.left + m_ball_bounds.width / 2;
        float playerCenterX = m_player_bounds.left + m_player_bounds.width / 2;

        float offset = ballCenterX - playerCenterX;
        float maxOffset = m_player_bounds.width / 2;

        m_gameContent.m_ball_velocity.x += offset / maxOffset * 0.5f;

    }
    for (auto it = m_gameContent.m_blocks.begin(); it != m_gameContent.m_blocks.end(); )
    {
        if (m_ball_bounds.intersects(it->getGlobalBounds()))
        {
            m_gameContent.m_ball_velocity.y = -m_gameContent.m_ball_velocity.y; // Odbicie pi³ki
            *m_playerScore = *m_playerScore + 20;
            it = m_gameContent.m_blocks.erase(it);
        }
        else
        {
            ++it;
        }
    }

}

void DrawManager::DrawBlocks(sf::RenderWindow* window)
{
    for (const auto& block : m_gameContent.m_blocks)
    {
        window->draw(block);
    }
}

void DrawManager::DrawNickInput(sf::RenderWindow* window, std::string* m_currentNick)
{
    SetupText(m_nickContent.m_currentNickText, m_font, "Wpisz swój nick: " + *m_currentNick, 30, sf::Color::White, sf::Text::Regular, 640, 360);
    m_nickContent.m_nickInputText.setPosition(200, 100);
    window->draw(m_nickContent.m_nickInputText);

    // Rysowanie tekstu, który u¿ytkownik wpisuje
    window->draw(m_nickContent.m_currentNickText);
}

bool DrawManager::LoadFont()
{
    if (!m_font.loadFromFile(FONT_PATH)) {
        std::cerr << "Error during loading font!" << std::endl;
        return false;
    }
    return true;
}

bool DrawManager::LoadBackgroundTexture()
{
    if (!m_bgTexture.loadFromFile(BG_TEXTURE_PATH)) {
        std::cerr << "Error during loading texture!" << std::endl;
        return false;
    }
    return true;
}

bool DrawManager::LoadLevelTexture()
{
    if (!m_gameContent.lvl1Block.loadFromFile(LVL1_BLOCK_PATH)) {
        std::cerr << "Error during loading LVL1 texture!" << std::endl;
        return false;
    }
    if (!m_gameContent.lvl2Block.loadFromFile(LVL2_BLOCK_PATH)) {
        std::cerr << "Error during loading LVL2 texture!" << std::endl;
        return false;
    }
    if (!m_chooseContent.lvl1pic.loadFromFile(LVL1_PIC_PATH)) {
        std::cerr << "Error during loading LVL1 miniature!" << std::endl;
        return false;
    }
    if (!m_chooseContent.lvl2pic.loadFromFile(LVL2_PIC_PATH)) {
        std::cerr << "Error during loading LVL2 miniature!" << std::endl;
        return false;
    }


    return true;
}

void DrawManager::SetupText(sf::Text& text, const sf::Font& font, const std::string & content,
        unsigned int characterSize, const sf::Color & color,
        sf::Text::Style style, float xPos, float yPos) 
{
        text.setString(content);
        text.setFont(font);
        text.setCharacterSize(characterSize);
        text.setFillColor(color);
        text.setStyle(style);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(
            textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);
        text.setPosition(xPos, yPos);
}

void DrawManager::InitializeBackgroundSprite()
{
    sf::Vector2u textureSize = m_bgTexture.getSize();

    m_bgSprite.setTexture(m_bgTexture);
    m_bgSprite.setScale(
        static_cast<float>(m_windowSize.x) / textureSize.x,
        static_cast<float>(m_windowSize.y) / textureSize.y);
}

void DrawManager::InitializeMenuContent()
{
    m_menuContent.title = sf::Text("Menu Glowne", m_font, 50);
    m_menuContent.title.setPosition(200, 100);

    m_menuContent.playOption = sf::Text("1. Graj", m_font, 30);
    m_menuContent.playOption.setPosition(200, 200);

    m_menuContent.exitOption = sf::Text("2. Wyjdz", m_font, 30);
    m_menuContent.exitOption.setPosition(200, 300);
}

void DrawManager::InitializePauseContent()
{
    m_pauseContent.title = sf::Text("Pauza", m_font, 50);
    m_pauseContent.title.setPosition(300, 100);

    m_pauseContent.continueOption = sf::Text("1. Kontynuuj", m_font, 30);
    m_pauseContent.continueOption.setPosition(300, 200);

    m_pauseContent.menuReturnOption = sf::Text("2. Powrót do menu", m_font, 30);
    m_pauseContent.menuReturnOption.setPosition(300, 300);

    m_pauseContent.exitOption = sf::Text("3. Wyjdz", m_font, 30);
    m_pauseContent.exitOption.setPosition(300, 400);
}

void DrawManager::InitializeChooseContent()
{
    sf::Vector2u textureSize = m_chooseContent.lvl1pic.getSize();
    sf::Vector2u textureSize = m_chooseContent.lvl2pic.getSize();

    m_chooseContent.lvl1sprite.setTexture(m_chooseContent.lvl1pic);
    m_chooseContent.lvl2sprite.setScale(
        (static_cast<float>(m_windowSize.x) / textureSize.x)/4,
        (static_cast<float>(m_windowSize.y) / textureSize.y) / 4);

    m_chooseContent.lvl2sprite.setTexture(m_chooseContent.lvl2pic);
    m_chooseContent.lvl2sprite.setScale(
        static_cast<float>(m_windowSize.x) / textureSize.x,
        static_cast<float>(m_windowSize.y) / textureSize.y);


    SetupText(m_chooseContent.choose, m_font, "Poziom 1", 100, sf::Color::White, sf::Text::Bold, 640, 150);
    SetupText(m_chooseContent.lvl1, m_font, "Poziom 1", 40, sf::Color::Blue, sf::Text::Bold, 320, 250);
    SetupText(m_chooseContent.lvl2, m_font, "Poziom 2", 40, sf::Color::Red, sf::Text::Bold, 960, 250);
    SetupText(m_chooseContent.exit, m_font, "1.Wyjdz do menu", 40, sf::Color::White, sf::Text::Bold, 320, 600);
}

void DrawManager::InitializeGameOver(int *m_playerScore)
{
    SetupText(m_overContent.over, m_font, "GAME OVER", 100, sf::Color::Red, sf::Text::Bold, 640, 200);

    SetupText(m_overContent.score, m_font, "Score: " + std::to_string(*m_playerScore), 30, sf::Color::Blue, sf::Text::Regular, 640, 280);

    SetupText(m_overContent.exit, m_font, "1. Wyjdz do menu", 30, sf::Color::Blue, sf::Text::Regular, 640, 350);

    


    
    m_overContent.splash.setPointCount(20);
    m_overContent.splash.setPoint(0, sf::Vector2f(1243.f, 360.f));
    m_overContent.splash.setPoint(1, sf::Vector2f(1108.f, 512.f));
    m_overContent.splash.setPoint(2, sf::Vector2f(985.f, 611.f));
    m_overContent.splash.setPoint(3, sf::Vector2f(876.f, 685.f));
    m_overContent.splash.setPoint(4, sf::Vector2f(793.f, 633.f));
    m_overContent.splash.setPoint(5, sf::Vector2f(640.f, 582.f));
    m_overContent.splash.setPoint(6, sf::Vector2f(529.f, 401.f));
    m_overContent.splash.setPoint(7, sf::Vector2f(290.f, 540.f));
    m_overContent.splash.setPoint(8, sf::Vector2f(244.f, 347.f));
    m_overContent.splash.setPoint(9, sf::Vector2f(221.f, 196.f));
    m_overContent.splash.setPoint(10, sf::Vector2f(53.f, 60.f));
    m_overContent.splash.setPoint(11, sf::Vector2f(93.f, -17.f));
    m_overContent.splash.setPoint(12, sf::Vector2f(280.f, -101.f));
    m_overContent.splash.setPoint(13, sf::Vector2f(429.f, -129.f));
    m_overContent.splash.setPoint(14, sf::Vector2f(492.f, -292.f));
    m_overContent.splash.setPoint(15, sf::Vector2f(640.f, -284.f));
    m_overContent.splash.setPoint(16, sf::Vector2f(826.f, -413.f));
    m_overContent.splash.setPoint(17, sf::Vector2f(865.f, -150.f));
    m_overContent.splash.setPoint(18, sf::Vector2f(1127.f, -194.f));
    m_overContent.splash.setPoint(19, sf::Vector2f(1044.f, 28.f));


    
    sf::FloatRect splashBounds = m_overContent.splash.getLocalBounds();
    m_overContent.splash.setOrigin(
        splashBounds.left + splashBounds.width / 2.0f,
        splashBounds.top + splashBounds.height / 2.0f);
    m_overContent.splash.setPosition(640, 360);

    m_overContent.splash.setFillColor(sf::Color::Yellow);
    m_overContent.splash.setOutlineColor(sf::Color::Red);
    m_overContent.splash.setOutlineThickness(60);

}

void DrawManager::InitializeGameWon(int* m_playerScore)
{
    SetupText(m_wonContent.won, m_font, "Wygrana!!!", 100, sf::Color::Green, sf::Text::Bold, 640, 200);
    SetupText(m_wonContent.score , m_font, "Score: " + std::to_string(*m_playerScore), 30, sf::Color::Blue, sf::Text::Regular, 640, 300);
    SetupText(m_wonContent.exit, m_font, "1. Wyjdz do menu", 30, sf::Color::Blue, sf::Text::Regular, 640, 350);
}


void DrawManager::InitializeLevels(int* m_levelIndex)
{
    if (*m_levelIndex == 1) {
        m_gameContent.m_ball_velocity = sf::Vector2f(5.0f, -5.0f);
        // Ustawienia dla poziomu 1
        m_gameContent.m_blocks.clear();
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 10; ++j) {
                sf::RectangleShape block;
                block.setSize(sf::Vector2f(100, 40));
                block.setPosition(40.f + j * (100 + 20), 50.f + i * (10 + 40));
                block.setTexture(&m_gameContent.lvl1Block);
                m_gameContent.m_blocks.push_back(block);
            }
        }
    }
    else if (*m_levelIndex == 2) {
        m_gameContent.m_ball_velocity = sf::Vector2f(7.0f, -7.0f);
        // Ustawienia dla poziomu 2
        m_gameContent.m_blocks.clear();
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 10; ++j) {
                sf::RectangleShape block;
                block.setSize(sf::Vector2f(100, 40));
                block.setPosition(50 + j * (100 + 20), 40 + i * (10 + 40));
                block.setTexture(&m_gameContent.lvl2Block);
                m_gameContent.m_blocks.push_back(block);
            }
        }
        for (int i = 0; i < 2; ++i) {

            for (int j = 0; j < 4; ++j) {
                sf::RectangleShape block;
                block.setSize(sf::Vector2f(100, 40));
                block.setPosition(50 + j * (100 + 20), 140 + i * (10 + 40));
                block.setTexture(&m_gameContent.lvl2Block);
                m_gameContent.m_blocks.push_back(block);
            }
            for (int j = 0; j < 4; ++j) {
                sf::RectangleShape block;
                block.setSize(sf::Vector2f(100, 40));
                block.setPosition(1130 - j * (100 + 20), 140 + i * (10 + 40));
                block.setTexture(&m_gameContent.lvl2Block);
                m_gameContent.m_blocks.push_back(block);
            }
        }
    }
    else {
        std::cout << "Nieprawid³owy numer poziomu!" << *m_levelIndex << std::endl;
    }
}

void DrawManager::InitializePlayer()
{
    m_gameContent.m_player = sf::RectangleShape(sf::Vector2f(120, 20));
    m_gameContent.m_player.setFillColor(sf::Color::Green);
    m_gameContent.m_player.setPosition(640, 650);
    m_gameContent.m_player_velocity = 15;
}

void DrawManager::InitializeBall()
{
    m_gameContent.m_ball.setRadius(15.0);
    m_gameContent.m_ball.setFillColor(sf::Color::White);
    m_gameContent.m_ball.setPosition(640, 580);
    m_gameContent.m_ball_velocity = sf::Vector2f(5.0f, -5.0f);
}

void DrawManager::InitializeBlocks()
{
    const int rows = 4;           
    const int cols = 10;          
    const sf::Vector2f blockSize(100.0f, 40.0f); 
    const float spacing = 10.0f;  
    const float startX = 40.0f;   
    const float startY = 50.0f;   

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            sf::RectangleShape block(blockSize);
            block.setFillColor(sf::Color::Blue);
            block.setPosition(
                startX + col * (blockSize.x + spacing),
                startY + row * (blockSize.y + spacing)
            );
            m_gameContent.m_blocks.push_back(block);
        }
    }
}

void DrawManager::LoadLevel(int* levelIndex)
{
    m_gameContent.m_blocks.clear();  // Wyczyœæ istniej¹ce bloczki

    InitializeLevels(levelIndex);

    // Zresetuj pozycje pi³ki i gracza
    m_gameContent.m_ball.setPosition(640, 580);
    m_gameContent.m_player.setPosition(640, 650);
}

bool DrawManager::WonGame(int *m_levelIndex)
{
    if (m_gameContent.m_blocks.empty()) {
        if (*m_levelIndex + 1 < 2) {
            
            *m_levelIndex = *m_levelIndex + 1;// Wczytaj nastêpny poziom
            std::cout << "Wczytujê poziom: " << *m_levelIndex << std::endl;
            LoadLevel(m_levelIndex);

            return true;
        }

        else {
             *m_levelIndex = 1;
            std::cout << "Wczytujê poziom: " << *m_levelIndex << std::endl;
            
            return true;
        }
    }
    return false;
}

void DrawManager::InitializeGameContent()
{
    
    m_gameContent.score = sf::Text("Punkty:", m_font, 30);
    m_gameContent.score.setPosition(300, 200);
      
    m_gameContent.level = sf::Text("Poziom:", m_font, 30);
    m_gameContent.level.setPosition(300, 300);
      
    m_gameContent.help = sf::Text("[F1] Pomoc", m_font, 30);
    m_gameContent.help.setPosition(300, 400);

}