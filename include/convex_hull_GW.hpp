
// Contributed by Aditya Mohan

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_ALGORITHMS_CONVEX_HULL_GW_HPP
#define BOOST_GEOMETRY_ALGORITHMS_CONVEX_HULL_GW_HPP

#include <boost/geometry/algorithms/append.hpp>

#include <boost/geometry/arithmetic/cross_product.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_system.hpp>

#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include <boost/range/size.hpp>


namespace bg = boost::geometry;
typedef boost::tuple<double, double> point;

namespace convex_hull{

namespace detail{
template <typename multipoint>
struct init
{

	//Initialize first point in convex hull
   	static inline int initialize(multipoint mp)
	{
		int res = 0;
		for(int i=1;i<boost::size(mp);i++)
		{
			if(bg::get<0>(mp[i]) < bg::get<0>(mp[res]))
				res = i; 
		}

	return res;
	}

};


template <typename output>
struct conv_hull
{
	// Insert into convex hull
    static inline void insert_ch( boost::tuple<double, double> x, output& ch)
    {
		bg::append(ch,x);
	}


};


struct obtain_vector
{
	static inline float subtract_x(point a, point b)
	{
		return (b.get<0>() - a.get<0>());
	}

	static inline float subtract_y(point a, point b)
	{
		return (b.get<1>() - a.get<1>());
	}

};

struct orient
{	
	// Check the orientation of the points
	static inline float orientation(point a, point b, point c)
	{
		double x_1,x_2,y_1,y_2;
		x_1 = obtain_vector::subtract_x(a, b);
		x_2 = obtain_vector::subtract_x(b, c);
		y_1 = obtain_vector::subtract_y(a, b);
		y_2 = obtain_vector::subtract_y(b, c);

		bg::model::point<double, 2, bg::cs::cartesian> p1(y_1, y_2);
		bg::model::point<double, 2, bg::cs::cartesian> p2(x_1, x_2);
		bg::model::point<double, 2, bg::cs::cartesian> r1;

		r1 = bg::cross_product(p1,p2);
		return (r1.get<0>());
	}



};
}//namespace detail


//Main Code
template 
<
	typename multipoint, 
	typename output
>
static inline void convex_hull_GW(multipoint mp, output& ch)
{


	int x, y, start;	
	typedef typename boost::range_size<multipoint>::type s_type;

	s_type size = boost::size(mp);
	
	start = detail::init<multipoint>::initialize(mp); //(left-most point)
	x = start;
	do
	{
		detail::conv_hull<output>::insert_ch(mp[x],ch);
		y = (x+1)%size;
		for( int i=0; i<size; i++)
		{
			if( detail::orient::orientation(mp[x],mp[i],mp[y]) < 0 )
			y = i;
		}
		x = y;
	}
	while(x!=start);
}




} //namespace convex_hull
#endif
