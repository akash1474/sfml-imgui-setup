#include <iostream>
#include <SFML/Graphics.hpp>
#include "imgui.h"
#include <vector>
#include "imgui-SFML.h"
#include <string>

int main(){

	sf::RenderWindow window(sf::VideoMode(750,550),"Physics Engine");
	window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    bool isDragging=false;

	// int dimensions[2]={50,50};
    sf::Vector2f size(50,50)
	sf::Vector2f rectPos((int)350-size.x/2,(int)250-size.y/2);
	sf::RectangleShape rect(&rectPos,&size);
    float rectColor[3] = { (float)247 / 255, (float)56 / 255, (float)89 / 255 };
    float windowColor[3] = { (float)56 / 255, (float)66 / 255, (float)89 / 255 };
    rect.setFillColor(sf::Color
    (
        (int)(rectColor[0] * 255), 
        (int)(rectColor[1] * 255), 
        (int)(rectColor[2] * 255)
    )); // Color circle
    sf::Clock deltaClock;
    sf::Clock gameClock;

    //using font
    // Declare and load a font
    sf::Font font;
    font.loadFromFile("./font.ttf");
    // Create a text
    sf::Text my_text;
    my_text.setString("Hello World");
    my_text.setFont(font);
    my_text.setCharacterSize(30);
    // my_text.setStyle(sf::Text::Bold);
    my_text.setFillColor(sf::Color::White);

    // char title[]="Hii THere";

	while(window.isOpen()){
		sf::Event e;
		while(window.pollEvent(e)){
            ImGui::SFML::ProcessEvent(e);
			if(e.type==sf::Event::Closed) window.close();
			if(e.key.code==sf::Keyboard::Escape) window.close();
			if(e.mouseButton.button == sf::Mouse::Left){
				// std::cout<<"{ x:" << e.mouseButton.x << ",  y:"<<e.mouseButton.y<< "}"<< std::endl;
				if(e.mouseButton.x > rectPos.x && e.mouseButton.x < (rectPos.x+size.x) && e.mouseButton.y > rectPos.y && e.mouseButton.y < (rectPos.y+size.y)){
					rect.setOutlineThickness(1);
					rect.setOutlineColor(sf::Color(255, 255, 255));
				}else{
					rect.setOutlineThickness(0);
					// rect.setOutlineColor(sf::Color(255, 255, 255));
				}
			}
		}
        // if(e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left ){
        //     isDragging = true;
        //     std::cout << "Time Passed: " << int(gameClock.getElapsedTime().asMilliseconds()) << "\n";
        //     // std::cout << "Dragging";
            rectPos.x=(int)e.mouseButton.x-size.x/2;
            rectPos.y=(int)e.mouseButton.y-size.y/2;
        // }else{
        //     isDragging=false;
        //     gameClock.restart();
        // }

        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Configuration");
        ImGui::ColorEdit3("Color Circle", rectColor);
        // ImGui::InputText("Title: ",&title);
        ImGui::ColorEdit3("Window Circle", windowColor);
        ImGui::SliderInt("Width", &size.x, 10, 300);
        ImGui::SliderInt("Height", &size.y, 10, 300);
        ImGui::End();


        // rect.setPosition(sf::Vector2f(size.x,size.y));
        // if(isDragging){
            sf::Vector2f rectPos(rectPos.x,rectPos.y);
            rect.setPosition(&rectPos);
        // }

        rect.setSize(sf::Vector2f(size.x,size.y));
        rect.setFillColor(sf::Color
        (
            (int)(rectColor[0] * 255),
            (int)(rectColor[1] * 255),
            (int)(rectColor[2] * 255)
        )); // Color circle
		//render
		window.clear(sf::Color(
        (int)(windowColor[0] * 255), 
        (int)(windowColor[1] * 255), 
        (int)(windowColor[2] * 255)
		));
		window.draw(my_text);
		window.draw(rect);
        ImGui::SFML::Render(window);
		window.display();
	}
    ImGui::SFML::Shutdown();
    return 0;

}