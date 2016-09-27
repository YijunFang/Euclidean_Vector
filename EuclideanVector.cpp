#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <cmath>
#include "EuclideanVector.h"

namespace evec{

	//constructors
	EuclideanVector::EuclideanVector(unsigned int d, double m): 
		dimension{d},magnitude{new double[d]}{

		for(double *p = magnitude; p != magnitude+d; ++p){
			*p = m;
		}
	}

	EuclideanVector::EuclideanVector(unsigned int d): 
		dimension{d},magnitude{new double [d]}{
		
		for(double *p = magnitude; p != magnitude+d; p++){
			*p = 0.0;
		}
	}

	EuclideanVector::EuclideanVector(): EuclideanVector(1){};

	EuclideanVector::EuclideanVector(std::initializer_list<double> l): 
		dimension{static_cast<unsigned int>(l.size())},
		magnitude{new double [static_cast<unsigned int>(l.size())]}{

		double *p = magnitude;
		for( auto q = l.begin(); q != l.end(); q++){
			*p = *q;
			p++;
		}
	}


	//copy constructor
	EuclideanVector::EuclideanVector(const EuclideanVector &v): 
		dimension{v.dimension}, magnitude{new double [v.dimension]}{
		
		auto q = magnitude;
		for(auto pt = v.magnitude; pt !=v.magnitude + v.dimension; pt++){
			*q = *pt;
			q++;
		}

	}

	//move constructor
	EuclideanVector::EuclideanVector(EuclideanVector &&v):
		dimension{v.dimension}, magnitude{v.magnitude}
	{
		v.dimension = 0;
		v.magnitude = nullptr;
	}

	//copy assignment
	EuclideanVector& EuclideanVector::operator=(const EuclideanVector &v){
		if (this != &v) {
			dimension = v.dimension;
			delete[] magnitude;
			magnitude = new double[v.dimension];
			auto q = magnitude;
			for(auto pt = v.magnitude; pt !=v.magnitude + v.dimension; pt++){
				*q = *pt;
				q++;
			}
		}
		  return *this;
	}
	//move assignment
	EuclideanVector& EuclideanVector::operator=( EuclideanVector &&v){
		if (this != &v) {
			dimension = v.dimension;
		    delete[] magnitude;
		    magnitude = std::move(v.magnitude);
		    v.dimension = 0;
		    v.magnitude = nullptr;
		}
		return *this;
	}

	EuclideanVector::~EuclideanVector(){
		delete[] magnitude;
	}

	//operations
	unsigned int EuclideanVector::getNumDimensions() const{
		return dimension;
	}

	double * EuclideanVector::getNumMagnitude()const{
		return magnitude;
	}

	double EuclideanVector::getEuclideanNorm(){
		double result = 0;
		for(double *p = magnitude; p != magnitude+dimension; ++p){
			result += (*p) * (*p);
		}
		return sqrt(result);
	}

	double EuclideanVector::get(unsigned int index){
		return magnitude[index];
	}

	EuclideanVector EuclideanVector::createUnitVector()const{
		EuclideanVector newVector {*this};
		double norm = newVector.getEuclideanNorm();
	 	for(double *p = newVector.magnitude; p != newVector.magnitude+newVector.dimension; ++p){
			*p = (*p)/norm; 
		}
		return newVector;
	}


	double& EuclideanVector::operator[](const unsigned int index) {
		if(dimension >= index +1)
	   		return magnitude[index];
	   	else return magnitude[0];
	}

	EuclideanVector& EuclideanVector::operator+=(const EuclideanVector &other){
		auto *q = other.magnitude;
		for(auto pt = magnitude; pt != magnitude + dimension; pt++){
			*pt += *q;
			q++;
		}
		return *this;
	}
	EuclideanVector& EuclideanVector::operator-=(const EuclideanVector &other){
		auto *q = other.magnitude;
		for(auto pt = magnitude; pt != magnitude + dimension; pt++){
			*pt -= *q;
			q++;
		}
		return *this;
	}
	EuclideanVector& EuclideanVector::operator*=(const unsigned int scalar){
		for(auto pt = magnitude; pt != magnitude + dimension; pt++)
			*pt = (*pt) * scalar;
		return *this;
	}

	EuclideanVector& EuclideanVector::operator/=(const unsigned int scalar){
		for(auto pt = magnitude; pt != magnitude + dimension; pt++)
			*pt = (*pt) / scalar;
		return *this;
	}

	EuclideanVector::operator std::vector<double>() {
		std::vector<double> v;
		for(auto pt = magnitude; pt != magnitude + dimension; pt++){
			v.push_back(*pt);
		}
		return v;
	}

	EuclideanVector::operator std::list<double>() {
		std::list<double> l;
		for(auto pt = magnitude; pt != magnitude + dimension; pt++){
			l.push_back(*pt);
		}
		return l;
	}



	//friends operations
	bool operator==(const EuclideanVector &l, const EuclideanVector &r){
		if(l.dimension != r.dimension)
			return false;
		else{
			auto q = l.magnitude;
			for(auto pt = r.magnitude; pt !=r.magnitude + r.dimension; pt++){
				if( (*q) != (*pt)) return false;
				q++;
			}
		}
		return true;
	}

	bool operator!=(const EuclideanVector &l, const EuclideanVector &r){
		if(l.dimension != r.dimension)
			return true;
		else{
			auto q = l.magnitude;
			for(auto pt = r.magnitude; pt !=r.magnitude + r.dimension; pt++){
				if( (*q) != (*pt)) return true;
				q++;
			}
		}
		return false;
	}

	EuclideanVector operator+(const EuclideanVector &l, const EuclideanVector &r){
		if(l.dimension != r.dimension) exit(0);
		EuclideanVector v{l};
		v += r;
		return v;
	}

	EuclideanVector operator-(const EuclideanVector &l, const EuclideanVector &r){
		if(l.dimension != r.dimension) exit(0);
		EuclideanVector v{l};
		v -= r;
		return v;
	}

	double operator*(const EuclideanVector &l, const EuclideanVector &r){
		if(l.dimension != r.dimension) exit(0);
		double result = 0;
		auto q = l.magnitude;
		for(auto pt = r.magnitude; pt !=r.magnitude + r.dimension; pt++){
			result += (*q) * (*pt);
			q++;
		}
		return result;
	}

	EuclideanVector operator*(const EuclideanVector &l, const unsigned int scalar){
		EuclideanVector v{l};
		v *= scalar;
		return v;
	}

	EuclideanVector operator*(const unsigned int scalar, const EuclideanVector &l){
		EuclideanVector v{l};
		v *= scalar;
		return v;
	}

	EuclideanVector operator/(const EuclideanVector &l, const unsigned int scalar){
		EuclideanVector v{l};
		v /= scalar;
		return v;
	}


	std::ostream& operator<<(std::ostream &os,const EuclideanVector &v)
	{ 
		if(v.getNumDimensions() == 0) {
			os<<"[]";
			return os;
		}
		double *p = v.getNumMagnitude();
		os << "[";
		for(; p != v.getNumMagnitude()+ v.getNumDimensions()-1; p++)
			os << *p << " ";
		os << *p << "]";
		return os;
	}
}
