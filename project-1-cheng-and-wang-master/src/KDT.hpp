//
// KDT.hpp
// CSE 100 Project 1
//
// Last modified by Heitor Schueroff on 01/10/2019
//

#ifndef KDT_HPP
#define KDT_HPP

#include <iostream>
#include <algorithm>
#include <math.h>
#include <limits>
#include <vector>

#include "BST.hpp"

using namespace std;

#define DELTA 0.00005

/**
 * A simple 2D Point struct with (x, y) coordinates.
 */
class Point {
public:
    double x, y;

    /** Default constructor: initializes point at (0, 0) */
    Point() : x(0.0), y(0.0) {}

    /** Constructor that initializes point to given coordinates (x, y) */
    Point(double x, double y) : x(x), y(y) {}

    /** Equals operator */
    bool operator==(const Point &other) const {
        return abs(x - other.x) < DELTA && abs(y - other.y) < DELTA;
    }

    /** Not-equals operator */
    bool operator!=(const Point &other) const {
        return abs(x - other.x) > DELTA || abs(y - other.y) > DELTA;
    }

    /** Less than operator */
    bool operator<(const Point &other) const {
        cerr << "This operator should not be called, you will need "
             << "check the x and y components each time" << endl;
        return false;
    }

    /** Returns the square of the Euclidean distance between points p1 and p2 */
    // TODO
    static double squareDistance(const Point &p1, const Point &p2) {
	return  (pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    }
};

/** 
 * Overload operator<< to print a Point object to an ostream. 
 */
std::ostream &operator<<(std::ostream &out, const Point &data) {
    out << "(" << data.x << ", " << data.y << ")";
    return out;
}

bool xLessThan(const Point &p1, const Point &p2) { 
    return p1.x < p2.x; 
}

bool yLessThan(const Point &p1, const Point &p2) { 
    return p1.y < p2.y; 
}

/**
 * A 2D Tree with operations to find nearest points in 2D space.
 */
class KDT : public BST<Point> {
public:
    /** 
     * Given a vector of Point references, insert a copy into the KDT.
     *
     * Note. Because of the nature of the KDTree, a simple < operator
     *       will not be sufficient. You will need to check the x and y
     *       coordinates individually.
     * Note. Since KDT inherits from BST, you still have access to the
     *       root, isize, and iheight instance variables and should modify
     *       them accordingly.
     * Note. We have also provided a private helper method for the build
     *       function called buildSubset defined below.
     *
     * Parameters:
     *     points - a vector of points to add into a new KDT
     *
     * Returns:
     *     the number of elements in the built KDT
     */
    // TODO
    virtual unsigned int build(vector<Point> points) {
	isize = points.size();
	root = buildSubset( points, 0, points.size(), 0, 1);
	return points.size();
    }

    /** 
     * Find the nearest neighbor to a given point.
     *
     * Note. THIS IS DIFFERENT THAN HOW THE PREVIOUS FIND FUNCTION WORKS
     * Note. Since KDT inherits from BST, you still have access to the
     *       root, isize, and iheight member variables.
     * Note. The same dimension ordering you used to build the tree must be used
     *       to search through it.
     * Note. We have added a private helper method for your convenience called
     *       findNNHelper defined below.
     *
     * Paremeters:
     *     p - the query point for which to find its nearest neighbor
     *
     * Returns:
     *     an iterator pointing at the nearest neighbor, or pointing at nullptr
     *     if tree is empty
     */
    // TODO

    virtual iterator findNearestNeighbor(const Point &p) const {
	if ( root == nullptr ){
		return BST<Point>::iterator(0);
	}
	BSTNode<Point> * closestNode = nullptr;
	double max = numeric_limits<double>::max();
	findNNHelper( root, p,  &max, &closestNode, 0);
	return BST<Point>::iterator(closestNode);
	
    }

    /** 
     * For the kd-tree, the find method should not be used. Use the function
     * findNearestNeighbor instead.
     */
    virtual iterator find(const Point &p) const override {
        cerr << "The KD Tree find method should not be called" << endl;
        cerr << "Use findNearestNeighbor instead" << endl;
        return 0;
    }

