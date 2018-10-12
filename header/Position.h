#ifndef __POSITION_H__
#define __POSITION_H__

class Position {

private:
	double latitude, longitude;

public:
	Position();
	Position(const double latitude, const double longitude);
	double getLatitude() const;
	double getLongitude() const;
	void setPosition(const double latitude, const double longitude);
	void setLatitude(const double latitude);
	void setLongitude(const double longitude);
	bool operator <(const Position &a) const;
};

#endif
