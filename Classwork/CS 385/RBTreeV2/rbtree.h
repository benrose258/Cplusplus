/*******************************************************************************
 * Name        : rbtree.h
 * Author      : Ben Rose
 * Version     : 2.0
 * Date        : April 14, 2019
 * Description : Implementation of red-black tree.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#ifndef RBTREE_H_
#define RBTREE_H_

#include "node.h"
#include "tree.h"
#include "treeprinter.h"
#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>

// Forward declaration
template <typename K, typename V>
class RedBlackTree;

/**
 * tree_exception class
 * Demonstrates how you can write your own custom exceptions in C++.
 */
class tree_exception: public std::exception {
public:
    tree_exception(const std::string &message) : message_{message} { }

    ~tree_exception() throw() { }

    virtual const char* what() const throw() {
        return message_.c_str();
    }

private:
    std::string message_;
};

template <typename K, typename V>
class RedBlackTreeIterator {
public:
    /**
     * Constructor
     */
    RedBlackTreeIterator() : node_ptr{NULL}, tree{NULL} { }

    /**
     * Equality operator. Compares node pointers.
     */
    bool operator==(const RedBlackTreeIterator &rhs) const {
        return node_ptr == rhs.node_ptr;
    }

    /**
     * Inequality operator. Compares node pointers.
     */
    bool operator!=(const RedBlackTreeIterator &rhs) const {
        return node_ptr != rhs.node_ptr;
    }

    /**
     * Dereference operator. Returns a reference to the Node pointed to
     * by node_ptr.
     */
    Node<K, V>& operator*() const {
        return *node_ptr;
    }

    /**
     * Dereference operator. Returns a pointer to the Node pointed to
     * by node_ptr.
     */
    Node<K, V>* operator->() const {
        return node_ptr;
    }

    /**
     * Preincrement operator. Moves forward to next larger value.
     */
    RedBlackTreeIterator& operator++() {
        Node<K, V> *p;

        if (node_ptr == NULL) {
            // ++ from end(). Get the root of the tree.
            node_ptr = tree->root_;

            // Error, ++ requested for an empty tree.
            if (node_ptr == NULL)
                throw tree_exception(
                        "RedBlackTreeIterator operator++(): tree empty");

            // Move to the smallest value in the tree, which is the first node
            // in an inorder traversal.
            while (node_ptr->left != NULL) {
                node_ptr = node_ptr->left;
            }
        } else {
            if (node_ptr->right != NULL) {
                // Successor is the leftmost node of right subtree.
                node_ptr = node_ptr->right;

                while (node_ptr->left != NULL) {
                    node_ptr = node_ptr->left;
                }
            } else {
                // Have already processed the left subtree, and
                // there is no right subtree. Move up the tree,
                // looking for a parent for which node_ptr is a left child,
                // stopping if the parent becomes NULL (or in this case,
                // root_parent_. A non-NULL parent is the successor. If parent
                // is NULL, the original node was the last node inorder, and
                // its successor is the end of the list.
                p = node_ptr->parent;
                while (p != NULL && node_ptr == p->right) {
                    node_ptr = p;
                    p = p->parent;
                }

                // If we were previously at the rightmost node in
                // the tree, node_ptr = NULL, and the iterator specifies
                // the end of the list.
                node_ptr = p;
            }
        }

        return *this;
    }

    /**
     * Postincrement operator. Moves forward to next larger value.
     */
    RedBlackTreeIterator operator++(int) {
        RedBlackTreeIterator tmp(*this);
        operator++(); // prefix-increment this instance
        return tmp;   // return value before increment
    }

private:
    // node_ptr is the current location in the tree. We can move
    // freely about the tree using left, right, and parent.
    // tree is the address of the RedBlackTree object associated
    // with this iterator. It is used only to access the
    // root pointer, which is needed for ++ and --
    // when the iterator value is end().
    Node<K, V> *node_ptr;
    RedBlackTree<K, V> *tree;
    friend class RedBlackTree<K, V>;

    /**
     * Constructor used to construct an iterator return value from a tree
     * pointer.
     */
    RedBlackTreeIterator(Node<K, V> *p, RedBlackTree<K, V> *t) :
        node_ptr(p), tree(t) { }
};

template<typename K, typename V>
class RedBlackTree : public Tree {
public:
    typedef RedBlackTreeIterator<K, V> iterator;

    /**
     * Constructor to create an empty red-black tree.
     */
    RedBlackTree() : root_{NULL}, size_{0} { }

    /**
     * Constructor to create a red-black tree with the elements from the
     * vector.
     */
    RedBlackTree(std::vector< std::pair<K, V> > &elements) :
                                            root_(NULL), size_(0) {
        insert_elements(elements);
    }

    /**
     * Destructor.
     */
    ~RedBlackTree() {
        delete_tree(root_);
    }

