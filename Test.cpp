#include "doctest.h"
#include "Graph.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("Test graph addition")
{
    Graph g1;
    g1.loadGraph({{1, 2}, {3, 4}});
    Graph g2;
    g2.loadGraph({{5, 6}, {7, 8}});
    Graph result = g1 + g2;
    Graph expected;
    expected.loadGraph({{6, 8}, {10, 12}});
    CHECK(result == expected);
}

TEST_CASE("Test graph subtraction")
{
    Graph g1;
    g1.loadGraph({{5, 6}, {7, 8}});
    Graph g2;
    g2.loadGraph({{1, 2}, {3, 4}});
    Graph result = g1 - g2;
    Graph expected;
    expected.loadGraph({{4, 4}, {4, 4}});
    CHECK(result == expected);
}

TEST_CASE("Test scalar addition")
{
    Graph g;
    g.loadGraph({{1, 2}, {3, 4}});
    g += 1;
    Graph expected;
    expected.loadGraph({{2, 3}, {4, 5}});
    CHECK(g == expected);
}

TEST_CASE("Test scalar subtraction")
{
    Graph g;
    g.loadGraph({{5, 6}, {7, 8}});
    g -= 1;
    Graph expected;
    expected.loadGraph({{4, 5}, {6, 7}});
    CHECK(g == expected);
}

TEST_CASE("Test increment prefix")
{
    Graph g;
    g.loadGraph({{1, 2}, {3, 4}});
    ++g;
    Graph expected;
    expected.loadGraph({{2, 3}, {4, 5}});
    CHECK(g == expected);
}

TEST_CASE("Test decrement prefix")
{
    Graph g;
    g.loadGraph({{2, 3}, {4, 5}});
    --g;
    Graph expected;
    expected.loadGraph({{1, 2}, {3, 4}});
    CHECK(g == expected);
}

TEST_CASE("Test increment postfix")
{
    Graph g;
    g.loadGraph({{1, 2}, {3, 4}});
    g++;
    Graph expected;
    expected.loadGraph({{2, 3}, {4, 5}});
    CHECK(g == expected);
}

TEST_CASE("Test decrement postfix")
{
    Graph g;
    g.loadGraph({{2, 3}, {4, 5}});
    g--;
    Graph expected;
    expected.loadGraph({{1, 2}, {3, 4}});
    CHECK(g == expected);
}

TEST_CASE("Test equality operator")
{
    Graph g1;
    g1.loadGraph({{1, 2}, {3, 4}});
    Graph g2;
    g2.loadGraph({{1, 2}, {3, 4}});
    Graph g3;
    g3.loadGraph({{1}});
    CHECK(g1 == g2);
    CHECK_FALSE(g1 == g3);
}

TEST_CASE("Test inequality operator")
{
    Graph g1;
    g1.loadGraph({{1, 2}, {3, 4}});
    Graph g2;
    g2.loadGraph({{2, 3}, {4, 5}});
    Graph g3;
    g3.loadGraph({{1}});
    CHECK(g1 != g2);
    CHECK(g1 != g3);
}

TEST_CASE("Test greater than operator")
{
    Graph g1;
    g1.loadGraph({{2, 2}, {3, 4}});
    Graph g2;
    g2.loadGraph({{0, 2}, {3, 4}});
    Graph g3;
    g3.loadGraph({{2, 2, -1}, {3, 4, 5}, {0, 0, 0}});
    Graph g4;
    g4.loadGraph({{2, 0, -1}, {3, 4, 5}, {0, 1, 0}});
    CHECK(g1 > g2);
    CHECK(g3 > g1);
    CHECK(g4 > g1);
    CHECK_FALSE(g3 > g4);
}

TEST_CASE("Test less than operator")
{
    Graph g1;
    g1.loadGraph({{2, 2}, {3, 4}});
    Graph g2;
    g2.loadGraph({{0, 2}, {3, 4}});
    Graph g3;
    g3.loadGraph({{2, 2, -1}, {3, 4, 5}, {0, 0, 0}});
    Graph g4;
    g4.loadGraph({{2, 0, -1}, {3, 4, 5}, {0, 1, 0}});
    CHECK(g2 < g1);
    CHECK(g1 < g3);
    CHECK(g1 < g4);
    CHECK_FALSE(g4 < g3);
}

TEST_CASE("Test greater than or equal operator")
{
    Graph g1;
    g1.loadGraph({{2, 2}, {3, 4}});
    Graph g2;
    g2.loadGraph({{2, 2}, {3, 4}});
    Graph g3;
    g3.loadGraph({{2, 2, -1}, {3, 4, 5}, {0, 0, 0}});
    Graph g4;
    g4.loadGraph({{2, 0, -1}, {3, 4, 5}, {0, 0, 0}});
    CHECK(g1 >= g2);
    CHECK(g3 >= g4);
}

TEST_CASE("Test less than or equal operator")
{
    Graph g1;
    g1.loadGraph({{2, 2}, {3, 4}});
    Graph g2;
    g2.loadGraph({{2, 2}, {3, 4}});
    CHECK(g1 <= g2);
}

TEST_CASE("Test scalar multiplication")
{
    Graph g;
    g.loadGraph({{1, 2}, {3, 4}});
    Graph result = g * 2;
    Graph expected;
    expected.loadGraph({{2, 4}, {6, 8}});
    CHECK(result == expected);
}

TEST_CASE("Test graph multiplication")
{
    Graph g1;
    g1.loadGraph({{1, 2}, {3, 4}});
    Graph g2;
    g2.loadGraph({{2, 0}, {1, 2}});
    Graph result = g1 * g2;
    Graph expected;
    expected.loadGraph({{4, 4}, {10, 8}});
    CHECK(result == expected);
}

TEST_CASE("Test invalid graph")
{
    Graph g1;
    CHECK_THROWS(g1.loadGraph({{3, 4}}));
}

TEST_CASE("Test unary plus operator")
{
    Graph g;
    g.loadGraph({{1, 2}, {-3, 4}});
    +g;
    Graph expected;
    expected.loadGraph({{1, 2}, {-3, 4}});
    CHECK(g == expected);
}

TEST_CASE("Test unary minus operator")
{
    Graph g;
    g.loadGraph({{1, 2}, {-3, 4}});
    -g;
    Graph expected;
    expected.loadGraph({{-1, -2}, {3, -4}});
    CHECK(g == expected);
}
