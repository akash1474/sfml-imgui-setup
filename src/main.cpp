#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <string>
#include "imgui.h"
#include "imgui-SFML.h"

sf::Clock deltaClock;
sf::Clock gameClock;

void eventHandler(sf::Event &e,sf::RenderWindow &window){
	ImGui::SFML::ProcessEvent(e);
	if(e.type==sf::Event::Closed) window.close();
	if(e.key.code==sf::Keyboard::Escape) window.close();
}

float get_angular_speed(int &rpm,int &FPS){
	return (float)(4*rpm/FPS);

}

class Object{

public:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Color color;
	sf::RectangleShape rect;
	bool isSelected=false;
	int rotation=0.f;


	Object(sf::Vector2f pos,sf::Vector2f size,sf::Color color){
		this->position=pos;
		this->size=size;
		this->color=color;

		rect.setPosition(this->position.x,this->position.y);
		rect.setFillColor(this->color);
		rect.setSize(this->size);
		rect.setOrigin(this->size.x/2,this->size.y/2);
	}

	void eventHandler(sf::Event &e,sf::RenderWindow &window){
		if(e.mouseButton.button == sf::Mouse::Left){
			if(sf::Mouse::getPosition(window).x > this->position.x-this->size.x/2 && sf::Mouse::getPosition(window).x < (this->position.x+this->size.x/2) && sf::Mouse::getPosition(window).y > this->position.y-this->size.y/2 && sf::Mouse::getPosition(window).y < (this->position.y+this->size.y/2)){
				// std::cout<<"{ x:" << sf::Mouse::getPosition(window).x << ",  y:"<<sf::Mouse::getPosition(window).y<< "}"<< std::endl;
				this->isSelected=true;
			}else{
				rect.setOutlineThickness(0);
				this->isSelected=false;
				// rect.setOutlineColor(sf::Color(255, 255, 255));
			}

		}
	}

	void update(sf::RenderWindow &window){
		if(this->isSelected){
			this->rect.setOutlineThickness(1);
			this->rect.setOutlineColor(sf::Color(255, 255, 255));
			sf::Cursor cursor;
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				if (cursor.loadFromSystem(sf::Cursor::Hand))
					window.setMouseCursor(cursor);
				this->position.x=sf::Mouse::getPosition(window).x;
				this->position.y=sf::Mouse::getPosition(window).y;
				this->rect.setScale(1.2,1.2);
				this->rect.setPosition(this->position.x,this->position.y);
			}else{
				this->rect.setScale(1,1);
				if (cursor.loadFromSystem(sf::Cursor::Arrow))
					window.setMouseCursor(cursor);
			}
		}else{
			this->rect.setOutlineThickness(0);
		}

	}

	void draw(sf::RenderWindow &window){
		window.draw(this->rect);
	}

	~Object(){
	}

};

void make_request(){
	sf::Http::Request request;
	sf::Http http("http://www.reqres.in/api/users/1");
	request.setMethod(sf::Http::Request::Get);
	// request.setUri("https://reqres.in/api/users/1");
	// request.setHttpVersion(1, 1); // HTTP 1.1
	// request.setField("From", "me");
	// request.setField("Content-Type", "application/x-www-form-urlencoded");
	// request.setBody("para1=value1&param2=value2");
	sf::Http::Response response = http.sendRequest(request);
	std::cout << "status: " << response.getStatus() << std::endl;
}


int main(){
	sf::RenderWindow window(sf::VideoMode(1000,500),"Engine");
	make_request();
	int FPS=60;
	window.setFramerateLimit(FPS);
	ImGui::SFML::Init(window);
	bool isSelected=false;
	int RPM=2;
	sf::Vector2f size(30,30);
	sf::Vector2f position(100,200);
	sf::RectangleShape rect(size);
	float rectColor[3] = { (float)247 / 255, (float)56 / 255, (float)89 / 255 };
	rect.setPosition(position.x,position.y);
	rect.setFillColor(sf::Color((int)(rectColor[0]*255),(int)(rectColor[1]*255),(int)(rectColor[2]*255)));
	rect.setOrigin(size.x/2,size.y/2);
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(10, 10)),
		sf::Vertex(sf::Vector2f(150, 150))
	};

	Object shape=Object(sf::Vector2f(100,100),sf::Vector2f(250,250),sf::Color(100,86,98));
	// sf::Music music;
	// if (!music.openFromFile("The Road Home.wav"))
	//     return -1; // error
	// music.play();


	while(window.isOpen()){
		sf::Event e;
		while(window.pollEvent(e)){
			eventHandler(e,window);
			if(e.mouseButton.button == sf::Mouse::Left){
				if(sf::Mouse::getPosition(window).x > position.x-size.x/2 && sf::Mouse::getPosition(window).x < (position.x+size.x/2) && sf::Mouse::getPosition(window).y > position.y-size.y/2 && sf::Mouse::getPosition(window).y < (position.y+size.y/2)){
					// std::cout<<"{ x:" << sf::Mouse::getPosition(window).x << ",  y:"<<sf::Mouse::getPosition(window).y<< "}"<< std::endl;
					isSelected=true;
				}else{
					rect.setOutlineThickness(0);
					isSelected=false;
					// rect.setOutlineColor(sf::Color(255, 255, 255));
				}

			}
			shape.eventHandler(e,window);
		}
		ImGui::SFML::Update(window, deltaClock.restart());
		ImGui::Begin("Configuration");
		ImGui::ColorEdit3("Rectange Color",rectColor);
        ImGui::SliderInt("Rotation(RMP)", &RPM, 0, 360);
        ImGui::Text("X: %f",position.x);
        ImGui::Text("Y: %f",position.y);
		ImGui::End();
		window.clear(sf::Color(56,66,89));
		rect.rotate(get_angular_speed(RPM,FPS));
		/////////////////////////////////
		rect.setFillColor(sf::Color((int)(rectColor[0]*255),(int)(rectColor[1]*255),(int)(rectColor[2]*255)));
		if(RPM > 200){
			rect.setOutlineThickness(1);
			rect.setOutlineColor(sf::Color(247,196,56));
			if(RPM > 250){
				rect.setOutlineThickness(2);
				rect.setOutlineColor(sf::Color(255,84,3));
			}
			if(RPM > 300){
				rect.setOutlineThickness(2);
				rect.setOutlineColor(sf::Color(255,30,115));
			}
		}
		if(isSelected){
			rect.setOutlineThickness(1);
			rect.setOutlineColor(sf::Color(255, 255, 255));
			sf::Cursor cursor;
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && gameClock.getElapsedTime().asMilliseconds() > 200){
				if (cursor.loadFromSystem(sf::Cursor::Hand))
					window.setMouseCursor(cursor);
				position.x=sf::Mouse::getPosition(window).x;
				position.y=sf::Mouse::getPosition(window).y;
				rect.setScale(1.2,1.2);
				rect.setPosition(position.x,position.y);
			}else{
				rect.setScale(1,1);
				if (cursor.loadFromSystem(sf::Cursor::Arrow))
					window.setMouseCursor(cursor);
				gameClock.restart();
			}
		}else{
			rect.setOutlineThickness(0);
		}

		shape.update(window);
		window.draw(line, 2, sf::Lines);	
		window.draw(rect);
		shape.draw(window);
		/////////////////////////////////
		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
	return 0;
}