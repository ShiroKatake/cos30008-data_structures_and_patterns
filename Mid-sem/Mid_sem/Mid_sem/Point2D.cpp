#include "Point2D.h"
#include <iostream>

using namespace std;

static const Point2D gCoordinateOrigin;
static const double gEpsilon = 0.0001;

double Point2D::directionTo(const Point2D& aOther) const {
	return (*this - aOther).direction();
}

double Point2D::magnitudeTo(const Point2D& aOther) const {
	return (*this - aOther).magnitude();
}

Point2D::Point2D() : fId(""), fPosition(0, 0), fOrigin(&gCoordinateOrigin) {

}

Point2D::Point2D(const std::string& aId, double aX, double aY) : fId(aId), fPosition(aX, aY), fOrigin(&gCoordinateOrigin) {

}

Point2D::Point2D(std::istream& aIStream) : fOrigin(&gCoordinateOrigin) {
	double lX, lY;

	aIStream >> fId >> lX >> lY;

	fPosition.setX(lX);
	fPosition.setY(lY);
}

const std::string& Point2D::getId() const {
	return fId;
}

void Point2D::setX(const double& aX) {
	fPosition.setX(aX);
}

const double Point2D::getX() const {
	return fPosition.getX();
}

void Point2D::setY(const double& aY) {
	fPosition.setX(aY);
}

const double Point2D::getY() const {
	return fPosition.getY();
}

void Point2D::setOrigin(const Point2D& aPoint) {
	fOrigin = &aPoint;
}

const Point2D& Point2D::getOrigin() const {
	return *fOrigin;
}

Vector2D Point2D::operator-(const Point2D& aRHS) const {
	return Vector2D(fPosition.getX() - aRHS.getX(), fPosition.getY() - aRHS.getY());
}

double Point2D::direction() const {
	return directionTo(*fOrigin);
}

double Point2D::magnitude() const {
	return magnitudeTo(*fOrigin);
}

bool Point2D::isCollinear(const Point2D& aOther) const {
	double lResult = abs(direction() - aOther.direction());
	return	lResult <= gEpsilon && lResult >= 0 || lResult <= 3.1416 && lResult >= 3.1415;
}

bool Point2D::isClockwise(const Point2D& aP0, const Point2D& aP2) const {
	return Vector2D(*this - aP0).cross(Vector2D(aP2 - aP0)) > 0;
}

bool Point2D::operator<(const Point2D& aRHS) const {
	Vector2D lResult = *this - aRHS;
	if (lResult.getY() <= -gEpsilon || lResult.getY() == 0 && lResult.getX() <= -gEpsilon)
		return true;
	return false;
}

std::ostream& operator<<(std::ostream& aOStream, const Point2D& aObject) {
	aOStream << aObject.fId << ": (" << aObject.fPosition.getX() << ", " << aObject.fPosition.getY() << ")";
	return aOStream;
}

std::istream& operator>>(std::istream& aIStream, Point2D& aObject) {
	aObject = Point2D(aIStream);
	return aIStream;
}