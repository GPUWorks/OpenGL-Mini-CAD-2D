#include "IndexBufferTree.h"





ds::IndexBufferTree::IndexBufferTree()
{

}

ds::IndexBufferTree::IndexBufferTree(GLuint max_indices_no, GLuint min_indices_no)
{
	this->max_indices_no = max_indices_no;
	this->min_indices_no = min_indices_no;

	this->height = (GLuint)(std::log2(max_indices_no) - std::log2(min_indices_no));

	for (GLuint i = 0, j = 1; i <= this->height; i++, j *= 2)
		this->no_of_segments += j;

	this->tree_segments = new ds::ibt_seg[this->no_of_segments];

	this->build();
}


void ds::IndexBufferTree::build()
{
	GLuint nodes_idx = 0;

	this->tree = tree_segments + nodes_idx;
	this->tree->id = nodes_idx;
	nodes_idx++;

	buildSegment(nullptr, tree, 0, this->max_indices_no, &nodes_idx, 0);
}

void ds::IndexBufferTree::buildSegment(ds::ibt_seg *parent, ds::ibt_seg *node, GLuint offset, GLuint indices_no, GLuint *nodes_idx, GLuint height)
{
	node->parent = parent;
	node->offset = offset;
	node->indices_no = indices_no;

	if (this->height == height) {
		for (GLuint i = 0; i < 2; i++) {
			node->children[i] = nullptr;
		}

		return;
	}

	for (GLuint i = 0; i < 2; i++)
	{
		node->children[i] = tree_segments + *nodes_idx;
		node->children[i]->id = *nodes_idx;
		*nodes_idx += 1;

		buildSegment(node, node->children[i], offset + i * indices_no / 2, indices_no / 2, nodes_idx, height + 1);
	}
}


ds::ibt_seg* ds::IndexBufferTree::search(GLuint indices_no)
{
	return this->searchSegment(this->tree, indices_no, 0);
}

ds::ibt_seg* ds::IndexBufferTree::searchSegment(ds::ibt_seg *node, GLuint indices_no, GLuint height)
{
	if (node->available_children_paths == 0) {
		return nullptr;
	}

	if (node->indices_no / 2 < indices_no || this->height == height) {
		if ((node->available_children_paths >> 4) & 1)
		{
			node->available_children_paths = 0;
			return node;
		}
		else
			return nullptr;
	}


	for (GLuint i = 0; i < 2; i++)
	{
		ds::ibt_seg *res = searchSegment(node->children[i], indices_no, height + 1);

		if (node->children[i]->available_children_paths == 0)
			node->available_children_paths &= ~(1 << i);

		if (res) {
			node->available_children_paths &= ~(1 << 4);
			return res;
		}
	}

	return nullptr;
}


void ds::IndexBufferTree::free(GLuint node_id)
{
	ds::ibt_seg *node = &(this->tree_segments[node_id]);
	node->available_children_paths = 0x13;

	freeSegment(node);
}

void ds::IndexBufferTree::freeSegment(ds::ibt_seg *node)
{
	ds::ibt_seg* parent = node->parent;

	if (node->parent == nullptr)
		return;

	for (GLuint i = 0; i < 2; i++)
	{
		if (parent->children[i] == node)
		{
			parent->available_children_paths |= 1 << i;
			break;
		}
	}

	if (parent->available_children_paths == 3)
		parent->available_children_paths |= 1 << 4;

	freeSegment(parent);
}

void ds::IndexBufferTree::clean()
{
	delete[] this->tree_segments;

	this->tree_segments = new ds::ibt_seg[this->no_of_segments];

	this->build();
}