    /** 
     * For the kd-tree, the insert method should not be used. The tree is
     * built all at once. There is no need to add individual points.
     */
    virtual bool insert(const Point &p) override {
        cerr << "The KD Tree insert method should not be called" << endl;
        return false;
    }

private:
    /* 
     * Recursively add a subset of the array to the KD tree.
     *
     * Parameters:
     *     items - the list of points that are used to build the kd tree
     *     start - the starting index for this subsection of the tree
     *     end - the non-inclusive ending index for this subtree
     *     dimension - 0 if sorting along the x-axis, and 1 if sorting
     *                 along the y-axis
     * PostConditions: 
     *     the parent node should have its left and right children
     *     set if there are any available points and recursive
     *     calls should be made for the left and right subtree
     *     (again, if there are any remaining points).
     *
     * NOTE: 
     *     We gave you two methods: xLessThan and yLessThan. You may
     *     find them useful for the sort function from #include <algorithm>.
     */
    // TODO
    BSTNode<Point> *buildSubset(vector<Point>& points, 
                                unsigned int start,
                                unsigned int end, 
                                unsigned int dimension,
                                unsigned int height) {
	if ( start == end ){
		return 0;
	}
	iheight = height;
	
	if ( dimension == 0 ){
		std::sort( points.begin()+start, points.begin()+end, xLessThan);
	}
	else if ( dimension == 1 ){
		std::sort( points.begin()+start, points.begin()+end, yLessThan);
	}
	int index = (start+end-1)/2;
	BSTNode<Point> * node = new BSTNode<Point>(points[index]);
	if ( dimension == 0 ){
		node->left = buildSubset( points, start, index, 1, height+1 );
		if( node->left != nullptr ){
			node->left->parent = node;
		}
	}
	else{
		node->left = buildSubset( points, start, index, 0, height+1 );
                if( node->left != nullptr){
			node->left->parent = node;
		}
	}
	if ( dimension == 0 ){
		node->right = buildSubset( points, index+1, end, 1, height+1 );
		if( node->right != nullptr ){
			node->right->parent = node;
		}
	}
	else{
		node->right = buildSubset( points, index+1, end, 0, height+1 );
                if( node->right != nullptr ){
			node->right->parent = node;
		}
	}
	return node;
    }

    /* 
     * Find the node in the subtree that is closest to the given point p
     *  
     * Parameters: 
     *     node - the root of the subtree being searched
     *     queryPoint - the point whose nearest neighbor should be found
     *     smallestSquareDistance - the smallest distance value found in
     *                              the tree so far which can be updated
     *     closestPoint - the node corresponding to the current closest
     *                    node in the tree which can be udpated
     *     dimension - flags whether the node parameter splits remaining
     *                 nodes in its subtree by the x or y dimension
     *                 (has the value of either 0 or 1)
     *
     * PostCondition:
     *     closestPoint points to the nearest neighbor
     */
    // TODO
    void findNNHelper(BSTNode<Point> *node, 
                      const Point &queryPoint,
                      double *smallestSquareDistance,
                      BSTNode<Point> **closestPoint,
                      unsigned int dimension) const {
	
	if ( node == nullptr ){
		return;
	}
	double dis = (Point::squareDistance( node->data, queryPoint ));
        if (dis < *smallestSquareDistance ){
                *smallestSquareDistance = dis;
                *closestPoint = node; //why closestPoint is a node pointer pointer
        }

	if (dimension == 0 ){
		if ( xLessThan( node->data , queryPoint ) == true ){
			findNNHelper( node->right, queryPoint, smallestSquareDistance, closestPoint, 1);
		}
		else{
			findNNHelper( node->left, queryPoint, smallestSquareDistance, closestPoint, 1);
		}
	}
	else{
                if ( yLessThan( node->data , queryPoint ) == true ){
                        findNNHelper( node->right, queryPoint, smallestSquareDistance, closestPoint, 0);
                }
                else{
                        findNNHelper( node->left, queryPoint, smallestSquareDistance, closestPoint, 0);
                }

	}
	if (dimension == 0){
		dis = pow(node->data.x - queryPoint.x,2);
	}
	else{
		dis = pow(node->data.y - queryPoint.y,2);
	}
	if( dis < *smallestSquareDistance ){
		if( dimension == 0 && (xLessThan( node->data , queryPoint ) == false) ){
			 findNNHelper( node->right, queryPoint, smallestSquareDistance, closestPoint, 1);
		}
		if( dimension == 0 && (xLessThan( node->data , queryPoint ) == true) ){
                         findNNHelper( node->left, queryPoint, smallestSquareDistance, closestPoint, 1);
                }
                if( dimension == 1 && (yLessThan( node->data , queryPoint ) == true)) {
                         findNNHelper( node->left, queryPoint, smallestSquareDistance, closestPoint, 0);
                }
		if( dimension == 1 && (yLessThan( node->data , queryPoint ) == false)) {
                         findNNHelper( node->right, queryPoint, smallestSquareDistance, closestPoint, 0);
                }
	}
	else{
		return;
	}
    }
};

#endif  // KDT_HPP
