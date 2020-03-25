
#include <iostream>

#include <boost/geometry.hpp>
#include "convex_hull_GW.hpp"
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian)
namespace bg = boost::geometry;
int main()
{
    typedef boost::tuple<double, double> point;
    typedef boost::geometry::model::multi_point<point> multi_point;
    typedef boost::geometry::model::polygon<point> polygon;


    //Example 1
    multi_point input_1;
    bg::read_wkt("MULTIPOINT( (2 2), (0 1), (0 0), (0.5 0.5), (0.62 0.71) (0.75 0.25) )", input_1);

    polygon conv_hull_1;
    convex_hull::convex_hull_GW(input_1, conv_hull_1);

    using bg::dsv;
    std::cout << "polygon: " << dsv(input_1) << std::endl << "hull: " << dsv(conv_hull_1) << std::endl;



    //Example 2
    multi_point input_2;
    bg::read_wkt("multipoint( (24 12), (82 15), (69 13), (15 45), (4 4), (62 85), (24 36), (92 40), (36 14), (92 16), (35 33), (88 26), (56 22) )", input_2);

    polygon conv_hull_2;
    convex_hull::convex_hull_GW(input_2, conv_hull_2);

    using bg::dsv;
    std::cout << "polygon: " << dsv(input_2) << std::endl << "hull: " << dsv(conv_hull_2) << std::endl;

    return 0;
}


