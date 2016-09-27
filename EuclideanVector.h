#ifndef UB_STACK_H 
#define UB_STACK_H

#include <string>
#include <iostream>
#include <iterator>
#include <initializer_list>

namespace evec{
	class EuclideanVector {

	public:
		//constructors
		EuclideanVector(unsigned int d, double m);
		EuclideanVector(unsigned int d);
		EuclideanVector();
		EuclideanVector(std::initializer_list<double> l);

		template<typename Iterator>
		EuclideanVector(Iterator start,  Iterator end): 
			dimension{static_cast<unsigned int>(std::distance(start,end))},
			magnitude{new double [static_cast<unsigned int>(std::distance(start,end))]}
		{
			auto q = start;
			for(double *p = magnitude; p != magnitude+dimension && q != end ; p++){
				*p = *q;
				q++;
			}
		}

		//copy constructor
		EuclideanVector(const EuclideanVector &eucVec);
		//move constructor
		EuclideanVector(EuclideanVector &&eucVec);
		//copy assignment
		EuclideanVector& operator=(const EuclideanVector &eucVec);
		//move assignment
		EuclideanVector& operator=(EuclideanVector &&eucVec);

		//destructor
		~EuclideanVector();

		//operations
		double get(unsigned int);
		double getEuclideanNorm();
		EuclideanVector createUnitVector()const;
		unsigned int getNumDimensions() const;
		double * getNumMagnitude()const;

		//operator overload
		double& operator[](const unsigned int index);
		EuclideanVector& operator+=(const EuclideanVector &other);
		EuclideanVector& operator-=(const EuclideanVector &other);
		EuclideanVector& operator*=(const unsigned int scalar);
		EuclideanVector& operator/=(const unsigned int scalar);
		operator std::vector<double>();
		operator std::list<double>();

	private:
		unsigned int dimension;
		double *magnitude;
		friend bool operator==(const EuclideanVector &l, const EuclideanVector &r);
		friend bool operator!=(const EuclideanVector &l, const EuclideanVector &r);
		friend EuclideanVector operator+(const EuclideanVector &l, const EuclideanVector &r);
		friend EuclideanVector operator-(const EuclideanVector &l, const EuclideanVector &r);
		friend double operator*(const EuclideanVector &l, const EuclideanVector &r);
		friend EuclideanVector operator*(const EuclideanVector &l, const unsigned int scalar);
		friend EuclideanVector operator*(const unsigned int scalar, const EuclideanVector &l);
		friend EuclideanVector operator/(const EuclideanVector &l, const unsigned int scalar);
		friend std::ostream& operator<<(std::ostream &os, const EuclideanVector &eucVec);

	};
		
	bool operator==(const EuclideanVector &l, const EuclideanVector &r);
	bool operator!=(const EuclideanVector &l, const EuclideanVector &r);
	EuclideanVector operator+(const EuclideanVector &l, const EuclideanVector &r);
	EuclideanVector operator-(const EuclideanVector &l, const EuclideanVector &r);
	double operator*(const EuclideanVector &l, const EuclideanVector &r);
	EuclideanVector operator*(const EuclideanVector &l, const unsigned int scalar);
	EuclideanVector operator*(const unsigned int scalar, const EuclideanVector &l);
	EuclideanVector operator/(const EuclideanVector &l, const unsigned int scalar);
	std::ostream& operator<<(std::ostream &os, const EuclideanVector &eucVec);
}

#endif