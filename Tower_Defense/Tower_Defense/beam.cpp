#include "beam.h"

#include <cmath>

#include "globals.h"

Beam::Beam(double xBV, double yBV, double xVector, double yVector, sf::RectangleShape * beamRect)
	: m_beamXVector{ xBV }, m_beamYVector{ yBV }, m_xVector{ xVector }, m_yVector{ yVector }, m_beamRect{ beamRect }
{}

void Beam::beamsGetCloser()
{
	m_beamRect->move(-m_beamXVector * m_beamSpeed * (1 + 2 * gameSpeed), -m_beamYVector * m_beamSpeed * (1 + 2 * gameSpeed));
	m_xDistanceMade += m_beamXVector * m_beamSpeed * (1 + 2 * gameSpeed);
	if (abs(m_xDistanceMade) >= abs(m_xVector)) {
		m_beamRect->move(m_xVector, m_yVector);
		m_xDistanceMade = 0;
	}
}