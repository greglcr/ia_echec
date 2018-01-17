#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

const int STATUT_MENU = 0;
const int STATUT_JOUER = 1;

const int winWidth = 400;
const int winHeight = 400;
int statut = STATUT_MENU;

int main()
{
    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Echecs", sf::Style::Close);
    
    sf::Font font;
    font.loadFromFile("arial.ttf"); // BEST FONT EVER !!
    sf::Text title(L"Echecs de compétition", font);
    title.setCharacterSize(30);
    title.setColor(sf::Color::White);

    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width/2.0f,
                    titleRect.top + titleRect.height/2.0f);
    title.setPosition(sf::Vector2f(winWidth/2.0f, 40.0));

    sf::Texture playTexture;
    if(!playTexture.loadFromFile("play.png"))
    {
        std::cout << "[Erreur] play.png n'a pas pu etre charge !\n";
        return 0;
    }
    playTexture.setSmooth(true);
    sf::Texture playHoverTexture;
    if(!playHoverTexture.loadFromFile("play_hover.png"))
    {
        std::cout << "[Erreur] play_hover.png n'a pas pu etre charge !\n";
        return 0;
    }
    playTexture.setSmooth(true);

    sf::Sprite play;
    play.setTexture(playTexture);

    sf::FloatRect playRect = play.getLocalBounds();
    play.setOrigin(playRect.left + playRect.width/2.0f,
                    playRect.top + playRect.height/2.0f);
    play.setPosition(sf::Vector2f(winWidth/2.0f, winHeight/2.0f));
    play.setScale(sf::Vector2f(0.25, 0.25));


    sf::Text enCours(L"En cours...", font);
    enCours.setCharacterSize(30);
    enCours.setColor(sf::Color::White);

    sf::FloatRect enCoursRect = enCours.getLocalBounds();
    enCours.setOrigin(enCoursRect.left + enCoursRect.width/2.0f,
                    enCoursRect.top + enCoursRect.height/2.0f);
    enCours.setPosition(sf::Vector2f(winWidth/2.0f, winHeight/2.0f));



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonReleased)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f playPos = play.getPosition();

                    if(abs(mousePos.x-playPos.x) < 40 && abs(mousePos.y-playPos.y) < 40)
                        statut = STATUT_JOUER;
                }
            }
        }

        {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f playPos = play.getPosition();

            if(abs(mousePos.x-playPos.x) < 40 && abs(mousePos.y-playPos.y) < 40)
                play.setTexture(playHoverTexture);
            else
                play.setTexture(playTexture);
        }

        window.clear();

        if(statut == STATUT_MENU)
        {
            window.draw(title);
            window.draw(play);
        }
        if(statut == STATUT_JOUER)
        {
            window.draw(enCours);
        }
        window.display();
    }

    return 0;
}
