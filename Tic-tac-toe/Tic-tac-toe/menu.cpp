#include <SFML/Graphics.hpp>
#include "menu.h"

void openMenu(int &n, int &p)
{
	using sf::Text;
	using sf::Color;
	using sf::RectangleShape;
	using sf::Vector2f;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::Font font;
	font.loadFromFile("sansation.ttf");

	// окно меню
	sf::RenderWindow menu(sf::VideoMode(310, 430), "Tic-tac-toe", sf::Style::Titlebar | sf::Style::Close, settings);

	Text sizeOfField("Field size", font, 35);
	sizeOfField.setFillColor(Color::Black);
	sizeOfField.setPosition(75, 20);

	Text x3("3x3", font, 35);
	x3.setFillColor(Color::Green);
	x3.setPosition(25, 82);

	Text x4("4x4", font, 35);
	x4.setFillColor(Color::Black);
	x4.setPosition(25 + 100, 82);

	Text x5("5x5", font, 35);
	x5.setFillColor(Color::Black);
	x5.setPosition(25 + 200, 82);

	Text who_vs_who("Who vs who", font, 35);
	who_vs_who.setFillColor(Color::Black);
	who_vs_who.setPosition(55, 140);

	Text p_vs_p("Player vs Player", font, 35);
	p_vs_p.setFillColor(Color::Black);
	p_vs_p.setPosition(28, 195);

	Text p_vs_AI("Player vs AI", font, 35);
	p_vs_AI.setFillColor(Color::Green);
	p_vs_AI.setPosition(60, 250);

	Text _AI_vs_AI("AI vs AI", font, 35);
	_AI_vs_AI.setFillColor(Color::Black);
	_AI_vs_AI.setPosition(100, 305);

	Text play("Play", font, 35);
	play.setFillColor(Color::Red);
	play.setPosition(120, 370);

	while (menu.isOpen())
	{
		// получаем координаты курсора мышы
		sf::Vector2i pos = sf::Mouse::getPosition(menu);
		int x{ pos.x };
		int y{ pos.y };

		sf::Event event;
		// обработчик событий
		while (menu.pollEvent(event))
		{
			// закрытие окна
			if (event.type == sf::Event::Closed) {
				menu.close();
			}
			// нажата кнопка мыши?
			if (event.type == sf::Event::MouseButtonPressed) {
				// если ЛКМ
				if (event.mouseButton.button == sf::Mouse::Left) {
					// если была нажата одна из кнопок выбора размера
					if (y > 80 && y < 130) {
						if (x > 10 && x < 100) {
							n = 3;
							x3.setFillColor(Color::Green);
							x4.setFillColor(Color::Black);
							x5.setFillColor(Color::Black);
						}
						else if (x > 110 && x < 200) {
							n = 4;
							x4.setFillColor(Color::Green);
							x3.setFillColor(Color::Black);
							x5.setFillColor(Color::Black);
						}
						else if (x > 210 && x < 300) {
							n = 5;
							x5.setFillColor(Color::Green);
							x3.setFillColor(Color::Black);
							x4.setFillColor(Color::Black);
						}
					}
					// если была нажата одна из кнопок выбора противника
					if (x > 10 && x < 300) {
						if (y > 195 && y < 245) {
							p = 1;
							p_vs_p.setFillColor(Color::Green);
							p_vs_AI.setFillColor(Color::Black);
							_AI_vs_AI.setFillColor(Color::Black);
						}
						if (y > 250 && y < 300) {
							p = 2;
							p_vs_AI.setFillColor(Color::Green);
							p_vs_p.setFillColor(Color::Black);
							_AI_vs_AI.setFillColor(Color::Black);
						}
						if (y > 305 && y < 355) {
							p = 3;
							_AI_vs_AI.setFillColor(Color::Green);
							p_vs_p.setFillColor(Color::Black);
							p_vs_AI.setFillColor(Color::Black);
						}
					}
					if (x > 80 && x < 230 && y > 370 && y < 420) {
						menu.close();
					}
				}
			}
		}
		// цвет фона
		menu.clear(Color(200, 200, 200));

		// разный текст
		menu.draw(sizeOfField);
		menu.draw(who_vs_who);

		// "кнопки" для выбора размера поля
		for (int i = 0; i < 3; ++i) {
			RectangleShape borders(Vector2f(90, 50));
			borders.move(i * 100 + 10, 80);
			borders.setFillColor(Color::Black);
			menu.draw(borders);
			RectangleShape borders2(Vector2f(80, 40));
			borders2.move(i * 100 + 15, 85);
			borders2.setFillColor(Color(200, 200, 200));
			menu.draw(borders2);
		}
		// "кнопки" для выбора, кто с кем играет
		for (int i = 0; i < 3; ++i) {
			RectangleShape borders(Vector2f(290, 50));
			borders.move(10, i * 55 + 195);
			borders.setFillColor(Color::Black);
			menu.draw(borders);
			RectangleShape borders2(Vector2f(280, 40));
			borders2.move(15, i * 55 + 200);
			borders2.setFillColor(Color(200, 200, 200));
			menu.draw(borders2);
		}
		// кнопка Play
		RectangleShape borders(Vector2f(150, 50));
		borders.move(80, 370);
		borders.setFillColor(Color::Black);
		menu.draw(borders);
		RectangleShape borders2(Vector2f(140, 40));
		borders2.move(85, 375);
		borders2.setFillColor(Color(200, 200, 200));
		menu.draw(borders2);

		// текст 3x3 и т.д
		menu.draw(x3);
		menu.draw(x4);
		menu.draw(x5);

		// текст AI vs AI и т.д
		menu.draw(p_vs_p);
		menu.draw(p_vs_AI);
		menu.draw(_AI_vs_AI);

		menu.draw(play);

		menu.display();
	}
}