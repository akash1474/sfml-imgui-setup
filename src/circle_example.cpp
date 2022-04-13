#include "imgui.h"
#include "imgui-SFML.h"

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 600), "Window Title");
    ImGui::SFML::Init(window);

    window.setFramerateLimit(60);
    bool circleExists = true;
    bool enableRotation=false;
    float circleRadius = 100.0f;
    int circleSegments = 100;
    int rpm = 1;
    float angle=1.0f;
    float circleColor[3] = { (float)204 / 255, (float)77 / 255, (float)5 / 255 };
    sf::CircleShape shape(circleRadius, circleSegments);
    shape.setFillColor(sf::Color
    (
        (int)(circleColor[0] * 255), 
        (int)(circleColor[1] * 255), 
        (int)(circleColor[2] * 255)
    )); // Color circle
    shape.setOrigin(circleRadius, circleRadius);
    shape.setPosition(250, 200); // Center circle



    sf::Transform t;
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        

        ImGui::Begin("Window title");
        ImGui::Text("Window text!");
        ImGui::Checkbox("Circle", &circleExists);
        ImGui::Checkbox("Rotation", &enableRotation);
        ImGui::SliderFloat("Radius", &circleRadius, 100.0f, 300.0f);
        ImGui::SliderInt("Sides", &circleSegments, 3, 150);
        if(enableRotation){
            ImGui::SliderInt("RPM", &rpm, 0, 10);
            angle+=rpm*2*3.14/60;
        }
        ImGui::ColorEdit3("Color Circle", circleColor);
        ImGui::End();

        shape.setRadius(circleRadius);
        shape.setOrigin(circleRadius, circleRadius);
        shape.setPointCount(circleSegments);
        shape.setFillColor(sf::Color
        (
            (int)(circleColor[0] * 255),
            (int)(circleColor[1] * 255),
            (int)(circleColor[2] * 255)
        )); // Color circle
        if(enableRotation){
            t.rotate(angle,{250.0f,200.0f});
        }
        window.clear(sf::Color(18, 33, 43)); // Color background
        if (circleExists)
            window.draw(shape, t);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}