#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// headers from PA's main.cpp
#include "chain.h"
#include "block.h"
#include "cs221util/PNG.h"
using namespace cs221util;
using namespace std;


// test moveBack function with no boundary cases
TEST_CASE("chain::basic moveBack forward","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(3,5,4);
    PNG result = c.render(12);

    PNG expected; 
    expected.readFromFile("images/given-moveBack.png");

    REQUIRE(result==expected);
}

// test moveBack function rendered in reverse with no boundary cases
TEST_CASE("chain::basic moveBack reverse","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(3,5,4);
    PNG result = c.renderBack(12);

    PNG expected; 
    expected.readFromFile("images/given-moveBackReverse.png");

    REQUIRE(result==expected);
}

// test reverseSub function with no boundaries
TEST_CASE("chain::basic reverseSub","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,16);
    c.reverseSub(2,15);
    PNG result = c.render(16);

    PNG expected; 
    expected.readFromFile("images/given-reverseEasy.png");

    REQUIRE(result==expected);
}

// test reverseSub function with no boundaries in reverse
TEST_CASE("chain::basic reverseSub reverse","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,16);
    c.reverseSub(2,15);
    PNG result = c.renderBack(16);

    PNG expected; 
    expected.readFromFile("images/given-reverseEasyReverse.png");

    REQUIRE(result==expected);
}

// test weave function with no boundaries and same size Chains
// bad test... assumes block test passed.
TEST_CASE("chain::basic weave","[weight=1][part=chain]"){

	PNG pngin1;
    pngin1.readFromFile("images/rosegarden.png");
    PNG pngin2;
    pngin2.readFromFile("images/rosegarden.png");
    
    Block b;
    b.build(pngin1,20,150);
    b.greyscale();
    b.render(pngin2,20);

    Chain c(pngin1,36);
    Chain d(pngin2,36);
    c.weave(d);

    PNG result = c.render(64);

    PNG expected; 
    expected.readFromFile("images/given-weaveSameSize.png");

    REQUIRE(result==expected);
}

// test weave function with no boundaries and same size Chains in reverse
// bad test... assumes block test passed.
TEST_CASE("chain::basic weave reverse","[weight=1][part=chain]"){

	PNG pngin1;
    pngin1.readFromFile("images/rosegarden.png");
    PNG pngin2;
    pngin2.readFromFile("images/rosegarden.png");
    
    Block b;
    b.build(pngin1,20,150);
    b.greyscale();
    b.render(pngin2,20);

    Chain c(pngin1,36);
    Chain d(pngin2,36);
    c.weave(d);

    PNG result = c.renderBack(64);

    PNG expected; 
    expected.readFromFile("images/given-weaveRenderBack.png");

    REQUIRE(result==expected);
}

// chain copy constructor
TEST_CASE("chain::basic copy constructor","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,36);
    Chain d(c);

    PNG result = d.render(36);

    REQUIRE(result==pngin);
}

// chain copy constructor reverse
TEST_CASE("chain::basic copy constructor reverse","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,36);
    Chain d(c);

    PNG result = d.renderBack(36);

    REQUIRE(result==pngin);
}

// test moveBack function 3, 10, 0
TEST_CASE("chain::grading moveBack 3, 10, 0, forward","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(3,10,0);
    PNG result = c.render(12);

    REQUIRE(result==pngin);
}

// test moveBack function 3, 10, 0
TEST_CASE("chain::grading moveBack 3, 10, 0, reverse","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(3,10,0);
    PNG result = c.renderBack(12);

    REQUIRE(result==pngin);
}

// test moveBack function 1, 10, 2
TEST_CASE("chain::grading moveBack 1, 10, 3, forward","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(1,10,2);
    PNG result = c.render(12);

    PNG expected; 
    expected.readFromFile("images/given-move1102f.png");
    //expected.readFromFile("images/given-moveBack.png");

    REQUIRE(result==expected);
}

// test moveBack function 1, 10, 2
TEST_CASE("chain::grading moveBack 1, 10, 2, reverse","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(1,10,2);
    PNG result = c.renderBack(12);

    PNG expected; 
    expected.readFromFile("images/given-move1102b.png");

    REQUIRE(result==expected);
}

// test moveBack function 1, 12, 0
TEST_CASE("chain::grading moveBack 1, 12, 0, forward","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(1,12,0);
    PNG result = c.render(12);

    REQUIRE(result==pngin);
}