    /**
     * Inserts elements from the vector into the red-black tree.
     * Duplicate elements are not inserted.
     */
    void insert_elements(std::vector< std::pair<K, V> > &elements) {
        for (size_t i = 0, len = elements.size(); i < len; ++i) {
            try {
                insert(elements[i].first, elements[i].second);
            } catch (const tree_exception &te) {
                std::cerr << "Warning: " << te.what() << std::endl;
            }
        }
    }

    /**
     * Inserts a key-value pair into the red black tree.
     * const iterator &it indicates where to start the search for the place to
     * insert the node. If it == end(), the search starts at the root.
     */
    void insert(const iterator &it, const std::pair<K, V> &key_value) {
        const K& z_key = key_value.first; // The key in the key-value pair
		const V& z_value = key_value.second; // The value in the key-value pair
        Node<K, V> *x;
		Node<K, V> *y;
        if (it != end()) { // If the iterator is not at the end
            x = it.node_ptr;
            y = x->parent;
        } else { // We are now at the end
            x = root_; // Since we are at the end, the search starts at the root. --- By the way, this was written early on
            y = NULL; // Value of the root equals null. This is why the last thing printed is "Root is null." --- so was this, so it may be slightly inaccurate.
        }
        Node<K, V> *z = new Node<K, V>(z_key, z_value); // New node with z's key and z's value

        while (x != NULL) {
        	y = x;
        	if (z->key() == x->key()) {
        		std::ostringstream z_key_string; // Create a string version of z's key
        		z_key_string << z_key; // Add the key to the string
        		delete z; // Delete the Z-Node, which would otherwise leak
        		throw tree_exception("Attempt to insert duplicate key '" + z_key_string.str() + "'."); // Throw tree exception and print the duplicated key
        	}
        	if (z->key() < x->key()) { // Change to z->key() when node z is working.
        		x = x->left;
        	} else {
        		x = x->right;
        	}
        }
        if (y == NULL) { // if this is an empty tree?
        	root_ = z;
        } else if (z->key() < y->key()) { // If the key we are inserting is less than y
        	y->left = z; // Then the node becomes y's left child.
        	y->left->parent = y;
        } else { // The key we are inserting is greater than y
        	y->right = z; // Then the node becomes y's right child.
        	y->right->parent = y;
        }
        // Regardless of whether z becomes the root, left child, or right child of y, this line is applicable.
        // If z is the root, its parent should be null to begin with, which is y's value.
        // If z is a left or right child of y, y should be set as its parent.
        z->left = NULL; // Z's left is NULL
        z->right = NULL; // Z's right is NULL
        z->color = RED; // And set Z's color to RED
        size_++;
        insert_fixup(z); // Repair the Red-Black Tree Properties
    }

    /**
     * Inserts a key-value pair into the red-black tree.
     */
    void insert(const K &key, const V &value) {
        iterator e = end(); // end() function: Returns an iterator just past the end of the tree data, so essentially the tree in its entirety.
        insert(e, std::pair<K, V>(key, value)); // Calls insert with the tree and the node we want to insert.
    }

    /**
     * Returns an ASCII representation of the red-black tree.
     */
    std::string to_ascii_drawing() {
        BinaryTreePrinter<K, V> printer(root_);
        return printer.to_string();
    }

    /**
     * Returns the height of the red-black tree.
     */
    int height() const {
        return height(root_) - 1;
    }

    /**
     * Returns the number of nodes in the red-black tree.
     */
    size_t size() const {
        return size_;
    }

    /**
     * Returns the leaf count of the red-black tree.
     */
    size_t leaf_count() const {
        return leaf_count(root_);
    }

    /**
     * Returns the internal node count of the red-black tree.
     */
    size_t internal_node_count() const {
        return internal_node_count(root_);
    }

    /**
     * Returns the diameter of the red-black tree.
     */
    size_t diameter() const {
        return diameter(root_);
    }

    /**
     * Returns the max width of the red-black tree, i.e. the largest number of
     * nodes on any level.
     */
    size_t max_width() const {
        size_t max_width = 0;
        for (int i = 0, h = height(root_) + 1; i < h; ++i) {
            size_t w = width(root_, i);
            if (w > max_width) {
                max_width = w;
            }
        }
        return max_width;
    }

    /**
     * Returns the successful search cost, i.e. the average number of nodes
     * visited to find a key that is present.
     */
    double successful_search_cost() const {
        return size_ == 0 ? 0 : ((double)sum_levels() / size_) - 1;
    }

    /**
     * Returns the unsuccessful search cost, i.e. the average number of nodes
     * visited to find a key that is not present.
     */
    double unsuccessful_search_cost() const {
        return (double)sum_null_levels() / null_count();
    }

