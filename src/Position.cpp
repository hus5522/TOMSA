#include "Position.h"

Position::Position()
	:latitude(0), longitude(0)
{
}

Position::Position(const double latitude, const double longitude)
{
	this->latitude = latitude;
	this->longitude = longitude;
}

double Position::getLatitude() const
{
	return this->latitude;
}

double Position::getLongitude() const
{
	return this->longitude;
}

void Position::setPosition(const double latitude, const double longitude)
{
	this->latitude = latitude;
	this->longitude = longitude;
}

void Position::setLatitude(const double latitude)
{
	this->latitude = latitude;
}

void Position::setLongitude(const double longitude)
{
	this->longitude = longitude;
}

bool Position::operator<(const Position &a) const
{
	if(this->latitude < a.getLatitude() || 
		(this->latitude == a.getLatitude() && this->longitude < a.getLongitude()))
		return true;
	return false;
}