// test moveBack function 1, 10, 2
TEST_CASE("chain::grading moveBack 1, 12, 0, reverse","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(1,12,0);
    PNG result = c.renderBack(12);

    REQUIRE(result==pngin);
}

// test reverseSub function with full image
TEST_CASE("chain::grading reverseSub full image forward","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,16);
    c.reverseSub(1,16);
    PNG result = c.render(16);

    PNG expected; 
    expected.readFromFile("images/given-reversefull.png");
    //result.writeToFile("images/given-reversefullf.png");

    REQUIRE(result==expected);
}

// test reverseSub function with full image in reverse
TEST_CASE("chain::grading reverseSub full image reverse","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,16);
    c.reverseSub(1,16);
    PNG result = c.renderBack(16);

    PNG expected; 
    expected.readFromFile("images/given-reversefull.png");
    //result.writeToFile("images/given-reversefullb.png");

    REQUIRE(result==expected);
}

// test weave function with shorter first forward
TEST_CASE("chain::grading weave shorter first forward","[weight=1][part=chain]"){

	PNG pngin1;
    pngin1.readFromFile("images/rosegarden.png");
    
    Chain c(pngin1,36);

    PNG pngin2 = c.render(18);
    Chain d(pngin2,18);
    
    c.weave(d);

    PNG result = c.render(54);

    PNG expected; 
    //expected.readFromFile("images/given-weaveSameSize.png");
    expected.readFromFile("images/given-weaveShorterFirstf.png");

    REQUIRE(result==expected);
}

// test weave function with shorter first back
TEST_CASE("chain::grading weave shorter first reverse","[weight=1][part=chain]"){

	PNG pngin1;
    pngin1.readFromFile("images/rosegarden.png");

    Chain c(pngin1,36);

    PNG pngin2 = c.render(18);
    Chain d(pngin2,18);

    c.weave(d);

    PNG result = c.renderBack(54);

    PNG expected; 
    //expected.readFromFile("images/given-weaveRenderBack.png");
    expected.readFromFile("images/given-weaveShorterFirstb.png");

    REQUIRE(result==expected);
}

// test weave function with longer first forward
TEST_CASE("chain::grading weave longer first forward","[weight=1][part=chain]"){

	PNG pngin1;
    pngin1.readFromFile("images/rosegarden.png");
    
    Chain c(pngin1,36);

    PNG pngin2 = c.render(18);
    Chain d(pngin2,18);
    
    d.weave(c);

    PNG result = d.render(54);

    PNG expected; 
    //expected.readFromFile("images/given-weaveSameSize.png");
    expected.readFromFile("images/given-weaveLongerFirstf.png");

    REQUIRE(result==expected);
}

// test weave function with longer first back
TEST_CASE("chain::grading weave longer first reverse","[weight=1][part=chain]"){

	PNG pngin1;
    pngin1.readFromFile("images/rosegarden.png");

    Chain c(pngin1,36);

    PNG pngin2 = c.render(18);
    Chain d(pngin2,18);

    d.weave(c);

    PNG result = d.renderBack(54);

    PNG expected; 
    //expected.readFromFile("images/given-weaveRenderBack.png");
    expected.readFromFile("images/given-weaveLongerFirstb.png");

    REQUIRE(result==expected);
}

// test roll part forward
TEST_CASE("chain::grading roll part forward","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,18);
    c.roll(10);
    PNG result = c.render(18);

    PNG expected; 
    expected.readFromFile("images/given-rollpart.png");
    //result.writeToFile("images/given-rollpart.png");

    REQUIRE(result==expected);
}

// test roll part reverse
TEST_CASE("chain::grading roll part reverse","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,18);
    c.roll(10);
    PNG result = c.renderBack(18);

    PNG expected; 
    expected.readFromFile("images/given-rollpart.png");
    //result.writeToFile("images/given-rollpartb.png");

    REQUIRE(result==expected);
}

// test roll all forward
TEST_CASE("chain::grading roll all forward","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,18);
    c.roll(18);
    PNG result = c.render(18);

    REQUIRE(result==pngin);
}

// test roll part reverse
TEST_CASE("chain::grading roll all reverse","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,18);
    c.roll(18);
    PNG result = c.renderBack(18);

    REQUIRE(result==pngin);
}

