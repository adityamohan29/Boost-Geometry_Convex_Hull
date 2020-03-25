


#include "convex_hull_GW.hpp"


#include <iostream>
#include <boost/geometry.hpp>



#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/core/point_type.hpp>

#include <boost/geometry/views/detail/range_type.hpp>

#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>

#include <boost/geometry/geometries/multi_point.hpp>



BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)
namespace bg = boost::geometry;

template <typename P>
void test_multi()
{
    typedef bg::model::multi_point<P> mp;
    typedef bg::model::multi_linestring<bg::model::linestring<P> > ml;
    typedef bg::model::multi_polygon<bg::model::polygon<P> > mpoly;
    typedef boost::geometry::model::polygon<P> poly;

    mp input1, input2, input3, input4, input5, input6 ,input7, input8, input9, input10;
    poly hull1, hull2, hull3, hull4, hull5, hull6, hull7;

    // All points below in upper-points and lower-points
    bg::read_wkt("multipoint((0 0),(5 0),(1 1),(4 1))", input1);
    convex_hull::convex_hull_GW(input1 , hull1);

    using bg::dsv;
    std::cout << "polygon: " << dsv(input1) << std::endl << "hull: " << dsv(hull1) << std::endl;

    bg::read_wkt("MULTIPOINT((0 1),(5 1),(1 0),(4 0))", input2);
    convex_hull::convex_hull_GW(input2, hull2);

    using bg::dsv;
    std::cout << "polygon: " << dsv(input2) << std::endl << "hull: " << dsv(hull2) << std::endl;

    // All points in vertical line 
    bg::read_wkt("MULTIPOINT((1 0),(5 0),(3 0),(4 0),(2 0))", input3);
    convex_hull::convex_hull_GW(input3, hull3);

    using bg::dsv;
    std::cout << "polygon: " << dsv(input3) << std::endl << "hull: " << dsv(hull3) << std::endl;

    // One point only
    bg::read_wkt("MULTIPOINT((1 0))", input4);
    convex_hull::convex_hull_GW(input4, hull4);

    using bg::dsv;
    std::cout << "polygon: " << dsv(input4) << std::endl << "hull: " << dsv(hull4) << std::endl;

    
    bg::read_wkt("MULTIPOINT((2 9),(1 3),(9 4),(1 1),(1 0),(7 9),(2 5),(3 7),(3 6),(2 4))", input5);
    convex_hull::convex_hull_GW(input5, hull5);

    using bg::dsv;
    std::cout << "polygon: " << dsv(input5) << std::endl << "hull: " << dsv(hull5) << std::endl;


    bg::read_wkt("multipoint((0 53), (0 103), (1 53))", input6);
    convex_hull::convex_hull_GW(input6, hull6);

    using bg::dsv;
    std::cout << "polygon: " << dsv(input6) << std::endl << "hull: " << dsv(hull6) << std::endl;

    bg::read_wkt("multipoint((1.1 1.1), (2.5 2.1), (3.1 3.1), (4.9 1.1), (3.1 1.9))", input7);
    convex_hull::convex_hull_GW(input7, hull7);

    using bg::dsv;
    std::cout << "polygon: " << dsv(input7) << std::endl << "hull: " << dsv(hull7) << std::endl; 


}


int main()
{
    test_multi<boost::tuple<double, double> >();

    return 0;
}