    /**
     * Searches for item. If found, returns an iterator pointing
     * at it in the tree; otherwise, returns end().
     */
    iterator find(const K &key) {
        Node<K, V> *x = root_;
        while (x != NULL) {
            const K& current_key = x->key();
            if (key == current_key) {
                break; // Found!
            } else if (key < current_key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        return iterator(x, this);
    }

    /**
     * Returns an iterator pointing to the first item in order.
     */
    iterator begin() {
        Node<K, V> *curr = root_;

        // if the tree is not empty, the first node
        // in order is the farthest node left from root
        if (curr != NULL) {
            while (curr->left != NULL) {
                curr = curr->left;
            }
        }

        // build return value using private constructor
        return iterator(curr, this);
    }

    /**
     * Returns an iterator pointing just past the end of the tree data.
     */
    iterator end() {
        return iterator(NULL, this);
    }

private:
    Node<K, V> *root_;
    size_t size_;
    friend class RedBlackTreeIterator<K, V>;

    /**
     * Deletes all nodes from the red-black tree.
     */
    void delete_tree(Node<K, V> *n) {
        if (n != NULL) {
        	delete_tree(n->left);
        	delete_tree(n->right);
        	delete n;
        }
    }

    /**
     * Fixup method
     */
    void insert_fixup(Node<K, V> *z) {
    	if (z->parent != NULL) { // If Z isn't initially the root. If it is, then just recolor it, which is done in the last line.
        	while (z->parent != NULL && z->parent->color == RED) { // While Z isn't the root and Z's Parent's Color is Red
        		Node<K, V> *y; // Create temporary helper node y. This is done before the if statement to prevent duplicate code.
        		if (z->parent == z->parent->parent->left) { // If Z's parent is a left child
        			y = z->parent->parent->right; // y equals z's uncle
        			if (y != NULL && y->color == RED) { // If y isn't NULL and y's color is RED
        				z->parent->color = BLACK; // Case 1
        				y->color = BLACK; // Case 1
        				z->parent->parent->color = RED; // Case 1
        				z = z->parent->parent; // Case 1

        			} else { // Else, y is null or y is a black node
        				if (z == z->parent->right) { // If Z is a right child
        					z = z->parent; // Z = Z's parent
        					left_rotate(z); // Perform a left rotation on Z
        				}
        				z->parent->color = BLACK; // Z's parent's color is BLACK
        				z->parent->parent->color = RED; // Z's grandparent's color is RED
        				right_rotate(z->parent->parent); // Perform a right rotation on Z's grandparent
        			}

        		} else { // Else, Z's parent is a right child
					y = z->parent->parent->left; // y equals z's uncle
        			if (y != NULL && y->color == RED) { // If y isn't NULL and y's color is RED
						z->parent->color = BLACK; // Case 1
						y->color = BLACK; // Case 1
						z->parent->parent->color = RED; // Case 1
						z = z->parent->parent; // Case 1
					} else { // Else, y is NULL or y's color is BLACK
						if (z == z->parent->left) { // If Z is a left child
							z = z->parent; // Z equals Z's parent
							right_rotate(z); // Perform a right rotation on Z
						}
						z->parent->color = BLACK; // Z's parent's color equals BLACK
						z->parent->parent->color = RED; // Z's grandparent's color equals RED
						left_rotate(z->parent->parent); // Perform a left rotation on Z's grandparent
					}
        		}
        	}
    	}
        root_->color = BLACK; // Recolor the root to be BLACK
    }

    /**
     * Left-rotate method
     */
    void left_rotate(Node<K, V> *x) {
    	Node<K, V> *y; // Create node Y for rotation help
    	y = x->right; // Set y
    	if (y != NULL) { // check to make sure x's right child isn't null
			x->right = y->left; // Turn y's left subtree into x's right subtree
			if (y->left != NULL) { // If y's left child isn't null, i.e. if y has a left child
				y->left->parent = x; // Set y's left child's parent node to be x
			}
			y->parent = x->parent; // Link x's parent to y
			if (x->parent == NULL) { // If x doesn't have a parent, i.e. if x is the root
				root_ = y; // Make y the new root.
			} else if (x == x->parent->left) { // If x is x's parent's left child (if x is a left child)
				x->parent->left = y; // Set x's parent's left child to be y
			} else { // then x is x's parent's right child (x is a right child)
				x->parent->right = y; // Set x's parent's right child to be y
			}
			y->left = x; // Put x on y's left
			x->parent = y; // Set x's parent to be y
    	}
    }

    /**
     * Right-rotate method
     */
    void right_rotate(Node<K, V> *x) {
    	Node<K, V> *y; // Create node Y for rotation help
		y = x->left; // Set y
		if (y != NULL) { // check to make sure x's left child isn't null
			x->left = y->right; // Turn y's right subtree into x's left subtree
			if (y->right != NULL) { // If y's right child isn't null, i.e. if y has a right child
				y->right->parent = x; // Set y's right child's parent node to be x
			}
			y->parent = x->parent; // Link x's parent to y
			if (x->parent == NULL) { // If x doesn't have a parent, i.e. if x is the root
				root_ = y; // Make y the new root.
			} else if (x == x->parent->left) { // If x is x's parent's left child (if x is a left child)
				x->parent->left = y; // Set x's parent's left child to be y
			} else { // then x is x's parent's right child (x is a right child)
				x->parent->right = y; // Set x's parent's right child to be y
			}
			y->right = x; // Put x on y's right
			x->parent = y; // Set x's parent to be y
		}
    }

    /**
     * Returns the height of the red-black tree starting at node.
     * A null node starts at height -1.
     */
    int height(Node<K, V> *node) const {
    	// (The result of this function) - 1 == height, so result is decremented in public height function.
    	return node == NULL ? 0 : 1 + std::max(height(node->left), height(node->right));
    }

    /**
     * Returns the count of leaves in the red-black tree starting at node.
     * For this method, a leaf is a non-null node that has no children.
     */
    size_t leaf_count(Node<K, V> *node) const {
    	if (node == NULL) {
    		return 0;
    	}
    	if (node->left == NULL && node->right == NULL) {
    		return 1;
    	}
    	return leaf_count(node->left) + leaf_count(node->right);
    }

    /**
     * Returns the count of internal nodes in the red-black tree starting at
     * node.
     * An internal node has at least one child.
     */
    size_t internal_node_count(Node<K, V> *node) const {
    	return (!(node == NULL) && (node->left != NULL || node->right != NULL)) ? // Is the node not null and have at least one child?
    			1 + internal_node_count(node->left) + internal_node_count(node->right) : 0; // If so, node is an internal node, and look at its children. Else, don't.
    }

    /**
     * Returns the diameter of the red-black tree rooted at node.
     * Diameter is defined as the number of nodes on the longest path between
     * two (non-null) leaves in the tree. The path does not necessarily have to
     * pass through the root.
     */
    int diameter(Node<K, V> *node) const {
    	if (node == NULL) { // If we are looking at a null node, the diameter is zero.
    		return 0;
    	}
    	int max_diameter = std::max(diameter(node->left), diameter(node->right));
    	int left_right_heights = height(node->left) + height(node->right);
    	return std::max(max_diameter, left_right_heights);
//    	return 0; // Just passing makefile, delete later
    }

    /**
     * Returns the width of the red-black tree at the designated level.
     * Width is defined as the number of nodes residing at a level.
     */
    size_t width(Node<K, V> *node, size_t level) const {
    	if (node == NULL) { // If the node is null (base case)
    		return 0; // Return 0
    	}
    	// If level == 0, return 1, else decrement level and call width on the node's children
    	return level == 0 ? 1 : width(node->left, level - 1) + width(node->right, level - 1); // Just passing makefile, delete later
    }

    size_t null_count() const {
        return null_count(root_);
    }

    /**
     * Returns the count of null nodes in the red-black tree starting at node.
     */
    size_t null_count(Node<K, V> *node) const {
//    	return 0; // Just passing makefile, delete later
    	return node == NULL ? 1 : null_count(node->left) + null_count(node->right);
    }

    size_t sum_levels() const {
        return sum_levels(root_, 0);
    }

    /**
     * Returns the sum of the levels of each non-null node in the red-black
     * tree starting at node.
     * For example, the tree
     *   5 <- level 0
     *  / \
     * 2   8 <- level 1
     *      \
     *       10 <- level 2
     * has sum 0 + 2(1) + 2 = 4.
     */
    size_t sum_levels(Node<K, V> *node, size_t level) const {
    	// If node == null return zero,
		// Else return the current level plus the node's left and right child, each on the next level (level = level + 1)
		return node == NULL ? 0 : level + sum_null_levels(node->left, level + 1) + sum_null_levels(node->right, level + 1);
    }

    size_t sum_null_levels() const {
        return sum_null_levels(root_, 0);
    }

    /**
     * Returns the sum of the levels of each null node in the red-black tree
     * starting at node.
     * For example, the tree
     *    5 <- level 0
     *   / \
     *  2   8 <- level 1
     * / \ / \
     * * * * 10 <- level 2
     *       / \
     *       * * <- level 3
     * has sum 3(2) + 2(3) = 12.
     */
    size_t sum_null_levels(Node<K, V> *node, size_t level) const {
      // If node == null return level,
    	// Else return the sum of the node's left and right children, each on the next level (level = level + 1)
    	return node == NULL ? level : sum_null_levels(node->left, level + 1) + sum_null_levels(node->right, level + 1);
    }
};

#endif /* RBTREE_H_ */
