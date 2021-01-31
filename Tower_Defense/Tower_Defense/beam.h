#pragma once

#include <SFML/Graphics.hpp>

// эффекты дл€ последнего врага в волне в виде лучей
class Beam
{
private:
	// скорость луча
	float m_beamSpeed{ 0.1f };
	// длина луча по ос€м x и y
	double m_beamXVector, m_beamYVector;
	// изначальна€ дистанци€ до центра по ос€м x и y
	double m_xVector, m_yVector;
	// сколько пройдено по оси x
	double m_xDistanceMade{ 0 };
	// указатель напр€моунольник луча
	sf::RectangleShape *m_beamRect;
public:
	Beam(double xBV, double yBV, double xVector, double yVector, sf::RectangleShape * beamRect);
	~Beam() { delete m_beamRect; }

	// лучи сближаютс€
	void beamsGetCloser();

	sf::RectangleShape *getBeamRect() { return m_beamRect; }
};